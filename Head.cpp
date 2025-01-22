#include "Command.h"
#include <iostream>
#include <sstream>
#include <string>

void Head::execute() {
	std::string input;

	ifBufferNotEmpty();
	if (argument.empty()) {
		input = ifArgumentEmpty();
	}
	else {
		input = getArgumentType();
		if (input.empty()) return;
	}

	RedirectInput(input);

	if (!option.empty() && option.rfind("-n", 0) == 0) {
		int n = stoi(option.substr(2, option.length() - 2));
		if (n > 0 && n < 100000) {
			std::istringstream stream(input);
			std::string line;
			std::string output;
			for (int i = 0; i < n; i++) {
				if (std::getline(stream, line)) {
					output += line + "\n";
				}
				else {
					break;
				}
			}
			if (output.back() == '\n') {
				output.pop_back();
			}
			RedirectOutput(output);
		}
		else {
			std::cerr << "Error: n count is either smaller than 1 or bigger than 99999" << std::endl;
		}
	}
	else {
		std::cerr << "Error: Missing option -n<count>" << std::endl;
	}
}

void Head::print() {

}
