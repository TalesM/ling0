/*
 * expression.h
 *
 *  Created on: 2 de nov de 2016
 *      Author: talesm
 */

#ifndef GRAMMAR_EXPRESSION_H_
#define GRAMMAR_EXPRESSION_H_

#include <boost/spirit/home/x3.hpp>
#include "../ast/Expression.h"

namespace ling0 {
namespace grammar {

using namespace boost::spirit::x3;

rule<class add_operation, ast::AddExpression> add_operation = "add_expression";
auto const add_operation_def = double_ >> '+' >> (add_operation | double_);

rule<class expression, ast::Expression> expression = "expression";
auto const expression_def = add_operation | double_;

BOOST_SPIRIT_DEFINE(expression, add_operation);

}
}

#endif /* GRAMMAR_EXPRESSION_H_ */
