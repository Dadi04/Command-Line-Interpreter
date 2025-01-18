#include "Parser.h"
#include <iostream>

Parser::ParsedCommand Parser::parseCommand(std::string input) {
	ParsedCommand parsedCommand;
	int i = 0;

	skipWhiteSpace(input, i);

	parsedCommand.commandName = readToken(input, i);

	skipWhiteSpace(input, i);

	if (i < input.length() && input[i] == '-') {
		parsedCommand.commandOpt = readToken(input, i);
	}

	skipWhiteSpace(input, i);

	if (i < input.length()) {
		parsedCommand.commandArg = readArgument(input, i);
	}

	return parsedCommand;
}

void Parser::skipWhiteSpace(std::string input, int& i) {
	while (i < input.length() && (std::isspace(input[i]) || input[i] == '\t')) {
		i++;
	}
}

std::string Parser::readToken(std::string input, int& i) {
	std::string token;
	while (i < input.length() && !std::isspace(input[i]) && input[i] != '\t') {
		token += input[i];
		i++;
	}
	return token;
}

std::string Parser::readArgument(std::string input, int& i) {
	std::string token;

	if (i >= input.length() || input[i] != '"') {
		return token;
	}

	i++;

	while (i < input.length()) {
		if (input[i] == '"' && (i + 1 >= input.length() || input[i + 1] == ' ')) {
			break;
		}
		token += input[i];
		i++;
	}

	if (i < input.length() && input[i] == '"') {
		i++;
	}

	return "\"" + token + "\"";
}
