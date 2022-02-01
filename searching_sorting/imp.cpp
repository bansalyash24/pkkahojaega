#include<bits/stdc++.h>
using namespace std;

void swap(vector<int>&nums,int i,int val){
    int temp=nums[nums[i]-1];
    nums[nums[i]-1]=val;
    nums[i]=temp;
}

//First Missing Positive
int firstMissingPositive(vector<int>& nums) {
    int len=nums.size();
    int i=0;
    while(i<len){
        if(nums[i]>=1 && nums[i]<=len && nums[nums[i]-1]!=nums[i]){
            swap(nums,i,nums[i]);
        }else{
            i++;
        }
    }
    for(int i=0;i<len;i++){
        if(nums[i]!=i+1){
            return i+1;
        }
    }
    return len+1;
}

// kth Missing Positive

int main(){
    
    return 0;
}