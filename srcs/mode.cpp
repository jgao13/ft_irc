#include "../include/Channel.hpp"

namespace ft
{
    //commence forcement par + ou -
    // il peut y avoir plusieur lettre
    // le channel cible cmd->arg[0]
    // les lettre sont coller donc dans cmd->arg[1]
    //parametre a prendre en compte dans l'ordre des lettre

    /*
    liste des lettre :
        i : invite only
        t : topic set par operator only
        k : definir un mdp
        o : donner le statut operateur
        l : definir une limite d'user / que faire si au moment d'activer il y a deja plus d'user ?
    */
    void	Server::mode(User * user, Command *  cmd)
    {
        std::string nick = cmd->arguments()[0];
        std::cout << nick;
        user->printStatus();
    }
}