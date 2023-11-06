#ifndef USERSET_H
#define USERSET_H

#include "user.h"

class userset
{
    public:
        userset(user*& loggedUser, PersonalAssistant* assistant);
        virtual ~userset();
        void Save_Users();
        void Load_Users();
        void Register_User(string name, string password);
        void login(int ID, string password);

    protected:

    private:
        user*& loggedUser;
        PersonalAssistant* assistant;
        list<user> userList;
};

#endif // USERSET_H
