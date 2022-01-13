#include<bits/stdc++.h>
using namespace std;

void printIncreasing(int a,int b){
    if(a>b) return;
    cout<<a<<" ";
    printIncreasing(a+1,b);
}

void printDecreasing(int a,int b){
    if(a>b) return;
    printDecreasing(a+1,b);
    cout<<a<<" ";
}

void printIncreasingDecreasing(int a,int b){
    if(a>b) return;
    cout<<a<<" ";
    printIncreasingDecreasing(a+1,b);
    cout<<a<<" ";
}

void printOddEven(int a,int b){
    if(a>b) return;

    if(a%2!=0) cout<<a<<" ";

    printOddEven(a+1,b);

    if(a%2==0) cout<<a<<" ";
    
}

int fac(int n){
    return n==0?1:fac(n-1)*n;
}
int power(int a,int b){
    return b==0?1:power(a,b-1)*a;
}
int power_better(int a,int b){
    if(b==0) return 1;

    int answer=power(a,b/2);
    answer*=answer;

    if(b%2!=0) return answer*a;
    else return answer;
}

int maximum(vector<int>&arr,int idx){
    if(idx==arr.size()){
        return -1e9;
    }
    int ans=maximum(arr,idx+1);
    return max(arr[idx],ans);
}

int minimum(vector<int>&arr,int idx){
    if(idx==arr.size()){
        return 1e9;
    }
    int ans=minimum(arr,idx+1);
    return min(arr[idx],ans);
}

bool find(vector<int>&arr,int idx,int val){

    if(idx==arr.size()) return false;
    return arr[idx]==val || find(arr,idx+1,val);

}

int firstIndex(vector<int>&arr,int idx,int val){
    if(idx==arr.size()){
        return -1;
    }
    if(arr[idx]==val) return idx;
    return firstIndex(arr,idx+1,val);
}

// int firstIndex(vector<int>&arr,int idx,int val){
//     if(idx==arr.size()){
//         return -1;
//     }
//     int res=firstIndex(arr,idx+1,val);
//     if(arr[idx]==val) return idx;
//     return res;
// }

int ans=-1;
int lastIndex(vector<int>&arr,int idx,int val){
    if(idx==arr.size()){
        return ans;
    }
    if(arr[idx]==val) ans=idx;
    return lastIndex(arr,idx+1,val);
}

int printTreePath(int n){
    if(n==0 || n==1){
        cout<<"base: "<<n<<endl;
        return n;
    }   

    int ans=0;
    cout<<"pre: "<<n<<endl;
    ans+=printTreePath(n-1);

    cout<<"in: "<<n<<endl;

    ans+=printTreePath(n-2);
    cout<<"post: "<<n<<endl;

    return ans+3;
}

int main(){
    // printIncreasing(5,9);
    // printDecreasing(5,9);
    // printIncreasingDecreasing(5,9);
    // printOddEven(5,9);
    // cout<<fac(15);
    // cout<<power(2,30);
    // cout<<power_better(2,30);
    // vector<int>ans={1,2,3,4,5,3};
    // cout<<maximum(ans,0);
    // cout<<find(ans,0,5);
    // cout<<firstIndex(ans,0,3);
    // cout<<lastIndex(ans,0,3);
    cout<<printTreePath(5)<<endl;
    return 0;
}