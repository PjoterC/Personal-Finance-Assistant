#include "personalassistant.h"

PersonalAssistant::PersonalAssistant() : todayDate(1, 1, 2000)
{
    //ctor
}

PersonalAssistant::~PersonalAssistant()
{
    //dtor
}



bool PersonalAssistant::Check_For_User_ID(int ID){
    for (auto it = userIDs.begin(); it != userIDs.end(); ++it) {
        if ((*it) == ID) return true;
    }
    return false;

}




account* PersonalAssistant::Check_For_Account_ID(int ID){
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if ((*it).GetID() == ID) return &(*it);
    }
    return nullptr;
}




void PersonalAssistant::Register_New_User_ID(int ID){
    userIDs.push_front(ID);
}

void PersonalAssistant::Remove_User(int userID){
    for (auto it = userIDs.begin(); it != userIDs.end(); ++it) {
        if((*it) == userID) userIDs.erase(it);
        return;
    }
}


void PersonalAssistant::Print_All_Users_List(list<user>& users){
    for (auto it = users.begin(); it != users.end(); ++it) {
            cout<<(*it).GetName()<<"    "<<(*it).GetPassword()<<"   "<<(*it).GetID()<<endl;
    }
}





string PersonalAssistant::Get_Owners_Name(int ID){
    for (auto it = accounts.begin(); it != accounts.end(); ++it){
        if((*it).GetID() == ID) return (*it).GetOwnerName();
    }
    return "";
}




int PersonalAssistant::Register_Personal_Account(int ownerID, string ownerName, int ID, float balance){
    int id = ID;
    while(Check_For_Account_ID(id) != nullptr){
        id += 1;
    }
    unique_ptr<personalAccount> acc = make_unique<personalAccount>(id, ownerID, ownerName, balance);
    accounts.push_back(*acc);
    Write_Account_IDs();
    return id;

}

int PersonalAssistant::Register_Investment_Account(int ownerID, string ownerName, int ID, float balance){
    int id = ID;
    while(Check_For_Account_ID(id) != nullptr){
        id += 1;
    }
    unique_ptr<investmentAccount> acc = make_unique<investmentAccount>(id, ownerID, ownerName, balance);
    accounts.push_back(*acc);
    Write_Account_IDs();
    return id;
}





void PersonalAssistant::Print_All_Accounts_List(){

    for (auto it = accounts.begin(); it != accounts.end(); ++it) {

            cout<<(*it).GetOwnerName()<<"   ";
            if((*it).Check_If_Investment()) cout<<"(I) ";
            else cout<<"(P) ";


            cout<<"ID: "<<(*it).GetID()<<endl;   //"     "<<(*it).GetOwnerID()<<endl;
    }
}

void PersonalAssistant::Print_User_Accounts_List(int userID){
    for (auto it = accounts.begin(); it != accounts.end(); ++it){
        if((*it).GetOwnerID() == userID){
            if((*it).Check_If_Investment()) cout<<"(I) ";
            else cout<<"(P) ";


            cout<<"ID: "<<(*it).GetID()<<endl;
        }
    }
}

void PersonalAssistant::Set_Date(int day, int month, int year){
    if(day < 1 || day > 31) throw to_string(day)+" of day";
    if(month < 1 || month > 12) throw to_string(month)+" of month";
    if(year < 2000) throw to_string(year)+" of year";
    if(day > 30 && (month%2 != 0)) throw to_string(day)+" of day for this month";
    if(day > 28 && month == 2) throw to_string(day)+" of day for this month";
    this->todayDate.day = day;
    this->todayDate.month = month;
    this->todayDate.year = year;
}



void PersonalAssistant::Check_Account_History_By_Name(int accNumber, string name){
    if(Check_For_Account_ID(accNumber) == nullptr){
        cout<<YELLOW<<"Account ID not valid, please enter ID value for an existing account."<<RESET<<endl;
        return;
    }
    else{
        cout<<endl<<"Account "<<accNumber<<endl;
        Check_For_Account_ID(accNumber)->Display_By_Person(name);
    }

}

void PersonalAssistant::Check_By_Name_For_All(int ownerID, string name){
    for (auto it = accounts.begin(); it != accounts.end(); ++it){
        if((*it).GetOwnerID() == ownerID){
            Check_Account_History_By_Name((*it).GetID(), name);
        }
    }

}


float PersonalAssistant::GetTotalUserBalance(int ownerID){
    float balance = 0;
    for (auto it = accounts.begin(); it != accounts.end(); ++it){
        if((*it).GetOwnerID() == ownerID){
            balance += (*it).GetBalance();
        }
    }
    return balance;

}




//TRANSFER HANDLING
void PersonalAssistant::Register_Transfer_Between(float value, string title, int recID, int sendID){

    if(Check_For_Account_ID(sendID) == nullptr || Check_For_Account_ID(recID) == nullptr){
        cout<<RED<<"Target account ID not valid, please enter ID value for an existing account."<<RESET<<endl;
        return;
    }

    if(((Check_For_Account_ID(sendID)->Check_If_Investment() == true)) && (Check_For_Account_ID(sendID)->GetOwnerID()) != Check_For_Account_ID(recID)->GetOwnerID()){
        cout<<RED<<"Cannot send money to other users from an investment account."<<RESET<<endl;
        return;
    }
    if((Check_For_Account_ID(recID)->Check_If_Investment() == true) && (Check_For_Account_ID(sendID)->GetOwnerID()) != Check_For_Account_ID(recID)->GetOwnerID()){
        cout<<RED<<"Cannot send money to other users' investment accounts."<<RESET<<endl;
        return;
    }

    if(Check_For_Account_ID(sendID)->Create_Transfer_Out(value, title, recID, Get_Owners_Name(recID), todayDate)){
        Check_For_Account_ID(recID)->Create_Transfer_In(value, title, sendID, Get_Owners_Name(sendID), todayDate);
        Write_All_Accounts();
        return;
    }




}






//Personal Account handing
void PersonalAssistant::Register_Transfer(int accNumber, float value, string target){
    if(Check_For_Account_ID(accNumber) == nullptr || Check_For_Account_ID(accNumber)->Check_If_Investment()){
        cout<<RED<<"You can only Earn or Spend with your personal account. Please check the entered account ID"<<RESET<<endl;
        return;
    }
    if(value == 0){
        cout<<RED<<"Value of income or expenditure cannot be 0"<<RESET<<endl;
        return;
    }

    if(value > 0){
        ((personalAccount*)Check_For_Account_ID(accNumber))->Earn(value, target, todayDate);
        Write_Account(accNumber);
        return;
    }
    else if(value < 0){
        ((personalAccount*)Check_For_Account_ID(accNumber))->Spend(value, target, todayDate);
        Write_Account(accNumber);
        return;
    }
}







//STOCKS

Stock* PersonalAssistant::Find_Stock(string code){
    for (auto it = availableStocks.begin(); it != availableStocks.end(); ++it){
            if((*it).code == code) return &(*it);
    }
    return nullptr;
}


void PersonalAssistant::Add_Stock(float price, string name, string code){
    if(Find_Stock(code) != nullptr){
        cout<<RED<<"Stock with a given code already exists"<<RESET<<endl;
        return;
    }
    try{
    unique_ptr<Stock> s = make_unique<Stock>(price, name, code);
    availableStocks.push_back(*s);
    }
    catch(string e){
        cout<<e;
        return;
    }


    return;

}


void PersonalAssistant::Set_Stock_Price(float value, string code){
    if(value == 0){
        cout<<RED<<"Stock value cannot be negative"<<RESET<<endl;
        return;
    }
    if(Find_Stock(code) == nullptr){
        cout<<RED<<"Stock with a given code does not exist"<<RESET<<endl;
        return;
    }
    Find_Stock(code)->price = value;
    return;
}

void PersonalAssistant::Display_Available_Stocks(){
    cout<<"Available stocks:"<<endl;
    for (auto it = availableStocks.begin(); it != availableStocks.end(); ++it){
            cout<<"Company name: "<<(*it).name<<"   Code: "<<(*it).code<<"  Current price: "<<(*it).price<<" PLN"<<endl;

    }
    cout<<endl;
}



void PersonalAssistant::Buy_Stock(int accNumber, string code, int amount){
    if(Check_For_Account_ID(accNumber) == nullptr){
        cout<<YELLOW<<"Account not found"<<RESET<<endl;
        return;
    }
    if(Find_Stock(code) == nullptr){
        cout<<RED<<"No stock with a given code found"<<RESET<<endl;
        return;
    }

    if(Check_For_Account_ID(accNumber)->GetBalance() < (Find_Stock(code)->price * amount) || amount <= 0){
        cout<<RED<<"You can't buy this number of stocks"<<RESET<<endl;
        return;
    }

    ((investmentAccount*)Check_For_Account_ID(accNumber))->Buy_Stock(amount, Find_Stock(code)->name, code, Find_Stock(code)->price * amount, todayDate);
    Write_Account(accNumber);


}


void PersonalAssistant::Sell_Stock(int accNumber, string code, int amount){
    if(Check_For_Account_ID(accNumber) == nullptr){
        cout<<YELLOW<<"Account not found"<<RESET<<endl;
        return;
    }

    pair<int, string> p = ((investmentAccount*)Check_For_Account_ID(accNumber))->Sell_Stock(amount, code);

    if(p.first == 0){
        return;
    }
    string text = "Sold "+to_string(amount)+" stocks of "+(Find_Stock(code)->name);
    Check_For_Account_ID(accNumber)->Create_Transfer_In(Find_Stock(code)->price*amount, text, 0, "Stock market", todayDate);
    Write_Account(accNumber);
}





void PersonalAssistant::Remove_Account(int accID){
    for (auto it = accounts.begin(); it != accounts.end(); ++it){
        if((*it).GetID() == accID){
            string source = (to_string(accID)+".txt");
            const char * c = source.c_str();
            remove(c);
            if((*it).Check_If_Investment()){
                string sourceS = (to_string(accID)+"s.txt");
                const char * s = sourceS.c_str();
                remove(s);
            }
            accounts.erase(it);
            cout<<"Successfully closed account "<<accID<<endl;
            Write_Account_IDs();
            Write_All_Accounts();
            return;
        }

    }
}





//TEXTFILES

void PersonalAssistant::Write_Account(int accountID){
    fstream accFile;
    accFile.open(to_string(accountID)+".txt", ios::out);
    if(accFile.is_open()){
        if(Check_For_Account_ID(accountID)->Check_If_Investment()){
            accFile << "I" <<endl;
        }
        else accFile << "P" << endl;
       accFile << accountID << endl << Check_For_Account_ID(accountID)->GetOwnerID() << endl << Get_Owners_Name(accountID) << endl << Check_For_Account_ID(accountID)->GetBalance() <<endl;
       accFile << Check_For_Account_ID(accountID)->Save_History() << endl;
    }
    accFile.close();
    if(Check_For_Account_ID(accountID)->Check_If_Investment()){
        fstream stockFile;
        stockFile.open(to_string(accountID)+"s.txt", ios::out);
        if(stockFile.is_open()){
            stockFile << ((investmentAccount*)(Check_For_Account_ID(accountID)))->Save_Stocks();
        }
        stockFile.close();
    }


}

void PersonalAssistant::Write_Account_IDs(){
    fstream accIDs;
    accIDs.open("accountIDs.txt", ios::out);
    for (auto it = accounts.begin(); it != accounts.end(); ++it){
        accIDs << (*it).GetID() << endl;
    }
}

void PersonalAssistant::Write_All_Accounts(){
     Write_Account_IDs();
    for (auto it = accounts.begin(); it != accounts.end(); ++it){
        Write_Account((*it).GetID());
    }

}


void PersonalAssistant::Load_Account(int accountID){

    string type;
    string accID;
    string ownerID;
    string ownerName;
    string balance;
    fstream accFile;

    accFile.open(to_string(accountID)+".txt", ios::in);
    if(accFile.is_open()){

        getline(accFile, type);
        getline(accFile, accID);
        getline(accFile, ownerID);
        getline(accFile, ownerName);
        getline(accFile, balance);
        string value;
        string title;
        string recID;
        string sendID;
        string recName;
        string sendName;
        string day;
        string month;
        string year;


            if(type == "P"){

                Register_Personal_Account(stoi(ownerID), ownerName, stoi(accID), stof(balance));
            }
            else{

                Register_Investment_Account(stoi(ownerID), ownerName, stoi(accID), stof(balance));
            }
            while(getline(accFile, value)){
                    if(value == ""){
                        break;
                    }
                    getline(accFile, title);
                    getline(accFile, recID);
                    getline(accFile, sendID);
                    getline(accFile, recName);
                    getline(accFile, sendName);
                    getline(accFile, day);
                    getline(accFile, month);
                    getline(accFile, year);

                    Check_For_Account_ID(accountID)->Load_Transfer(stof(value), title, stoi(recID), stoi(sendID), recName, sendName, stoi(day), stoi(month), stoi(year));
                }
    }
        accFile.close();

    if(type == "I"){

        string stockPrice;
        string stockCode;
        string stockName;
        string stockAmount;

        fstream stockFile;
        stockFile.open(to_string(accountID)+"s.txt", ios::in);

                if(stockFile.is_open()){
                    while(getline(stockFile, stockPrice)){
                        if(stockPrice == "") return;
                        getline(stockFile, stockName);
                        getline(stockFile, stockCode);
                        getline(stockFile, stockAmount);
                        //cout<<stockPrice << endl << stockName << endl << stockCode << endl << stockAmount << endl;
                        ((investmentAccount*)(Check_For_Account_ID(accountID)))->Load_StockPair(stof(stockPrice), stockName, stockCode, stoi(stockAmount));
                    }
                    stockFile.close();
                }

    }
}


void PersonalAssistant::Load_All_Accounts(){
    string id;
    fstream accIDs;
    accIDs.open("accountIDs.txt", ios::in);
    if(accIDs.is_open()){
      while(getline(accIDs, id)){
        if(id == "") return;
        Load_Account(stoi(id));
      }
    }

}
