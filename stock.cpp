#include "stock.h"

Stock::Stock(float price, string name, string code)
{
    if(price < 0) throw "Price of stock cannot be less than 0";
    this->price = price;
    this->name = name;
    this->code = code;
}

Stock::~Stock()
{
    //dtor
}
