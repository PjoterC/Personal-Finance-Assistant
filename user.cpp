#include "user.h"

user::user(string name, string password, PersonalAssistant* assistant, int ID)
{

    int id = ID;
    if(id == 0){
        id = 1;
    }
    this->name = name;
    while(assistant->Check_For_User_ID(id)){
        id++;
    }
    this->userID = id;
    this->password = password;
    this->assistant = assistant;
    assistant->Register_New_User_ID(id);

}

user::~user()
{
    //dtor
}

int user::GetID(){
    return userID;
}

string user::GetName(){
    return name;
}

string user::GetPassword(){
    return password;
}

void user::Register_Personal_Account(){
    int id = assistant->Register_Personal_Account(this->userID, this->name);
    assistant->Write_All_Accounts();
    cout<<"Registered personal account with ID: "<<id<<endl;
}

void user::Register_Investment_Account(){
    int id = assistant->Register_Investment_Account(this->userID, this->name);
    assistant->Write_All_Accounts();
    cout<<"Registered investment account with ID: "<<id<<endl;
}


bool user::Verify_Ownership(int accNumber){
    if(assistant->Check_For_Account_ID(accNumber) == nullptr || assistant->Check_For_Account_ID(accNumber)->GetOwnerID() != this->userID){
        return false;
    }
    return true;
}

bool user::Verify_Date_Range(int smonth, int syear, int emonth, int eyear){
    if(eyear < syear || (eyear == syear && emonth < smonth) || emonth > 12 || emonth < 1 || smonth > 12 || smonth < 1 || eyear < 2000 || syear < 2000){
        return false;
    }
    return true;

}


void user::Display_Account_Info(int accNumber){
    if(!Verify_Ownership(accNumber)) throw "You don't own an account with an ID: "+to_string(accNumber)+". Please check your input.";
    cout<<"Account nr: "<<accNumber<<endl;
    cout<<"Account type: ";
    if(assistant->Check_For_Account_ID(accNumber)->Check_If_Investment()) cout<<"(I)   ";
    else cout<<"(P)   ";
    cout<<"Balance: "<<assistant->Check_For_Account_ID(accNumber)->GetBalance()<<" PLN"<<endl;
    if(assistant->Check_For_Account_ID(accNumber)->Check_If_Investment()){
        ((investmentAccount*)assistant->Check_For_Account_ID(accNumber))->Display_Owned_Stocks();
    }
    cout<<endl;
}

void user::Display_Accountlist_Info(){
    cout<<"Your accounts are:"<<endl;
    assistant->Print_User_Accounts_List(this->userID);
}
void user::Display_All_Accounts(){
    assistant->Print_All_Accounts_List();
}


void user::Send_Money(int accNumber, float value, int recID, string title){
    if(!Verify_Ownership(accNumber)) throw "You don't own an account with an ID: "+to_string(accNumber)+". Please check your input.";
    if(recID == accNumber){
        throw (string)"Account can't send money to itself.";

    }
    if(value <= 0){
        throw (string)"You can't send that amount of money. Try any amount greater than 0";

    }
    assistant->Register_Transfer_Between(value, title, recID, accNumber);

}

void user::Change_Money_Amount(int accNumber, float value, string reason){
    if(!Verify_Ownership(accNumber)) throw "You don't own an account with an ID: "+to_string(accNumber)+". Please check your input.";
    if(value == 0) throw (string)"You can't register a transfer with value 0";
    if(assistant->Check_For_Account_ID(accNumber)->Check_If_Investment()){
        throw (string)"Investment account can't register income or expenditure.";
    }
    assistant->Register_Transfer(accNumber, value, reason);
}

void user::Print_Total_Balance(){
    cout<<"Total amount of money on all accounts: ";
    cout<<assistant->GetTotalUserBalance(this->userID)<<endl;
}


void user::Set_Date(int day, int month, int year){
    try{
    assistant->Set_Date(day, month, year);
    }
    catch(string d){
        cout<<RED<<"Could not set the date"<<RESET<<endl;
        cout<<RED<<"Value "<<d<<" is an improper one. Try any real date starting from 1.1.2000"<<RESET<<endl;
        return;
    }
    cout<<"Successfully set date to "<<day<<"."<<month<<"."<<year<<endl;

}

void user::Print_Account_History(int accNumber){
    if(!Verify_Ownership(accNumber)) throw "You don't own an account with an ID: "+to_string(accNumber)+". Please check your input.";
    cout<<"Account "<<accNumber<<endl;
    assistant->Check_For_Account_ID(accNumber)->Display_History();
    cout<<endl;
}


void user::Print_History_With(string name){

    assistant->Check_By_Name_For_All(this->GetID(), name);

}


void user::Print_History_By_Date(int accNumber, int smonth, int syear, int emonth, int eyear){
    if(!Verify_Ownership(accNumber)) throw "You don't own an account with an ID: "+to_string(accNumber)+". Please check your input.";
    if(!Verify_Date_Range(smonth, syear, emonth, eyear)){
        throw "Improper date range value";
    }
    cout<<"Account "<<accNumber<<endl;
    assistant->Check_For_Account_ID(accNumber)->Display_By_Date(smonth, syear, emonth, eyear);
    cout<<endl;

}


void user::Print_Balance_By_Date(int accNumber, int smonth, int syear, int emonth, int eyear){
    if(!Verify_Ownership(accNumber)) throw "You don't own an account with an ID: "+to_string(accNumber)+". Please check your input.";
    if(!Verify_Date_Range(smonth, syear, emonth, eyear)){
        throw (string)"Improper date range value";
        return;
    }

    cout<<"For a given time range: ";
    if(smonth < 10) cout<<"0";
    cout<<smonth<<"."<<syear<<" - ";
    if(emonth < 10) cout<<"0";
    cout<<emonth<<"."<<eyear<<endl;
    cout<<"Account "<<accNumber<<":"<<endl<<endl;
    cout<<"Income: "<<endl;
    float income = assistant->Check_For_Account_ID(accNumber)->Display_Income(smonth, syear, emonth, eyear);
    cout<<endl;
    cout<<"Expenses: "<<endl;
    float expenses = assistant->Check_For_Account_ID(accNumber)->Display_Expenses(smonth, syear, emonth, eyear);

    float balance = income+expenses;
    cout<<endl<<endl;

    cout<<"Income: "<<income<<" PLN"<<endl;
    cout<<"Expenses: "<<expenses<<" PLN"<<endl;
    cout<<"Balance: "<<balance<<" PLN"<<endl;

}


void user::Close_Account(int accNumber){
    if(!Verify_Ownership(accNumber)){
        throw "You don't own an account with an ID: "+to_string(accNumber)+". Please check your input.";
    }
    assistant->Remove_Account(accNumber);
}




void user::Buy_Stock(int accNumber, string stockcode, int amount){
    if(!Verify_Ownership(accNumber)){
        throw "You don't own an account with an ID: "+to_string(accNumber)+". Please check your input.";
    }
    if(!assistant->Check_For_Account_ID(accNumber)->Check_If_Investment()){
        throw (string)"Personal account can't own stocks.";
    }
    assistant->Buy_Stock(accNumber, stockcode, amount);
}

void user::Sell_Stock(int accNumber, string stockcode, int amount){
    if(!Verify_Ownership(accNumber)){
       throw "You don't own an account with an ID: "+to_string(accNumber)+". Please check your input.";
    }
    if(!assistant->Check_For_Account_ID(accNumber)->Check_If_Investment()){
        throw (string)"Personal account can't own stocks.";
    }
    assistant->Sell_Stock(accNumber, stockcode, amount);
}
