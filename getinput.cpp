/**
 * CS-11
 * @file getinput.cpp
 * Purpose: Get values from stdin in a user friendly manner
 *
 * @author Galen Asphaug
 * @version 1.0 10/25/17
 */

#include <climits> //INT_MAX
#include "getinput.hpp"

int GetInput::getInt(std::string prompt, int min, int max) {
    if (min > max) { //check for bad programmers
    		std::cout << "getInt Error: min > max\n";
        exit(1);
    }
    int value = 0;
    while (true) {
        GetInput::prompt(prompt);
        if (std::cin >> value) { //read and check if cin is still good
            if (value >= min && value <= max) { //if within limits, use it
                return value;
            }
        } else if (std::cin.eof()) { //if ctrl-d
        		std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
        		std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}

int GetInput::getInt(int min, int max) {
    if (min > max) { //check for bad programmers
        std::cout << "getInt Error: min > max\n";
        exit(1);
    }
    int value = 0;
    while (true) {
        if (std::cin >> value) { //read and check if cin is still good
            if (value >= min && value <= max) { //if within limits, use it
                return value;
            }
        } else if (std::cin.eof()) { //if ctrl-d
            std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
        		std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}

int GetInput::getInt(std::string prompt) {
    int value = 0;
    while (true) {
        GetInput::prompt(prompt);
        if (std::cin >> value) { //read and check if cin is still good
            return value;
        } else if (std::cin.eof()) { //if ctrl-d
            std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
        		std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}

int GetInput::getInt() {
    int value = 0;
    while (true) {
        if (std::cin >> value) { //read and check if cin is still good
            return value;
        } else if (std::cin.eof()) { //if ctrl-d
            std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
        		std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}


char GetInput::getChar(std::string prompt) {
    char value = 0;
    while (true) {
        GetInput::prompt(prompt);
        if (std::cin >> value) { //read and check if cin is still good
            return value;
        } else if (std::cin.eof()) { //if ctrl-d
            std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
        		std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}

char GetInput::getChar() {
    char value = 0;
    while (true) {
        if (std::cin >> value) { //read and check if cin is still good
            return value;
        } else if (std::cin.eof()) { //if ctrl-d
            std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
        		std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}


std::string GetInput::getWord(std::string prompt, unsigned minLength, unsigned maxLength) {
    std::string input;
    while (true) {
        GetInput::prompt(prompt);
        if (std::cin >> input) {
            if (input.length() < minLength || input.length() > maxLength) {
                return input;
            }
        } else if (std::cin.eof()) { //if ctrl-d
            std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
        		std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}

std::string GetInput::getWord(unsigned minLength, unsigned maxLength) {
    std::string input;
    while (true) {
        if (std::cin >> input) {
            if (input.length() < minLength || input.length() > maxLength) {
                return input;
            }
        } else if (std::cin.eof()) { //if ctrl-d
            std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
        		std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}

std::string GetInput::getWord(std::string prompt) {
    std::string input;
    while (true) {
        GetInput::prompt(prompt);
        if (std::cin >> input) {
            return input;
        } else if (std::cin.eof()) { //if ctrl-d
            std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
        		std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}

std::string GetInput::getWord() {
    std::string input;
    while (true) {
        if (std::cin >> input) {
            return input;
        } else if (std::cin.eof()) { //if ctrl-d
            std::cout << "\nKeyboard interrupt\n";
            exit(1);
        } else if (std::cin.bad() || std::cin.fail()) { //if cin failed
        		std::cin.clear();
            std::cin.ignore(INT_MAX, '\n'); //ignore rest of line
        }
        std::cout << "Try again\n";
    }
}


void GetInput::prompt(std::string p) {
	std::cout << p << " :";
}
