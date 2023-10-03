#include "../include/Server.hpp"
namespace ft
{

    //faut aussi check pour le channel
    
void Server::whois(User* sender, Command* cmd) {
    // Vérifiez que la commande a des paramètres
    if (cmd->arguments().size() < 1) {
        sender->sendMsg("461 ERR_NEEDMOREPARAMS :Not enough parameters\r\n");
        return;
    }

    // Récupérez le nom de l'utilisateur cible à partir des paramètres de la commande
    std::string targetName = cmd->arguments()[0];

    // Recherchez l'utilisateur cible
    User* targetUser = getUserByName(targetName);

    // Vérifiez si l'utilisateur cible existe
    if (!targetUser) {
        sender->sendMsg("401 ERR_NOSUCHNICK :No such nick/channel\r\n");
        return;
    }

    // Construisez et envoyez les informations WHOIS
    std::string response = "311 " + sender->getNickname() + " " + targetUser->getNickname() + " " +
                          targetUser->getUsername() + " " + targetUser->hostname() + " * :" + targetUser->getFirstName() + "\r\n";
    sender->sendMsg(response);

    // Vous pouvez ajouter plus d'informations WHOIS ici, en fonction de vos besoins.

    // Envoyez la réponse finale de fin de WHOIS
    sender->sendMsg("318 " + sender->getNickname() + " " + targetUser->getNickname() + " :End of WHOIS list\r\n");
}
}