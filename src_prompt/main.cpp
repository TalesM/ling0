#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

#include <VirtualMachine.h>

using namespace std;
using namespace ling0;

bool blank(const string &line);

int main() {
	cout << "Welcome to Ling0 Interactive prompt." << endl;
	string line;
	VirtualMachine context(cout);
	for (;;) {
		cout << ">> ";
		getline(cin, line);
		if (line == "exit") {
			break;
		} else if(!blank(line)) {
			cout << context.exec(line) << endl;
		}
	};
	cout << "Exited Successfully" << endl;
	return EXIT_SUCCESS;
}

bool blank(const string &line){
	return all_of(line.begin(), line.end(), [](char c){return isblank(c);});

}
