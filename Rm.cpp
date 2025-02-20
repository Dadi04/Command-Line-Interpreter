#include "Command.h"
#include <iostream>
#include <fstream>

void Rm::execute() {
	ifBufferNotEmpty();

	RedirectInput(argument);

	if (!argument.empty() && argument.front() == '"' && argument.back() == '"') {
		argument = argument.substr(1, argument.size() - 2);
	}
	else if (argument.empty()) {
		std::cerr << "Error: Command needs an argument. Its format is: rm argument" << std::endl;
		return;
	}

	std::ifstream file(argument);
	if (!file) {
		std::cerr << "Error: File \"" << argument << "\" does not exist." << std::endl;
		file.close();
	}
	else {
		file.close();
		int status = remove(argument.c_str());
		if (status == 0) {
			std::cout << "File \"" << argument << "\" deleted successfully." << std::endl;
		}
		else {
			std::cerr << "Error: Failed to delete \"" << argument << "\"." << std::endl;
		}
	}
}