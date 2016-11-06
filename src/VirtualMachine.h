/*
 * Context.h
 *
 *  Created on: 25 de out de 2016
 *      Author: Tales
 */

#ifndef VIRTUALMACHINE_H_
#define VIRTUALMACHINE_H_

#include <iostream>
#include <string>
#include <vector>
#include <boost/variant.hpp>

namespace ling0 {

using Value = boost::variant<double, bool>;

namespace ast {
struct Expression;
struct Program;
}
/**
 * A context for executing commands
 */
class VirtualMachine {
public:
	VirtualMachine(std::ostream &out);
	~VirtualMachine();

	/**
	 * Executes a program
	 * @param program
	 */
	void runProgram(const ast::Program &program);

	/**
	 * Solve an expression
	 * @param expression
	 * @return The Value
	 */
	Value solve(const ast::Expression &expression);
private:
	Value rawSolve(const ast::Expression &expression);
	void pushLocal(ast::Expression const &initializer);
private:
	std::ostream &out;
	std::vector<Value> memory;
};

} /* namespace ling0 */

#endif /* VIRTUALMACHINE_H_ */
