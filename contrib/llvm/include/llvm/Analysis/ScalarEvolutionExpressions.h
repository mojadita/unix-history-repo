//===- llvm/Analysis/ScalarEvolutionExpressions.h - SCEV Exprs --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the classes used to represent and build scalar expressions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_ANALYSIS_SCALAREVOLUTION_EXPRESSIONS_H
#define LLVM_ANALYSIS_SCALAREVOLUTION_EXPRESSIONS_H

#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Support/ErrorHandling.h"

namespace llvm {
  class ConstantInt;
  class ConstantRange;
  class DominatorTree;

  enum SCEVTypes {
    // These should be ordered in terms of increasing complexity to make the
    // folders simpler.
    scConstant, scTruncate, scZeroExtend, scSignExtend, scAddExpr, scMulExpr,
    scUDivExpr, scAddRecExpr, scUMaxExpr, scSMaxExpr,
    scUnknown, scCouldNotCompute
  };

  //===--------------------------------------------------------------------===//
  /// SCEVConstant - This class represents a constant integer value.
  ///
  class SCEVConstant : public SCEV {
    friend class ScalarEvolution;

    ConstantInt *V;
    SCEVConstant(const FoldingSetNodeIDRef ID, ConstantInt *v) :
      SCEV(ID, scConstant), V(v) {}
  public:
    ConstantInt *getValue() const { return V; }

    Type *getType() const { return V->getType(); }

    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVConstant *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scConstant;
    }
  };

  //===--------------------------------------------------------------------===//
  /// SCEVCastExpr - This is the base class for unary cast operator classes.
  ///
  class SCEVCastExpr : public SCEV {
  protected:
    const SCEV *Op;
    Type *Ty;

    SCEVCastExpr(const FoldingSetNodeIDRef ID,
                 unsigned SCEVTy, const SCEV *op, Type *ty);

  public:
    const SCEV *getOperand() const { return Op; }
    Type *getType() const { return Ty; }

    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVCastExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scTruncate ||
             S->getSCEVType() == scZeroExtend ||
             S->getSCEVType() == scSignExtend;
    }
  };

  //===--------------------------------------------------------------------===//
  /// SCEVTruncateExpr - This class represents a truncation of an integer value
  /// to a smaller integer value.
  ///
  class SCEVTruncateExpr : public SCEVCastExpr {
    friend class ScalarEvolution;

    SCEVTruncateExpr(const FoldingSetNodeIDRef ID,
                     const SCEV *op, Type *ty);

  public:
    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVTruncateExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scTruncate;
    }
  };

  //===--------------------------------------------------------------------===//
  /// SCEVZeroExtendExpr - This class represents a zero extension of a small
  /// integer value to a larger integer value.
  ///
  class SCEVZeroExtendExpr : public SCEVCastExpr {
    friend class ScalarEvolution;

    SCEVZeroExtendExpr(const FoldingSetNodeIDRef ID,
                       const SCEV *op, Type *ty);

  public:
    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVZeroExtendExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scZeroExtend;
    }
  };

  //===--------------------------------------------------------------------===//
  /// SCEVSignExtendExpr - This class represents a sign extension of a small
  /// integer value to a larger integer value.
  ///
  class SCEVSignExtendExpr : public SCEVCastExpr {
    friend class ScalarEvolution;

    SCEVSignExtendExpr(const FoldingSetNodeIDRef ID,
                       const SCEV *op, Type *ty);

  public:
    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVSignExtendExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scSignExtend;
    }
  };


  //===--------------------------------------------------------------------===//
  /// SCEVNAryExpr - This node is a base class providing common
  /// functionality for n'ary operators.
  ///
  class SCEVNAryExpr : public SCEV {
  protected:
    // Since SCEVs are immutable, ScalarEvolution allocates operand
    // arrays with its SCEVAllocator, so this class just needs a simple
    // pointer rather than a more elaborate vector-like data structure.
    // This also avoids the need for a non-trivial destructor.
    const SCEV *const *Operands;
    size_t NumOperands;

    SCEVNAryExpr(const FoldingSetNodeIDRef ID,
                 enum SCEVTypes T, const SCEV *const *O, size_t N)
      : SCEV(ID, T), Operands(O), NumOperands(N) {}

  public:
    size_t getNumOperands() const { return NumOperands; }
    const SCEV *getOperand(unsigned i) const {
      assert(i < NumOperands && "Operand index out of range!");
      return Operands[i];
    }

    typedef const SCEV *const *op_iterator;
    op_iterator op_begin() const { return Operands; }
    op_iterator op_end() const { return Operands + NumOperands; }

    Type *getType() const { return getOperand(0)->getType(); }

    NoWrapFlags getNoWrapFlags(NoWrapFlags Mask = NoWrapMask) const {
      return (NoWrapFlags)(SubclassData & Mask);
    }

    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVNAryExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scAddExpr ||
             S->getSCEVType() == scMulExpr ||
             S->getSCEVType() == scSMaxExpr ||
             S->getSCEVType() == scUMaxExpr ||
             S->getSCEVType() == scAddRecExpr;
    }
  };

  //===--------------------------------------------------------------------===//
  /// SCEVCommutativeExpr - This node is the base class for n'ary commutative
  /// operators.
  ///
  class SCEVCommutativeExpr : public SCEVNAryExpr {
  protected:
    SCEVCommutativeExpr(const FoldingSetNodeIDRef ID,
                        enum SCEVTypes T, const SCEV *const *O, size_t N)
      : SCEVNAryExpr(ID, T, O, N) {}

  public:
    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVCommutativeExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scAddExpr ||
             S->getSCEVType() == scMulExpr ||
             S->getSCEVType() == scSMaxExpr ||
             S->getSCEVType() == scUMaxExpr;
    }

    /// Set flags for a non-recurrence without clearing previously set flags.
    void setNoWrapFlags(NoWrapFlags Flags) {
      SubclassData |= Flags;
    }
  };


  //===--------------------------------------------------------------------===//
  /// SCEVAddExpr - This node represents an addition of some number of SCEVs.
  ///
  class SCEVAddExpr : public SCEVCommutativeExpr {
    friend class ScalarEvolution;

    SCEVAddExpr(const FoldingSetNodeIDRef ID,
                const SCEV *const *O, size_t N)
      : SCEVCommutativeExpr(ID, scAddExpr, O, N) {
    }

  public:
    Type *getType() const {
      // Use the type of the last operand, which is likely to be a pointer
      // type, if there is one. This doesn't usually matter, but it can help
      // reduce casts when the expressions are expanded.
      return getOperand(getNumOperands() - 1)->getType();
    }

    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVAddExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scAddExpr;
    }
  };

  //===--------------------------------------------------------------------===//
  /// SCEVMulExpr - This node represents multiplication of some number of SCEVs.
  ///
  class SCEVMulExpr : public SCEVCommutativeExpr {
    friend class ScalarEvolution;

    SCEVMulExpr(const FoldingSetNodeIDRef ID,
                const SCEV *const *O, size_t N)
      : SCEVCommutativeExpr(ID, scMulExpr, O, N) {
    }

  public:
    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVMulExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scMulExpr;
    }
  };


  //===--------------------------------------------------------------------===//
  /// SCEVUDivExpr - This class represents a binary unsigned division operation.
  ///
  class SCEVUDivExpr : public SCEV {
    friend class ScalarEvolution;

    const SCEV *LHS;
    const SCEV *RHS;
    SCEVUDivExpr(const FoldingSetNodeIDRef ID, const SCEV *lhs, const SCEV *rhs)
      : SCEV(ID, scUDivExpr), LHS(lhs), RHS(rhs) {}

  public:
    const SCEV *getLHS() const { return LHS; }
    const SCEV *getRHS() const { return RHS; }

    Type *getType() const {
      // In most cases the types of LHS and RHS will be the same, but in some
      // crazy cases one or the other may be a pointer. ScalarEvolution doesn't
      // depend on the type for correctness, but handling types carefully can
      // avoid extra casts in the SCEVExpander. The LHS is more likely to be
      // a pointer type than the RHS, so use the RHS' type here.
      return getRHS()->getType();
    }

    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVUDivExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scUDivExpr;
    }
  };


  //===--------------------------------------------------------------------===//
  /// SCEVAddRecExpr - This node represents a polynomial recurrence on the trip
  /// count of the specified loop.  This is the primary focus of the
  /// ScalarEvolution framework; all the other SCEV subclasses are mostly just
  /// supporting infrastructure to allow SCEVAddRecExpr expressions to be
  /// created and analyzed.
  ///
  /// All operands of an AddRec are required to be loop invariant.
  ///
  class SCEVAddRecExpr : public SCEVNAryExpr {
    friend class ScalarEvolution;

    const Loop *L;

    SCEVAddRecExpr(const FoldingSetNodeIDRef ID,
                   const SCEV *const *O, size_t N, const Loop *l)
      : SCEVNAryExpr(ID, scAddRecExpr, O, N), L(l) {}

  public:
    const SCEV *getStart() const { return Operands[0]; }
    const Loop *getLoop() const { return L; }

    /// getStepRecurrence - This method constructs and returns the recurrence
    /// indicating how much this expression steps by.  If this is a polynomial
    /// of degree N, it returns a chrec of degree N-1.
    /// We cannot determine whether the step recurrence has self-wraparound.
    const SCEV *getStepRecurrence(ScalarEvolution &SE) const {
      if (isAffine()) return getOperand(1);
      return SE.getAddRecExpr(SmallVector<const SCEV *, 3>(op_begin()+1,
                                                           op_end()),
                              getLoop(), FlagAnyWrap);
    }

    /// isAffine - Return true if this is an affine AddRec (i.e., it represents
    /// an expressions A+B*x where A and B are loop invariant values.
    bool isAffine() const {
      // We know that the start value is invariant.  This expression is thus
      // affine iff the step is also invariant.
      return getNumOperands() == 2;
    }

    /// isQuadratic - Return true if this is an quadratic AddRec (i.e., it
    /// represents an expressions A+B*x+C*x^2 where A, B and C are loop
    /// invariant values.  This corresponds to an addrec of the form {L,+,M,+,N}
    bool isQuadratic() const {
      return getNumOperands() == 3;
    }

    /// Set flags for a recurrence without clearing any previously set flags.
    /// For AddRec, either NUW or NSW implies NW. Keep track of this fact here
    /// to make it easier to propagate flags.
    void setNoWrapFlags(NoWrapFlags Flags) {
      if (Flags & (FlagNUW | FlagNSW))
        Flags = ScalarEvolution::setFlags(Flags, FlagNW);
      SubclassData |= Flags;
    }

    /// evaluateAtIteration - Return the value of this chain of recurrences at
    /// the specified iteration number.
    const SCEV *evaluateAtIteration(const SCEV *It, ScalarEvolution &SE) const;

    /// getNumIterationsInRange - Return the number of iterations of this loop
    /// that produce values in the specified constant range.  Another way of
    /// looking at this is that it returns the first iteration number where the
    /// value is not in the condition, thus computing the exit count.  If the
    /// iteration count can't be computed, an instance of SCEVCouldNotCompute is
    /// returned.
    const SCEV *getNumIterationsInRange(ConstantRange Range,
                                       ScalarEvolution &SE) const;

    /// getPostIncExpr - Return an expression representing the value of
    /// this expression one iteration of the loop ahead.
    const SCEVAddRecExpr *getPostIncExpr(ScalarEvolution &SE) const {
      return cast<SCEVAddRecExpr>(SE.getAddExpr(this, getStepRecurrence(SE)));
    }

    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVAddRecExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scAddRecExpr;
    }
  };


  //===--------------------------------------------------------------------===//
  /// SCEVSMaxExpr - This class represents a signed maximum selection.
  ///
  class SCEVSMaxExpr : public SCEVCommutativeExpr {
    friend class ScalarEvolution;

    SCEVSMaxExpr(const FoldingSetNodeIDRef ID,
                 const SCEV *const *O, size_t N)
      : SCEVCommutativeExpr(ID, scSMaxExpr, O, N) {
      // Max never overflows.
      setNoWrapFlags((NoWrapFlags)(FlagNUW | FlagNSW));
    }

  public:
    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVSMaxExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scSMaxExpr;
    }
  };


  //===--------------------------------------------------------------------===//
  /// SCEVUMaxExpr - This class represents an unsigned maximum selection.
  ///
  class SCEVUMaxExpr : public SCEVCommutativeExpr {
    friend class ScalarEvolution;

    SCEVUMaxExpr(const FoldingSetNodeIDRef ID,
                 const SCEV *const *O, size_t N)
      : SCEVCommutativeExpr(ID, scUMaxExpr, O, N) {
      // Max never overflows.
      setNoWrapFlags((NoWrapFlags)(FlagNUW | FlagNSW));
    }

  public:
    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVUMaxExpr *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scUMaxExpr;
    }
  };

  //===--------------------------------------------------------------------===//
  /// SCEVUnknown - This means that we are dealing with an entirely unknown SCEV
  /// value, and only represent it as its LLVM Value.  This is the "bottom"
  /// value for the analysis.
  ///
  class SCEVUnknown : public SCEV, private CallbackVH {
    friend class ScalarEvolution;

    // Implement CallbackVH.
    virtual void deleted();
    virtual void allUsesReplacedWith(Value *New);

    /// SE - The parent ScalarEvolution value. This is used to update
    /// the parent's maps when the value associated with a SCEVUnknown
    /// is deleted or RAUW'd.
    ScalarEvolution *SE;

    /// Next - The next pointer in the linked list of all
    /// SCEVUnknown instances owned by a ScalarEvolution.
    SCEVUnknown *Next;

    SCEVUnknown(const FoldingSetNodeIDRef ID, Value *V,
                ScalarEvolution *se, SCEVUnknown *next) :
      SCEV(ID, scUnknown), CallbackVH(V), SE(se), Next(next) {}

  public:
    Value *getValue() const { return getValPtr(); }

    /// isSizeOf, isAlignOf, isOffsetOf - Test whether this is a special
    /// constant representing a type size, alignment, or field offset in
    /// a target-independent manner, and hasn't happened to have been
    /// folded with other operations into something unrecognizable. This
    /// is mainly only useful for pretty-printing and other situations
    /// where it isn't absolutely required for these to succeed.
    bool isSizeOf(Type *&AllocTy) const;
    bool isAlignOf(Type *&AllocTy) const;
    bool isOffsetOf(Type *&STy, Constant *&FieldNo) const;

    Type *getType() const { return getValPtr()->getType(); }

    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const SCEVUnknown *S) { return true; }
    static inline bool classof(const SCEV *S) {
      return S->getSCEVType() == scUnknown;
    }
  };

  /// SCEVVisitor - This class defines a simple visitor class that may be used
  /// for various SCEV analysis purposes.
  template<typename SC, typename RetVal=void>
  struct SCEVVisitor {
    RetVal visit(const SCEV *S) {
      switch (S->getSCEVType()) {
      case scConstant:
        return ((SC*)this)->visitConstant((const SCEVConstant*)S);
      case scTruncate:
        return ((SC*)this)->visitTruncateExpr((const SCEVTruncateExpr*)S);
      case scZeroExtend:
        return ((SC*)this)->visitZeroExtendExpr((const SCEVZeroExtendExpr*)S);
      case scSignExtend:
        return ((SC*)this)->visitSignExtendExpr((const SCEVSignExtendExpr*)S);
      case scAddExpr:
        return ((SC*)this)->visitAddExpr((const SCEVAddExpr*)S);
      case scMulExpr:
        return ((SC*)this)->visitMulExpr((const SCEVMulExpr*)S);
      case scUDivExpr:
        return ((SC*)this)->visitUDivExpr((const SCEVUDivExpr*)S);
      case scAddRecExpr:
        return ((SC*)this)->visitAddRecExpr((const SCEVAddRecExpr*)S);
      case scSMaxExpr:
        return ((SC*)this)->visitSMaxExpr((const SCEVSMaxExpr*)S);
      case scUMaxExpr:
        return ((SC*)this)->visitUMaxExpr((const SCEVUMaxExpr*)S);
      case scUnknown:
        return ((SC*)this)->visitUnknown((const SCEVUnknown*)S);
      case scCouldNotCompute:
        return ((SC*)this)->visitCouldNotCompute((const SCEVCouldNotCompute*)S);
      default:
        llvm_unreachable("Unknown SCEV type!");
      }
    }

    RetVal visitCouldNotCompute(const SCEVCouldNotCompute *S) {
      llvm_unreachable("Invalid use of SCEVCouldNotCompute!");
    }
  };
}

#endif
