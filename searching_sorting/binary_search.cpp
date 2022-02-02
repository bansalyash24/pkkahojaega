#include<bits/stdc++.h>
using namespace std;


int countMissing(vector<int>&nums,int mid){
    return nums[mid]-nums[0]-mid;
}

//Missing Element in Sorted Array
int missingElement(vector<int>&nums,int k){
    int si=0;
    int ei=nums.size()-1;
    while(si<=ei){
        int mid=(si+ei)/2;
        int miss=countMissing(nums,mid);
        if(miss>=k){
            ei=mid-1;
        }else{
            si=mid+1;
        }
    }
    return nums[ei]-countMissing(nums,ei)+k;
}

// <---------------------Binary search in 2D Matrix------------------------>

// SEARCH IN 2D SORTED 1
bool searchMatrixI(vector<vector<int>>& matrix, int target) {
    int r=matrix.size(),c=matrix[0].size();
    int lo=0,hi=r*c-1;
    while(lo<=hi){
        int mid=lo+(hi-lo)/2;
        int val=matrix[mid/c][mid%c];
        if(val==target) return true;
        else if(val<target) lo=mid+1;
        else hi=mid-1;
    }
    return false;
}

// SEARCH IN 2D SORTED 2
//kono ko pakdo jha se ghat rha ho or badh bhi rha ho
bool searchMatrixII(vector<vector<int>>& matrix, int tar) {
    int i=0;
    int j=matrix[0].size()-1;
    int n=matrix.size(),m=matrix[0].size();
    while(i>=0 && i<n && j>=0 && j<m){
        if(matrix[i][j]==tar) return true;
        else if(tar>matrix[i][j]){
            i++;
        }else{
            j--;
        }
    }
    return false;
}



int main(){
    
    return 0;
}