#include "../include/Server.hpp"

//cmd->arguments()[1] est vide alors qu'il devrait avoir des arguments ???

namespace ft
{
// void Server::topic(User* sender, Command* cmd) {
//     // Vérifie que l'utilisateur est bien enregistré
//     // if (sender->printStatus() != "REGISTER") {
//     //     sender->sendMsg("451 ERR_NOTREGISTERED :You have not registered\r\n");
//     //     return;
//     // }

//     // Vérifie que les paramètres de la commande sont corrects
//     if (cmd->arguments().size() < 1) {
//         sender->sendMsg("461 ERR_NEEDMOREPARAMS :Not enough parameters\r\n");
//         return;
//     }

//     std::string channelName = cmd->arguments()[0];

//     // Vérifie que le canal existe
//     Channel* channel = getChannelByName(channelName);
//     if (!channel) {
//         sender->sendMsg("403 ERR_NOSUCHCHANNEL :No such channel\r\n");
//         return;
//     }

//     // Vérifie que l'utilisateur est membre du canal
//     if (!channel->isUserMember(sender)) {
//         sender->sendMsg("442 ERR_NOTONCHANNEL :You're not on that channel\r\n");
//         return;
//     }

//     if (cmd->arguments().size() == 1)
//     {
//         std::string test = channel->getTopic();
//         if (test.empty())
//             {
//                 sender->sendMsg("331 " + channel->getName() + ": No topic is set\r\n");
//                 return;
//             }
//         else 
//         {
//             sender->sendMsg("332 " + channel->getName() + " :" + channel->getTopic());
//             return ;
//         }
//     }
//     // Vérifie que l'utilisateur a le droit de changer le sujet (topic) du canal
//     if (!channel->isOperator(sender) && channel->isTopicProtected() == true) {
//         sender->sendMsg("482 ERR_CHANOPRIVSNEEDED :You're not channel operator\r\n");
//         return;
//     }

//     // Obtient le nouveau sujet (topic) à définir
//     if (cmd->arguments().size() == 2)
//     {
//         std::string newTopic = cmd->arguments()[1];
//         std::cout << "cmd->arg()[1] = " << cmd->arguments()[0] << std::endl;

//     // Définit le nouveau sujet (topic) du canal
//         channel->setTopic(newTopic);
//         std::cout << "topic actuel ?" << newTopic << std::endl;
//     }
//     // Informe les utilisateurs du changement de sujet (topic)
//     std::string topicMessage = ":" + sender->getNickname() + " TOPIC " + channelName + " :" + channel->getTopic() + "\r\n";
//     channel->sendMessageToMembers(topicMessage);
// }


/////////////////////////////////
// ok donc la le message prend en compte le new il faut que je l'enleve. (substr ?)

void Server::topic(User* sender, Command* cmd)
{
    cmd->print_command();
    // if (cmd->arguments().empty()) {
    //     // Aucun argument n'est fourni, vérifiez si l'utilisateur est dans un canal
    //     Channel* userChannel = sender->getCurrentChannel(sender);

    //     if (userChannel) {
    //         std::string topic = userChannel->getTopic();
    //         if (!topic.empty()) {
    //             sender->sendMsg("332 " + sender->getNickname() + " " + userChannel->getName() + " :" + topic + "\r\n");
    //         } else {
    //             sender->sendMsg("331 " + sender->getNickname() + " " + userChannel->getName() + " :No topic is set\r\n");
    //         }
    //     } else {
    //         sender->sendMsg("461 " + sender->getNickname() + " TOPIC :Not enough parameters\r\n");
    //     }
    //     return;
    // }
    //comportement bizarre : /topic = size arg a 1 /topic new = size arg 1 / /topic chan phrASE = arg 2

    //if (cmd->arguments().size() < 1) {
    if (cmd->arguments()[0].empty())
    {
        // Insuffisamment d'arguments, envoie un message d'erreur
        sender->sendMsg("461 " + sender->getNickname() + " TOPIC :Not enough parameters\r\n");
        return;
    }

    //std::cout << "nb of arg fct topic ? " << cmd->arguments().size() << std::endl;
    //std::cout << cmd->arguments()[0] << "\n\n";
    std::string channelName = cmd->arguments()[0];
    std::string newTopic = cmd->message();
    Channel* channel = getChannelByName(channelName);

    if (!channel) {
        // Le canal n'existe pas, envoie un message d'erreur
        sender->sendMsg("403 " + sender->getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }

    if (!channel->isUserMember(sender)) {
        // L'utilisateur n'est pas membre du canal, envoie un message d'erreur
        sender->sendMsg("442 " + sender->getNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }

    // Vérifie si l'utilisateur a le droit de modifier le sujet (operator ou si le sujet n'est pas protégé)
    if (!channel->isOperator(sender) && channel->isTopicProtected()) {
        // L'utilisateur n'a pas le droit de modifier le sujet protégé
        sender->sendMsg("482 " + sender->getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }
    if (cmd->arguments().size() == 2)
    {
        if (newTopic.empty()) {
        // L'utilisateur veut effacer le sujet
            channel->setTopic("");
        } else {
        // Mettez à jour le sujet du canal
            channel->setTopic(newTopic);
        }
    }
    // Envoyez un message de confirmation à tous les membres du canal
    std::string message = ":" + sender->getNickname() + " TOPIC " + channelName + " :" + newTopic + "\r\n";
    channel->sendMessageToMembers(message);
}
}