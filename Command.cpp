#include "Command.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

// metoda koja odredjuje da li je argument string ili file
std::string Command::getArgumentType() {
	std::string input;
	if (!argument.empty()) {
		if (argument.front() == '"' && argument.back() == '"') {
			input = argument.substr(1, argument.size() - 2);
		}
		else {
			std::ifstream file(argument);
			if (file.is_open()) {
				std::string line;
				while (std::getline(file, line)) {
					input += line + '\n';
				}
				if (!input.empty() && input.back() == '\n') {
					input.pop_back();
				}
				file.close();
			}
			else {
				std::cerr << "Error: File \"" << argument << "\" could not be opened.";
			}
		}
	}
	return input;
}

std::string Command::ifArgumentEmpty() {
	if (argument.empty()) {
		std::string line;
		while (true) {
			if (!std::getline(std::cin, line)) break;
			argument += line + '\n';
		}
	}

	return argument;
}

void Echo::execute() {
	std::string input;
	if (argument.empty()) {
		input = ifArgumentEmpty();
	}
	else {
		input = getArgumentType();
	}

	if (input.back() == '\n') {
		input.pop_back();
	}

	std::cout << input << std::endl;
}

void Prompt::execute() {
	this->promptSign = argument + " ";
}

std::string Prompt::promptSign = "$ ";
std::string Prompt::getPromptSign() {
	return promptSign;
}

void Time::execute() {
	time_t timestamp;
	time(&timestamp);
	struct tm currentTime;

	if (localtime_s(&currentTime, &timestamp) == 0) {
		char timeString[9];
		strftime(timeString, sizeof(timeString), "%H:%M:%S", &currentTime);

		std::cout << timeString << std::endl;
	}
}

void Date::execute() {
	time_t timestamp;
	time(&timestamp);
	struct tm currentDate;

	if (localtime_s(&currentDate, &timestamp) == 0) {
		char dateString[11];
		strftime(dateString, sizeof(dateString), "%d.%m.%Y", &currentDate);

		std::cout << dateString << std::endl;
	}
}

void Touch::execute() {
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

void Truncate::execute() {
	std::ifstream file(argument);
	if (!file) {
		std::cerr << "Error: File \"" << argument << "\" does not exist." << std::endl;
		file.close();
	}
	else {
		std::ofstream file(argument, std::ios::trunc);
		if (file.is_open()) {
			std::cout << "File content cleared successfully." << std::endl;
			file.close();
		}
		else {
			std::cerr << "Error: Failed to open \"" << argument << "\"." << std::endl;
		}
	}
	
}

void Rm::execute() {
	std::ifstream file(argument);
	if (!file) {
		std::cerr << "Error: File \"" << argument << "\" does not exist." << std::endl;
		file.close();
	}
	else {
		file.close();
		int status = remove(argument.c_str());
		if (status == 0) {
			std::cout << "File deleted successfully." << std::endl;
		}
		else {
			std::cerr << "Error: Failed to delete \"" << argument << "\"." << std::endl;
		}
	}
}

void Wc::execute() {
	std::string input;
	if (argument.empty()) {
		input = ifArgumentEmpty();
	}
	else {
		input = getArgumentType();
	}

	if (option == "-w") {
		int wordCount = 0;
		bool inWord = false;
		for (int i = 0; i < input.length(); i++) {
			if (std::isspace(input[i])) {
				wordCount++;
				inWord = false;
			}
			else {
				inWord = true;
			}
		}
		if (inWord) {
			wordCount++;
		}

		std::cout << wordCount << std::endl;
	}
	else if (option == "-c") {
		std::cout << input.length() << std::endl;
	}
}

//void Tr::execute() {
//
//}

void Head::execute() {
	std::string input;
	if (argument.empty()) {
		input = ifArgumentEmpty();
	}
	else {
		input = getArgumentType();
	}

	if (!option.empty()) {
		int n = stoi(option.substr(2, option.length() - 2));
		if (n > 0 && n < 100000) {
			std::istringstream stream(input);
			std::string line;
			for (int i = 0; i < n; i++) {
				if (std::getline(stream, line)) {
					std::cout << line << std::endl;
				}
				else {
					break;
				}
			}
		}
		else {
			std::cerr << "Error: n count is either smaller than 1 or bigger than 99999" << std::endl;
		}
	}
	else {
		std::cerr << "Error: Missing option -n<count>" << std::endl;
	}
}

void Batch::execute() {
	std::string input;
	if (argument.empty()) {
		input = ifArgumentEmpty();
	}
	else {
		input = getArgumentType();
	}

	
}
