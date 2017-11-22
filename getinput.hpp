/**
 * CS-11
 * @file getinput.hpp
 * Purpose: Get values from stdin in a user friendly manner
 *
 * @author Galen Asphaug
 * @version 1.0 10/25/17
 */
#ifndef MD5NAME_GETINT_H
#define MD5NAME_GETINT_H

#include <iostream>

class GetInput {
public:

    /**
     * Gets a integer value from stdin in a user friendly manner
     * @param prompt The string to print (not including a " :")
     * @param min The minimum integer value to allow
     * @param max The maximum integer value to allow
     * @return user entered integer between min and max
     */
    static int getInt(std::string prompt, int min, int max);

    static int getInt(int min, int max);

    static int getInt(std::string p);

    static int getInt();

    /**
     * Gets a double value from stdin in a user friendly manner
     * @param prompt The string to print (not including a " :")
     * @param min The minimum double value to allow
     * @return user entered double between min and max
     */
    static double getDouble(std::string prompt, double min);

    /**
     * Gets a char value from stdin in a user friendly manner
     * @param prompt The string to print (not including a " :")
     * @return single user entered char
     */
    static char getChar(std::string prompt);

    static char getChar();

    /**
     * Gets a single word from the user (not a line, no whitespace)
     * @param prompt The string to print (not including a " :")
     * @param minLength The minimum string length to allow
     * @param maxLength The maximum string length to allow
     * @return the user entered string with length between minLength and maxLength
     */
    static std::string getWord(std::string prompt, unsigned minLength, unsigned maxLength);

    static std::string getWord(unsigned minLength, unsigned maxLength);

    static std::string getWord(std::string prompt);

    static std::string getWord();

private:
    /**
     * Print a prompt to the user
     * @param p prompt
     */
    static void prompt(std::string p);
};

#endif //MD5NAME_GETINT_H
