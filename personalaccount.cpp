#include "personalaccount.h"

personalAccount::personalAccount(int accountID, int ownerID, string ownerName, float balance)
{

    this->accountID = accountID;
      this->ownerID = ownerID;
      this->ownerName = ownerName;
    this->balance = balance;
    this->isInvestment = false;

}

personalAccount::~personalAccount()
{

}


void personalAccount::Earn(float value, string target, Date date){

    try{
    unique_ptr<Transfer> newTransfer = make_unique<Transfer>(value, "Income", this->accountID, 0, "Yourself", target, date);
    Add_To_History(*newTransfer);
    }
    catch(string e){
        cout<<e;
        return;
    }
    balance+= value;
    return;
}

void personalAccount::Spend(float value, string target, Date date){

    if(-value > balance){
        cout<<RED<<"You don't have that much money"<<RESET<<endl;
        return;
    }
    try{
    unique_ptr<Transfer> newTransfer = make_unique<Transfer>(value, "Expenditure", 0, this->accountID, target, "Yourself", date);
    Add_To_History(*newTransfer);
    }
    catch(string e){
        cout<<e;
        return;
    }
    balance+= value;
    return;

}


