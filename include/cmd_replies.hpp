#ifndef COMMANDREPLIES_HPP
# define COMMANDREPLIES_HPP

# define RPL_WELCOME(nick) (":Welcome to the DeadProtChat Network, " + nick)										//1
# define RPL_YOURHOST(servername, version) (":Your host is " + servername + ", running version " + version) 		//2
# define RPL_CREATED(date) (":This server was created " + date)														//3
# define RPL_MYINFO(servername, version, usr_modes, chann_modes) (":" + servername + " " + version + " " + usr_modes + " " + chann_modes) //4
# define RPL_UMODEIS(modes) ("+" + modes)																			//221
# define RPL_AWAY(pseudo, str) (pseudo + " :" + str)																//301
# define RPL_UNAWAY() (":You are no longer marked as being away")													//305
# define RPL_NOWAWAY() (":You have been marked as being away")														//306
# define RPL_WHOISUSER(nick, user, host, realname) (nick + " " + user + " " + host + " * :" + realname) 			//311
# define RPL_WHOISOPERATOR(pseudo) (pseudo + " :is an IRC operator")												//313
# define RPL_ENDOFWHO(name) (name + " :End of WHO list")															//315
# define RPL_WHOISIDLE(pseudo, idle, signon) (pseudo + " " + idle + " " + signon + " :seconds idle, signon time")	//317
# define RPL_ENDOFWHOIS(pseudo) (pseudo + " :End of /WHOIS list")													//318
# define RPL_LIST(channel, visiblenb, topic) (channel + " " + visiblenb + " :" + topic)								//322
# define RPL_LISTEND() (":End of LIST")																				//323	
# define RPL_CHANNELMODEIS(channel, mode, params) (channel + " +" + mode + " " + params)							//324
# define RPL_NOTOPIC(channel) (channel + " :No topic is set")														//331
# define RPL_TOPIC(channel, topic) (channel + " :" + topic)															//332
# define RPL_INVITING(nick, channel) (nick + " " + channel)															//341
# define RPL_NAMREPLY(channel, nick_list) ("= " + channel + " :" + nick_list)										//353
# define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list")													//366
# define RPL_MOTD(message) (":- " + message)																		//372
# define RPL_MOTDSTART(server) (":- " + server + " Message of the day")												//375
# define RPL_ENDOFMOTD() (":End of MOTD command")																	//376
# define RPL_YOUREOPER() (" :You are now an IRC Operator")															//381

# define CODE_RPL_WELCOME 		1
# define CODE_RPL_YOURHOST 		2
# define CODE_RPL_CREATED 		3
# define CODE_RPL_MYINFO 		4
# define CODE_RPL_UMODEIS		221
# define CODE_RPL_AWAY 			301
# define CODE_RPL_UNAWAY 		305
# define CODE_RPL_NOWAWAY 		306
# define CODE_RPL_WHOISUSER 	311
# define CODE_RPL_WHOISOPERATOR 313
# define CODE_RPL_ENDOFWHO 		315
# define CODE_RPL_WHOISIDLE 	317
# define CODE_RPL_ENDOFWHOIS 	318
# define CODE_RPL_LIST			321
# define CODE_RPL_LISTEND		322
# define CODE_RPL_CHANNELMODEIS 324
# define CODE_RPL_NOTOPIC 		331
# define CODE_RPL_TOPIC 		332
# define CODE_RPL_INVITING		341
# define CODE_RPL_NAMREPLY 		353
# define CODE_RPL_ENDOFNAMES 	366
# define CODE_RPL_MOTD		 	372
# define CODE_RPL_MOTDSTART 	375
# define CODE_RPL_ENDOFMOTD 	376
# define CODE_RPL_YOUREOPER 	381



#endif