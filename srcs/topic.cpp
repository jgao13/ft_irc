#include "../include/Server.hpp"

namespace ft
{
void Server::topic(User* sender, Command* cmd) {
    // Vérifie que l'utilisateur est bien enregistré
    if (sender->printStatus() != "REGISTER") {
        sender->sendMsg("451 ERR_NOTREGISTERED :You have not registered\r\n");
        return;
    }

    // Vérifie que les paramètres de la commande sont corrects
    if (cmd->arguments().size() < 1) {
        sender->sendMsg("461 ERR_NEEDMOREPARAMS :Not enough parameters\r\n");
        return;
    }

    std::string channelName = cmd->arguments()[0];

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

    if (cmd->arguments().size() == 1)
    {
        std::string test = channel->getTopic();
        if (test.empty())
            {
                sender->sendMsg("331 " + channel->getName() + ": No topic is set\r\n");
                return;
            }
        else 
        {
            sender->sendMsg("332 " + channel->getName() + " :" + channel->getTopic()); //pas sur qu'il faut que sa d'ecrit
            return ; //sendmessage plus que std::cout la
        }
    }
    // Vérifie que l'utilisateur a le droit de changer le sujet (topic) du canal
    if (!channel->isOperator(sender) && channel->isTopicProtected() == true) {
        sender->sendMsg("482 ERR_CHANOPRIVSNEEDED :You're not channel operator\r\n");
        return;
    }

    // Obtient le nouveau sujet (topic) à définir
    std::string newTopic = cmd->arguments()[1];

    // Définit le nouveau sujet (topic) du canal
    channel->setTopic(newTopic);

    // Informe les utilisateurs du changement de sujet (topic)
    std::string topicMessage = ":" + sender->getNickname() + " TOPIC " + channelName + " :" + newTopic + "\r\n";
    channel->sendMessageToMembers(topicMessage);
}
}