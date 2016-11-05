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
#include <boost/spirit/home/x3.hpp>

namespace ling0 {

using Value = double;

namespace ast {
struct BindingAccess;
struct BinExpression;
struct Expression;
struct LogStatement;
struct Operation;
struct Program;
}
/**
 * A context for executing commands
 */
class VirtualMachine: public boost::static_visitor<Value> /*TODO Remove this*/ {
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
	 * @return
	 */
	Value solve(const ast::Expression &expression);

	/**
	 * Solve an expression
	 * @param value
	 * @return
	 */
	Value operator()(const double &value);

	/**
	 * Solve an add expression
	 * @param value
	 * @return
	 */
	Value operator()(const ast::BinExpression &value);

	/**
	 *
	 * @param value
	 * @return
	 */
	Value operator()(const ast::BindingAccess &value);
private:
	void logStm(ast::LogStatement const &logStm);
	void pushLocal(ast::Expression const &initializer);
private:
	std::ostream &out;
	std::vector<Value> memory;
};

} /* namespace ling0 */

#endif /* VIRTUALMACHINE_H_ */
