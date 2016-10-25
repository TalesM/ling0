#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main() {
	cout << "Welcome to Ling0 Interactive prompt." << endl;
	string line;
	for (;;) {
		cout << ">> ";
		getline(cin, line);
		if (line == "exit") {
			break;
		}
	};
	cout << "Exited Successfully" << endl;
	return EXIT_SUCCESS;
}
