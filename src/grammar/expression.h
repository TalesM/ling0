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
 * Multiplicative symbols
 */
struct multiplicativeSymbols_: symbols<ast::BinOperation> {
	multiplicativeSymbols_() {
		using ast::BinOperation;
		add
			("*", BinOperation::MUL)
			("/", BinOperation::DIV)
			("%", BinOperation::MOD);
	}
} const multiplicativeSymbols;

/**
 * @brief Current thread's bindings.
 *
 * @warning This will break if there is more than one VirtualMachine at the program, even if they never exists at same time.
 */
thread_local struct bindingId_ : symbols<unsigned> {
	bindingId_() {
	}

	unsigned push(std::string const &id){
		add(id, next_id);
		return next_id++;
	}

	unsigned next_id = 0;
} bindingId;

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
		auto result = at_c<0>(attr);
		for (auto &&tailPiece : at_c<1>(attr)) {
			result = BinExpression { result, at_c<0>(tailPiece), at_c<1>(
					tailPiece) };
		}
		_val(ctx) = result;
	}
};

rule<class constant, std::string> id = "id";
rule<class constant, ast::Expression> constant = "constant";
rule<class access, ast::Access> access = "access";
rule<class unary, ast::Expression> unary = "unary";
rule<class mul_expression, ast::Expression> mul_expression = "mul_expression";
rule<class add_expression, ast::Expression> add_expression = "add_expression";
rule<class expression, ast::Expression> expression = "expression";

auto const id_def = +(alnum | '_');
auto const constant_def = double_;
auto const access_def = bindingId;
auto const unary_def = constant | access | ('(' >> expression >> ')');
auto const mul_expression_def = (unary >> *(multiplicativeSymbols >> unary))[binaryOperatorWrapper { }];

/**
 * Parses additive expressions (with + and -)
 */
auto const add_expression_def =
		(mul_expression >> *(additiveSymbols >> mul_expression))[binaryOperatorWrapper { }];

/**
 * Parses expressions
 */
auto const expression_def = add_expression | double_;

BOOST_SPIRIT_DEFINE(expression, add_expression, mul_expression, unary, access, constant, id)

}
}

#endif /* GRAMMAR_EXPRESSION_H_ */
