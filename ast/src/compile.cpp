#include <vector>
#include <compile.hpp>
#include <state.hpp>

int Compile::qstringTypeId = QVariant(static_cast<QString>("")).typeId();
int Compile::allocaInstTypeId = QVariant::fromValue(static_cast<AllocaInst*>(nullptr)).typeId();

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
Module* TheModule;
//map<string, AllocaInst*> NamedValues;
legacy::FunctionPassManager* TheFPM;

void Compile::VisitPlaceholderExprAST(PlaceholderExprAST& obj) {
    value_ = Compile(obj.expr_).value_;
}

void Compile::VisitValueExprAST(ValueExprAST& obj) {
    value_ = QVariant::fromValue(ConstantFP::get(TheContext, APFloat(obj.getValue())));
}

void Compile::VisitVariableExprAST(VariableExprAST& obj) {
    value_ = State::Domains().getValue(obj.getName());
}

void Compile::VisitNotExprAST(NotExprAST& obj) {
    auto v = Compile(obj.getOperand()).value_;
    value_ = QVariant::fromValue(Builder.CreateNot(v.value<AllocaInst*>(), "nottmp")); // Maybe CreateNeg ? (Has additional arguments
}

void Compile::VisitMulExprAST(MulExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateFMul(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "multmp"));
}

void Compile::VisitDivExprAST(DivExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateFDiv(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "divtmp"));
}

void Compile::VisitAddExprAST(AddExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateFAdd(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "addtmp"));
}

void Compile::VisitSubExprAST(SubExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateFSub(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "subtmp"));
}

void Compile::VisitLtExprAST(LtExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateUIToFP(Builder.CreateFCmpOLT(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "lttmp"), Type::getDoubleTy(TheContext), "booltmp"));
}

void Compile::VisitLeqExprAST(LeqExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateUIToFP(Builder.CreateFCmpOLE(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "letmp"), Type::getDoubleTy(TheContext), "booltmp"));
}

void Compile::VisitGtExprAST(GtExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateUIToFP(Builder.CreateFCmpOGT(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "gttmp"), Type::getDoubleTy(TheContext), "booltmp"));
}

void Compile::VisitGeqExprAST(GeqExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateUIToFP(Builder.CreateFCmpOGE(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "getmp"), Type::getDoubleTy(TheContext), "booltmp"));
}

void Compile::VisitEqExprAST(EqExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateUIToFP(Builder.CreateFCmpOEQ(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "eqtmp"), Type::getDoubleTy(TheContext), "booltmp"));
}

void Compile::VisitNeqExprAST(NeqExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateUIToFP(Builder.CreateFCmpONE(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "netmp"), Type::getDoubleTy(TheContext), "booltmp"));
}

void Compile::VisitAndExprAST(AndExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateUIToFP(Builder.CreateAnd(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "andtmp"), Type::getDoubleTy(TheContext), "booltmp"));
    // Maybe CreateLocigalAnd ?
}

void Compile::VisitOrExprAST(OrExprAST& obj) {
    auto l = Compile(obj.getLeft()).value_;
    auto r = Compile(obj.getRight()).value_;

    value_ = QVariant::fromValue(Builder.CreateUIToFP(Builder.CreateOr(l.value<AllocaInst*>(), r.value<AllocaInst*>(), "ortmp"), Type::getDoubleTy(TheContext), "booltmp"));
    // Maybe CreateLocigalOr ?
}

void Compile::VisitStartExprAST(StartExprAST& obj) {
    //TODO error handling
}

void Compile::VisitAssignExprAST(AssignExprAST& obj) {
    //TODO default value_

    auto instrValue = Compile(obj.getExpr()).value_;
    if(!instrValue.value<AllocaInst*>()){
        //TODO error handling
    }
    State::Domains().assignValue(obj.getName(), instrValue);
}

void Compile::VisitBlockExprAST(BlockExprAST& obj) {
    //TODO default value_

    State::Domains().createNewDomain();
    QVector<InstructionExprAST*> tmpVector = obj.getBody();
    for (unsigned i = 0; i < tmpVector.size(); i++) {
        auto expr = Compile(tmpVector[i]).value_;
        if(!expr.value<AllocaInst*>()){
            //TODO error handling
        }
    }
    //value_ = QVariant::fromValue(ConstantFP::get(TheContext, APFloat(0.0)));
    State::Domains().removeCurrentDomain();
}

void Compile::VisitIfExprAST(IfExprAST& obj) {
    //TODO default value_

    Function* f = Builder.GetInsertBlock()->getParent();
	BasicBlock* ThenBB = BasicBlock::Create(TheContext, "then", f);
	BasicBlock* ElseBB = BasicBlock::Create(TheContext, "else", f);
	BasicBlock* MergeBB = BasicBlock::Create(TheContext, "ifcont", f);
    
    auto condV = Compile(obj.getCond()).value_;
    if(!condV.value<AllocaInst*>()){
        //TODO error handling
    }
    
    Value* tmp = Builder.CreateFCmpONE(condV.value<AllocaInst*>(), ConstantFP::get(TheContext, APFloat(0.0)), "ifcond");
    
    Builder.CreateCondBr(tmp, ThenBB, ElseBB);
    
    Builder.SetInsertPoint(ThenBB);
    auto thenV = Compile(obj.getThen()).value_;
    if(!thenV.value<AllocaInst*>()){
        //TODO error handling
    }
    Builder.CreateBr(MergeBB);
    ThenBB = Builder.GetInsertBlock();
    
    f->getBasicBlockList().push_back(ElseBB);
    Builder.SetInsertPoint(ElseBB);
    auto elseV = Compile(obj.getElse()).value_;
    if(!elseV.value<AllocaInst*>()){
        //TODO error handling
    }
    Builder.CreateBr(MergeBB);
    ElseBB = Builder.GetInsertBlock();
    
    f->getBasicBlockList().push_back(MergeBB);
    Builder.SetInsertPoint(MergeBB);
    PHINode* phi = Builder.CreatePHI(Type::getDoubleTy(TheContext), 2, "iftmp");
    phi->addIncoming(thenV.value<AllocaInst*>(),ThenBB);
    phi->addIncoming(elseV.value<AllocaInst*>(),ElseBB);
	
    value_ = QVariant::fromValue(phi);
}

void Compile::VisitWhileExprAST(WhileExprAST& obj) {
    //TODO default value_

	Function* f = Builder.GetInsertBlock()->getParent();
    BasicBlock* CondBB = BasicBlock::Create(TheContext, "cond", f);
    BasicBlock* LoopBB = BasicBlock::Create(TheContext, "loop", f);
    BasicBlock* AfterLoopBB = BasicBlock::Create(TheContext, "afterloop", f);
  
    Builder.CreateBr(CondBB);
    Builder.SetInsertPoint(CondBB);
  
    auto condV = Compile(obj.getCond()).value_;
    if(!condV.value<AllocaInst*>()){
        //TODO error handling
    }
    
    Value* tmp = Builder.CreateFCmpONE(condV.value<AllocaInst*>(), ConstantFP::get(TheContext, APFloat(0.0)), "loopcond");
    Builder.CreateCondBr(tmp, LoopBB, AfterLoopBB);
  
    Builder.SetInsertPoint(LoopBB);
    auto bodyV = Compile(obj.getBody()).value_;
    if (!bodyV.value<AllocaInst*>()){
        //TODO error handling
    }
    
    Builder.CreateBr(CondBB);

    Builder.SetInsertPoint(AfterLoopBB);

    value_ = QVariant::fromValue(ConstantFP::get(TheContext, APFloat(0.0)));
}

void Compile::VisitFunctionExprAST(FunctionExprAST& obj) {
    //TODO default value_

    Function* f = TheModule->getFunction(obj.getName().toStdString());
    if(f){
        //TODO error handling (function already defined)
    }
    
    QVector<QString> args = obj.getParameters();
    
    QVector<Type*> Qtypes(args.size(), Type::getDoubleTy(TheContext));
    std::vector<Type*> types(Qtypes.size());
    for(int i = 0; i < Qtypes.size(); i++)
    {
        types[i] = Qtypes[i];
    }
    
    FunctionType* ft = FunctionType::get(Type::getDoubleTy(TheContext), types, false);
    f = Function::Create(ft, Function::ExternalLinkage, obj.getName().toStdString(), TheModule);
    
    unsigned i = 0;
    for(auto &arg : f->args()){
        arg.setName(args[i++].toStdString());
    }
    
    if(!f){
        //TODO error handling (code can't be generated because prototype failed to initialize)
    }
    
    BasicBlock* BB = BasicBlock::Create(TheContext, "entry", f);
	Builder.SetInsertPoint(BB);
    
    /*
     * Ovde ide cuvanje promenljivih
     */
    
    auto bodyV = Compile(obj.getBody()).value_;
    if(bodyV.value<AllocaInst*>()){
        Builder.CreateRet(bodyV.value<AllocaInst*>());
        
        verifyFunction(*f);
        
        TheFPM->run(*f);
        
        //value_ = QVariant::fromValue(f);
    }
    else{
        //TODO error handling if bodyV == nullptr 
        f->eraseFromParent();
    }
}

// FunctionType *FT1 = FunctionType::get(Type::getDoubleTy(TheContext), PointerType::get(Type::getInt8Ty(TheContext), 0), true);
// printFunction = Function::Create(FT1, Function::ExternalLinkage, "print", TheModule);
// 
// Value* Compile::VisitPrintExprAST(PrintExprAST& obj) {
//     //TODO default value_
//
//     auto s = Compile(obj.getValue()).value_;
//     if(!v.value<AllocaInst*>()){
//         TODO error handling
//     }
// 
//     /* globalni stringovi potreban za ispis */
//     auto Str = Builder.CreateGlobalStringPtr("%lf\n");
// 
//     std::vector<AllocaInst*> ArgsV;
//     ArgsV.push_back(Str);
//     ArgsV.push_back(s.value<AllocaInst*>());
//     Builder.CreateCall(printfFunction, ArgsV, "printCall");
// 
//     return QVariant::fromValue(s);
// }

void InitializeModuleAndPassManager(){
	TheModule = new Module("Module", TheContext);
	
	TheFPM = new legacy::FunctionPassManager(TheModule);
	
	TheFPM->add(createInstructionCombiningPass());
	TheFPM->add(createReassociatePass());
	TheFPM->add(createGVNPass());
	TheFPM->add(createCFGSimplificationPass());
	TheFPM->add(createPromoteMemoryToRegisterPass());
	
	TheFPM->doInitialization();
}

//TODO implement "AllocaInst* CreateEntryBlockAlloca(Function* f, string s)"

AllocaInst* CreateEntryBlockAlloca(Function *f, QString s){
	IRBuilder<> TmpBuilder(&(f->getEntryBlock()), f->getEntryBlock().begin());
    return TmpBuilder.CreateAlloca(Type::getDoubleTy(TheContext), 0, s.toStdString());
}
