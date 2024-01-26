#include "Master.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <conio.h>
using namespace std;

Master::Master()
{
   _head = nullptr;
   _numItems = 0;
   _empLog = "000111";
   _mgtLog = "889303";
   E_auth = 'E';
   M_auth = 'M';
   StartUp();

}

char Master::Login()
{
    string input;
    cout << "\t\t\t Enter you employee or management pin:  " ;
    cin >> input;

    if(input == _empLog)
    {
        return E_auth;
    }
    else if(input == _mgtLog)
    {
        return M_auth;
    }

    return 'X';
}

void Master::StartUp()
{
    bool running = true;
    FetchMenu();
    char login = Login();
    while(running == true)
    {
        if(login == E_auth)
        {
            cout << " You are logged in as an EMPLOYEE" << endl;
            PrintMenu();
            double total = 0;
            cout << "Enter the number next to the item you would like ";
            cout << "to purchase: ";
            string ip;
            bool close = false;
            while(close == false)
            {
                bool again = false;
                cin >> ip;
                if(ip == "C" || ip == "c")
                {
                    close = true;
                    running = false;
                    reg.PrintReceipt(total);
                    break;
                }

                for(int i = 0; i < ip.length(); i++)
                {
                    if(isdigit(ip[i]) == false)
                       {
                        again = true;
                        break;
                       }
                }
                if(again == true)
                    continue;
                Node *ptr = _head;
                while(ptr != nullptr)
                {
                    if(stoi(ip) == ptr->_key)
                    {
                      total = total + reg.StartSale(GetItem(ip), GetPrice(ip));
                      break;
                    }
                    ptr = ptr->_next;
                }

            }


        }
        else if(login == M_auth)
        {
            string input;
            cout << " You are logged in as MANAGEMENT" << endl;
            PrintMenu();
            cout << "Which Menu item would you like to edit?" << endl;
            cout << "Enter number: ";
            cin >> input;
            if(input == "R")
            {
                login = Login();
                continue;
            }
            cout << " Delete item or edit price (D/E): " << endl;
            bool flag = false;
            while(flag == false)
            {
                switch(getch())
                {
                    case 'D':
                        DeleteNode(input);
                        flag = true;
                        break;
                    case 'E':
                        EditPrice(input);
                        PrintMenu();
                        flag = true;
                        break;
                };
            }
        }
        else
        {
            cout << " The pin you entered is INCORRECT..." << endl;
            login = Login();
            continue;

        }

    }

}

void Master::EditPrice(string key)
{
    Node *temp = new Node();
    temp = _head;
    double newPrice;
    while(temp != nullptr)
    {
        if(stoi(key) == temp->_key)
        {
            cout << temp->_item << endl;
            cout << "Current Price: $" << temp->_price << endl;
            cout << "New Price: $";
            bool flag = false;
            while(flag == false)
            {
                cin >> newPrice;
                if(newPrice > 0.01 && newPrice < 10.99)
                {
                    temp->_price = newPrice;
                    flag = true;
                }
            }

        }
        temp = temp->_next;
    }
}

void Master::AppendNode(int key, string item, double price)
{
    Node *ptr = new Node();
    ptr->_key = key;
    ptr->_item = item;
    ptr->_price = price;
    ptr->_next = nullptr;
    if(_head == nullptr)
    {
        _head = ptr;
        _numItems++;
    }
    else
    {
        Node *temp = new Node();
        temp = _head;
        while(temp->_next != nullptr)
        {
            temp = temp->_next;
        }
        temp->_next = ptr;
        _numItems++;
    }
}

void Master::DeleteNode(string key)
{
    if(_head == nullptr)
    {
        cout << " You have no items on your Menu..." << endl;
        return;
    }
    else if(stoi(key) == _numItems-(_numItems-1))
    {
        Node *ptr = new Node();
        ptr = _head;
        _head = _head->_next;
        cout << "You deleted " << ptr->_item << " from the menu..." << endl;
        delete ptr;
        _numItems--;
        Node *a = _head;
        while(a != nullptr)
        {
            a->_key = a->_key-1;
            a = a->_next;
        }
        return;
    }

    Node *ptr1, *prev;
    if(_head == nullptr)
    {
        cout << " You have no items on your Menu..." << endl;
        return;
    }
    else if(_head->_next == nullptr)
    {
        ptr1 = _head;
        _head = nullptr;
        delete ptr1;
        return;
    }
    else if(stoi(key) == _numItems)
    {
        ptr1 = _head;
        while(ptr1->_next != nullptr)
        {
            prev = ptr1;
            ptr1 = ptr1->_next;
        }
        prev->_next = nullptr;
        cout << "You deleted " << ptr1->_item << " from the menu..." << endl;
        delete ptr1;
        _numItems--;
        return;
    }
    Node *temp = new Node();
    temp = _head;
    while(temp->_next != nullptr)
    {
        if(temp->_key == stoi(key))
        {
            cout << "You deleted " << temp->_item << " from the menu..." << endl;
            Node *temp2 = temp->_next;
            temp->_key = temp2->_key-1;
            temp->_item = temp2->_item;
            temp->_price = temp2->_price;
            temp->_next = temp2->_next;
            delete temp2;
            _numItems--;
            temp = temp->_next;

            Node *num = temp;
            while(num != nullptr)
            {
                num->_key = num->_key-1;
                num = num->_next;
            }
            return;

        }
        temp = temp->_next;
    }


}

void Master::FetchMenu()
{
    ifstream inFile;
    inFile.open("menu.txt");
    if(inFile.is_open())
    {
        cout << "File opened successfully..." << endl;
        int key;
        string item;
        double price;
        while(inFile >> key)
        {
            inFile.ignore();
            getline(inFile, item);
            inFile >> price;
            AppendNode(key, item, price);

        }
    }
    else
    {
        cout << " Error opening the file..." << endl;
    }
    inFile.close();
}

void Master::PrintMenu()
{
    Node *temp = new Node();
    temp = _head;
    cout << "***************" << endl;
    cout << "*             *" << endl;
    cout << "   " << _numItems << " Items    " << endl;
    cout << "*             *" << endl;
    cout << "***************" << endl;
    while(temp != nullptr)
    {
        cout << temp->_key << ") " << setw(30) << temp->_item << setw(30)
        << fixed << showpoint << setprecision(2) << temp->_price << endl;
        temp = temp->_next;
    }

}

string Master::GetItem(string key)
{
    Node *ptr = new Node();
    ptr = _head;
    string holder;
    while(ptr != nullptr)
    {
        if(stoi(key) == ptr->_key)
        {
            holder = ptr->_item;
            return holder;
        }
        ptr = ptr->_next;
    }
    return "X";
}

double Master::GetPrice(string key)
{
    double holder;
    Node *ptr = new Node();
    ptr = _head;
    while(ptr != nullptr)
    {
        if(stoi(key) == ptr->_key)
        {
            holder = ptr->_price;
            return holder;
        }
        ptr = ptr->_next;
    }
    return 0;
}
