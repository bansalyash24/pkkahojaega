#include<bits/stdc++.h>
using namespace std;

int combinationInfiCoins(vector<int>&arr,int tar,int idx,string asf){
    if(tar==0){
        cout<<asf<<endl;
        return 1;
    }

    int count=0;
    for(int i=idx;i<arr.size();i++){
        if(tar-arr[idx]>=0){
            count+=combinationInfiCoins(arr,tar-arr[i],i,asf+to_string(arr[i]));
        }
    }
    return count;
}

int combinationSingleCoins(vector<int>&arr,int tar,int idx,string asf){
    if(tar==0){
        cout<<asf<<endl;
        return 1;
    }

    int count=0;
    for(int i=idx;i<arr.size();i++){
        if(tar-arr[idx]>=0){
            count+=combinationInfiCoins(arr,tar-arr[i],i+1,asf+to_string(arr[i]));
        }
    }
    return count;
}

int permutationSingleCoin(vector<int>&arr,int tar,string asf){
    if(tar==0){
        cout<<asf<<endl;
        return 1;
    }

    int count=0;
    for(int i=0;i<arr.size();i++){
        if(arr[i]>0 and tar-arr[i]>=0){
            int val=arr[i];
            arr[i]=-val;
            count+=permutationSingleCoin(arr,tar-val,asf+to_string(val));
            arr[i]=val;
        }
    }
    return count;
}
int main(){
    freopen("../input.txt","r",stdin);
    freopen("../output.txt","w",stdout);
    vector<int>arr{2,3,5,7};
    // cout<<combinationSingleCoins(arr,10,0,"");
    // cout<<permutationSingleCoin(arr,10,"");
    
    return 0;
}