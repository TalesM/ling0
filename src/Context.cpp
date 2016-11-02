/*
 * Context.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: Tales
 */

#include "Context.h"

#include <boost/spirit/home/x3/char/char_class.hpp>
#include <boost/spirit/home/x3/numeric/real.hpp>
#include <boost/spirit/home/x3/operator/list.hpp>
#include <boost/variant/detail/apply_visitor_binary.hpp>
#include <boost/variant/detail/apply_visitor_delayed.hpp>
#include <boost/variant/detail/apply_visitor_unary.hpp>
#include <stdexcept>

#include "ast/Expression.h"

namespace ling0 {
using namespace ast;
using namespace std;
using namespace boost;

Context::Context(std::ostream &out) :
		out(out) {

}

Context::~Context() {
}

template<typename ITERATOR>
Expression parse_numbers(ITERATOR first, ITERATOR last) {
	using namespace boost::spirit::x3;
	Operation r;
	phrase_parse(first, last, double_ % '+', space, r);
	if (first != last) {
		throw std::runtime_error("<ERROR>");
	}
	return Expression{r};
}

std::string Context::exec(const std::string& code) {
	try {
		return to_string(solve(parse_numbers(code.begin(), code.end())));
	} catch (std::exception& e) {
		return e.what();
	}
}

double Context::solve(const ast::Expression& expression) {
	return apply_visitor(*this, expression);
}


double Context::operator ()(const ast::Operation& value) {
	double r = 0;
	for(auto &&operand: value.operands){
		r += apply_visitor(*this, operand);
	}
	return r;
}

double Context::operator ()(const double& value) {
	return value;
}

} /* namespace ling0 */
