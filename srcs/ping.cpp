#include "../include/Server.hpp"
namespace ft
{
void Server::ping(User* sender, Command* cmd) {
        if (cmd->arguments()[0].empty())
        {
            sender->sendMsg("409 ERR_NOORIGIN : No origin specified\r\n");
            return ;
        }

        std::string pingId = cmd->arguments()[0];
        sender->sendMsg("PONG :" + pingId + "\r\n");
}
}