#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "ast/Program.h"
#include "Parser.h"
#include "VirtualMachine.h"

using namespace std;
using namespace ling0;

bool blank(string const &line);

void execute(ast::Program const &p, ostream &out);

int main(int argc, char **argv) {
	//TODO Boost...
	int i;
	string outputName = "";
	if(argc <= 1){
		cerr << "No parameters given" << endl;
		return EXIT_FAILURE;
	}
	for(i = 1; i < argc-1; ++i){
		if(argv[i] == "--version"s){
			cerr << "ling0 Version 0.1 Alpha" << endl;
			return EXIT_SUCCESS;
		}
		if(argv[i][0] == '-'){
			if(argv[i][1] == 'O'){
				outputName = &argv[i][2];
			}
		}
	}
	fstream source(argv[i], ios_base::in);
	if(!source.good()){
		cerr << "Invalid file" << endl;
		return EXIT_FAILURE;
	}


	Parser parser(source);
	auto result = parser.parseAll();
	if(!result){
		return EXIT_FAILURE;
	}
	if(outputName != ""){
		fstream outputStream(outputName, ios_base::out);
		execute(*result, outputStream);
	} else {
		execute(*result, cout);

	}
	return EXIT_SUCCESS;
}

bool blank( string const&line){
	return all_of(line.begin(), line.end(), [](char c){return isblank(c);});
}

void execute(ast::Program const &p, ostream &out){
	VirtualMachine vm(out);
	vm.runProgram(p);
}
