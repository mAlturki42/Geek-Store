/*
    File Name: functions.cpp
    Author: Mohammed Alturki
    Date: November 30, 2020
    Purpose: Geek store program that stores items from user either manually or from a file
*/

#include "item.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//function called manu that calls the main menu and return choice
int menu(){
    int choice;

    cout << "Please choose from the following options:" << endl;
    cout << "1.\tAdd awesome item(s)." << endl;
    cout << "2.\tPrint all items." << endl;
    cout << "3.\tEnd the program." << endl;
    cout << "\nCHOOSE 1-3:  ";
    cin >> choice;
    while(choice < 1 || choice > 3 )
    {
        cout << "Invalid Entry. Please choose 1-3: ";
        cin >> choice;
        cin.ignore();
    }
    return choice;
}

//function to convert string to float
float stringToFloat(string str){
    float number;
    char convertStr[1000];
    strcpy(convertStr, str.c_str()); //convert the string to c-string
    number = atof(convertStr);
    return number;
}

int add(Item items[], int max_size, int &curr_size){
    //defining variabls
    int ctr = 0;
    int choice;
    int num;
    string temp;
    string fileName;
    ifstream inFile(fileName);
    Money cost;

    do{
        cout << "\nDo you want to...." << endl;
        cout << "1.\tAdd items from a file?" << endl;
        cout << "2.\tAdd one item manually?" << endl;
        cout << "3.\tReturn to main menu?" << endl;
        cout << "CHOOSE 1-3:  ";
        cin >> choice;
        while(choice < 1 || choice > 3 )
        {
            cout << "Invalid Entry. Please choose 1-3: ";
            cin >> choice;
            cin.ignore();
        }

        switch(choice){
            case 1:
                //checks if size is full
                if(curr_size == max_size)
                {
                    cout<<"OOPS! Your factory warehouse is full \n\n";
                    break;
                }

                cout<<"\nWhat is the name of the file that contains your inventory items? " << endl;
                cin>>fileName;
                cin.ignore();
                inFile.open(fileName);


                if(!inFile)
                {
                    cout<<"\nI am unable to open your file.  I'm sorry." << endl;
                    break;
                }

                else{
                    ctr = 0;
                    //reading items from a file
                    while(curr_size<max_size && getline(inFile,temp,'#')){
                        for(int i=0; i<temp.size(); i++){
                            cout << temp[i];
                            items[curr_size].name= temp;
                            cout << "name has been read.\n\n";

                            getline(inFile,items[curr_size].description, '#');

                            getline(inFile, temp, '#');
                            items[curr_size].cost.rawPrice = stringToFloat(temp);
                            
                            getline(inFile, temp, '#');
                            items[curr_size].cost.salePrice = stringToFloat(temp);

                            getline(inFile, temp, '#');
                            items[curr_size].cost.profit = stringToFloat(temp);

                            getline(inFile,temp,'#');
                            items[curr_size].numStores = stringToFloat(temp);
                            items[curr_size].stores = new string[items[curr_size].numStores];

                            for(int x=0; x<items[curr_size].numStores; x++){
                                getline(inFile, items[curr_size].stores[x], '#');
                            }

                            getline(inFile, items[curr_size].date, '#');

                            //incrementing current size 
                            curr_size++;
                            
                        }
                        ctr++;
                    }
                }
                inFile.close();
                cout<<ctr<<" items from the " << fileName << " file have been added!\n\n";
                break;

            case 2:
                if(curr_size == max_size)
                {
                    cout<<"OOPS! Your factory warehouse is full \n\n";
                    break;
                }
                //getting input from user manually
                cin.ignore();
                cout<<"NAME:   ";
                getline(cin,items[curr_size].name);
                cout<<"DESCRIPTION:   ";
                getline(cin,items[curr_size].description);
                
                cout<<"RAW MATERIALS COST (cost to make item):   ";
                cin>>items[curr_size].cost.rawPrice;
                cout<<"SALE PRICE (price when you sell item):   ";
                cin>>items[curr_size].cost.salePrice;
                cin.ignore();
                
                items[curr_size].cost.profit = items[curr_size].cost.salePrice - items[curr_size].cost.rawPrice;
                
                cout<<"ENTER THE NUMBER OF STORES THAT SUPPLY THIS ITEM: ";
                cin>>items[curr_size].numStores;
                cin.ignore();
                
                items[curr_size].stores = new string[items[curr_size].numStores];
                for(int i=0;i<items[curr_size].numStores;i++){
                    cout << "STORE " << i+1 << " NAME:   ";
                    cin>>items[curr_size].stores[i];
                    cin.ignore();
                }
                cout<<"CREATION DATE (example:  04 02 16): ";
                getline(cin,items[curr_size].date);
                
                // add item to items[]
                curr_size++;
                
                cout<<"Item added \n\n";
                break;
            
            case 3:
                break;
        }
    }while(choice != 3);

    delete [] items[curr_size].stores;
    
    return curr_size;
}

//function to print items
void printItems(Item items[],int curr_size)
{
    if(curr_size>0)
    {
        cout << "ALL ITEMS:" << endl << endl;
        for(int i=0; i<curr_size; i++){
            cout << "----------------------------------------------------------------------" << endl;
            cout << "\t\t\t\t\t\t\tITEM " << i+1 << endl;
            cout << "NAME:\t" << items[i].name << endl << endl;
            cout << "DESCRIPTION:\t" << items[i].description << endl << endl;
            cout << "GOODS PRICE:\t" << items[i].cost.rawPrice << endl << endl;
            cout << "SALE PRICE:\t" << items[i].cost.salePrice << endl << endl;
            cout << "PROFIT:\t\t" << items[i].cost.profit << endl << endl;
            cout << "STORES WHO SALE THIS ITEM:" << endl;
            for(int x=0; x<items[i].numStores; x++){
                cout << "\t\tSTORE " << x+1 << " NAME: " << items[i].stores[x] << endl;
            }
            cout << "\nCREATION DATE:\t" << items[i].date << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }
    }
    else{
        cout << "There are no items to print." << endl << endl;
        return;
    }
}

//write items into a file
void saveInventory(Item items[],int curr_size)
{
    string fileName;
    ofstream outFile(fileName);
    
    if(curr_size>0){
        cout << "\nWhat do you want to name your inventory file? (example.txt):" << endl;
        cin >> fileName;
        //cin.ignore();
       
        for(int i=0; i<curr_size; i++){
            outFile << items[i].name << "#";
            outFile << items[i].description << "#";
            outFile << items[i].cost.rawPrice << "#";
            outFile << items[i].cost.salePrice << "#";
            outFile << items[i].cost.profit << "#";
            outFile << items[i].numStores << "#";

            for(int x=0; x<items[i].numStores; x++){
                outFile << items[i].stores[x] << "#";
            }
            outFile << items[i].date << "#";  
        } 
    }
    else{
        cout << "There are no items to save to a file." << endl << endl;
        return;
    }

    cout << "\nAll your weird items have been saved to " << fileName << endl << endl;
    outFile.close();
}