/**
 * @file Available Expression Dataflow Analysis
 */
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Pass.h>

#include <dfa/Framework.h>
#include <dfa/MeetOp.h>

#include "Expression.h"

using namespace dfa;
using namespace llvm;

namespace {

using AvailExprFrameworkBase =
    Framework<Expression, bool, Direction::kForward, Intersect>;

class AvailExpr final : public AvailExprFrameworkBase, public FunctionPass {
private:
  virtual void initializeDomainFromInst(const Instruction &Inst) override {
    if (const BinaryOperator *const BinaryOp =
            dyn_cast<BinaryOperator>(&Inst)) {
      /**
       * @todo(cscd70) Please complete the construction of domain.
       */
      //把所有的二元式插入Domain
      Domain.push_back(BinaryOp);
    }
  }
  virtual bool transferFunc(const Instruction &Inst, const DomainVal_t &IBV,
                            DomainVal_t &OBV) override {
    /**
     * @todo(cscd70) Please complete the definition of the transfer function.
     */
    bool hasChanges=true;
    DomainVal_t bvi,bv0;
    DomainVal_t temp_bv0=IBV;
    //get kill x-kill
    for(const auto& elem:Domain){
        if(elem.LHS==Expression(Inst)||elem==Expression(Inst)){
            temp_bv0[position(elem)]=false;
        }
    }
    //get gen
    if(isa<BinaryOperator>(Inst)&&Domain.find(Expression(Inst))!=Domain.end()){
        temp_bv0[position(elem)]=true;
    }
    hasChanges=temp_bv0==OBV;
    OBV=temp_bv0;
    return hasChanges;
  }

public:
  static char ID;

  AvailExpr() : AvailExprFrameworkBase(), FunctionPass(ID) {}

  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesAll();
  }
  bool runOnFunction(Function &F) override {
    return AvailExprFrameworkBase::runOnFunction(F);
  }
};

char AvailExpr::ID = 0;
RegisterPass<AvailExpr> X("avail-expr", "Available Expression");

} // anonymous namespace
