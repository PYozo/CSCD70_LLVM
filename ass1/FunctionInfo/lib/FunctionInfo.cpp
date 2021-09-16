#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

class FunctionInfo final : public ModulePass {
public:
  static char ID;

  FunctionInfo() : ModulePass(ID) {}

  // We don't modify the program, so we preserve all analysis.
  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesAll();
  }

  virtual bool runOnModule(Module &M) override {
    outs() << "CSCD70 Function Information Pass"
           << "\n";

    /**
     * @todo(cscd70) Please complete this method.
     */
    outs()<<M.getName()<<"\n";
    outs()<<"Name:   "<<"# Args   "<<"# Calls   "<<"# Blocks   "<<"# Insts   "<<"\n";
    for(auto &F:M){
        outs()<<F.getName()<<"   ";
	outs()<<F.arg_size()<<"   ";
	outs()<<F.getNumUses()<<"   ";
	outs()<<F.getBasicBlockList().size()<<"   ";
	size_t ins_size=0;
	for(auto &Ins:F){
		ins_size+=Ins.getInstList().size();
	}
	outs()<<ins_size<<"   "<<"\n";

    }

    return false;
  }
}; // class FunctionInfo

char FunctionInfo::ID = 0;
RegisterPass<FunctionInfo> X("function-info", "CSCD70: Function Information");

} // anonymous namespace
