/*
    File Name: driver.cpp
    Author: Mohammed Alturki
    Date: November 30, 2020
    Purpose: Geek store program that stores items from user either manually or from a file
*/

#include <iostream>
#include "item.h"

using namespace std;

int main()
{
    //defining variabls
    int max_size, curr_size = 0;
    int choice;
    Item *items;

    cout<<"GEEK FACTORY"<<endl;
    cout<<"What is the maximum number of items your factory can hold?"<<endl;
    cin>>max_size;
    cin.ignore();
    
    //dynamic allocation
    items = new Item[max_size];

    do{
        //calling case based on the user choice
        choice = menu();
        switch(choice)
        {
            case 1:
                curr_size = add(items, max_size, curr_size);
                break;
            
            case 2:
                printItems(items, curr_size);
                break;

            case 3:
                saveInventory(items, curr_size);
                cout<<"Goodbye! \n";
                break;
        }
    }while(choice!=3);

    delete [] items;
}