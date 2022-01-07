#include<bits/stdc++.h>
using namespace std;


//permutation infinite coin do with memorization
int permutations_infy_tab(int target,vector<int>&arr){
    static int dp[1000];
    if(target==0) return 1;

    if(dp[target]!=-1) return dp[target];

    int ans=0;
    for (int i = 0; i < arr.size(); i++)
    {
        if(target-arr[i]>=0){
            ans+=permutations_infy_tab(target-arr[i],arr);
        }
    }
    
    return dp[target]=ans;
}

int permut_infy_tab(){
    return 1;   
}

//for loop -- column wise
int combinationinfytab(vector<int>&nums,int tar){
    vector<vector<int>>dp(nums.size(),vector<int>(tar+1,0));
    for(int j=0;j<=tar;j++){
        for (int i = 0; i<nums.size(); i++)
        {
            if(j==0){
                dp[i][j]=1;
                continue;
            }
            // storing prev elements
            dp[i][j]+=(i==0)?0:dp[i-1][j];
            if(j-nums[i]>=0){
                dp[i][j]+=dp[i][j-nums[i]];
            }
        }
    }
    //check dp by filling
    return dp[nums.size()-1][tar];
}

//for loop -- column wise
int combinationsingletab(vector<int>&nums,int tar){
    vector<vector<int>>dp(nums.size()+1,vector<int>(tar+1,0));
    dp[0][0]=1;
    for(int j=0;j<=tar;j++){
        for (int i = 1; i<=nums.size(); i++)
        {
            // storing prev elements
            dp[i][j]+=dp[i-1][j];
            if(j-nums[i-1]>=0){
                dp[i][j]+=dp[i-1][j-nums[i-1]];
            }
        }
    }
    //check dp by filling
    return dp[nums.size()][tar];
}


int combinationsingletab_subsequence(vector<int>&nums,int tar){
    vector<vector<int>>dp(nums.size()+1,vector<int>(tar+1,0));
    dp[0][0]=1;
    for (int i = 1; i<=nums.size(); i++)
        for(int j=0;j<=tar;j++){
        {
            // storing prev elements
            dp[i][j]+=dp[i-1][j];
            if(j-nums[i-1]>=0){
                dp[i][j]+=dp[i-1][j-nums[i-1]];
            }
        }
    }
    //check dp by filling
    return dp[nums.size()][tar];
}

int combinationsingletab_subsequence1D(vector<int>&nums,int tar){
    vector<int>prev(tar+1,0);
    prev[0]=1;
    for (int i = 1; i<=nums.size(); i++){
        vector<int>dp(tar+1,0);
        for(int j=0;j<=tar;j++)
        {
            // storing prev elements
            dp[j]+=prev[j];
            if(j-nums[i-1]>=0){
                dp[j]+=prev[j-nums[i-1]];
            }
        }
        prev=dp;
    }
    // check dp by filling
    return prev[tar];
}

int combinationinfytab_subsequence1D(vector<int>&nums,int tar){
    vector<int>dp(tar+1,0);
    dp[0]=1;
    for (int i = 0; i<nums.size(); i++){
        for(int j=0;j<=tar;j++)
        {
            if(j-nums[i]>=0){
                dp[j]+=dp[j-nums[i]];
            }
        }
    }
    // check dp by filling
    return dp[tar];
}
int main(){
    vector<int>nums{2,3,5,7};
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    //  <-------------2D DP--------------->

    // cout<<combinationinfytab(nums,10);
    // cout<<combinationsingletab(nums,10);
    // cout<<combinationsingletab_subsequence(nums,10);

    //  <-------------1D DP--------------->
    // cout<<combinationsingletab_subsequence1D(nums,10);
    cout<<combinationinfytab_subsequence1D(nums,10);


    return 0;
}