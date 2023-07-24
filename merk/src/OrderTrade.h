#include <iostream>
#include <vector>
#include "OrderBookEntry.h"


class OrderTrade    
{
    public: 
        OrderTrade(std::string filename, std::string product);
        OrderTrade(std::string filename);
        std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product);

    
     private:
        std::vector<OrderBookEntry> orders;

    
};