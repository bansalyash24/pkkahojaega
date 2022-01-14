#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

// no two consecutive one's allowed
int binary_string(int n){
    int one=1,zero=1;
    for(int i=1;i<n;i++){
        int nzero=zero+one;
        int none=zero;

        one=none;
        zero=nzero;
    }
    return one+zero;
}

//no three consecutive one's allowed
int binary_string_02(int n){
    int one=1,zero=1,oneone=0;
    for(int i=1;i<n;i++){
        int nzero=zero+one+oneone;
        int none=zero;
        int noneone=one;

        one=none;
        zero=nzero;
        oneone=noneone;
    }
    return one+zero+oneone;
}

//no leading zeroes allowed and no duplicates allowed
int numberOfUniqueGoodSubsequences(string str){
    int zero=0;
    int one=0;
    bool iszp=true; //is zero present
    for(int i=0;i<str.size();i++){
        if(str[i]=='0'){
            iszp=true;
            zero=zero+one;
        }else{
            one=one+zero+1;
        }
    }
    return iszp?(zero+one):(zero+one+1);
}

vi dp(1000,-1);
void caller(vi &nums){
    cout<<houseRobberI(nums,0);
    // cout<<houseRobberII(nums);
}

//memo
int houseRobberI(vi &nums,int idx){
    if(idx>=nums.size()){
        return 0;
    }

    if(dp[idx]!=-1) return dp[idx];

    //incude
    int inc=houseRobberI(nums,idx+2)+nums[idx];

    //exclude
    int exc=houseRobberI(nums,idx+1);

    return dp[idx]=max(inc,exc);
}

//tabu
int houseRobberI(vi &nums){
    int inc=nums[0],exc=0;
    for(int i=1;i<nums.size();i++){
        int previnc=inc;
        inc=exc+nums[i];
        exc=max(previnc,exc);
    }

    return max(inc,exc);
}


//tabu
int houserobberII(vi &nums) {
    if(nums.size()==1) return nums[0];
    int first=helper(nums,0,nums.size()-2);
    int second=helper(nums,1,nums.size()-1);
    return max(first,second);
}

int helper(vector<int>nums,int si,int ei){
    if(si>=ei){
        return nums[si];
    }
    int inc=nums[si],exc=0;
    for(int i=si+1;i<=ei;i++){
        int previnc=inc;
        inc=exc+nums[i];
        exc=max(previnc,exc);
    }
    return max(inc,exc);
}

//paint fence
int numWays(int n,int k){
    int same=0;
    int diff=k;
    for(int i=1;i<n;i++){
        int presame=same;
        same=diff;
        diff=(presame+diff)*(k-1);
    }
    return same+diff;
}

//paint house
int mincost(vvi &nums){
    int c1=0;
    int c2=0;
    int c3=0;
    for(int i=0;i<nums.size();i++){
        int nc1=min(c2,c3)+nums[i][0];
        int nc2=min(c1,c3)+nums[i][1];
        int nc3=min(c1,c2)+nums[i][2];

        c1=nc1;
        c2=nc2;
        c3=nc3;
    }
    return min({c1,c2,c3});
}
int main(){
    vi nums;
    caller(nums);
    return 0;
}