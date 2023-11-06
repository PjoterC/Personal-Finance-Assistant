#ifndef STOCK_H
#define STOCK_H

#include <string>
using namespace std;
class Stock
{
    public:
        Stock(float price, string name, string code);
        ~Stock();
        float price;
        string name;
        string code;

    protected:

    private:
};

#endif // STOCK_H
