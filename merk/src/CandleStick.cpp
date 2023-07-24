#include "CandleStick.h"
#include <iostream>


std::vector<Candlestick> Candlestick::computeCandlesticks(std::vector<OrderBookEntry>& trades) {

    std::vector<Candlestick> candlesticks;
    

    for (size_t i = 0; i < trades.size(); ++i) {

        double value = 0.0, amount = 0.0;
        Candlestick candle(0.0, 0.0, 0.0, 10000000000000);

        // Open = the average price per unit in the previous time frame. 

        while (i + 1 < trades.size() && trades[i + 1].timestamp == trades[i].timestamp) {
            // sumation of all amount * price / summation of price
           
            value += (trades[i].amount * trades[i].price);
            amount += trades[i].amount;
            candle.high = std::max(candle.high, trades[i].price);
            candle.low = std::min(candle.low, trades[i].price);
            ++i;
        }

        // previous close
       if (candlesticks.size() != 0) candle.open = candlesticks.back().close;

        candle.close = value / amount;

        candlesticks.push_back(candle);
    }

    return candlesticks;
}