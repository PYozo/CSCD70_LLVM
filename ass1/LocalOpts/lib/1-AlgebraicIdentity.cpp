#include <llvm/IR/Module.h>
#include <llvm/Pass.h>

using namespace llvm;

namespace {

class AlgebraicIdentity final : public FunctionPass {
public:
  static char ID;
  int AlgebraicOptNum=0;
  AlgebraicIdentity() : FunctionPass(ID) {}

  /**
   * @todo(cscd70) Please complete the methods below.
   */
  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {}

  virtual bool runOnFunction(Function &F) override {
	  algebraic_identies(F);
	  outs()<<"Algebraic identies: "<<AlgebraicOptNum<<"\n";
	  return false; 
  }

  void algebraic_identies(Function &F);
}; // class AlgebraicIdentity

char AlgebraicIdentity::ID = 0;
RegisterPass<AlgebraicIdentity> X("algebraic-identity",
                                  "CSCD70: Algebraic Identity");

  void deleteDeadInstrs(std::vector<Instruction*>instrs){
  	for(auto &instr:instrs){
		if(instrs->isSafeToRemove()){
			instr->eraseFromParent();
		}
	}
  }

  void algebraic_identies(Function &F){
	std::vector<Instruction*> DeadInstrList;
  	for(auto &BB:F)
		for(auto &inst:BB){
			unsigned op_num=inst.getNumOperands();
			if(op_num==2){
				Value* op1=inst.getOperand(0);
				Value* op2=inst.getOperand(1);
				int64_t v1,v2;
				bool AlgebraicFlag=true;
				if(isa<ConstantInt>(op1)){
					v1=dyn_cast<ConstantInt>(op1).getSExtValue();
				}
				if(isa<ConstantInt>(op2)){
					v2=dyn_cast<ConstantInt>(op2).getSExtValue();
				}

				switch(inst.getOpcode()){
					case Instruction::Add:
						if(isa<ConstantInt>(op1)&&v1==0){
							inst.replaceAllUsesWith(op2);
						}else if(isa<ConstantInt>(op2)&&v2==0){
							inst.replaceAllUsesWith(op1);
						}else{
							AlgebraicFlag=false;
						}
						break;
					case Instruction::Sub:
						if(isa<ConstantInt>(op2)&&v2=0){
							inst.replaceAllUsesWith(op1);
						}else if(op1==op2){
							inst.replaceAllUsesWith(ConstantInt::getSigned(inst.getType(),0));
						}else{
							AlgebraicFlag=false;
						}
						break;
					case Instruction::Mul:
						if(isa<ConstantInt>(op1)&&v1==1){
							inst.replaceAllUsesWith(op2);
						}else if(isa<ConstantInt>(op2)&&v2==1){
							inst.replaceAllUsesWith(op1);
						}else{
							AlgebraicFlag=false;
						}
						break;
					case Instruction::SDiv:
						if(isa<ConstantInt>(op2)&&v2=1){
							inst.replaceAllUsesWith(op1);
						}
						else if(isa<ConstantInt>(op1)&&isa<ConstantInt>(op2)&&v1==v2){
							inst.replaceAllUsesWith(ConstantInt::getSigned(inst.getType(),1));
						}else{
							AlgebraicFlag=false;
						}
						break;
					default:
						AlgebraicFlag=false;
						break;
				}
				if(AlgebraicFlag==true){
					DeadInstrList.push_back(inst);
					++AlgebraicOptNum;
				}
			}
		}
	deleteDeadInstrs(DeadInstrList);
  }

} // anonymous namespace
