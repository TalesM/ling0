/*
 * Context.h
 *
 *  Created on: 25 de out de 2016
 *      Author: Tales
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <iostream>
#include <string>
#include <boost/spirit/home/x3.hpp>

namespace ling0 {

namespace ast {
struct Expression;
struct Operation;
}
/**
 * A context for executing commands
 */
class Context {
public:
	Context(std::ostream &out);
	~Context();

	/**
	 * Executes a piece of code.
	 * @param code
	 * @return the result
	 */
	std::string exec(const std::string &code);

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
	double operator()(const ast::Operation &value);

	/**
	 * Solve an expression
	 * @param value
	 * @return
	 */
	double operator()(const double &value);
private:
	std::ostream &out;
};

} /* namespace ling0 */

#endif /* CONTEXT_H_ */
