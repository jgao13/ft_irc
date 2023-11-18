/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnr <lnr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:18:23 by lnr               #+#    #+#             */
/*   Updated: 2023/10/11 21:18:24 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

int User::_cmd_JOIN(Msg & cmd) // ----------------------------------------- JOIN
{
	str_vec arg = cmd.payloadAsVector(2, 1); //
	if (arg.size() < 1)
		return (rpl(ERR_NEEDMOREPARAMS, "JOIN"));

	str_vec ChannelNames;
	while (!arg[0].empty())
		ChannelNames.push_back(extract_first_word(arg[0], ','));
// on peut donner une liste de channel a rejoindre separer par des virgule et une liste de mdp aussi separer par des virgules
//une fonction split "," peut etre utiliser pour te faire une liste/vector d'arguments
	str_vec Key;
	if (arg.size() == 2)
		while (!arg[1].empty())
			Key.push_back(extract_first_word(arg[1], ','));
//mdp est optionnel mais meme chose aue pour channel name si present
	str_vec::iterator keyIt = Key.begin();
	str_vec::iterator it;
	for (it = ChannelNames.begin(); it != ChannelNames.end(); it++) {

		Chan *channel = _serv->getChan(*it);

//verifier si channel existant sinon le creer
		if (!channel) {
			if (!is_valid_name(*it) || !is_name_chan(*it))
				rpl(ERR_BADCHANNAME, *it);
			else {
				channel = _serv->addChan(*it);
				channel->opMode(this, 1);
			}
		}
		//on verifie si le user est dans le chan, si il est inviter si mode i activer,si mode k verifier que mdp correct, i mode L si chan est rempli
		//si toute les condition son bonne, msg a tous les user du chan et ajouter la personne (penser a ajouter sa liste de chan etc) et pour le user lui renvoyer le topic
		if (channel) {
			if (channel->getUser(_nick))
				;
			else if (channel->checkMode(MODE_I) && !channel->isInvited(this))
				rpl(ERR_INVITEONLYCHAN, *it);
			else if (channel->checkMode(MODE_K) && (keyIt == Key.end() || !channel->checkPasswd(*keyIt)))
				rpl(ERR_BADCHANNELKEY, *it);
			else if (channel->checkMode(MODE_L) && channel->isFull())
				rpl(ERR_CHANNELISFULL, *it);
			else {
				channel->addUser(this);
				_chans[*it] = channel;
				channel->chan_send(Msg(_pref, "JOIN", ":" + *it));
				if (channel->getTopic() != "")
					rpl(RPL_TOPIC, *it + " :" + channel->getTopic());
				Msg msg("", "", *it);
				_cmd_NAMES(msg);
			}
		}
		if (keyIt != Key.end())
			keyIt++; //mdp 1 est pour channel 1, 2 pour chan 2 etc
	}
	return (0);
}