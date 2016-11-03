/*
 * expression.h
 *
 *  Created on: 2 de nov de 2016
 *      Author: talesm
 */

#ifndef GRAMMAR_EXPRESSION_H_
#define GRAMMAR_EXPRESSION_H_

#include <boost/spirit/home/x3/core/action.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#include <boost/spirit/home/x3/numeric/real.hpp>
#include <boost/spirit/home/x3/operator/alternative.hpp>
#include <boost/spirit/home/x3/operator/kleene.hpp>
#include <boost/spirit/home/x3/operator/sequence.hpp>
#include <boost/spirit/home/x3/string/symbols.hpp>

#include "../ast/Expression.h"

namespace ling0 {
namespace grammar {

using namespace boost::spirit::x3;

/**
 * Checks for additive priority level symbols
 */
struct additiveSymbols_: symbols<ast::BinOperation> {
	additiveSymbols_() {
		using ast::BinOperation;
		add
			("+", BinOperation::ADD)
			("-", BinOperation::SUB);
	}
} const additiveSymbols;

/**
 * Wraps binary operators sequences into the correct BinOperator tree hierarchy
 *
 * It is necessary to allow right to left priority.
 */
struct binaryOperatorWrapper {
	template<typename Context>
	void operator()(Context const &ctx) {
		using namespace boost::fusion;
		using namespace ast;

		auto const & attr = _attr(ctx);
		auto head = Expression(at_c<0>(attr));
		auto tail = at_c<1>(attr);
		for (auto &&tailPiece : tail) {
			head = BinExpression { head, at_c<0>(tailPiece),
					Expression(at_c<1>(tailPiece)) };
		}
		_val(ctx) = head;
	}
};

/**
 * Parses additive expressions (with + and -)
 */
rule<class add_operation, ast::Expression> add_operation = "add_expression";
auto const add_operation_def =
		(double_ >> *(additiveSymbols >> double_))[binaryOperatorWrapper { }];

/**
 * Parses expressions
 */
rule<class expression, ast::Expression> expression = "expression";
auto const expression_def = add_operation | double_;

BOOST_SPIRIT_DEFINE(expression, add_operation);

}
}

#endif /* GRAMMAR_EXPRESSION_H_ */
