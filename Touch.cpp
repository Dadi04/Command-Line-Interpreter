#include "Command.h"
#include <iostream>
#include <fstream>

void Touch::execute() {
	ifBufferNotEmpty();

	RedirectInput(argument);

	if (!argument.empty() && argument.front() == '"' && argument.back() == '"') {
		argument = argument.substr(1, argument.size() - 2);
	}
	else if (argument.empty()) {
		std::cerr << "Error: Command needs an argument. Its format is: touch argument" << std::endl;
		return;
	}

	std::ifstream file(argument);
	if (file) {
		std::cerr << "Error: File \"" << argument << "\" already exists." << std::endl;
	}
	else {
		std::ofstream newFile(argument);
		if (newFile) {
			newFile.close();
			std::cout << "File \"" << argument << "\" created successfully." << std::endl;
		}
		else {
			std::cerr << "Error: File \"" << argument << "\" could not be created." << std::endl;
		}
	}
}