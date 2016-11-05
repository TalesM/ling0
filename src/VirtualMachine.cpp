/*
 * Context.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: Tales
 */

#include "VirtualMachine.h"

#include <cmath>
#include <iterator>
#include <stdexcept>
#include <vector>

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
	for (auto const &logStm : program.statements) {
		struct _ : boost::static_visitor<void>{
			VirtualMachine &vm;
			_(VirtualMachine &vm): vm(vm){}
			void operator()(const ast::Log &logStm){
				vm.logStm(logStm);
			}

			void operator()(const ast::Binding &binding){
				//TODO
			}

		} visitor(*this);
		logStm.apply_visitor(visitor);
	}
}

double VirtualMachine::solve(const ast::Expression& expression) {
	return apply_visitor(*this, expression);
}

double VirtualMachine::operator ()(const double& value) {
	return value;
}

double VirtualMachine::operator ()(const ast::BinExpression& value) {
	switch (value.operation) {
		case BinOperation::ADD:
			return solve(value.left) + solve(value.right);
		case BinOperation::SUB:
			return solve(value.left) - solve(value.right);
		case BinOperation::MUL:
			return solve(value.left) * solve(value.right);
		case BinOperation::DIV:
			return solve(value.left) / solve(value.right);
		case BinOperation::MOD:
			return fmod(solve(value.left), solve(value.right));
	}
	throw std::runtime_error("Invalid Opcode");
}

double VirtualMachine::operator ()(const ast::Access& value) {
	return 0;
}

void VirtualMachine::logStm(const ast::Log& logStm) {
	string::size_type first = 0;
	string::size_type last;
	auto &content = logStm.content;
	auto currentValue = logStm.parameters.begin();
	while ((last = content.find("{}", first)) != string::npos) {
		out << content.substr(first, last) << solve(*currentValue++);
		first = last + 2;
	}
	out << content.substr(first) << endl;
}

} /* namespace ling0 */

