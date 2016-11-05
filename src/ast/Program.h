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
#include <boost/optional.hpp>

#include "Statement.h"

namespace ling0 {
namespace ast {

/**
 * @brief A program representation
 */
struct Program{
	std::string name;
	std::vector<Statement> statements;
};

}  // namespace ast
}  // namespace ling0

BOOST_FUSION_ADAPT_STRUCT(
    ling0::ast::Program,
    (std::string, name),
    (std::vector<ling0::ast::Statement>, statements)
)

#endif /* AST_PROGRAM_H_ */
