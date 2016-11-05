/*
 * Parser.cpp
 *
 *  Created on: 2 de nov de 2016
 *      Author: talesm
 */

#include "Parser.h"

#include <boost/spirit/home/x3.hpp>
#include <iterator>
#include <vector>

#include "grammar.h"

namespace ling0 {
using namespace boost::spirit::x3;

Parser::Parser(std::istream &in) :
		in(in) {

}

Parser::~Parser() {
}

boost::optional<ast::Program> Parser::parseAll() {
	std::string tempBuffer(std::istreambuf_iterator<char>(in),
			std::istreambuf_iterator<char> { });

	auto first = tempBuffer.begin();
	auto last = tempBuffer.end();
	ast::Program p;
	if (phrase_parse(first, last, program, space, p)
			&& first == last) {
		return p;
	} else {
		return {};
	}
}

boost::optional<ast::Expression> Parser::parseExpression() {
	std::string tempBuffer(std::istreambuf_iterator<char>(in),
			std::istreambuf_iterator<char> { });
	ast::Expression r;
	auto first = tempBuffer.begin();
	auto last = tempBuffer.end();
	if (phrase_parse(first, last, expression, space, r)
			&& first == last) {
		return r;
	} else {
		return {};
	}
}

} /* namespace ling0 */
