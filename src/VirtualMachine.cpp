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

#include "ast/Program.h"

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
			void operator()(const ast::LogStatement &logStm){
				vm.logStm(logStm);
			}

			void operator()(const ast::BindingStatement &binding){
				if(binding.initializer){
					vm.pushLocal(binding.initializer.value_or(Expression{}));
				}
			}

		} visitor(*this);
		logStm.apply_visitor(visitor);
	}
}

Value VirtualMachine::solve(const ast::Expression& expression) {
	return apply_visitor(*this, expression);
}

Value VirtualMachine::operator ()(const double& value) {
	return value;
}

Value VirtualMachine::operator ()(const ast::BinExpression& value) {
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

Value VirtualMachine::operator ()(const ast::BindingAccess& value) {
	assert(value.id < memory.size());
	return memory[value.id];
}

void VirtualMachine::logStm(const ast::LogStatement& logStm) {
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

Value VirtualMachine::operator ()(ast::IfExpression const &value) {
	auto condition = solve(value.condition);
	if(condition){
		return solve(value.thenBranch);
	} else {
		return solve(value.elseBranch);
	}
}

void VirtualMachine::pushLocal(const ast::Expression& initializer) {
	memory.push_back(solve(initializer));
}

} /* namespace ling0 */

