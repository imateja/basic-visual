#include <vector>
#include <QFile>
#include <compile.hpp>
#include <state.hpp>

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
Module* TheModule = nullptr;
legacy::FunctionPassManager* TheFPM;
//Value* doubleStr = Builder.CreateGlobalStringPtr("%lf\n");
//Value* trueStr = Builder.CreateGlobalStringPtr("true\n");
//Value* falseStr = Builder.CreateGlobalStringPtr("false\n");

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

//	TheFPM->add(createInstructionCombiningPass());
//	TheFPM->add(createReassociatePass());
//	TheFPM->add(createGVNPass());
//	TheFPM->add(createCFGSimplificationPass());
//	TheFPM->add(createPromoteMemoryToRegisterPass());

    TheFPM->doInitialization();

    //TODO: Functions

    std::vector<Type*> arg(0);
    FunctionType* FTMain = FunctionType::get(Type::getInt32Ty(TheContext), arg, false);
    Function* MainFunction = Function::Create(FTMain, Function::InternalLinkage, "main", TheModule);
    BasicBlock* MainBB = BasicBlock::Create(TheContext, "entry", MainFunction);
    Builder.SetInsertPoint(MainBB);
}

void Compile::compile(const QString& path){
    if(TheModule != nullptr){
        std::string Str;
        raw_string_ostream OS(Str);
        OS << *TheModule;
        OS.flush();
        QFile file(path);
        file.open(QFile::WriteOnly);
        file.write(QByteArray::fromStdString(Str));
        file.close();
    }
}

AllocaInst* CreateEntryBlockAlloca(Function *f, QString s, MyType type){
    IRBuilder<> TmpBuilder(&(f->getEntryBlock()), f->getEntryBlock().begin());

    switch (type) {
    case MyType::DOUBLE_T:
        return TmpBuilder.CreateAlloca(Type::getDoubleTy(TheContext), 0, s.toStdString().c_str());
    case MyType::BOOL_T:
        return TmpBuilder.CreateAlloca(Type::getInt1Ty(TheContext), 0, s.toStdString().c_str());
    }
    return nullptr;
}

void Compile::VisitPlaceholderExprAST(PlaceholderExprAST& obj) {
    if(obj.isEmpty()){
        value_ = QString("Expression not finished :: Placeholder exists.");
        return;
    }

    value_ = Compile(obj.expr_).value_;
}

void Compile::VisitValueExprAST(ValueExprAST& obj) {
    Value* val = ConstantFP::get(TheContext, APFloat(obj.getValue()));
    QVariantMap map;
    map.insert("value", QVariant::fromValue(val));
    map.insert("type", QVariant::fromValue(MyType::DOUBLE_T));
    value_ = map;
}

void Compile::VisitVariableExprAST(VariableExprAST& obj) {
    QString name = obj.getName();
    auto prevValue = State::Domains().getValue(name);
    QVariantMap map = prevValue.toMap();
    if(map.isEmpty()){ //if QVariant was not a map, toMap() returns empty map
        value_ = prevValue;
        return;
    }
    auto var = map.value("value").value<AllocaInst*>();
    auto type = map.value("type").value<MyType>();
    Value* value = Builder.CreateLoad(Type::getDoubleTy(TheContext), var, name.toStdString().c_str());

    map.clear();
    map.insert("value", QVariant::fromValue(value));
    map.insert("type", QVariant::fromValue(type));
    value_ = map;
}

void Compile::VisitNotExprAST(NotExprAST& obj) {
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

void Compile::VisitMulExprAST(MulExprAST& obj) {
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

void Compile::VisitDivExprAST(DivExprAST& obj) {
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

void Compile::VisitAddExprAST(AddExprAST& obj) {
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

void Compile::VisitSubExprAST(SubExprAST& obj) {
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

void Compile::VisitLtExprAST(LtExprAST& obj) {
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

void Compile::VisitLeqExprAST(LeqExprAST& obj) {
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

void Compile::VisitGtExprAST(GtExprAST& obj) {
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

void Compile::VisitGeqExprAST(GeqExprAST& obj) {
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

void Compile::VisitEqExprAST(EqExprAST& obj) {
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

void Compile::VisitNeqExprAST(NeqExprAST& obj) {
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

void Compile::VisitAndExprAST(AndExprAST& obj) {
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

void Compile::VisitOrExprAST(OrExprAST& obj) {
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

void Compile::VisitStartExprAST(StartExprAST& obj) {

}

void Compile::VisitAssignExprAST(AssignExprAST& obj) {
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

void Compile::VisitBlockExprAST(BlockExprAST& obj) {
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

void Compile::VisitIfExprAST(IfExprAST& obj) {
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
    QVariantMap thenMap = thenV.toMap();
    if(thenMap.isEmpty()){
        value_ = thenV;
        return;
    }
    Builder.CreateBr(MergeBB);
    
    Builder.SetInsertPoint(ElseBB);
    auto elseV = Compile(obj.getElse()).value_;
    QVariantMap elseMap = elseV.toMap();
    if(elseMap.isEmpty()){
        value_ = elseV;
        return;
    }
    Builder.CreateBr(MergeBB);
    
    Builder.SetInsertPoint(MergeBB);
    value_ = {};
}

void Compile::VisitWhileExprAST(WhileExprAST& obj) {
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
    QVariantMap bodyMap = bodyV.toMap();
    if (bodyMap.isEmpty()){
        value_ = bodyV;
        return;
    }
    
    Builder.CreateBr(CondBB);
    Builder.SetInsertPoint(AfterLoopBB);

    value_ = {};
}

void Compile::VisitFunctionExprAST(FunctionExprAST& obj) {
//    //TODO default value_

//    Function* f = TheModule->getFunction(obj.getName().toStdString());
//    if(f){
//        //TODO error handling (function already defined)
//    }
    
//    QVector<QString> args = obj.getParameters();
    
//    QVector<Type*> Qtypes(args.size(), Type::getDoubleTy(TheContext));
//    std::vector<Type*> types(Qtypes.size());
//    for(int i = 0; i < Qtypes.size(); i++)
//    {
//        types[i] = Qtypes[i];
//    }
    
//    FunctionType* ft = FunctionType::get(Type::getDoubleTy(TheContext), types, false);
//    f = Function::Create(ft, Function::ExternalLinkage, obj.getName().toStdString(), TheModule);
    
//    unsigned i = 0;
//    for(auto &arg : f->args()){
//        arg.setName(args[i++].toStdString());
//    }
    
//    if(!f){
//        //TODO error handling (code can't be generated because prototype failed to initialize)
//    }
    
//    BasicBlock* BB = BasicBlock::Create(TheContext, "entry", f);
//	Builder.SetInsertPoint(BB);
    
//    /*
//     * Ovde ide cuvanje promenljivih
//     */
    
//    auto bodyV = Compile(obj.getBody()).value_;
//    if(bodyV.value<AllocaInst*>()){
//        Builder.CreateRet(bodyV.value<AllocaInst*>());
        
//        verifyFunction(*f);
        
//        TheFPM->run(*f);
        
//        //value_ = QVariant::fromValue(f);
//    }
//    else{
//        //TODO error handling if bodyV == nullptr
//        f->eraseFromParent();
//    }
}

//FunctionType *FT1 = FunctionType::get(Type::getDoubleTy(TheContext), PointerType::get(Type::getInt8Ty(TheContext), 0), true);
//Function* printFunction = Function::Create(FT1, Function::ExternalLinkage, "printf", TheModule);

void Compile::VisitPrintAST(PrintAST& obj) {
//    //TODO default value_

//    auto s = Compile(obj.getExpr()).value_;
//    if(!s.value<AllocaInst*>()){
//        //TODO error handling
//    }

//    /* globalni stringovi potreban za ispis */
//    auto Str = Builder.CreateGlobalStringPtr("%lf\n");

//    std::vector<AllocaInst*> ArgsV;
//    ArgsV.push_back(Str.value<AllocaInst*>());
//    ArgsV.push_back(s.value<AllocaInst*>());
//    Builder.CreateCall(printfFunction, ArgsV, "printCall");

//    return QVariant::fromValue(s);
}
