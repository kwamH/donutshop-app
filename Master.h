#ifndef MASTER_H
#define MASTER_H
#include <string>
#include "Register.h"

class Master
{
    public:
        Master();
        char Login();
        void StartUp();
        void AppendNode(int key, std::string item, double price);
        void DeleteNode(std::string key);
        void FetchMenu();
        void PrintMenu();
        void EditPrice(std::string key);
        double GetPrice(std::string key);
        std::string GetItem(std::string key);


    private:
        int _numItems;
        std::string _empLog;
        std::string _mgtLog;
        char E_auth;
        char M_auth;
        Register reg;
        struct Node {
            std::string _item;
            double _price;
            int _key;
            Node *_next;
        };
    Node *_head;
};

#endif // MASTER_H
