#ifndef TRANSFER_H
#define TRANSFER_H
#include <string>
#include <iostream>
#include "date.h"
using namespace std;
class Transfer
{
    public:
        Transfer(float value, string title, int recID, int sendID, string recName, string sendName, Date& date);
        ~Transfer();


        void Disp(); //Displays the transfer data

        float GetValue() const;
        string GetTitle() const;
        int GetReceiverID() const;
        int GetSenderID() const;
        string GetReceiverName() const;
        string GetSenderName() const;
        friend std::ostream& operator<<(std::ostream& os, const Transfer& t); //used when saving to txt
        Date GetDate() const;



    protected:

    private:
        float value;
        string title;
        int receiverID;
        int senderID;
        string receiverName;
        string senderName;
        Date transferDate;


};

#endif // TRANSFER_H
