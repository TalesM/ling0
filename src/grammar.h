/*
 * program.h
 *
 *  Created on: 2 de nov de 2016
 *      Author: talesm
 */

#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#include <boost/spirit/home/x3.hpp>
#include "ast/Program.h"

namespace ling0 {
namespace {

using namespace boost::spirit::x3;
/**
 * Checks for additive priority level symbols
 */
struct additiveSymbol_: symbols<ast::BinOperation> {
	additiveSymbol_() {
		using ast::BinOperation;
		add
			("+", BinOperation::ADD)
			("-", BinOperation::SUB);
	}
} const additiveSymbol;

/**
 * Multiplicative symbols
 */
struct multiplicativeSymbol_: symbols<ast::BinOperation> {
	multiplicativeSymbol_() {
		using ast::BinOperation;
		add
			("*", BinOperation::MUL)
			("/", BinOperation::DIV)
			("%", BinOperation::MOD);
	}
} const multiplicativeSymbol;

/**
 * @brief Boolean symbols
 */
struct booleanSymbol_: symbols<ast::BinOperation> {
	booleanSymbol_() {
		using ast::BinOperation;
		add
			("and", BinOperation::AND)
			("or", BinOperation::OR)
			("xor", BinOperation::XOR);
	}
} const booleanSymbol;

/**
 * @brief Boolean symbols
 */
struct unarySymbol_: symbols<ast::UnaryOperation> {
	unarySymbol_() {
		using ast::UnaryOperation;
		add("not", UnaryOperation::NOT);
	}
} const unarySymbol;

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

struct unaryOperatorWrapper {
	template<typename Context>
	void operator()(Context const &ctx) {
		using namespace boost::fusion;
		using namespace ast;

		auto const & attr = _attr(ctx);
		auto result = at_c<1>(attr);
		auto &operators = at_c<0>(attr);
		for (auto it = operators.rbegin(); it != operators.rend(); ++it ) {
			result = UnaryExpression { *it, result};
		}
		_val(ctx) = result;
	}
};

struct bindingWrapper {
	template<typename Context>
	void operator()(Context const &ctx) {
		using namespace boost::fusion;
		using namespace ast;
		auto const & attr = _attr(ctx);
		bindingId.push(at_c<0>(attr));
		_val(ctx) = BindingStatement { at_c<1>(attr) };
	}
};

rule<class constant, std::string> identifier = "identifier";
rule<class constant, ast::Expression> constant = "constant";
rule<class access, ast::BindingAccess> access = "access";
rule<class if_expression, ast::IfExpression> if_expression = "if_expression";
rule<class top_level_expression, ast::Expression> top_level_expression = "top_level_expression";
rule<class unary_expression, ast::Expression> unary_expression = "unary_expression";
rule<class mul_expression, ast::Expression> mul_expression = "mul_expression";
rule<class add_expression, ast::Expression> add_expression = "add_expression";
rule<class bool_expression, ast::Expression> bool_expression = "bool_expression";
rule<class expression, ast::Expression> expression = "expression";
rule<class string_cte, std::string> string_cte = "string_cte";
rule<class log, ast::LogStatement> log = "log";
rule<class binding, ast::BindingStatement> binding = "binding";
rule<class statement, ast::Statement> statement = "statement";
rule<class program, ast::Program> program = "program";

auto const identifier_def = +(alnum | '_');
auto const constant_def = double_ | bool_;
auto const access_def = bindingId;

auto const if_expression_def = "if" >> expression >> ":" >> expression >> "else" >> ":" >> expression >> "end";

auto const top_level_expression_def = if_expression | constant | access | ('(' >> expression >> ')');
auto const unary_expression_def = (*unarySymbol >> top_level_expression)[unaryOperatorWrapper{} ];

auto const mul_expression_def =
		(unary_expression >> *(multiplicativeSymbol >> unary_expression))[binaryOperatorWrapper { }];
auto const add_expression_def = (mul_expression
		>> *(additiveSymbol >> mul_expression))[binaryOperatorWrapper { }];
auto const bool_expression_def = (add_expression >> *(booleanSymbol >> add_expression))[ binaryOperatorWrapper{} ];
auto const expression_def = bool_expression;

auto const string_cte_def = lexeme['"' >> *(char_ - '"') >> '"'];
auto const log_def = "log" >> lit('(') >> string_cte >> *(',' >> expression)
		>> ')';
auto const binding_def =
		("let" >> identifier >> -("=" >> expression))[bindingWrapper { }];
auto const statement_def = (log | binding) >> ';';

auto const program_def = "program" >> identifier >> ':' >> *statement >> "end"
		>> ';';

BOOST_SPIRIT_DEFINE(program, statement, binding, log, string_cte, expression,
		add_expression, mul_expression, bool_expression,unary_expression, if_expression, top_level_expression, access, constant, identifier)

}  // namespace grammar

}  // namespace ling0

#endif /* GRAMMAR_H_ */
