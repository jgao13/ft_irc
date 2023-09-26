#include "../include/Channel.hpp"

namespace ft
{
    void	Server::mode(User * user, Command *  cmd)
    {
        std::string nick = cmd->arguments()[0];
        std::cout << nick;
        user->printStatus();
    }
}