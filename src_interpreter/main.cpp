#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Parser.h"

using namespace std;
using namespace ling0;

bool blank(const string &line);

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
	if(outputName != ""){
		fstream outputStream(outputName, ios_base::out);
	}

	Parser parser(source);
	if(!parser.parseAll()){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool blank(const string &line){
	return all_of(line.begin(), line.end(), [](char c){return isblank(c);});

}
