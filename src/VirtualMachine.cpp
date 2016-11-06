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

static thread_local VirtualMachine *vm = nullptr;

template<typename RETURN>
struct AstVisitor: public boost::static_visitor<RETURN> {
	using base = AstVisitor<RETURN>;
};

struct VmGuard{
	VmGuard(VirtualMachine *current){
		old = vm;
		vm = current;
	}

	~VmGuard(){
		vm = old;
	}

	VirtualMachine *old;
};

VirtualMachine::VirtualMachine(std::ostream &out) :
		out(out) {
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::runProgram(const ast::Program& program) {
	VmGuard guard(this);
	struct _ : AstVisitor<void>{
		void operator()(const ast::LogStatement &logStm){
			string::size_type first = 0;
			string::size_type last;
			auto &content = logStm.content;
			auto currentValue = logStm.parameters.begin();
			while ((last = content.find("{}", first)) != string::npos) {
				vm->out << std::boolalpha<< content.substr(first, last) << vm->rawSolve(*currentValue++);
				first = last + 2;
			}
			vm->out << content.substr(first) << endl;
		}

		void operator()(const ast::BindingStatement &binding){
			vm->pushLocal(binding.initializer.value_or(Expression{}));
		}

	} visitor;
	for (auto const &logStm : program.statements) {
		logStm.apply_visitor(visitor);
	}
}

Value VirtualMachine::solve(const ast::Expression& expression) {
	VmGuard guard(this);
	return rawSolve(expression);
}

Value VirtualMachine::rawSolve(const ast::Expression& expression) {
	struct _: AstVisitor<Value> {
		Value operator()(bool value){
			return value;
		}
		Value operator()(const double &value) {
			return value;
		}
		Value operator()(const ast::BinExpression &value) {
			switch (value.operation) {
			case BinOperation::ADD:
				return boost::get<double>(vm->rawSolve(value.left)) + boost::get<double>(vm->rawSolve(value.right));
			case BinOperation::SUB:
				return boost::get<double>(vm->rawSolve(value.left)) - boost::get<double>(vm->rawSolve(value.right));
			case BinOperation::MUL:
				return boost::get<double>(vm->rawSolve(value.left)) * boost::get<double>(vm->rawSolve(value.right));
			case BinOperation::DIV:
				return boost::get<double>(vm->rawSolve(value.left)) / boost::get<double>(vm->rawSolve(value.right));
			case BinOperation::MOD:
				return fmod(boost::get<double>(vm->rawSolve(value.left)), boost::get<double>(vm->rawSolve(value.right)));
			}
			throw std::runtime_error("Invalid Opcode");
		}
		Value operator()(const ast::BindingAccess &value){
			assert(value.id < vm->memory.size());
			return vm->memory[value.id];
		}
		Value operator()(ast::IfExpression const &value){
			auto condition = vm->rawSolve(value.condition);
			if(boost::get<bool>(condition)){
				return vm->rawSolve(value.thenBranch);
			} else {
				return vm->rawSolve(value.elseBranch);
			}
		}
	} visitor;
	return apply_visitor(visitor, expression);
}

void VirtualMachine::pushLocal(const ast::Expression& initializer) {
	memory.push_back(rawSolve(initializer));
}

} /* namespace ling0 */

