#include "OrderTrade.h"
#include <iostream>
#include "CSVReader.h"


OrderTrade::OrderTrade(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

OrderTrade::OrderTrade(std::string filename, std::string product)
{
    orders = CSVReader::readCSV(filename);
}


std::vector<OrderBookEntry> OrderTrade::getOrders(OrderBookType type, 
                                        std::string product
                                        )
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type && 
            e.product == product)
            {
                orders_sub.push_back(e);
            }
    }
    return orders_sub;
}