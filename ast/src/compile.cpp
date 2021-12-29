#include <compile.hpp>
#include <state.hpp>

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
Module* TheModule;
//map<string, AllocaInst*> NamedValues;
legacy::FunctionPassManager* TheFPM;

void Compile::VisitPlaceholderExprAST(PlaceholderExprAST& obj) {
    //TODO error handling
}

void Compile::VisitValueExprAST(ValueExprAST& obj) {
    cValue_ = ConstantFP::get(TheContext, APFloat(obj.getValue()));
}

void Compile::VisitVariableExprAST(VariableExprAST& obj) {
	//TODO Discuss table
}

void Compile::VisitNotExprAST(NotExprAST& obj) {
    Value* v = Compile(obj.getOperand()).cValue_;
    if(!v){
        //TODO error handling
    }
    cValue_ = Builder.CreateNot(v, "nottmp"); // Maybe CreateNeg ? (Has additional arguments)
}

void Compile::VisitMulExprAST(MulExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateFMul(l, r, "multmp");
}

void Compile::VisitDivExprAST(DivExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateFDiv(l, r, "divtmp");
}

void Compile::VisitAddExprAST(AddExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateFAdd(l, r, "addtmp");
}

void Compile::VisitSubExprAST(SubExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateFSub(l, r, "subtmp");	
}

void Compile::VisitLtExprAST(LtExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateUIToFP(Builder.CreateFCmpOLT(l, r, "lttmp"), Type::getDoubleTy(TheContext), "booltmp");
}

void Compile::VisitLeqExprAST(LeqExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateUIToFP(Builder.CreateFCmpOLE(l, r, "letmp"), Type::getDoubleTy(TheContext), "booltmp");
}

void Compile::VisitGtExprAST(GtExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateUIToFP(Builder.CreateFCmpOGT(l, r, "gttmp"), Type::getDoubleTy(TheContext), "booltmp");
}

void Compile::VisitGeqExprAST(GeqExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateUIToFP(Builder.CreateFCmpOGE(l, r, "getmp"), Type::getDoubleTy(TheContext), "booltmp");
}

void Compile::VisitEqExprAST(EqExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateUIToFP(Builder.CreateFCmpOEQ(l, r, "eqtmp"), Type::getDoubleTy(TheContext), "booltmp");
}

void Compile::VisitNeqExprAST(NeqExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateUIToFP(Builder.CreateFCmpONE(l, r, "netmp"), Type::getDoubleTy(TheContext), "booltmp");
}

void Compile::VisitAndExprAST(AndExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateAnd(l, r, "andtmp"); // Maybe CreateLocigalAnd ?
}

void Compile::VisitOrExprAST(OrExprAST& obj) {
	Value* l = Compile(obj.getLeft()).cValue_;
    Value* r = Compile(obj.getRight()).cValue_;
    if(!l || !r){
        //TODO error handling
    }
    cValue_ = Builder.CreateOr(l, r, "ortmp"); // Maybe CreateLocigalOr ?
}

void Compile::VisitStartExprAST(StartExprAST& obj) {
    //TODO error handling
}

void Compile::VisitAssignExprAST(AssignExprAST& obj) {
	//TODO Discuss table
}

void Compile::VisitBlockExprAST(BlockExprAST& obj) {
    QVector<InstructionExprAST*> tmpVector = obj.getBody();
    for (unsigned i = 0; i < tmpVector.size(); i++) {
        Value* expr = Compile(tmpVector[i]).cValue_;
        if (!expr){
            //TODO error handling
        }
    }
    cValue_ = ConstantFP::get(TheContext, APFloat(0.0));
}

void Compile::VisitIfExprAST(IfExprAST& obj) {
	Function* f = Builder.GetInsertBlock()->getParent();
	BasicBlock* ThenBB = BasicBlock::Create(TheContext, "then", f);
	BasicBlock* ElseBB = BasicBlock::Create(TheContext, "else", f);
	BasicBlock* MergeBB = BasicBlock::Create(TheContext, "ifcont", f);
    
    Value* condV = Compile(obj.getCond()).cValue_;
    if(!condV){
        //TODO error handling
    }
    
    Value* tmp = Builder.CreateFCmpONE(condV, ConstantFP::get(TheContext, APFloat(0.0)), "ifcond");
    
    Builder.CreateCondBr(tmp, ThenBB, ElseBB);
    
    Builder.SetInsertPoint(ThenBB);
    Value* thenV = Compile(obj.getThen()).cValue_;
    if(!thenV){
        //TODO error handling
    }
    Builder.CreateBr(MergeBB);
    ThenBB = Builder.GetInsertBlock();
    
    f->getBasicBlockList().push_back(ElseBB);
    Builder.SetInsertPoint(ElseBB);
    Value* elseV = Compile(obj.getElse()).cValue_;
    if(!elseV){
        //TODO error handling
    }
    Builder.CreateBr(MergeBB);
    ElseBB = Builder.GetInsertBlock();
    
    f->getBasicBlockList().push_back(MergeBB);
    Builder.SetInsertPoint(MergeBB);
    PHINode* phi = Builder.CreatePHI(Type::getDoubleTy(TheContext), 2, "iftmp");
    phi->addIncoming(thenV,ThenBB);
    phi->addIncoming(elseV,ElseBB);
	
	cValue_ = phi;
}

//TODO Variable domains
void Compile::VisitWhileExprAST(WhileExprAST& obj) {
	Function* f = Builder.GetInsertBlock()->getParent();
    BasicBlock* CondBB = BasicBlock::Create(TheContext, "cond", f);
    BasicBlock* LoopBB = BasicBlock::Create(TheContext, "loop", f);
    BasicBlock* AfterLoopBB = BasicBlock::Create(TheContext, "afterloop", f);
  
    Builder.CreateBr(CondBB);
    Builder.SetInsertPoint(CondBB);
  
    Value* condV = Compile(obj.getCond()).cValue_;
    if(!condV){
        //TODO error handling
    }
    
    Value* tmp = Builder.CreateFCmpONE(condV, ConstantFP::get(TheContext, APFloat(0.0)), "loopcond");
    Builder.CreateCondBr(tmp, LoopBB, AfterLoopBB);
  
    Builder.SetInsertPoint(LoopBB);
    Value* bodyV = Compile(obj.getBody()).cValue_;
    if (!bodyV){
        //TODO error handling
    }
    
    Builder.CreateBr(CondBB);

    Builder.SetInsertPoint(AfterLoopBB);

    cValue_ = ConstantFP::get(TheContext, APFloat(0.0));
}

//TODO Needs "args_" field in FunctionExprAST definition (getArgs())
//TODO Variable domains
void Compile::VisitFunctionExprAST(FunctionExprAST& obj) {
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
    
    Value* bodyV = Compile(obj.getBody()).cValue_;
    if(bodyV){
        Builder.CreateRet(bodyV);
        
        verifyFunction(*f);
        
        TheFPM->run(*f);
        
        cValue_ = f;
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
//     Value* s = Compile(obj.getValue()).cValue_;
//     if(!v){
//         TODO error handling
//     }
// 
//     /* globalni stringovi potreban za ispis */
//     Str = Builder.CreateGlobalStringPtr("%lf\n");
// 
//     vector<Value *> ArgsV;
//     ArgsV.push_back(Str);
//     ArgsV.push_back(s);
//     Builder.CreateCall(printfFunction, ArgsV, "printCall");
// 
//     return s;
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
