/*
    File Name: item.h
    Author: Mohammed Alturki
    Date: November 30, 2020
    Purpose: Geek store program that stores items from user either manually or from a file
*/

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string> 

using namespace std;

//structure called Money
struct Money
{
    float rawPrice, salePrice, profit;
    
    //constructors
    Money(){}
    Money(float rawPrice,float salePrice,float profit):rawPrice(rawPrice),salePrice(salePrice),profit(profit){}
};

//structure called Item that has Money nusted structure 
struct Item
{
    string name, description, date;
    Money cost;
    int numStores;
    string *stores;
    
    //constructors
    Item(){}
    Item(string n, string d, Money m, int num, string ns[], string dt)
    {
        name = n;
        description = d;
        cost = m;
        numStores = num;
        stores = ns;
        date = dt;
    }
};

//functions prototype
int menu();
int add(Item*, int, int &);
void saveInventory(Item items[],int curr_size);
void printItems(Item items[],int curr_size);
float stringToFloat(string);



#endif