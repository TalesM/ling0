/*
 * Parser.h
 *
 *  Created on: 2 de nov de 2016
 *      Author: talesm
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <boost/optional.hpp>
#include <istream>

namespace ling0 {
//Forward declarations
namespace ast {
struct Expression;
struct Program;
}

/**
 * Parses a character representation of the program and mounts the AST
 */
class Parser {
public:
	Parser(std::istream &in);
	~Parser();

	/**
	 * Parses everything
	 * @return
	 */
	boost::optional<ast::Program> parseAll();

	/**
	 * Parse an expression
	 * @return
	 */
	boost::optional<ast::Expression> parseExpression();
private:
	std::istream &in;
};

} /* namespace ling0 */

#endif /* PARSER_H_ */
