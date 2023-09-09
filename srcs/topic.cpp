#include "Server.hpp"

// ...

void Server::topic(User* sender, Command* cmd) {
    // Vérifie que l'utilisateur est bien enregistré
    if (sender->getStatus() != User::ONLINE) {
        sender->sendMsg("451 ERR_NOTREGISTERED :You have not registered\r\n");
        return;
    }

    // Vérifie que les paramètres de la commande sont corrects
    if (cmd->getParameters().size() < 1) {
        sender->sendMsg("461 ERR_NEEDMOREPARAMS :Not enough parameters\r\n");
        return;
    }

    std::string channelName = cmd->getParameters()[0];

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

    if (cmd->getParameters().size() == 1)
    {
        if (!channel->getTopic())
            {
                sender->sendMsg("331 " + channel->getName() + ": No topic is set\r\n");
                return;
            }
    }
    // Vérifie que l'utilisateur a le droit de changer le sujet (topic) du canal
    if (!channel->isOperator(sender)) {
        sender->sendMsg("482 ERR_CHANOPRIVSNEEDED :You're not channel operator\r\n");
        return;
    }

    // Obtient le nouveau sujet (topic) à définir
    std::string newTopic = cmd->getParameters()[1];

    // Définit le nouveau sujet (topic) du canal
    channel->setTopic(newTopic);

    // Informe les utilisateurs du changement de sujet (topic)
    std::string topicMessage = ":" + sender->getNickname() + " TOPIC " + channelName + " :" + newTopic + "\r\n";
    channel->sendMessageToMembers(topicMessage);
}
