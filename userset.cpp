#include "userset.h"

userset::userset(user*& loggedUser, PersonalAssistant* assistant) :
    loggedUser(loggedUser), assistant(assistant)
{

}

userset::~userset()
{
    //dtor
}


void userset::Save_Users(){
    fstream userfile;
    userfile.open("users.txt", ios::out);
    if(userfile.is_open()){
        for (auto it = userList.begin(); it != userList.end(); ++it) {
                userfile << (*it).GetID() << endl << (*it).GetName() << endl << (*it).GetPassword() << endl;
        }
        userfile.close();
    }
    else cout << "Something went wrong" << endl;
}

void userset::Load_Users(){
    fstream userfile;
    userfile.open("users.txt", ios::in);
    if(userfile.is_open()){
        string ID;
        string name;
        string password;
        while(getline(userfile, ID)){
            if(ID == "") return;
            getline(userfile, name);
            getline(userfile, password);
            unique_ptr<user> u = make_unique<user>(name, password, assistant, stoi(ID));
            userList.push_front(*u);

        }
        userfile.close();
    }
    else cout << "No users found" << endl;
}




void userset::Register_User(string name, string password){
    unique_ptr<user> u = make_unique<user>(name, password, assistant);
    cout<<"Registered "<<u->GetName() << " with ID: "<<u->GetID()<<endl;
    userList.push_front(*u);
    Save_Users();
}

void userset::login(int ID, string password){
//While in actual application with user input, the login parameters would be checked at the time of input,
// in this build, the function will always have correct parameters in order to prevent errors during testing
    for (auto it = userList.begin(); it != userList.end(); ++it) {
            if((*it).GetID() == ID && (*it).GetPassword() == password){
                cout<<"Logged in as "<<(*it).GetName()<<endl;
                loggedUser = &(*it);
                return;
            }
    }
    cout<<RED<<"Could not login. Try checking your input"<<RESET<<endl;
}

