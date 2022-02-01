#include<bits/stdc++.h>
using namespace std;

// longest common subsequence memo
int lcs(string &s1,string &s2,int i,int j){
    if(i==s1.length() || j==s2.length()){
        return 0;
    }
    
    int a=lcs(s1,s2,i+1,j);
    int b=lcs(s1,s2,i,j+1);
    int ans=max(a,b);

    if(s1[i]==s2[j]){
        return max(ans,lcs(s1,s2,i+1,j+1));
    }
    return ans;
}

int ans=0;
int lcss(string s1,string s2,int i,int j){
    if(i==s1.length() || j==s2.length()){
        return 0;
    }

    lcss(s1,s2,i+1,j);
    lcss(s1,s2,i,j+1);

    if(s1[i]==s2[j]){
        return ans=max(ans,lcss(s1,s2,i+1,j+1)+1);
    }
    return 0;
}
int main(){
    lcss("abcd","bcd",0,0);
    cout<<ans;
    return 0;
}