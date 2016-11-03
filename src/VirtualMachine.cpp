/*
 * Context.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: Tales
 */

#include "VirtualMachine.h"

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

VirtualMachine::VirtualMachine(std::ostream &out) :
		out(out) {
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::runProgram(const ast::Program& program) {
	for (auto const &stm : program.statements) {
		out << stm.content << endl;
	}
}

double VirtualMachine::solve(const ast::Expression& expression) {
	return apply_visitor(*this, expression);
}

double VirtualMachine::operator ()(const ast::Operation& value) {
	double r = 0;
	for (auto &&operand : value.operands) {
		r += apply_visitor(*this, operand);
	}
	return r;
}

double VirtualMachine::operator ()(const double& value) {
	return value;
}

} /* namespace ling0 */

