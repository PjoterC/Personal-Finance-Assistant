#include "investmentaccount.h"

investmentAccount::investmentAccount(int accountID, int ownerID, string ownerName, float balance)
{
    this->accountID = accountID;
    this->ownerID = ownerID;
    this->ownerName = ownerName;
    this->balance = balance;
    this->isInvestment = true;
    this->ownedStocks = list<pair<Stock, int>>();


}

investmentAccount::~investmentAccount()
{
    //dtor
}

pair<Stock, int>* investmentAccount::Check_If_Stock_Owned(string stockCode){
    for (auto it = ownedStocks.begin(); it != ownedStocks.end(); ++it){
        if((*it).first.code == stockCode) return &(*it);
    }
    return nullptr;
}

void investmentAccount::Display_Owned_Stocks(){
    cout<<"Stocks Owned:"<<endl;
    for (auto it = ownedStocks.begin(); it != ownedStocks.end(); ++it){
        cout<<"---------------------------------------------"<<endl;
        cout<<"Company name: "<<(*it).first.name<<"   Code: "<<(*it).first.code<<"  Amount: "<<(*it).second<<endl;
    }
    cout<<"---------------------------------------------"<<endl<<endl;
}


void investmentAccount::Buy_Stock(int amount, string stockName, string stockCode, float totalPrice, Date date) {

    try{
    unique_ptr<Stock> stock = make_unique<Stock>(totalPrice / amount, stockName, stockCode);
    unique_ptr<pair<Stock, int>> stockPair = make_unique<pair<Stock, int>>(*stock, amount);


    string text = "Purchased "+to_string(amount)+" stocks of "+stockName;
    Create_Transfer_Out(totalPrice, text, 0, "Stock Market", date);


    if(Check_If_Stock_Owned(stockCode) == nullptr){
        ownedStocks.push_back(*stockPair);
    }
    else{
        Check_If_Stock_Owned(stockCode)->second += amount;
    }
    }
    catch(string e){
        cout<<e;
        return;
    }

}


pair<int, string> investmentAccount::Sell_Stock(int amount, string stockCode){
    unique_ptr<pair<int, string>> p = make_unique<pair<int, string>>(amount, stockCode);
    if(Check_If_Stock_Owned(stockCode) == nullptr){
        cout<<RED<<"No stock owned with given code: "<<stockCode<<" found. Try checking input data."<<RESET<<endl;
        p->first = 0;
        return *p;
    }
    if(Check_If_Stock_Owned(stockCode)->second < amount){
        cout<<RED<<"You don't have that many stocks of "<<stockCode<<RESET<<endl;
        p->first = 0;
        return *p;
    }
    if(Check_If_Stock_Owned(stockCode)->second > amount) Check_If_Stock_Owned(stockCode)->second -= amount;
    else if(Check_If_Stock_Owned(stockCode)->second == amount){

        for (auto it = ownedStocks.begin(); it != ownedStocks.end(); ++it){
            if((*it).first.code == stockCode){
                ownedStocks.erase(it);
                return *p;
            }
        }
    }

    return *p;

}


string investmentAccount::Save_Stocks(){
    stringstream out;

    for(auto it = ownedStocks.begin(); it != ownedStocks.end(); ++it){
        out << (*it).first.price << endl << (*it).first.name << endl << (*it).first.code << endl << (*it).second << endl;
    }

    return out.str();
}

void investmentAccount::Load_StockPair(float price, string name, string code, int amount){
    try{
    unique_ptr<Stock> stock = make_unique<Stock>(price, name, code);
    unique_ptr<pair<Stock, int>> stockPair = make_unique<pair<Stock, int>>(*stock, amount);
    ownedStocks.push_front(*stockPair);
    }
    catch(string s){
    cout<<s;
    return;
    }

}


