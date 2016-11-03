/*
 * Program.h
 *
 *  Created on: 2 de nov de 2016
 *      Author: talesm
 */

#ifndef AST_PROGRAM_H_
#define AST_PROGRAM_H_

#include <string>
#include <vector>
#include <boost/fusion/include/adapt_struct.hpp>

#include "Expression.h"

namespace ling0 {
namespace ast {

struct Log {
	std::string content;
	std::vector<Expression> parameters;
};

/**
 * A program
 */
struct Program{
	std::string name;
	std::vector<Log> statements;
};

}  // namespace ast
}  // namespace ling0

BOOST_FUSION_ADAPT_STRUCT(
	ling0::ast::Log,
	(std::string, content),
    (std::vector<ling0::ast::Expression>, parameters)
)
BOOST_FUSION_ADAPT_STRUCT(
    ling0::ast::Program,
    (std::string, name),
    (std::vector<ling0::ast::Log>, statements)
)

#endif /* AST_PROGRAM_H_ */
