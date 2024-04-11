#include <memory>

#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

class IExpression {
 public:
  virtual int Calculate() const = 0;
  virtual ~IExpression() = default;
};

class Constant : public IExpression {
 public:
  Constant(int value) : value_(value) {};  // NOLINT

  int Calculate() const override {
    return value_;
  }

 private:
  int value_;
};

class IUnaryOperation : public IExpression {
 public:
  IUnaryOperation(std::unique_ptr<IExpression> child) : child (std::move(child)) {};  // NOLINT

  int Calculate() const override = 0;

 protected:
  virtual int Operation(int operand) const = 0;

  std::unique_ptr<IExpression> child;
};

class IBinaryOperation : public IExpression {
 public:
  IBinaryOperation(std::unique_ptr<IExpression> operand1, std::unique_ptr<IExpression> operand2)
                       : operand1_(std::move(operand1)), operand2_(std::move(operand2)) {};

  int Calculate() const override = 0;

 protected:
  virtual int Operation(int operand1, int operand2) const = 0; 

  std::unique_ptr<IExpression> operand1_;

  std::unique_ptr<IExpression> operand2_;
};

class Square : public IUnaryOperation {
 public:
  Square(std::unique_ptr<IExpression> child) : IUnaryOperation(std::move(child)) {};  // NOLINT
  int Calculate() const override {
    return Operation(child->Calculate());
  }
 protected:
  int Operation(int operand) const override {
    return operand * operand;
  }
};

class Sum : public IBinaryOperation {
 public:
  Sum(std::unique_ptr<IExpression> first, std::unique_ptr<IExpression> second) : IBinaryOperation(std::move(first), std::move(second)) {};
  int Calculate() const override {
    return Operation(operand1_->Calculate(), operand2_->Calculate());
  }
 protected:
  int Operation(int operand1, int operand2) const override {
    return operand1 + operand2;
  }
};

class Subtract : public IBinaryOperation {
 public:
  Subtract(std::unique_ptr<IExpression> first, std::unique_ptr<IExpression> second) : IBinaryOperation(std::move(first), std::move(second)) {};
  int Calculate() const override {
    return Operation(operand1_->Calculate(), operand2_->Calculate());
  }
 protected:
  int Operation(int operand1, int operand2) const override {
    return operand1 - operand2;
  }
};

class Multiply : public IBinaryOperation {
 public:
  Multiply(std::unique_ptr<IExpression> first, std::unique_ptr<IExpression> second) : IBinaryOperation(std::move(first), std::move(second)) {};
  int Calculate() const override {
    return Operation(operand1_->Calculate(), operand2_->Calculate());
  }
 protected:
  int Operation(int operand1, int operand2) const override {
    return operand1 * operand2;
  }
};

class Divide : public IBinaryOperation {
 public:
  Divide(std::unique_ptr<IExpression> first, std::unique_ptr<IExpression> second) : IBinaryOperation(std::move(first), std::move(second)) {};
  int Calculate() const override {
    return Operation(operand1_->Calculate(), operand2_->Calculate());
  }
 protected:
  int Operation(int operand1, int operand2) const override {
    return operand1 / operand2;
  }
};

class Residual : public IBinaryOperation {
 public:
  Residual(std::unique_ptr<IExpression> first, std::unique_ptr<IExpression> second) : IBinaryOperation(std::move(first), std::move(second)) {};
  int Calculate() const override {
    return Operation(operand1_->Calculate(), operand2_->Calculate());
  }
 protected:
  int Operation(int operand1, int operand2) const override {
    return operand1 % operand2;
  }
};

class Minimum : public IBinaryOperation {
 public:
  Minimum(std::unique_ptr<IExpression> first, std::unique_ptr<IExpression> second) : IBinaryOperation(std::move(first), std::move(second)) {};
  int Calculate() const override {
    return Operation(operand1_->Calculate(), operand2_->Calculate());
  }
 protected:
  int Operation(int operand1, int operand2) const override {
    return (operand1 < operand2 ? operand1 : operand2);
  }
};

class Maximum : public IBinaryOperation {
 public:
  Maximum(std::unique_ptr<IExpression> first, std::unique_ptr<IExpression> second) : IBinaryOperation(std::move(first), std::move(second)) {};
  int Calculate() const override {
    return Operation(operand1_->Calculate(), operand2_->Calculate());
  }
 protected:
  int Operation(int operand1, int operand2) const override {
    return (operand2 < operand1 ? operand1 : operand2);
  }
};

class AbsoluteValue : public IUnaryOperation {
 public:
  AbsoluteValue(std::unique_ptr<IExpression> child) : IUnaryOperation(std::move(child)) {};  // NOLINT

  int Calculate() const override {
    return Operation(child->Calculate());
  }
 protected:
  int Operation(int operand) const override {
    return (operand >= 0 ? operand : -operand);
  }
};

#endif