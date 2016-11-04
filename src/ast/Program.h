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

#include "Expression.h"

namespace ling0 {
namespace ast {

struct Log {
	std::string content;
	std::vector<Expression> parameters;
};

struct Binding {
	boost::optional<Expression> initializer;
};

struct Statement: x3::variant<Log, Binding> {
	using base_type::base_type;
	using base_type::operator=;
	Statement(Statement const &) = default;
	Statement &operator=(Statement const &) = default;
	Statement() = default;
};

/**
 * A program
 */
struct Program{
	std::string name;
	std::vector<Statement> statements;
};

}  // namespace ast
}  // namespace ling0

BOOST_FUSION_ADAPT_STRUCT(
	ling0::ast::Log,
	(std::string, content),
    (std::vector<ling0::ast::Expression>, parameters)
)
BOOST_FUSION_ADAPT_STRUCT(
	ling0::ast::Binding,
    (boost::optional<ling0::ast::Expression>, initializer)
)
BOOST_FUSION_ADAPT_STRUCT(
    ling0::ast::Program,
    (std::string, name),
    (std::vector<ling0::ast::Statement>, statements)
)

#endif /* AST_PROGRAM_H_ */
