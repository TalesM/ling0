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

rule<class operation, ast::Operation> operation = "operation";
auto const operation_def = double_ % '+';

rule<class expression, ast::Expression> expression = "expression";
auto const expression_def = operation | double_;

BOOST_SPIRIT_DEFINE(expression, operation);

}
}

#endif /* GRAMMAR_EXPRESSION_H_ */
