#include "../include/Channel.hpp"

namespace ft 
{
    Channel::Channel(const std::string& name) : _name(name)
    {
        bool inviteOnly = false; 
        bool topicProtected = false;
        bool keyActivated = false; 
        //std::string key = NULL; 
        bool limitedUser = false;
        unsigned int numberOfMaxUser = 64; 
        unsigned int numberofCurrentUser = 0;

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

//////////////je rajoute plein de getter et setter ici, mashallah le travail a la chaine

    // Getter et Setter pour inviteOnly
    bool Channel::isInviteOnly() const 
    {
        return inviteOnly;
    }

    void Channel::setInviteOnly(bool inviteOnly) 
    {
        this->inviteOnly = inviteOnly;
    }

    // Getter et Setter pour topicProtected
    bool Channel::isTopicProtected() const 
    {
        return topicProtected;
    }

    void Channel::setTopicProtected(bool topicProtected) 
    {
        this->topicProtected = topicProtected;
    }

    // Getter et Setter pour keyActivated
    bool Channel::isKeyActivated() const 
    {
        return keyActivated;
    }

    void Channel::setKeyActivated(bool keyActivated) 
    {
        this->keyActivated = keyActivated;
    }

    // Getter et Setter pour key
    std::string Channel::getKey() const 
    {
        return key;
    }

    void Channel::setKey(const std::string& key) 
    {
        this->key = key;
    }

    // Getter et Setter pour limitedUser
    bool Channel::isLimitedUser() const 
    {
        return limitedUser;
    }

    void Channel::setLimitedUser(bool limitedUser) 
    {
        this->limitedUser = limitedUser;
    }

    // Getter et Setter pour numberOfMaxUser
    unsigned int Channel::getNumberOfMaxUser() const 
    {
        return numberOfMaxUser;
    }

    void Channel::setNumberOfMaxUser(unsigned int numberOfMaxUser) 
    {
        this->numberOfMaxUser = numberOfMaxUser;
    }

    // Getter et Setter pour numberOfCurrentUser
    unsigned int Channel::getNumberOfCurrentUser() const 
    {
        return numberofCurrentUser;
    }

    void Channel::setNumberOfCurrentUser(unsigned int numberOfCurrentUser) 
    {
        this->numberofCurrentUser = numberOfCurrentUser;
    }

}