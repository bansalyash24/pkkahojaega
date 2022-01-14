#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int helper(vi &nums,int idx){
    if(idx>=nums.size()){
        return 0;
    }
    //incude
    int inc=helper(nums,idx+2)+nums[idx];

    //exclude
    int exc=helper(nums,idx+1);

    return max(inc,exc);
}

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
int main(){
    
    return 0;
}