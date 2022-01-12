#include<bits/stdc++.h>
using namespace std;

//BEST TIME TO BUY AND SELL I
int maxProfit(vector<int>& prices){
    int buy=-prices[0];
    int sell=0;
    for(int i=1;i<prices.size();i++){
        sell=max(sell,prices[i]+buy);
        buy=max(buy,prices[i]);
    }
    return sell;
}

//BEST TIME TO BUY AND SELL II (infinite transactions)
int maxProfit(vector<int>& prices){
    int buy=-prices[0];
    int sell=0;
    for(int i=1;i<prices.size();i++){
        //sell variable will be changed so store it before
        int prevsell=sell;
        sell=max(sell,prices[i]+buy);
        buy=max(buy,prevsell-prices[i]);
    }
    return sell;
}

//BEST TIME TO BUY AND SELL With Transaction Fees
int maxProfit(vector<int>& prices, int fee) {
    int buy=-prices[0]-fee;
    int sell=0;
    for(int i=1;i<prices.size();i++){
        //sell variable will be changed so store it before
        int prevsell=sell;
        sell=max(sell,prices[i]+buy);
        buy=max(buy,prevsell-prices[i]-fee);
    }
    return sell;
}


int main(){
    
    return 0;
}