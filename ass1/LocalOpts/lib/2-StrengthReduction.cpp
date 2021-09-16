#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <vector>
using namespace llvm;

namespace {

class StrengthReduction final : public FunctionPass {
public:
  static char ID;
  int StrengthOptNum=0;
  StrengthReduction() : FunctionPass(ID) {}

  /**
   * @todo(cscd70) Please complete the methods below.
   */
  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {}

  virtual bool runOnFunction(Function &F) override { 
	  strength_reduction(&F);
	  outs()<<"StrengthReduction identies: "<<StrengthOptNum<<"\n"
	  return false; 
  }

  void strength_reduction(Function &F);

  int64_t shirft(int64_t x){
	  if(x<=0&&x&(~x+1)!=x){
		  return -1;
	  }
	  int i=0;
	  while(x>1){
	  	x>>=1;
		i++;
	  }
	  return i;
  }

}; // class StrengthReduction

char StrengthReduction::ID = 0;
RegisterPass<StrengthReduction> X("strength-reduction",
		"CSCD70: Strength Reduction");

void strength_reduction(Function &F){
	std::vector<Instruction*> DeadInstrList;
	for(auto &BB:F)
		for(auto &inst:BB){
			unsigned op_num=inst.getNumOperands();
			if(op_num==2){
				Value* op1=inst.getOperand(0);
				Value* op2=inst.getOperand(1);
				int64_t v1,v2;
				bool StrengthFlag=true;
				if(isa<ConstantInt>(op1)){
					v1=dyn_cast<ConstantInt>(op1).getSExtValue();
				}
				if(isa<ContantInt>(op2)){
					v2=dyn_cast<ConstantInt>(op2).getSExtValue();
				}
				switch(inst.getOpcode()){
					case Instruction::Mul:
						if(isa<ConstantInt>(opt1)&&getShirt(v1)!=-1){
							inst.replaceAllUsesWith(BinaryOperator(Instruction::Shl,op2,\
										ConstantInt::getSigned(inst.getType(),getShirt(v1)),\
										"shl",&inst));
						}
						else if(isa<ConstantInt>(opt2)&&getShirt(v2)!=-1){
							inst.replaceAllUsesWith(BinaryOperator(Instruction::Shl,op1,\
										ConstantInt::getSigned(inst.getType(),getShirt(v2)),\
										"shl",&inst));
						}
						else{
							StrengthFlag=false;
						}
						break;
					case Instruction::SDiv:
						if(isa<ConstantInt>(op2)&&getSh){
							inst.replaceAllUsesWith(BinaryOperator(Instruction::lShr,opt1,\
										ConstantInt::getSigned(inst.getType(),getShirt(v2)),\
										"shr",&inst));
						}
						else{
							StrengthFlag=false;
						}
						break;
					default :
						StrengthFlag=false;
						break;
				}
				if(StrengthFlag==true){
					DeadInstrList.push_back(inst);
					++StrlengthOptNum;
				}
				
			}
			
		}
	deleteDeadInstrs(DeadInstrList);
  }

} // anonymous namespace
