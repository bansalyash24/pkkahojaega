#include<bits/stdc++.h>
using namespace std;

bool wordBreak(string str, vector<string>& arr) {
    vector<bool>dp(str.length(),false);
    unordered_set<string>umap;
    for(auto x:arr){
        umap.insert(x);
    }
    for(int i=0;i<str.length();i++){
        for (int j = i; j >=0; j--)
        {
            string lastpart=str.substr(j,i-j+1);
            if(umap.find(lastpart)!=umap.end()){
                if(j==0 || dp[j-1]){
                    dp[i]=true;
                    break;
                }
            }
        } 
    }
    return dp[str.size()-1];
}


int main(){
    
    return 0;
}