#pragma once

#include "Utils.hpp"
// Define command and error strings used by message builder
#include "cmd_err_replies.hpp"
#include "cmd_replies.hpp"
#include "Server.hpp"

// Va falloir pouvoir dire pk ya 4 arg potentiellement!

namespace ft
{
	std::string		commandMessageBuilder(
		const	short code, 
		User * user, 
		std::string const arg1 = std::string(), 
		std::string const arg2 = std::string(), 
		std::string const arg3 = std::string(), 
		std::string const arg4 = std::string());
		
	std::string		userMessageBuilder(User * user, std::string content);
	std::string		serverMessageBuilder(Server * server, std::string content);

}


/*
	NOTES: Message formatters should be included and restricted inside a specific class,
	but I'm a bit lazy and don't know yet what part of the program specifically will 
	need it.
*/