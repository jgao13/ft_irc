/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnr <lnr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:18:42 by lnr               #+#    #+#             */
/*   Updated: 2023/10/11 21:18:43 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

int User::_cmd_INVITE(Msg & cmd) //-------------------------------------- INVITE
{
	str_vec arg = cmd.payloadAsVector(2, 1);
	if (arg.size() < 2)
		return (rpl(ERR_NEEDMOREPARAMS, "INVITE"));

	User *target = _serv->getUser(arg[0]);
	if (!target)
		return (rpl(ERR_NOSUCHNICK, arg[0]));

	Chan *channel = _serv->getChan(arg[1]);
	if (!channel)
		return (rpl(ERR_NOSUCHCHANNEL, arg[1]));

	if (!channel->getUser(_nick))
		return (rpl(ERR_NOTONCHANNEL, arg[1]));

	if (channel->checkMode(MODE_I) && !channel->isOp(this))
		return (rpl(ERR_CHANOPRIVSNEEDED, arg[1]));

	if (channel->getUser(arg[0]))
		return (rpl(ERR_USERONCHANNEL, arg[0] + " " + arg[1]));

	channel->invite(target);
	rpl(RPL_INVITING, target->getNick() + " " + arg[1]);
	target->user_send(Msg(_pref, "INVITE", target->getNick() + " :" + arg[1]));
	return (0);
}
/*
	payLoad as vector est notre fonction aui coupe les parametre, teo les stock dans argument et message
	pour invite dans l'ordre :
	- on verifie si la target exist (non d'utilisateur)
	- on verifie si le chan dans leauel on invite existe
	- on verifie si la personne qui invite est dans le chan
	- si le mode i est active il faut on check si le sender est un operateur
	- on verifie si l'inviter est deja dans le chan
	(pour les return tu peux voir sur google le message exact a retourner en tapant ERR_* sur la doc)
	ensuite il faut envoyer un message a la targer pour dire que sender l'invite dans <channel>
	et un message a sender pour dire qu'il q inviter target dans channel
*/