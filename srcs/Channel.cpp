#include "../include/Channel.hpp"

namespace ft {
    Channel::Channel(const std::string& name) : _name(name)
    {
        //set tout les bool a true or false ?
    }

    Channel::~Channel()
    {
        //free les map ?
    }

    const std::string& Channel::getName() const
    {
        return _name;
    }

    void Channel::addUser(User* user)
    {
        if (user)
        {
            _members[user->getNickname()] = user;
        }
    }

    void Channel::removeUser(User* user)
    {
        _members.erase(user->getNickname());
    }

    bool Channel::isUserMember(User* user) const
    {
        return _members.find(user->getNickname()) != _members.end();
    }

    bool Channel::isOperator(User* user) const
    {
        return _operators.find(user->getNickname()) != _operators.end();
    }

    void Channel::addOperator(User* user)
    {
        _operators[user->getNickname()] = user;
    }

    void Channel::removeOperator(User* user)
    {
        _operators.erase(user->getNickname());
    }

    void Channel::sendMessageToMembers(const std::string& message)
    {
        for (std::map<std::string, User*>::iterator it = _members.begin(); it != _members.end(); ++it)
        {
            User* user = it->second;
            user->sendMsg(message);
        }
    }
	std::string Channel::getTopic()
    {
        return (_topic);
    }
	void Channel::setTopic(std::string subject)
    {
        _topic = subject;
    }

}
