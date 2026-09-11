/*
 * Chat command help menu
 * Contains the list of available commands and
 * usage instructions displayed to connected clients.
 */
#pragma once
#include <iostream>
#include <string>
using std::string;

string helpman=GRAY+"Wellcome to HELPMAN\n"
"\tCommands:\n"
"HELPMAN\n"
"\tShow this help menu.\n"
"Exit\n"
"\tLeave the chat.\n"
"CLEAR\n"
"\tClear the screen.\n"
"ONLINE\n"
"\tShow online users.\n"
"TIME\n"
"\tShow current server time."
"\nRULES:\n"
"\t- Messages are sent by pressing Enter.\n"
"\t- Your messages are purple.\n"
"\t- Messages from other users are cyan.\n"
"\t- Join/Leave notifications are yellow.\n"
"\t- Errors are shown in red.\n"+PURPLE;

