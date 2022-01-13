#include<bits/stdc++.h>
using namespace std;

//general -> buy ko negative lege already
//ek question se hi saare hojaege

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

//BEST TIME TO BUY AND SELL With Cooldown
int maxProfit(vector<int>& prices){
    int buy=-prices[0];
    int sell=0;
    int pot=0;
    for(int i=1;i<prices.size();i++){
        //sell variable will be changed so store it before
        int prevsell=sell;
        sell=max(sell,prices[i]+buy);
        buy=max(buy,pot-prices[i]);
        pot=prevsell;
    }
    return sell;
}

//BEST TIME TO BUY AND SELL With m Cooldown
int maxProfit(vector<int>& prices){
    int buy=-prices[0];
    int sell=0;
    queue<int>q;
    for(int i=1;i<prices.size();i++){
        //sell variable will be changed so store it before
        int prevsell=sell;
        sell=max(sell,prices[i]+buy);
        buy=max(buy,pot-prices[i]);
        pot=prevsell;
    }
    return sell;
}

int main(){
    
    return 0;
}