/*
 * program.h
 *
 *  Created on: 2 de nov de 2016
 *      Author: talesm
 */

#ifndef GRAMMAR_PROGRAM_H_
#define GRAMMAR_PROGRAM_H_

#include <boost/spirit/home/x3.hpp>
#include "../ast/Program.h"
#include "expression.h"

namespace ling0 {
namespace grammar {

using namespace boost::spirit::x3;

auto const program_id = +(alnum | '_');


rule<class string_cte, std::string> string_cte = "string_cte";
auto const string_cte_def = lexeme['"' >> *(char_ - '"') >> '"'];

rule<class command, ast::Log> command = "command";
auto const command_def = "log" >> lit('(') >> string_cte >> *(',' >> expression) >>')' >> ';';

rule<class program, ast::Program> program = "program";
auto const program_def = "program" >> program_id >> ':' >> *command >> "end" >> ';';
BOOST_SPIRIT_DEFINE(program, command, string_cte);

}  // namespace grammar


}  // namespace ling0



#endif /* GRAMMAR_PROGRAM_H_ */
