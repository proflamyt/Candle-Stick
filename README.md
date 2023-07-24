# Candle-Stick


To Access the added Features to this simulation, plotCandle(product, type, input3); and plotDataGraph(); were added with option 6 and 7; ones option 6 is clicked you would have to choose between displaying the graph and displaying the candlestick data .


HOW THIS WAS IMPLEMENTED


In the file "OrderTrade.cpp", The CSV was read and parsed to be processed in the "CandleStick.cpp"


To Represent Each Candle Stick, A Candlestick object was created containing the attributes of a candle stick 
which are the high, low, close, and open.

# High :

As stated in the question the High is the highest price seen in a specific time frame; to compute this , i compared the prices to find which is higher until that current time stamp changes or the loops stop, doing this, i get the highest price of that timestamp.

this snippet of code shows me comparing each prices with the previous one and storing the maximum of both until the timestamp changes or the loop ends. 

```c++
while (i + 1 < trades.size() && trades[i + 1].timestamp == trades[i].timestamp) {
 candle.high = std::max(candle.high, trades[i].price);
}
```


# Low 

To Compute the low i only had to do the opossite of what was done in the high, that is , checking the minimum of the two until that current time stamp changes.


# Close 

This is the average price per unit in this time frame , that is : the summation of the product of the prices and the amounts (value) divided by the summation of the amounts.


```c++

candle.close = value / amount;

```

# Open

The open on the other hand is a little tricky, it is the close for the previous time frame. To access the candlestick of the previous timestamp, i used the back() method to pick the previous candlestick and access its close attribute

```c++
candle.open = candlesticks.back().close;

```

All these computed and stored in an array *candlesticks* are returned to be accessed in MerkelMain