#include "../include/Server.hpp"

namespace ft
{
    void    Server::privmsg(User *sender, Command *cmd)
    {
        //arg < 2 ou 0 vide ou 1 vide, coller les arguments pour faire une phrase
        if (cmd->arguments().size() < 2 || cmd->arguments()[0].empty() || cmd->arguments()[1].empty())
        {
            sender->sendMsg("411 " + sender->getNickname() + " :No recipient given (PRIVMSG)\r\n");
            return ;
        }
        cmd->print_command();
        std::string target = cmd->arguments()[0];
        std::string message = cmd->arguments()[1]; //va surement falloir changer par message


        Channel* targetChannel = getChannelByName(target);
        if (targetChannel)
        {
            targetChannel->sendMessageToMembers(":" + sender->getNickname() + " PRIVMSG " + targetChannel->getName() + " :" + message +"\r\n");
        }
        else
        {
        //std::cout << "segfault a else ? \n\n";

            User *targetUser = getUserByName(target);

            if (targetUser)
                targetUser->sendMsg(":" + sender->getNickname() + "PRIVMSG " + targetUser->getNickname() + " :" + message + "\r\n");
            else
                sender->sendMsg("401 " + sender->getNickname() + " " + target + " :No such nick/channel\r\n");
        }
    }
}