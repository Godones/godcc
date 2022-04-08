#include "visitor.h"

BinaryOp to_BinaryOp(const std::string_view &op) {
  if (op == "+") return BinaryOp::Add;
  if (op == "-") return BinaryOp::Sub;
  if (op == "*") return BinaryOp::Mul;
  if (op == "/") return BinaryOp::Div;
  if (op == "%") return BinaryOp::Mod;
  if (op == "==") return BinaryOp::Eq;
  if (op == "!=") return BinaryOp::Ne;
  if (op == "<") return BinaryOp::Lt;
  if (op == "<=") return BinaryOp::Le;
  if (op == ">") return BinaryOp::Gt;
  if (op == ">=") return BinaryOp::Ge;
  if (op == "&&") return BinaryOp::And;
  if (op == "||") return BinaryOp::Or;
  return BinaryOp::Invalid;
}
