/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnr <lnr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:19:30 by lnr               #+#    #+#             */
/*   Updated: 2023/10/11 21:19:33 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

int User::_cmd_KICK(Msg & cmd) // ----------------------------------------- KICK
{
	str_vec arg = cmd.payloadAsVector(3);
	if (arg.size() < 2)
		return (rpl(ERR_NEEDMOREPARAMS, "KICK"));
//besoin de 3 arg cf la doc
	Chan * channel = _serv->getChan(arg[0]);
	if (!channel)
		return (rpl(ERR_NOSUCHCHANNEL, arg[0]));
//verif de si il y a un chan, si le user et dedans et donner une raison (possible de virer plusieur personne d'ou le set d'user)
	std::set<str> UserNames;
	while (!arg[1].empty())
		UserNames.insert(extract_first_word(arg[1], ','));

	str comment = (arg.size() == 3 ? arg[2] : _nick);

	std::set<str>::iterator it;
	for (it = UserNames.begin(); it != UserNames.end(); it++) {

		User *target = _serv->getUser(*it);
//verif dans l'ordre si target exist, si il est dans le chan, si le sender est operateur
// si toute les condition son verif, envoyer au chat que cible a ete virer et message au gars qu'on la degager et ne pas oublier de l'enlever du chan
		if (!target)
			rpl(ERR_NOSUCHNICK, *it);
		else if (!channel->getUser(_nick))
			rpl (ERR_NOTONCHANNEL, arg[0]);
		else if (!channel->getUser(*it))
			rpl(ERR_USERNOTINCHANNEL, *it + " " + arg[0]);
		else if (!channel->isOp(this))
			rpl(ERR_CHANOPRIVSNEEDED, arg[0]);
		else {
			channel->chan_send(Msg(_pref, "KICK", arg[0] + " " + *it + " :" + comment));
			channel->rmUser(target);
			target->_chans.erase(arg[0]);
		}
	}
	return 0;
}