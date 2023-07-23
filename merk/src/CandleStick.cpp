#include "CandleStick.h"
#include <iostream>

std::vector<Candlestick> Candlestick::computeCandlesticks(std::vector<Trade>& trades) {
    std::vector<Candlestick> candlesticks;
    double value = 0, price;

    for (auto& trade : trades) {

        Candlestick candle(0,0,0,0);

        // Open = the average price per unit in the previous time frame. 

        // sumation of all amount * price / summation of price
        value += trade.getQuantity() * trade.getPrice();
        price += trade.getPrice();


        candle.high = std::max(candle.high, price);
        candle.low = std::min(candle.low, price);

        candle.open = candlesticks.back().getValue();

        candle.close = value/price;

        candle.setValue(close);

        candlesticks.push_back(candle);
    }

    
   

    return candlesticks;
}