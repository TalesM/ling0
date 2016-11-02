#include <algorithm>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "Context.h"

using namespace std;
using namespace ling0;

bool blank(const string &line);

int main(int argc, char **argv) {
	//TODO Boost...
	if(argc <= 1){
		cout << "No parameters given" << endl;
		return -1;
	}
	if(argv[1] == "--version"s){
		cout << "ling0 Version 0.1 Alpha" << endl;
		return 0;
	}
	fstream input(argv[1], ios_base::in);
	if(!input.good()){
		cout << "Invalid file" << endl;
		return 1;
	}

	Context context(cout);
	return 0;
}

bool blank(const string &line){
	return all_of(line.begin(), line.end(), [](char c){return isblank(c);});

}
