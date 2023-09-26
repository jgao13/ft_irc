#include "../include/Server.hpp"

namespace ft
{

void Server::join(User* user, Command* cmd) {
    // Vérifier le nombre d'arguments de la commande JOIN
    if (cmd->arguments().size() == 0 ) {
        user->sendMsg("461 " + user->getNickname() + " JOIN :Not enough parameters\r\n");
        return;
    }
	//else if ( > 2) un check si superieur a 2 ?

    std::string channelName = cmd->arguments()[0];



    // Rechercher le canal par son nom
    Channel* channel = getChannelByName(channelName);
	std::string key = NULL;

	if (cmd->arguments().size() == 2)
		key = cmd->arguments()[1];
    if (!channel) {
        // Si le canal n'existe pas, le créer
        channel = new Channel(channelName);
        addChannel(channelName, channel); // Ajoutez le canal à la map
		channel->addOperator(user);
		if (!key.empty())
		{
			channel->setKey(key);
			channel->setKeyActivated(true);
		}
    }

    // Vérifier si l'utilisateur est déjà membre du canal
    if (channel->isUserMember(user))
	{
        user->sendMsg("479 " + user->getNickname() + " " + channelName + " :Already registered\r\n");
        return;
    }
    // Vérifier si le canal est invite-only
    if (channel->isInviteOnly()) {
        // Vérifier si l'utilisateur a été invité
        if (!user->isInvitedTo(channelName)) {
            user->sendMsg("473 " + user->getNickname() + " " + channelName + " :Invitation needed\r\n");
            return;
        }
    }

    // Vérifier si le canal est protégé par mot de passe (key)
    if (channel->isKeyActivated()) {
        // Vérifier si l'utilisateur a fourni le bon mot de passe
        if (key != channel->getKey()) {
            user->sendMsg("475 " + user->getNickname() + " " + channelName + " :Cannot join channel (+k)\r\n");
            return;
        }
    }

    // Ajouter l'utilisateur au canal
    channel->addUser(user);
    user->joinChannel(channel);

    // Envoyer un message de bienvenue à l'utilisateur
    user->sendMsg(":" + user->getNickname() + " JOIN " + channelName + "\r\n");

    // Informer les membres du canal de la nouvelle arrivée
    channel->sendMessageToMembers(":" + user->getNickname() + " JOIN " + channelName + "\r\n");
}
}