

#include <iostream>
#include <list>
#include <string>
#include "transfer.h"
#include "account.h"
#include "personalaccount.h"
#include "investmentaccount.h"
#include "user.h"
#include "date.h"

#include "personalassistant.h"
#include "userset.h"
#include <filesystem>
using namespace std;




// In this test logged user registers 5 personal accounts and sends money(50PLN) from them to the target account . If balance of target account changes by +250 the test is passed
// after test, the accounts are deleted
void Account_And_Transfer_TEST(PersonalAssistant& p1, user* loggedUser, int targetid){
    int accID = 1;
    while(p1.Check_For_Account_ID(accID) != nullptr){
        accID++;
    }
    float startBal = p1.Check_For_Account_ID(targetid)->GetBalance();
    for(int i = accID; i < accID+5; i++){
        loggedUser->Register_Personal_Account();
        loggedUser->Set_Date(1, i, 2000);
        loggedUser->Send_Money(i, 50, targetid, "C_A_TTEST");
    }
    for(int i = accID; i < accID+5; i++){
        loggedUser->Close_Account(i);
    }
    if(p1.Check_For_Account_ID(targetid)->GetBalance() != startBal+250) cout<<RED<<"C_A_TTEST FAILED"<<RESET<<endl;
}

// In this test logged user registers an investment account, buys 3 types of stocks (2 units) and then sells 1 unit of each. If balance of the account changed by sum of prices of single unit
// of each stock, the test is passed. After test, the investment account is deleted
void Stock_Buy_Sell_TEST(PersonalAssistant& p1, user* loggedUser){
    int accID = 1;
    while(p1.Check_For_Account_ID(accID) != nullptr){
        accID++;
    }
    loggedUser->Register_Investment_Account();
    float startBal = p1.Check_For_Account_ID(accID)->GetBalance();

    loggedUser->Buy_Stock(accID, "GOGL", 2);
    loggedUser->Buy_Stock(accID, "MIC", 2);
    loggedUser->Buy_Stock(accID, "PR", 2);
    loggedUser->Sell_Stock(accID, "GOGL", 1);
    loggedUser->Sell_Stock(accID, "MIC", 1);
    loggedUser->Sell_Stock(accID, "PR", 1);
    if(p1.Check_For_Account_ID(5)->GetBalance() != startBal - p1.Find_Stock("GOGL")->price - p1.Find_Stock("MIC")->price - p1.Find_Stock("PR")->price){
        cout<<RED<<"S_B_STEST FAILED"<<RESET<<endl;
    }
    loggedUser->Close_Account(accID);
}


//In this test logged user calls functions with parameters that are impossible to process or simply make no sense. If each function throws an exception, the test is passed.
//If at least 1 function doesn't throw an exception, the test is failed.
bool Impossible_Values_TEST(user* loggedUser, int pid, int iid){

    int excount = 0;
    try{
    loggedUser->Print_Account_History(-5); //Trying to access not owned account
    excount++;
    }
    catch(string s){

    }
    try{
    loggedUser->Print_Balance_By_Date(pid, 1, 2005, 5, 2001); //trying to pass impossible date range
    excount++;
    }
    catch(string s){

    }
    try{
    loggedUser->Print_Balance_By_Date(pid, 30, 2005, 5, 2007); //trying to pass impossible date range
    excount++;
    }
    catch(string s){

    }
    try{
    loggedUser->Buy_Stock(pid, "GOGL", 3); //buying stock with personal account
    excount++;
    }
    catch(string s){

    }
    try{
    loggedUser->Sell_Stock(pid, "GOGL", 3); //selling stock with personal account
    excount++;
    }
    catch(string s){

    }
    try{
    loggedUser->Change_Money_Amount(iid, 100, "Salary"); //Trying to change balance of investment account
    excount++;
    }
    catch(string s){

    }
    try{
    loggedUser->Change_Money_Amount(pid, 0, "Test"); //Registering a transfer of value 0
    excount++;
    }
    catch(string s){

    }
    try{
    loggedUser->Send_Money(pid, 100, pid, "TEST"); //account creating a transfer to itself
    }
    catch(string s){

    }
  if(excount == 0) return true;
  return false;

}


//In this test logged user calls functions with parameters that are theoretically valid, however the user does not have enough assets on his accounts to perform those operations
//The test is passed if each function in the test prints adequate red message for each function in the terminal
void Not_Enough_Assets_TEST(user* loggedUser, int pid, int iid){
    loggedUser->Change_Money_Amount(pid, -50000, "Test");
    loggedUser->Buy_Stock(iid, "GOO", 1);
    loggedUser->Buy_Stock(iid, "GOGL", 100000);
    loggedUser->Sell_Stock(iid, "GOGL", 100000);
    loggedUser->Send_Money(pid, 100, 7, "TEST");
    loggedUser->Send_Money(pid, 1000000, 1, "TEST");
}

int main()
{
    user* loggedUser = nullptr;
    PersonalAssistant p1;
    userset u1(loggedUser, &p1);
    p1.Add_Stock(15, "Gogole", "GOGL");
    p1.Add_Stock(125, "Microhard", "MIC");
    p1.Add_Stock(20, "Pear", "PR");
    u1.Load_Users();
    p1.Load_All_Accounts();



    //REGISTERING USERS AND ACCOUNTS TEST (uncomment only if running the program for the first time and no text files exist) - this is the base for testing. All test are written with assumption that 3 users and 4 accounts already exist.
{

    /*
    u1.Register_User("Adam", "PassWord");
    u1.Register_User("Piotr", "WordPass");
    u1.Register_User("Alex", "WassPord");

    u1.login(1, "PassWord");
    loggedUser->Register_Personal_Account();
    u1.login(2, "WordPass");
    loggedUser->Register_Investment_Account();
    loggedUser->Register_Personal_Account();
    loggedUser->Buy_Stock(2, "GOGL", 3);
    loggedUser->Buy_Stock(2, "MIC", 1);
    u1.login(3, "WassPord");
    loggedUser->Register_Personal_Account();
    */

}

u1.login(1, "PassWord");
if(loggedUser == nullptr) throw;


//TESTING CORRECT CASES - in this section only standard white messages should be displayed on the terminal
{


//Testing if accounts are correctly assigned to users
{
    /*
    u1.login(1, "PassWord");
    loggedUser->Display_Accountlist_Info();
    loggedUser->Display_Account_Info(1);
    u1.login(2, "WordPass");
    loggedUser->Display_Accountlist_Info();
    loggedUser->Display_Account_Info(2);
    loggedUser->Display_Account_Info(3);
    u1.login(3, "WassPord");
    loggedUser->Display_Accountlist_Info();
    loggedUser->Display_Account_Info(4);
    */

}





//Operations test - users perform various operations (TEST functions description above main() function). Uncomment the test to check
{
    /*
    int target = 3;
    u1.login(1, "PassWord");
    Account_And_Transfer_TEST(p1, loggedUser, target);
    //To additionaly verify the test one can check history of the target account. With no outside interference it should display 5 transfers - each with different date
    //p1.Check_For_Account_ID(target)->Display_History();
    */



    /*
    u1.login(2, "WordPass");
    Stock_Buy_Sell_TEST(p1, loggedUser);
    */


    //History display tests - best to use after performing A_A_TTEST at least once

    /*
    u1.login(2, "WordPass");
    loggedUser->Print_Account_History(target);
    loggedUser->Print_History_By_Date(target, 1, 2000, 7, 2000); //should display only transfers with latest dates in July
    loggedUser->Print_Balance_By_Date(target, 1, 2000, 7, 2000); //should display income transfers with latest dates in July, and no expenses with positive
    loggedUser->Print_History_With("Piotr"); //no history should be displayed as there were no interactions with user "Piotr"
    */

}


}

//TESTING INCORRECT CASES - in this section all functions used by user will be tested for incorrect input parameters.

{
    u1.login(2, "WordPass");

    //if(Impossible_Values_TEST(loggedUser, 3, 2)) cout<<"Test passed"<<endl;

    //Not_Enough_Assets_TEST(loggedUser, 3, 2);

}







return 0;
}
