#ifndef USER_H
#define USER_H
#define RESET   "\033[0m"
#define RED     "\033[31m"


#include "personalaccount.h"
#include "investmentaccount.h"
#include <string>
#include <iostream>
#include <list>
#include "personalassistant.h"


class PersonalAssistant;
class user
{
    public:
        user(string name, string password, PersonalAssistant* assistant, int ID = 0);
        ~user();

        void Set_Date(int day, int month, int year); //sets the todayDate of the assistant (substitutes actual passage of time)

        void Register_Personal_Account(); // calls the assistant to create a new personal account for the user

        void Register_Investment_Account(); // calls the assistant to create a new investment account for the user

        void Send_Money(int accNumber, float value, int recID, string title); //sends money from a chosen account to an account with given ID

        void Print_Account_History(int accNumber); //displays history of transfers of a chosen account

        void Print_History_With(string name); //displays history of transfers of all user's accounts with another user with given name

        void Print_History_By_Date(int accNumber, int smonth, int syear, int emonth, int eyear); //displays history of transfers of user's account in a given time period

        void Print_Balance_By_Date(int accNumber, int smonth, int syear, int emonth, int eyear); //display user's income and expenditure in a given time period and compares them

        void Display_Account_Info(int accNumber); // displays info about user's chosen account

        void Display_Accountlist_Info(); // calls assistant to display info about all of user's accounts

        void Display_All_Accounts(); // calls assistant to display info about all accounts currently open in the system

        void Close_Account(int accNumber); // deletes chosen account and all data it contains

        bool Verify_Ownership(int accNumber); //verifies whether the account belongs to this user, returns true if it does, false otherwise

        bool Verify_Date_Range(int smonth, int syear, int emonth, int eyear);

        void Change_Money_Amount(int accNumber, float value, string reason); //usable only for personal accounts, calls Buy() or Spend() methods of personal account. Reason is the reason for transfer

        void Buy_Stock(int accNumber, string stockcode, int amount); //usable only for investment account, calls Buy_Stock() method of investment account

        void Sell_Stock(int accNumber, string stockcode, int amount); //usable only for investment account, calls Sell_Stock() method of investment account


        void Print_Total_Balance(); // displays user's total asset value




        string GetPassword();
        string GetName();
        int GetID();

    protected:

    private:
        string password;
        string name;
        int userID;
        PersonalAssistant* assistant;

};

#endif // USER_H
