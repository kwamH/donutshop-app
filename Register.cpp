#include "Register.h"
#include <string>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

Register::Register()
{
    _tax = 0.0825;
}

int Register::GetOrderID()
{
    int num;
    srand(time(0));
    num = rand()%8999;
    return num;
}

double Register::StartSale(string item, double price)
{
    double total = 0.0;
    cout << "- " << item << setw(20) << price << endl;
    _item.push_back(item);
    _price.push_back(price);
    total = total + price;
    return total;
}

void Register::PrintReceipt(double subtotal)
{

    cout << "\n Your total is  $" << subtotal + (subtotal*_tax) << endl;
    cout << "\n\nPrinting Receipt...." << endl;
    cout << "       Thank You :)" << endl;
    ofstream outFile;
    outFile.open("rpt.txt");
    outFile << "\t\t\t\t\t Ticket #" << GetOrderID() << endl;
    outFile << "<World" << " " << "Famous" << " " << "Donuts>" << endl << endl;
    for(int i = 0; i < _item.size(); i++)
    {
        outFile << "- " << setw(29) << _item[i] << setw(43) << _price[i] << endl;
    }

    outFile << "\n\n";
    outFile << fixed << showpoint << setprecision(2);
    outFile << "subtotal: $" << subtotal << endl;
    outFile << "tax:      $" << subtotal * _tax << endl;
    outFile << "          ---------------" << endl;
    outFile << "Total:    $" << subtotal + (subtotal*_tax);
    outFile.close();
}

