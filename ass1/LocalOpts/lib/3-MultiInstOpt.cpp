#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <vector>
using namespace llvm;

namespace {

class MultiInstOpt final : public FunctionPass {
public:
  static char ID;

  MultiInstOpt() : FunctionPass(ID) {}

  /**
   * @todo(cscd70) Please complete the methods below.
   */
  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {}

  virtual bool runOnFunction(Function &F) override { return false; }

  void multiInst_Opt(Function& F);
}; // class MultiInstOpt

  void multiInst_Opt(Function& F){
	std::vector<Instruction*> DeadInstList;
	std::vector<Instruction*> AddInstList;
	std::vector<Instruction*> SubInstList;
	std::vector<Instruction*> MulInstList;
	std::vector<Instruction*> SDivInstList;
  	for(auto &BB:F)
		for(auto &inst:BB){
			unsigned op_num=inst.getNumOperands();
			if(op_num==2){
				Value* op1=inst.getOperand(0);
				Value* op2=inst.getOperand(1);
				int64_t v1,v2;
				bool MultiInstOptFlag=true;
				if(isa<ConstantInt>(op1)){
					v1=dyn_cast<ConstantInt>(op1).getSExtValue();
				}
				if(isa<ConstantInt>(op2)){
					v2=dyn_cast<ConstantInt>(op2).getSExtValue();
				}

				switch(inst.getOpcode()){
					case Instruction::Add:
						if(SubInstList.size()==0){
							if(isa<ConstantInt>(op1)||isa<ConstantInt>(op2)){
								AddInstList.push_back(inst);
								break;
							}
						}
						for(auto sil:SubInstList){
							if(isa<ConstantInt>(sil.getOperand(1))){
								if(isa<ConstantInt>(op1)&&\
										v1==dyn_cast<ConstantInt>(sil.gitOperand(1).getSExtValue())\
										){
									inst.replaceAllUsesWith(BinaryOperator::Create(Instruction::Mov,op2,sil.getOperand(0),"mov",&inst));
									break;
								}else if(isa<ConstantInt>(op2&&v2==dyn_cast<ConstantInt>(sil.gitOperand(1).getSExtValue())){
									inst.replaceAllUsesWith(BinaryOperator::Create(Instruction::Mov,op1,sil.getOperand(0),"mov",&inst));
									break;
								}
							}
						}
						if(isa<ConstantInt>(op1)){
							
						}
						break;
					case Instruction::Sub:
						break;
					case Instruction::Mul:
						break;
					case Instruction::SDiv:
						break;
				}
			}
		}
  }

char MultiInstOpt::ID = 0;
RegisterPass<MultiInstOpt> X("multi-inst-opt",
                             "CSCD70: Multi-Instruction Optimization");

} // anonymous namespace
