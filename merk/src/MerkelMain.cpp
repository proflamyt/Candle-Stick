#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <algorithm> 
#include <iomanip>


MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}


void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 print candlestick
    std::cout << "6: Print CandleStick " << std::endl;
    // 7 plot graph
    std::cout << "7: Plot Graph " << std::endl;
    // 8 continue   
    std::cout << "8: Continue " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, 
                                                                p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;



    }
    // std::cout << "OrderBook contains :  " << orders.size() << " entries" << std::endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.orderType == OrderBookType::ask)
    //     {
    //         asks ++;
    //     }
    //     if (e.orderType == OrderBookType::bid)
    //     {
    //         bids ++;
    //     }  
    // }    
    // std::cout << "OrderBook asks:  " << asks << " bids:" << bids << std::endl;

}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::ask 
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }   
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::bid 
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }   
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl; 
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
        
    }

    currentTime = orderBook.getNextTime(currentTime);
}
 
int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-8" << std::endl;
    std::getline(std::cin, line);
    try{
        userOption = std::stoi(line);
    }catch(const std::exception& e)
    {
        // 
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::plotCandle(std::string product, std::string type, int input3 = 1)
{
    std::cout << "Plotting " << std::endl;
    std::vector<OrderBookEntry>  trades = orderTrade.getOrders(OrderBookEntry::stringToOrderBookType(type), product);
    std::vector<Candlestick> candles = candleStick.computeCandlesticks(trades);
    if (input3 == 1) 
        Output(candles);
    else 
        Plot(candles);
    
}

void MerkelMain::plotDataGraph()
{
    std::cout << "Plotting Data Graph" << std::endl;
    std::vector<OrderBookEntry>  trades = orderTrade.getOrders(OrderBookEntry::stringToOrderBookType("ETH/BTC"), "bid");
    PlotGraph(trades);
    
};

void MerkelMain::PlotGraph(std::vector<OrderBookEntry> trades) 
{
    int lenght;
    std::vector<int> amounts ;
    std::vector<int> prices ;

    // extract data
    for (int i = 1; i <= 20; ++i) {
        amounts.push_back(trades[i].amount ); 
        prices.push_back(trades[i].price);
    }

    // sort data 

    std::sort(amounts.begin(), amounts.end());
    std::sort(prices.begin(), prices.end());

    for (int i=1; i < trades.size(); i++) {

        lenght =  (prices[i] / (prices[i] + prices[i-1])) * 6  ;

        for (int len = 0; len < lenght; len++) {
            std::cout << "|";
        }

        std::string spaces(amounts[i], ' ');
        std::cout << spaces << "*" << std::endl;

    }

    std::cout << "_________________" ;

}


void MerkelMain::Output(const std::vector<Candlestick>& candle)
{
        // Print the header row
             std::cout << std::left << std::setw(50) << "CLOSE"
              << std::setw(15) << "HIGH"
              << std::setw(50) << "OPEN"
              << std::setw(50) << "LOW" << std::endl;

    for (const auto& row : candle) {
        std::cout << std::left << std::setw(50) << row.getClose();
        std::cout << std::left << std::setw(15) << row.getHigh();
        std::cout << std::left << std::setw(50) << row.getOpen();
        std::cout << std::setprecision(10) << std::left << std::setw(50) << row.getLow() << std::endl;
    }
}

// Added  Box

std::string MerkelMain::Box(int width, int height) {
    // create box based on lenght of the top and bottom
    std::string box = "";
    // create width
    for (int i = 0; i < width; ++i) {
        box += "-";
    }

    // create hight
    for (int i = 1; i < height - 1; ++i) {
        std::string spaces(width - 1, ' ');
        box += "\n|";
        box += spaces;
        box += "|";
    }

    box += "\n";
    // create width
    for (int i = 0; i < width; ++i) {
        box += "-";
    }

    return box;

    
};

void MerkelMain::Plot(const std::vector<Candlestick>& candles)
{

    const int plotWidth = 11; 
    const int plotHight = 11;
    const int plotBase = 0 ;
    int btw_spaces = 3;


    for (auto candle : candles) {
    
    int openPosition = ((candle.getOpen() - candle.getLow()) / (candle.getHigh() - candle.getLow())) * (plotHight - plotBase) + plotBase;
    int closePosition = ((candle.getClose() - candle.getLow()) / (candle.getHigh() - candle.getLow())) * (plotHight - plotBase) + plotBase;
    int highPosition = (plotHight / (candle.getHigh() - candle.getLow())) * candle.getHigh();
    int lowPosition = (plotHight / (candle.getHigh() - candle.getLow())) * candle.getLow();
    

    // int opening = candle.getOpen() * 7 / 140; // _______________
    // int highing = candle.getHigh() * 7 / 140; // | at 11 till close
    // int lowhing = candle.getLow() * 7 / 140; // | at 11 till close
    // int closing = candle.getClose() * 7 / 140;


    // openPosition =  openPosition % 7;
    // closePosition =  closePosition % 7;

    std::cout << openPosition << std::endl;
    std::cout << closePosition << std::endl;

    for (int i = 0; i <= 7; ++i) {
        // 7 for 140 price 
        std::cout << "|" ;

        while (i != closePosition && i != openPosition && i < 8 && (i < openPosition || i > closePosition))
        {
            
            std::string spaces(plotWidth / 2, ' ');
            std::cout << spaces << "|" << std::endl;
            std::cout << "|" ;
            ++i;
        }
        while (i > openPosition && i < closePosition)
        {
            std::string spaces(20, ' ');
            std::cout << spaces << "|" << std::endl;
            std::cout << spaces  << "|" << std::endl;
            std::cout << "|" ;
            ++i;
        }
        
        std::cout << std::endl << "|" ;
        if (i == closePosition || i == openPosition) {
            std::string spaces(2, ' ');
            std::cout << spaces <<"_________________" ;
        }
        
        

        std::cout << std::endl;

    }

   
    std::cout << "| ";
    std::cout << "_____________________" << std::endl;

    std::cout << std::endl;



    }
}


void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printMarketStats();
    }
    if (userOption == 3) 
    {
        enterAsk();
    }
    if (userOption == 4) 
    {
        enterBid();
    }
    if (userOption == 5) 
    {
        printWallet();
    }
    if (userOption == 6) 
    {
        std::cout << "Enter Option For \n 1. ask \n 2. bid " << std::endl;
        std::string product, type;

        int input1 = getUserOption();

        std::cout << "Enter Option For \n1. ETH/UDST \n2. ETH/BTC \n3. DOGE/BTC" << std::endl;
        int input2 = getUserOption();

        std::cout << "Enter Option For \n 1. Display \n 2. Graph " << std::endl;
        int input3 = getUserOption();

        if (input1 == 1) {
            type = "ask";
        } else if (input1 == 2) {
            type = "bid";
        } else {
            std::cout << "Error: Invalid option. Please enter 1 for asks or 2 for bids." << std::endl;
        }
        
        if (input2 == 1) {
            product = "ETH/UDST";
        } else if (input2 == 2) {
            product = "BTC/USDT";
        } else if (input2 == 3) {
            product = "DOGE/BTC";
        }
        else {
            std::cout << "Error: Invalid option. Please enter 1 for asks or 2 for bids." << std::endl;
        }

        plotCandle(product, type, input3);
    }   
    if (userOption == 7) 
    {
        plotDataGraph();
    }
    if (userOption == 8) 
    {
        gotoNextTimeframe();
    }    
}


