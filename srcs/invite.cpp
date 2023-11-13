#include "../include/Server.hpp"

namespace ft{
void Server::invite(User* sender, Command* cmd) {
    // Vérifie que l'utilisateur est bien enregistré
    if (sender->printStatus() != "REGISTER") {
        sender->sendMsg("451 ERR_NOTREGISTERED :You have not registered\r\n");
        return;
    }

    // Vérifie que les paramètres de la commande sont corrects
    if (cmd->arguments().size() < 2) {
        sender->sendMsg("461 ERR_NEEDMOREPARAMS :Not enough parameters\r\n");
        return;
    }

    std::string targetUserName = cmd->arguments()[0];
    std::string channelName = cmd->arguments()[1];

    // Vérifie que l'utilisateur cible existe
    User* targetUser = getUserByName(targetUserName);
    if (!targetUser) {
        sender->sendMsg("401 ERR_NOSUCHNICK :No such nick\r\n");
        return;
    }

    // Vérifie que le canal existe
    Channel* channel = getChannelByName(channelName);
    if (!channel) {
        sender->sendMsg("403 ERR_NOSUCHCHANNEL :No such channel\r\n");
        return;
    }

    // Vérifie que l'utilisateur est membre du canal
    if (!channel->isUserMember(sender)) {
        sender->sendMsg("442 ERR_NOTONCHANNEL :You're not on that channel\r\n");
        return;
    }

    // Vérifie que l'utilisateur cible n'est pas déjà membre du canal
    if (channel->isUserMember(targetUser)) {
        sender->sendMsg("443 ERR_USERONCHANNEL :is already on channel\r\n");
        return;
    }

    // Envoyer une invitation à l'utilisateur cible
    std::string inviteMessage = ":" + sender->getNickname() + " INVITE " + targetUserName + " " + channelName + "\r\n";
    targetUser->sendMsg(inviteMessage);
}
}