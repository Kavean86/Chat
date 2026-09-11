/*
 * Terminal color definitions
 * Provides ANSI escape codes used for colored
 * output messages in the chat server.
 */
#pragma once
#include <iostream>
#include <string>
using std::string;

const string PURPLE  = "\033[35m";
const string YELLOW = "\033[33m";
const string RED   = "\033[31m";
const string BLUE  = "\033[36m";
const string RESET = "\033[0m";
const string WHITE = "\033[37m";
const string GRAY = "\033[90m";

