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
	if(argc <= 1){
		cout << "No parameters given" << endl;
		return EXIT_FAILURE;
	}
	if(argv[1] == "--version"s){
		cout << "ling0 Version 0.1 Alpha" << endl;
		return EXIT_SUCCESS;
	}
	fstream input(argv[1], ios_base::in);
	if(!input.good()){
		cout << "Invalid file" << endl;
		return EXIT_FAILURE;
	}

	Parser parser(input);
	if(!parser.parseAll()){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool blank(const string &line){
	return all_of(line.begin(), line.end(), [](char c){return isblank(c);});

}
