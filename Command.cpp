#include "Command.h"
#include <iostream>
#include <fstream>
#include <ctime>

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
