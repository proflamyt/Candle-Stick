#include <iostream>
#include <vector>
#include "OrderBookEntry.h"

class Candlestick {
public:
    Candlestick(double open, double close, double high, double low)
        : open(open), close(close), high(high), low(low) {}


    double getOpen() const { return open; }
    double getClose() const { return close; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    double getValue() { return value ;}
    
    std::vector<Candlestick> computeCandlesticks(std::vector<OrderBookEntry>& trades);
    



private:
    double open;
    double close;
    double high;
    double low;
    double value = 0.00;

};




                       
