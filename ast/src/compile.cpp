#include <vector>
#include <QFile>
#include <compile.hpp>
#include <state.hpp>


#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
Module* TheModule = nullptr;
legacy::FunctionPassManager* TheFPM;
Value* doublePrintStr = nullptr;
Value* truePrintStr = nullptr;
Value* falsePrintStr = nullptr;
Value* doubleInputStr = nullptr;

// ------ QVariantMap(Value*, TypeEnum);

enum class MyType{
    DOUBLE_T,
    BOOL_T
};

QString Compile::getValue() const{
    return value_.typeId() == QVariant(QString("")).typeId()? value_.toString(): "";
}

void Compile::InitializeModuleAndPassManager(){
    if(TheModule != nullptr){
        delete TheModule;
    }
    TheModule = new Module("Module", TheContext);

    TheFPM = new legacy::FunctionPassManager(TheModule);

    TheFPM->add(createInstructionCombiningPass());
    TheFPM->add(createReassociatePass());
    TheFPM->add(createGVNPass());
    TheFPM->add(createCFGSimplificationPass());
    TheFPM->add(createPromoteMemoryToRegisterPass());

    TheFPM->doInitialization();

    std::vector<Type*> arg(0);
    FunctionType* FTMain = FunctionType::get(Type::getInt32Ty(TheContext), arg, false);
    Function* MainFunction = Function::Create(FTMain, Function::ExternalLinkage, "main", TheModule);
    BasicBlock* MainBB = BasicBlock::Create(TheContext, "entry", MainFunction);
    Builder.SetInsertPoint(MainBB);
}

void Compile::compile(const QString& path){
    if(TheModule != nullptr){
        Builder.CreateRet(ConstantInt::get(TheContext, APInt(32, 0)));
        Function* mainFunction = Builder.GetInsertBlock()->getParent();
        TheFPM->run(*mainFunction);

        auto TargetTriple = sys::getDefaultTargetTriple();

        InitializeAllTargetInfos();
        InitializeAllTargets();
        InitializeAllTargetMCs();
        InitializeAllAsmParsers();
        InitializeAllAsmPrinters();

        std::string Error;
        auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

        if(!Target){
            qDebug() << QString::fromStdString(Error) << "/n";
            return;
        }

        auto CPU = "generic";
        auto Features = "";

        TargetOptions ops;
        auto RM = Optional<Reloc::Model>();
        auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, ops, RM);

        TheModule->setDataLayout(TargetMachine->createDataLayout());
        TheModule->setTargetTriple(TargetTriple);

        auto FileName = path.toStdString();
        std::error_code EC;
        raw_fd_ostream dest(FileName, EC, sys::fs::OF_None);

        if(EC){
            return;
        }

        legacy::PassManager pass;
        auto FileType = CodeGenFileType::CGFT_ObjectFile;

        if(TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)){
            qDebug() << "Machine can't emit file of this type!\n";
            return;
        }

        pass.run(*TheModule);
        dest.flush();


        delete TheModule;
        TheModule = nullptr;
    }
}

AllocaInst* CreateEntryBlockAlloca(Function *f, QString s, MyType type){
    IRBuilder<> TmpBuilder(&(f->getEntryBlock()), f->getEntryBlock().begin());

    switch (type) {
    case MyType::DOUBLE_T:
        return TmpBuilder.CreateAlloca(Type::getDoubleTy(TheContext), nullptr, s.toStdString().c_str());
    case MyType::BOOL_T:
        return TmpBuilder.CreateAlloca(Type::getInt1Ty(TheContext), nullptr, s.toStdString().c_str());
    }
    return nullptr;
}

void Compile::VisitPlaceholderExprAST(PlaceholderAST& obj) {
    if(obj.isEmpty()){
        value_ = QString("Expression not finished :: Placeholder exists.");
        return;
    }

    value_ = Compile(obj.getExpr()).value_;
}

void Compile::VisitValueExprAST(ValueAST& obj) {
    Value* val = ConstantFP::get(TheContext, APFloat(obj.getValue()));
    QVariantMap map;
    map.insert("value", QVariant::fromValue(val));
    map.insert("type", QVariant::fromValue(MyType::DOUBLE_T));
    value_ = map;
}

void Compile::VisitVariableExprAST(VariableAST& obj) {
    QString name = obj.getName();
    auto prevValue = State::Domains().getValue(name);
    QVariantMap map = prevValue.toMap();
    if(map.isEmpty()){ //if QVariant was not a map, toMap() returns empty map
        value_ = prevValue;
        return;
    }
    auto var = map.value("value").value<AllocaInst*>();
    auto type = map.value("type").value<MyType>();
    Value* value;
    if(type == MyType::DOUBLE_T) {
        value = Builder.CreateLoad(Type::getDoubleTy(TheContext), var, name.toStdString().c_str());
	}
    else if (type == MyType::BOOL_T) {
        value = Builder.CreateLoad(Type::getInt1Ty(TheContext), var, name.toStdString().c_str());
	}

    map.clear();
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(type));
    value_ = map;
}

void Compile::VisitNotExprAST(NotAST& obj) {
    auto prevValue = Compile(obj.getOperand()).value_;
    QVariantMap map = prevValue.toMap();
    if(map.isEmpty()){
        value_ = prevValue;
        return;
    }

    auto v = map.value("value").value<Value*>();
    auto type = map.value("type").value<MyType>();

    if(type != MyType::BOOL_T){
        value_ = QString("Not :: Invalid operand, boolean required.");
        return;
    }

    Value* value = Builder.CreateNot(v, "nottmp");

    map.clear();
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::BOOL_T));

    value_ = map; // Maybe CreateNeg ? (Has additional arguments)
}

void Compile::VisitMulExprAST(MulAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::DOUBLE_T || typeRight != MyType::DOUBLE_T){
        value_ = QString("Mul :: Invalid operand, number required.");
        return;
    }

    Value* value = Builder.CreateFMul(vLeft, vRight, "multmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::DOUBLE_T));

    value_ = map;
}

void Compile::VisitDivExprAST(DivAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::DOUBLE_T || typeRight != MyType::DOUBLE_T){
        value_ = QString("Div :: Invalid operand, number required.");
        return;
    }

    Value* value = Builder.CreateFDiv(vLeft, vRight, "divtmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::DOUBLE_T));

    value_ = map;
}

void Compile::VisitAddExprAST(AddAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::DOUBLE_T || typeRight != MyType::DOUBLE_T){
        value_ = QString("Add :: Invalid operand, number required.");
        return;
    }

    Value* value = Builder.CreateFAdd(vLeft, vRight, "addtmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::DOUBLE_T));

    value_ = map;
}

void Compile::VisitSubExprAST(SubAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::DOUBLE_T || typeRight != MyType::DOUBLE_T){
        value_ = QString("Sub :: Invalid operand, number required.");
        return;
    }

    Value* value = Builder.CreateFSub(vLeft, vRight, "subtmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::DOUBLE_T));

    value_ = map;
}

void Compile::VisitLtExprAST(LtAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::DOUBLE_T || typeRight != MyType::DOUBLE_T){
        value_ = QString("Lt :: Invalid operand, number required.");
        return;
    }

    Value* value = Builder.CreateFCmpOLT(vLeft, vRight, "lttmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::BOOL_T));

    value_ = map;
}

void Compile::VisitLeqExprAST(LeqAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::DOUBLE_T || typeRight != MyType::DOUBLE_T){
        value_ = QString("Leq :: Invalid operand, number required.");
        return;
    }

    Value* value = Builder.CreateFCmpOLE(vLeft, vRight, "leqtmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::BOOL_T));

    value_ = map;
}

void Compile::VisitGtExprAST(GtAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::DOUBLE_T || typeRight != MyType::DOUBLE_T){
        value_ = QString("Gt :: Invalid operand, number required.");
        return;
    }

    Value* value = Builder.CreateFCmpOGT(vLeft, vRight, "gttmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::BOOL_T));

    value_ = map;
}

void Compile::VisitGeqExprAST(GeqAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::DOUBLE_T || typeRight != MyType::DOUBLE_T){
        value_ = QString("Geq :: Invalid operand, number required.");
        return;
    }

    Value* value = Builder.CreateFCmpOGE(vLeft, vRight, "geqtmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::BOOL_T));

    value_ = map;
}

void Compile::VisitEqExprAST(EqAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft == MyType::DOUBLE_T && typeRight == MyType::DOUBLE_T){
        Value* value = Builder.CreateFCmpOEQ(vLeft, vRight, "eqtmp");

        QVariantMap map;
        map.insert("value", QVariant::fromValue(value));
        map.insert("type", QVariant::fromValue(MyType::BOOL_T));

        value_ = map;
        return;
    }

    if(typeLeft == MyType::BOOL_T && typeRight == MyType::BOOL_T){
        Value* value = Builder.CreateICmpEQ(vLeft, vRight, "eqtmp");

        QVariantMap map;
        map.insert("value", QVariant::fromValue(value));
        map.insert("type", QVariant::fromValue(MyType::BOOL_T));

        value_ = map;
        return;
    }

    value_ = QString("Eq :: Invalid operand, number required.");
    return;
}

void Compile::VisitNeqExprAST(NeqAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft == MyType::DOUBLE_T && typeRight == MyType::DOUBLE_T){
        Value* value = Builder.CreateFCmpONE(vLeft, vRight, "netmp");

        QVariantMap map;
        map.insert("value", QVariant::fromValue(value));
        map.insert("type", QVariant::fromValue(MyType::BOOL_T));

        value_ = map;
        return;
    }

    if(typeLeft == MyType::BOOL_T && typeRight == MyType::BOOL_T){
        Value* value = Builder.CreateICmpNE(vLeft, vRight, "netmp");

        QVariantMap map;
        map.insert("value", QVariant::fromValue(value));
        map.insert("type", QVariant::fromValue(MyType::BOOL_T));

        value_ = map;
        return;
    }

    value_ = QString("Eq :: Invalid operand, number required.");
    return;
}

void Compile::VisitAndExprAST(AndAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::BOOL_T || typeRight != MyType::BOOL_T){
        value_ = QString("And :: Invalid operand, boolean required.");
        return;
    }

    Value* value = Builder.CreateAnd(vLeft, vRight, "andtmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::BOOL_T));

    value_ = map;
}

void Compile::VisitOrExprAST(OrAST& obj) {
    auto left = Compile(obj.getLeft()).value_;
    QVariantMap mapLeft = left.toMap();
    if(mapLeft.isEmpty()){
        value_ = left;
        return;
    }

    auto right = Compile(obj.getRight()).value_;
    QVariantMap mapRight = right.toMap();
    if(mapRight.isEmpty()){
        value_ = right;
        return;
    }

    auto vLeft = mapLeft.value("value").value<Value*>();
    auto typeLeft = mapLeft.value("type").value<MyType>();

    auto vRight = mapRight.value("value").value<Value*>();
    auto typeRight = mapRight.value("type").value<MyType>();

    if(typeLeft != MyType::BOOL_T || typeRight != MyType::BOOL_T){
        value_ = QString("Or :: Invalid operand, boolean required.");
        return;
    }

    Value* value = Builder.CreateOr(vLeft, vRight, "ortmp");

    QVariantMap map;
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(MyType::BOOL_T));

    value_ = map;
}

void Compile::VisitStartExprAST(StartAST& obj) {

}

void Compile::VisitAssignExprAST(AssignAST& obj) {
    auto expr = Compile{obj.getExpr()}.value_;
    QVariantMap condMap = expr.toMap();
    if(condMap.isEmpty()){
        value_ = expr;
        return;
    }

    auto vExpr = condMap.value("value").value<Value*>();
    auto typeExpr = condMap.value("type").value<MyType>();

    QString name = obj.getName();
    auto prevValue = State::Domains().getValue(name);
    QVariantMap map = prevValue.toMap();
    if(map.isEmpty() || map.value("type").value<MyType>() != typeExpr){
        Function *F = Builder.GetInsertBlock()->getParent();
        AllocaInst* alloca = CreateEntryBlockAlloca(F, name, typeExpr);
        map.clear();
        map.insert("value", QVariant::fromValue(alloca));
        map.insert("type", QVariant::fromValue(typeExpr));
        State::Domains().assignValue(name, map);
    }
    auto var = map.value("value").value<AllocaInst*>();

    Builder.CreateStore(vExpr, var);

    value_ = {};
}

void Compile::VisitBlockExprAST(BlockAST& obj) {
    State::Domains().createNewDomain();
    for(auto instruction : obj.getBody()){
        auto res = Compile(instruction).value_;
        if(!res.isNull()){
            value_ = res;
            return;
        }
    }
    State::Domains().removeCurrentDomain();
    value_ = {};
}

void Compile::VisitIfExprAST(IfAST& obj) {
    Function* f = Builder.GetInsertBlock()->getParent();
	BasicBlock* ThenBB = BasicBlock::Create(TheContext, "then", f);
	BasicBlock* ElseBB = BasicBlock::Create(TheContext, "else", f);
	BasicBlock* MergeBB = BasicBlock::Create(TheContext, "ifcont", f);
    
    auto cond = Compile(obj.getCond()).value_;
    QVariantMap condMap = cond.toMap();
    if(condMap.isEmpty()){
        value_ = cond;
        return;
    }

    auto vCond = condMap.value("value").value<Value*>();
    auto typeCond = condMap.value("type").value<MyType>();

    if(typeCond != MyType::BOOL_T){
        value_ = QString("If :: Invalid condition.");
        return;
    }

    Value* condJump = Builder.CreateICmpEQ(vCond, ConstantInt::get(TheContext, APInt(1, 1)), "ifcond");
    Builder.CreateCondBr(condJump, ThenBB, ElseBB);

    Builder.SetInsertPoint(ThenBB);
    auto thenV = Compile(obj.getThen()).value_;
    if(!thenV.isNull()){
        value_ = thenV;
        return;
    }
    Builder.CreateBr(MergeBB);
    
    Builder.SetInsertPoint(ElseBB);
    auto elseV = Compile(obj.getElse()).value_;
    if(!elseV.isNull()){
        value_ = elseV;
        return;
    }
    Builder.CreateBr(MergeBB);
    
    Builder.SetInsertPoint(MergeBB);
    value_ = {};
}

void Compile::VisitWhileExprAST(WhileAST& obj) {
    Function* f = Builder.GetInsertBlock()->getParent();
    BasicBlock* CondBB = BasicBlock::Create(TheContext, "cond", f);
    BasicBlock* LoopBB = BasicBlock::Create(TheContext, "loop", f);
    BasicBlock* AfterLoopBB = BasicBlock::Create(TheContext, "afterloop", f);
  
    Builder.CreateBr(CondBB);
    Builder.SetInsertPoint(CondBB);
  
    auto cond = Compile(obj.getCond()).value_;
    QVariantMap condMap = cond.toMap();
    if(condMap.isEmpty()){
        value_ = cond;
        return;
    }

    auto vCond = condMap.value("value").value<Value*>();
    auto typeCond = condMap.value("type").value<MyType>();

    if(typeCond != MyType::BOOL_T){
        value_ = QString("While :: Invalid condition.");
        return;
    }

    Value* condJump = Builder.CreateICmpEQ(vCond, ConstantInt::get(TheContext, APInt(1, 1)), "whilecond");
    Builder.CreateCondBr(condJump, LoopBB, AfterLoopBB);
  
    Builder.SetInsertPoint(LoopBB);
    auto bodyV = Compile(obj.getBody()).value_;
    if (!bodyV.isNull()){
        value_ = bodyV;
        return;
    }
    Builder.CreateBr(CondBB);

    Builder.SetInsertPoint(AfterLoopBB);
    value_ = {};
}

void Compile::VisitPrintAST(PrintAST& obj) {
    auto expr = Compile{obj.getExpr()}.value_;
    QVariantMap exprMap = expr.toMap();
    if(exprMap.isEmpty()){
        value_ = expr;
        return;
    }

    auto* vExpr = exprMap.value("value").value<Value*>();
    auto typeExpr = exprMap.value("type").value<MyType>();

    Function* printFunction = TheModule->getFunction("printf");
    if(printFunction == nullptr){
        FunctionType *FT1 = FunctionType::get(Type::getInt32Ty(TheContext), PointerType::get(Type::getInt8Ty(TheContext), 0), true);
        printFunction = Function::Create(FT1, Function::ExternalLinkage, "printf", TheModule);
    }

    if(typeExpr == MyType::DOUBLE_T){
        if(doublePrintStr == nullptr){
            doublePrintStr = Builder.CreateGlobalStringPtr("%g\n");
        }

        std::vector<Value*> args;
        args.push_back(doublePrintStr);
        args.push_back(vExpr);
        Builder.CreateCall(printFunction, args, "printfDoubleCall");
    }
    else if(typeExpr == MyType::BOOL_T){

        if(truePrintStr == nullptr){
            truePrintStr = Builder.CreateGlobalStringPtr("true\n");
        }

        if(falsePrintStr == nullptr){
            falsePrintStr = Builder.CreateGlobalStringPtr("false\n");
        }

        Function* f = Builder.GetInsertBlock()->getParent();
        BasicBlock* TrueBB = BasicBlock::Create(TheContext, "trueprint", f);
        BasicBlock* FalseBB = BasicBlock::Create(TheContext, "falseprint", f);
        BasicBlock* MergeBB = BasicBlock::Create(TheContext, "mergeprint", f);

        Value* printJump = Builder.CreateICmpEQ(vExpr, ConstantInt::get(TheContext, APInt(1, 1)), "ifcond");
        Builder.CreateCondBr(printJump, TrueBB, FalseBB);

        Builder.SetInsertPoint(TrueBB);
        std::vector<Value*> args;
        args.push_back(truePrintStr);
        Builder.CreateCall(printFunction, args, "printfTrueCall");
        Builder.CreateBr(MergeBB);

        Builder.SetInsertPoint(FalseBB);
        args.clear();
        args.push_back(falsePrintStr);
        Builder.CreateCall(printFunction, args, "printfFalseCall");
        Builder.CreateBr(MergeBB);

        Builder.SetInsertPoint(MergeBB);
    }

    value_ = {};
}

void Compile::VisitInputAST(InputAST& obj) {
    Function* scanFunction = TheModule->getFunction("scanf");
    if(scanFunction == nullptr){
        FunctionType *FT1 = FunctionType::get(Type::getInt32Ty(TheContext), PointerType::get(Type::getInt8Ty(TheContext), 0), true);
        scanFunction = Function::Create(FT1, Function::ExternalLinkage, "scanf", TheModule);
    }

    if(doubleInputStr == nullptr){
        doubleInputStr = Builder.CreateGlobalStringPtr("%lf");
    }

    QString name = obj.getName();
    auto prevValue = State::Domains().getValue(name);
    QVariantMap map = prevValue.toMap();
    if(map.isEmpty() || map.value("type").value<MyType>() != MyType::DOUBLE_T){
        Function *F = Builder.GetInsertBlock()->getParent();
        AllocaInst* alloca = CreateEntryBlockAlloca(F, name, MyType::DOUBLE_T);
        map.clear();
        map.insert("value", QVariant::fromValue(alloca));
        map.insert("type", QVariant::fromValue(MyType::DOUBLE_T));
        State::Domains().assignValue(name, map);
    }
    auto var = map.value("value").value<AllocaInst*>();
    std::vector<Value*> args;
    args.push_back(doubleInputStr);
    args.push_back(var);
    Builder.CreateCall(scanFunction, args, "scanfCall");
    value_ = {};
}
