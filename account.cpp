#include "account.h"



account::account()
{
    //ctor
}

account::~account()
{

}

int account::GetID(){
    return accountID;
}

int account::GetOwnerID(){
    return ownerID;
}

string account::GetOwnerName(){
    return ownerName;
}

float account::GetBalance(){
    return balance;
}




int account::datecmp(const Transfer& transfer1, const Transfer& transfer2) {
    if (transfer1.GetDate().year > transfer2.GetDate().year) {
        return 1;
    }
    else if (transfer1.GetDate().year == transfer2.GetDate().year && transfer1.GetDate().month > transfer2.GetDate().month) {
        return 1;
    }
    else if (transfer1.GetDate().year == transfer2.GetDate().year && transfer1.GetDate().month == transfer2.GetDate().month && transfer1.GetDate().day > transfer2.GetDate().day) {
        return 1;
    }
    else {
        return -1;
    }
}






void account::Add_To_History(const Transfer& added){
    if(history.empty()){
        history.push_front(added);
        return;
    }

    if(datecmp(*history.begin(), added) <= 0){
        history.push_front(added);
        return;
    }
    for(auto it = history.begin(); it != history.end(); ++it){
        if(datecmp(*it, added) <= 0){
            history.insert(it, added);
            return;
        }
    }
history.push_back(added);
}


bool account::Create_Transfer_Out(float value, string title, int recID, string recName, Date date){

    if(value == 0){
        cout<<YELLOW<<"You can't send a transfer with a value of 0"<<RESET<<endl;
        return false;
    }

    if(balance >= value){
        balance -= value;
    }
    else{
        cout<<RED<<"You don't have enough money to send a transfer"<<RESET<<endl;
        return false;
    }
    unique_ptr<Transfer> newTransfer = make_unique<Transfer>(-value, title, recID, this->accountID, recName, "Yourself", date);
    Add_To_History(*newTransfer);


    return true;

}





void account::Create_Transfer_In(float value, string title, int sendID, string sendName, Date date){

    balance += value;
    unique_ptr<Transfer> newTransfer = make_unique<Transfer>(value, title, this->accountID, sendID, "Yourself", sendName, date);
    Add_To_History(*newTransfer);

}

bool account::Check_If_Investment(){
    if(this->isInvestment == true) return true;

    else return false;


}

void account::Clear_History(){
    while(!history.empty()){
            //cout<<"Pop"<<endl;
        history.pop_front();
    }
}


void account::Display_History(){
    if(history.empty()) return;
    for(auto it = history.begin(); it != history.end(); ++it){
        (*it).Disp();

    }

}

void account::Display_By_Person(string name){
    if(history.empty()) return;
    for(auto it = history.begin(); it != history.end(); ++it){
        if((*it).GetReceiverName() == name || (*it).GetSenderName() == name){
        (*it).Disp();
        }
    }
}


void account::Display_By_Date(int sMonth, int sYear, int eMonth, int eYear){
    if(history.empty()) return;
    if(sMonth > 12 || eMonth > 12 || sMonth < 1 || eMonth < 1 || sYear < 2000 || eYear < 2000){
        cout<<"Not valid date range for display. Try any date starting from 01.2000"<<endl;
        return;
    }
    for(auto it = history.begin(); it != history.end(); ++it){
        if((*it).GetDate().month >= sMonth && (*it).GetDate().month <= eMonth && (*it).GetDate().year >= sYear && (*it).GetDate().year <= eYear){
        (*it).Disp();
        }
    }
    cout<<endl;
}

float account::Display_Income(int sMonth, int sYear, int eMonth, int eYear){
    float val = 0;
    if(history.empty()) return 0;
    if(sMonth > 12 || eMonth > 12 || sMonth < 1 || eMonth < 1 || sYear < 2000 || eYear < 2000){
        cout<<"Not valid date range for display. Try any date starting from 01.2000"<<endl;
        return 0;
    }
    for(auto it = history.begin(); it != history.end(); ++it){
        if((*it).GetValue() > 0 && (*it).GetDate().month >= sMonth && (*it).GetDate().month <= eMonth && (*it).GetDate().year >= sYear && (*it).GetDate().year <= eYear){
        val+=(*it).GetValue();
        (*it).Disp();
        }
    }
    if(val == 0) cout<<"Could not find any income in a given time range"<<endl;
    cout<<endl;
    return val;
}


float account::Display_Expenses(int sMonth, int sYear, int eMonth, int eYear){
    float val = 0;
    if(history.empty()) return 0;
    if(sMonth > 12 || eMonth > 12 || sMonth < 1 || eMonth < 1 || sYear < 2000 || eYear < 2000){
        cout<<"Not valid date range for display. Try any date starting from 01.2000"<<endl;
        return 0;
    }
    for(auto it = history.begin(); it != history.end(); ++it){
        if((*it).GetValue() < 0 && (*it).GetDate().month >= sMonth && (*it).GetDate().month <= eMonth && (*it).GetDate().year >= sYear && (*it).GetDate().year <= eYear){
        val+=(*it).GetValue();
        (*it).Disp();
        }
    }
    if(val == 0) cout<<"Could not find any expenses in a given time range"<<endl;
     cout<<endl;
    return val;
}




string account::Save_History(){
    stringstream out;

    for(auto it = history.begin(); it != history.end(); ++it){
        out << (*it);
    }
    return out.str();
}

void account::Load_Transfer(float value, string title, int recID, int sendID, string recName, string sendName, int day, int month, int year){
    Date d(day, month, year);
    try{
    unique_ptr<Transfer> newTransfer = make_unique<Transfer>(value, title, recID, sendID, recName, sendName, d);
    Add_To_History(*newTransfer);
    }
    catch(string s){
    cout<<s;
    return;
    }


}
