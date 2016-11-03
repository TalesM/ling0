/*
 * Expression.h
 *
 *  Created on: 25 de out de 2016
 *      Author: Tales
 */

#ifndef AST_EXPRESSION_H_
#define AST_EXPRESSION_H_

#include <cstdint>
#include <vector>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace ling0 {
namespace ast {

namespace x3 = boost::spirit::x3;

// Forward
struct BinExpression;

/**
 * Represents an expression
 */
struct Expression: x3::variant<double, x3::forward_ast<BinExpression>> {
	using base_type::base_type;
	using base_type::operator=;
};

enum BinOperation : uint32_t {
	ADD = '+',
	SUB = '-',
};

/**
 * An Add Operation
 */
struct BinExpression {
	Expression left;
	BinOperation operation;
	Expression right;
};

} /* namespace ast */
} /* namespace ling0 */

BOOST_FUSION_ADAPT_STRUCT(
		ling0::ast::BinExpression,
		(ling0::ast::Expression, left),
		(ling0::ast::BinOperation, operation),
		(ling0::ast::Expression, right),
);

#endif /* AST_EXPRESSION_H_ */
