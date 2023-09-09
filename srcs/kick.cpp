#include "../include/Server.hpp"

namespace ft
{
	void	Server::kick(User *sender, Command * cmd)
	{
    // Vérifie que l'utilisateur est bien enregistré
        if (sender->getStatus() != User::ONLINE) {
            sender->sendMsg("451 ERR_NOTREGISTERED :You have not registered\r\n");
            return;
        }

    // Vérifie que les paramètres de la commande sont corrects
        if (cmd->getParameters().size() < 2) {
            sender->sendMsg("461 ERR_NEEDMOREPARAMS :Not enough parameters\r\n");
            return;
        }

        std::string channelName = cmd->getParameters()[0];
        std::string targetUserName = cmd->getParameters()[1];

    // Vérifie que le canal existe
        Channel *channel = getChannelByName(channelName);
        if (!channel) {
            sender->sendMsg("403 ERR_NOSUCHCHANNEL :No such channel\r\n");
            return;
        }

    // Vérifie que l'utilisateur est membre du canal
        if (!channel->isUserMember(sender)) {
            sender->sendMsg("442 ERR_NOTONCHANNEL :You're not on that channel\r\n");
            return;
        }

    // Vérifie que l'utilisateur a le droit de kicker
        if (!channel->isOperator(sender)) {
            sender->sendMsg("482 ERR_CHANOPRIVSNEEDED :You're not channel operator\r\n");
            return;
        }

    // Vérifie que l'utilisateur cible existe
        User *targetUser = getUserByName(targetUserName);
        if (!targetUser) {
            sender->sendMsg("401 ERR_NOSUCHNICK :No such nick\r\n");
            return;
        }

    // Vérifie que l'utilisateur cible est bien sur le canal
        if (!channel->isUserMember(targetUser)) {
            sender->sendMsg("441 ERR_USERNOTINCHANNEL :They aren't on that channel\r\n");
            return;
        }

        // Effectue le kick
        channel->removeUser(targetUser);
        targetUser->sendMsg("KICK " + channelName + " :You have been kicked by " + sender->getNickname() + "\r\n");
        // Envoyez également un message aux autres membres du canal pour les informer
        std::string kickMessage = ":" + sender->getNickname() + " KICK " + channelName + " " + targetUserName + "\r\n";
        channel->sendMessageToMembers(kickMessage);
    }
}