#ifndef REGISTER_H
#define REGISTER_H
#include <string>
#include <vector>


class Register
{
    public:
        Register();
        double StartSale(std::string item, double price);
        int GetOrderID();
        void PrintReceipt(double subtotal);


    private:
            std::string _time;
            double _tax;
            int _orderID;
            std::vector<std::string> _item;
            std::vector<double> _price;
};

#endif // REGISTER_H
