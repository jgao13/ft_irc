#ifndef CMD_ERR_REPLIES
# define CMD_ERR_REPLIES

/*
 	ERROR CODES
*/
# define CODE_ERR_NOSUCHNICK 		401
# define CODE_ERR_NOSUCHSERVER 		402
# define CODE_ERR_NOSUCHCHANNEL 	403
# define CODE_ERR_CANNOTSENDTOCHAN 	404
# define CODE_ERR_NORECIPIENT 		411
# define CODE_ERR_NOTEXTTOSEND 		412
# define CODE_ERR_UNKNOWNCOMMAND 	421
# define CODE_ERR_NOMOTD		 	422
# define CODE_ERR_NONICKNAMEGIVEN 	431
# define CODE_ERR_ERRONEUSNICKNAME 	432
# define CODE_ERR_NICKNAMEINUSE 	433
# define CODE_ERR_USERNOTINCHANNEL	441
# define CODE_ERR_NOTONCHANNEL		442
# define CODE_ERR_USERONCHANNEL		443
# define CODE_ERR_NOTREGISTERED 	451
# define CODE_ERR_NEEDMOREPARAMS 	461
# define CODE_ERR_ALREADYREGISTRED	462
# define CODE_ERR_PASSWDMISMATCH	464
# define CODE_ERR_UNKNOWNMODE		472
# define CODE_ERR_INVITEONLYCHAN	473
# define CODE_ERR_NOPRIVILEGES		481
# define CODE_ERR_CHANOPRIVSNEEDED	482
# define CODE_ERR_RESTRICTED 		484
# define CODE_ERR_NOOPERHOST 		491
# define CODE_ERR_UMODEUNKNOWNFLAG 	501
# define CODE_ERR_USERSDONTMATCH 	502




# define ERR_NOSUCHNICK(nick) (nick + " :No such nick/channel")														//401
# define ERR_NOSUCHSERVER(server) (server + " :No such server")														//402
# define ERR_NOSUCHCHANNEL(channel) (channel + " :No such channel")													//403
# define ERR_CANNOTSENDTOCHAN(channel) (channel + " :Cannot send to channel")										//404
# define ERR_NORECIPIENT(command) (":No recipient given " + command)												//411
# define ERR_NOTEXTTOSEND() ":No text to send"																		//412
# define ERR_UNKNOWNCOMMAND(command) (command + " :Unknown command")												//421
# define ERR_NOMOTD() (" :MOTD File is missing")																	//422
# define ERR_NONICKNAMEGIVEN() ":No nick given"																		//431
# define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname")													//433
# define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use")											//433
# define ERR_USERNOTINCHANNEL(nick, channel) (nick + " " + channel + " :They aren't on that channel")				//441
# define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel");										//442
# define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel")						//443
# define ERR_NOTREGISTERED() ":You have not registered"																//451
# define ERR_NEEDMOREPARAMS(command)  (command + " :Not enough parameters")											//461
# define ERR_ALREADYREGISTRED() ":Unauthorized command (already registered)"										//462
# define ERR_PASSWDMISMATCH() (":Password incorrect")																//464
# define ERR_UNKNOWNMODE(c, channel) (c + " :is unknown mode char to me for " + channel)							//472
# define ERR_INVITEONLYCHAN(channel) (channel + ":Cannot join channel (+i)")										//473
# define ERR_NOPRIVILEGES() (":Permission Denied- You're not an IRC operator")										//481
# define ERR_CHANOPRIVSNEEDED(channel) (channel + ":You're not channel operator")									//482
# define ERR_RESTRICTED() (":Your connection is restricted!")														//484
# define ERR_NOOPERHOST() (":No 0-lines for your host")																//491
# define ERR_UMODEUNKNOWNFLAG() (":Unknown MODE flag")																//501
# define ERR_USERSDONTMATCH(nick) (nick + ":Cant change mode for other users")										//502

#endif