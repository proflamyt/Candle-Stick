#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "OrderTrade.h"
#include "CandleStick.h"


class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void plotCandle(std::string product, std::string type, int input3);
        void plotDataGraph();
        std::string Box(int width, int height);
        void processUserOption(int userOption);
        void PlotGraph(std::vector<OrderBookEntry> trades);
        void Plot(const std::vector<Candlestick>& candle);
        void Output(const std::vector<Candlestick>& candle);

        std::string currentTime;

//        OrderBook orderBook{"20200317.csv"};
	    OrderBook orderBook{"20200601.csv"};
        OrderTrade orderTrade{"20200601.csv"};
        Candlestick candleStick{0.0, 0.0,0.0,0.0};
        Wallet wallet;

};
