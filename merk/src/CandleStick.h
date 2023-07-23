#include <iostream>
#include <vector>

class Candlestick {
public:
    Candlestick(double open, double close, double high, double low)
        : open(open), close(close), high(high), low(low) {}

    void update(double price) {
        close = price;
        high = std::max(high, price);
        low = std::min(low, price);
    }

    double getOpen() const { return open; }
    double getClose() const { return close; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    double getValue() { return value ;}
    void setValue(double newValue) { value = newValue; }



private:
    std::vector<Candlestick> computeCandlesticks(std::vector<Trade>& trades);
    double open;
    double close;
    double high;
    double low;
    double value = 0.0;

};




class Trade {
public:
    Trade(const std::string& timestamp, const std::string& pair, const std::string& type, double price, double quantity)
        : timestamp(timestamp), pair(pair), type(type), price(price), quantity(quantity) {}

    const std::string& getTimestamp() const { return timestamp; }
    const std::string& getPair() const { return pair; }
    const std::string& getType() const { return type; }
    double getPrice() const { return price; }
    double getQuantity() const { return quantity; }

private:
    std::string timestamp;
    std::string pair;
    std::string type;
    double price;
    double quantity;
};
