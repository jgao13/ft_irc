#pragma once

#include <string>
#include <map>
#include "User.hpp"
#include "Server.hpp"

namespace ft {
    class User;
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
		std::string getTopic();
		void setTopic(std::string subject);

    bool isInviteOnly() const ;
    void setInviteOnly(bool inviteOnly);


    bool isTopicProtected() const ;
    void setTopicProtected(bool topicProtected);


    bool isKeyActivated() const;
    void setKeyActivated(bool keyActivated);

    std::string getKey() const;
    void setKey(const std::string& key);


    bool isLimitedUser() const;
    void setLimitedUser(bool limitedUser);

    unsigned int getNumberOfMaxUser() const;
    void setNumberOfMaxUser(unsigned int numberOfMaxUser);

    unsigned int getNumberOfCurrentUser() const;
    void setNumberOfCurrentUser(unsigned int numberOfCurrentUser);

    private:
        std::string _name; //nom du chan
        std::map<std::string, User*> _members; //liste des membre
        std::map<std::string, User*> _operators; // liste des operateur
		std::string _topic; //topic du chan

        //partie en lien avec le flou
        bool inviteOnly; // si on peut entrer dans le channel seulement par invitation
        bool topicProtected; // si le topic est proteger et changeable que par operator
        bool keyActivated; //mdp necessaire pour aller dans le chan
        std::string key; //le mdp du chan
        bool limitedUser; //si il y a une limitation de personne dans le chan
        unsigned int numberOfMaxUser;
        unsigned int numberofCurrentUser;

        // toutes les variables la servent pour la commande mode et m'oblige a changer plus ou moins tous ce qui utilise channel sa clc mdr


    };
}
