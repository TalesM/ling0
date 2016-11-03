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
#include "ast/Program.h"

namespace ling0 {

namespace ast {
struct Expression;
struct Operation;
}
/**
 * A context for executing commands
 */
class VirtualMachine: public boost::static_visitor<double> /*TODO Remove this*/ {
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
	double solve(const ast::Expression &expression);

	/**
	 * Solve an expression
	 * @param value
	 * @return
	 */
	double operator()(const double &value);

	/**
	 * Solve an add expression
	 * @param value
	 * @return
	 */
	double operator()(const ast::BinExpression &value);
private:
	std::ostream &out;
};

} /* namespace ling0 */

#endif /* VIRTUALMACHINE_H_ */
