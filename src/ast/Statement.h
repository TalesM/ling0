/*
 * Statement.h
 *
 *  Created on: 5 de nov de 2016
 *      Author: talesm
 */

#ifndef AST_STATEMENT_H_
#define AST_STATEMENT_H_

#include "Expression.h"

namespace ling0 {
namespace ast {

/**
 * @brief A Logging statement
 */
struct LogStatement {
	std::string content;
	std::vector<Expression> parameters;
};

/**
 * @brief A binding (variable declaration) statement
 */
struct BindingStatement {
	boost::optional<Expression> initializer;
};

/**
 * @brief A generic statement
 */
struct Statement: x3::variant<LogStatement, BindingStatement> {
	using base_type::base_type;
	using base_type::operator=;
	Statement(Statement const &) = default;
	Statement &operator=(Statement const &) = default;
	Statement() = default;
};

}  // namespace ast
}  // namespace ling0

BOOST_FUSION_ADAPT_STRUCT(
	ling0::ast::LogStatement,
	(std::string, content),
    (std::vector<ling0::ast::Expression>, parameters)
)

BOOST_FUSION_ADAPT_STRUCT(
	ling0::ast::BindingStatement,
    (boost::optional<ling0::ast::Expression>, initializer)
)

#endif /* AST_STATEMENT_H_ */
