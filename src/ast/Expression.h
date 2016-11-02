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
struct Expression;

struct Operation {
	std::vector<Expression> operands;
//	Operator opcode;
};

/**
 * Represents
 */
struct Expression: x3::variant<double, Operation> {
	using base_type::base_type;
	using base_type::operator=;
};


} /* namespace ast */
} /* namespace ling0 */

BOOST_FUSION_ADAPT_STRUCT(
		ling0::ast::Operation,
		(std::vector<ling0::ast::Expression>, operands)
);

#endif /* AST_EXPRESSION_H_ */
