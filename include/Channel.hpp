#pragma once

#include <string>
#include <map>
#include "User.hpp"

namespace ft {
    class Channel {
    public:
	//constructeur destructeur
        Channel(const std::string& name);
		~Channel();
	//fonction membre (je pense les noms sont assez Obvious) 
        const std::string& getName() const;
        void addUser(User* user);
        void removeUser(User* user);
        bool isUserMember(User* user) const;
        bool isOperator(User* user) const;
        void addOperator(User* user);
        void removeOperator(User* user);
        void sendMessageToMembers(const std::string& message);

    private:
        std::string _name; //nom du chan
        std::map<std::string, User*> _members; //liste des membre
        std::map<std::string, User*> _operators; // liste des operateur
    };
}
