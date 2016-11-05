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
 * @brief Request for use of a binding
 */
struct BindingAccess {
	unsigned id; ///< Stack position
};

/**
 * Represents an expression
 */
struct Expression: x3::variant<double, x3::forward_ast<BinExpression>, BindingAccess> {
	using base_type::base_type;
	using base_type::operator=;
};

/**
 * @brief Binary operators
 */
enum BinOperation: uint32_t {
	ADD = '+', //!< ADD
	SUB = '-', //!< SUB
	MUL = '*', //!< MUL
	DIV = '/', //!< DIV
	MOD = '%', //!< MOD
};

/**
 * @brief A Binary expression
 */
struct BinExpression {
	Expression left;
	BinOperation operation;
	Expression right;
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

#endif /* AST_EXPRESSION_H_ */
