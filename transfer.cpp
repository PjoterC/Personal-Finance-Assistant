#include "transfer.h"


Transfer::Transfer(float value, string title, int recID, int sendID, string recName, string sendName, Date& date) : transferDate(date)

{

    if(value == 0) throw "You can't make a transfer of value 0";
    this->value = value;
   this->title = title;
   this->receiverID = recID;
   this->senderID = sendID;
   this->receiverName = recName;
   this->senderName = sendName;
   this->transferDate = date;


}

Transfer::~Transfer()
{

}


void Transfer::Disp(){ // Z jakiegoœ niewiarygodnego powodu jest b³¹d przy displayu


    cout<<"--------------------------------------"<<endl;


    if(this->GetDate().day < 10) std::cout<<0;
    cout<<this->GetDate().day;
    cout<<".";
    if(this->GetDate().month < 10) std::cout<<0;
    cout<<this->GetDate().month;
    cout<<".";
    cout<<this->GetDate().year<<endl;

    cout<<title<<endl;

    cout<<value<<" PLN"<<endl;

    if(senderID == 0){
            cout<<"Source: "<<senderName<<endl;
        }
        else{
            cout<<"From: "<<senderName<<" "<<senderID<<endl;
        }
    if(receiverID == 0){
        cout<<"For: "<<receiverName<<endl;
    }
        else{
            cout<<"To: "<<receiverName<<" "<<receiverID<<endl;
        }
        cout<<"--------------------------------------"<<endl;

    }







float Transfer::GetValue() const {
    return value;
}

string Transfer::GetTitle() const {
    return title;
}

int Transfer::GetReceiverID() const {
    return receiverID;
}

int Transfer::GetSenderID() const {
    return senderID;
}

string Transfer::GetReceiverName() const {
    return receiverName;
}

string Transfer::GetSenderName() const {
    return senderName;
}




Date Transfer::GetDate()const {
    return transferDate;
}

std::ostream& operator<<(std::ostream& os, const Transfer& t){

    os << t.GetValue() << endl << t.GetTitle() << endl << t.GetReceiverID() << endl << t.GetSenderID() << endl << t.GetReceiverName() << endl << t.GetSenderName() << endl << t.GetDate();

    return os;
}

