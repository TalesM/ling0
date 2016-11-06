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
struct IfExpression;

/**
 * @brief Request for use of a binding
 */
struct BindingAccess {
	unsigned id; ///< Stack position
};

/**
 * Represents an expression
 */
struct Expression: x3::variant<double, bool, x3::forward_ast<BinExpression>, x3::forward_ast<IfExpression>, BindingAccess> {
	using base_type::base_type;
	using base_type::operator=;
};

/**
 * @brief Binary operators
 */
enum BinOperation : uint32_t {
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/',
	MOD = '%',

	AND = 'a' | 'n' << 8 | 'd' << 16,
	OR = 'o' | 'r' << 8,
	XOR = 'x' | 'o' << 8 | 'r' << 16,
};

/**
 * @brief A Binary expression
 */
struct BinExpression {
	Expression left;
	BinOperation operation;
	Expression right;
};

/**
 * @brief An conditional branch.
 */
struct IfExpression{
	Expression condition;
	Expression thenBranch;
	//TODO ELSEIFs
	Expression elseBranch;
};

} /* namespace ast */
} /* namespace ling0 */

BOOST_FUSION_ADAPT_STRUCT(
		ling0::ast::BindingAccess,
		(unsigned, id)
)
BOOST_FUSION_ADAPT_STRUCT(
	ling0::ast::BinExpression,
	(ling0::ast::Expression, left),
	(ling0::ast::BinOperation, operation),
	(ling0::ast::Expression, right),
)
BOOST_FUSION_ADAPT_STRUCT(
	ling0::ast::IfExpression,
	(ling0::ast::Expression, condition),
	(ling0::ast::Expression, thenBranch),
	(ling0::ast::Expression, elseBranch),
)

#endif /* AST_EXPRESSION_H_ */
