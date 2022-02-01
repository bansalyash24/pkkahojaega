#include<bits/stdc++.h>
using namespace std;

typedef vector<vector<string>> vvs;
typedef vector<vector<bool>> vvb;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<string> vs;

// all palindromic substring
bool allpalin(string &s,int i,int j){
    if(i>j) return false;

    if(s[i]==s[j]){
        return allpalin(s,i+1,j-1);
    }
    allpalin(s,i+1,j);
    allpalin(s,i,j-1);
    return false;
}

// marking true all palindrome
vvb allpalin_(string &str){
    int len=str.length();
    vvb dp(len,vb(len,false));

    for(int gap=0;gap<len;gap++){
        int si=0;
        int ei=gap;
        while(ei<len){
            if(gap==0){
                dp[si][ei]=true;
            }else if(gap==1){
                if(str[si]==str[ei]){
                    dp[si][ei]=true;
                }
            }else{
                if(str[si]==str[ei] && dp[si+1][ei-1]){
                    dp[si][ei]=true;
                }
            }
            si++;
            ei++;
        }
    }
    return dp;
}

// Ist way
int countPalindrome(string str){
    int len=str.length();
    vvi dp(len,vi(len,0));
    vvb checkdp=allpalin_(str);
    for(int gap=0;gap<len;gap++){
        int si=0;
        int ei=gap;
        while(ei<len){
            if(gap==0){
                dp[si][ei]=1;
            }else if(gap==1){
                dp[si][ei]=2;
                if(str[si]==str[ei]){
                    dp[si][ei]++;
                }
            }else{
                dp[si][ei]=dp[si][ei-1]+dp[si+1][ei]-dp[si+1][ei-1];
                if(str[si]==str[ei] && checkdp[si+1][ei-1]){
                    dp[si][ei]++;
                }
            }
            si++;
            ei++;
        }
    }
    return dp[0][len-1];
}

//IInd Way
int countPalindrome(string s) {
        int n=s.length();
        int count=0;
        vector<vector<bool>>dp(n,vector<bool>(n,false));
        for(int g=0;g<n;g++){
            for(int i=0,j=g;j<n;i++,j++){
                if(g==0){
                    dp[i][j]=true;
                }else if(g==1){
                    if(s[i]==s[j]){
                        dp[i][j]=true;
                    }
                }else{
                    if(s[i]==s[j] and dp[i+1][j-1]==true){
                        dp[i][j]=true;
                    }
                }
                
                if(dp[i][j]==true) count++;
            }
        }
        return count;
}

//longest palindromic substring time-> 0(n2) space-> 0(n2) 
string longestPalindrome(string s) {
        if(s.length()==1) return s;
        string ans="";
        int n=s.size();
        int a=0,b=0;
        vector<vector<bool>>dp(n,vector<bool>(n,false));
        for(int g=0;g<n;g++){
            for(int i=0,j=g;j<n;i++,j++){
                if(g==0){
                    dp[i][j]=true;
                }else if(g==1){
                    if(s[i]==s[j]){
                        dp[i][j]=true;
                    }
                }else{
                    if(s[i]==s[j] and dp[i+1][j-1]==true){
                        dp[i][j]=true;
                    }
                }
                if(dp[i][j]==true){
                    a=i;
                    b=g;
                }
            }
        }
        return s.substr(a,b+1);
}

//longest palindromic substring time-> 0(n2) space-> 0(1) * best complexity
string longestPalindrome(string s){
    int n=s.length();
    int si=0;
    int ei=0;
    for(int i=0;i<2*n-1;i++){
        int l=(i+1)/2 - 1;
        int r=(i%2==0)?l+2:l+1;

        while(l>=0 && r<n && s[l]==s[r]){
                l--;
                r++;
            }
            if(ei-si+1<r-l-1){
                si=l+1;
                ei=r-1;
            }
    }
    return s.substr(si,ei-si+1);
}

//count all palindrome substring time-> 0(n2) space-> 0(1)  * best complexity
int countPalindrome(string s){
    int n=s.length();
    int ans=0;
    for(int i=0;i<2*n-1;i++){
        int l=(i+1)/2 - 1;
        int r=(i%2==0)?l+2:l+1;

        while(l>=0 && r<n && s[l]==s[r]){
            ans++;
            l--;
            r++;
        }
        if(i%2==0) ans++;
    }
    return ans;
}

int countPalindromicSubsequences(string str){
    int len=str.length();
    vvi dp(len,vi(len,0));
    for(int gap=0;gap<len;gap++){
        int si=0;
        int ei=gap;
        while(ei<len){
            if(gap==0){
                dp[si][ei]=1;
            }else if(gap==1){
                dp[si][ei]=2;
                if(str[si]==str[ei]){
                    dp[si][ei]++;
                }
            }else{
                dp[si][ei]=dp[si][ei-1]+dp[si+1][ei]-dp[si+1][ei-1];
                if(str[si]==str[ei]){
                    dp[si][ei]+=dp[si+1][ei-1]+1;
                }
            }
            si++;
            ei++;
        }
    }
    return dp[0][len-1];
}

int longestPalindromicSubsequences(string str){
    int len=str.length();
    vvi dp(len,vi(len,0));
    for(int gap=0;gap<len;gap++){
        int si=0;
        int ei=gap;
        while(ei<len){
            if(gap==0){
                dp[si][ei]=1;
            }else if(gap==1){
                dp[si][ei]=1;
                if(str[si]==str[ei]){
                    dp[si][ei]=2;
                }
            }else{
                if(str[si]==str[ei]){
                    dp[si][ei]=dp[si+1][ei-1]+2;
                }else{
                    dp[si][ei]=max(dp[si][ei-1],dp[si+1][ei]);
                }
            }
            si++;
            ei++;
        }
    }
    return dp[0][len-1];
}

int longestPalindromicSubstring(string str){
    int len=str.length();
    vvi dp(len,vi(len,0));
    for(int gap=0;gap<len;gap++){
        int si=0;
        int ei=gap;
        while(ei<len){
            if(gap==0){
                dp[si][ei]=1;
            }else if(gap==1){
                dp[si][ei]=1;
                if(str[si]==str[ei]){
                    dp[si][ei]=2;
                }
            }else{
                if(str[si]==str[ei] && dp[si+1][ei-1]==gap-1){
                    dp[si][ei]=dp[si+1][ei-1]+2;
                }else{
                    dp[si][ei]=max(dp[si][ei-1],dp[si+1][ei]);
                }
            }
            si++;
            ei++;
        }
    }
    return dp[0][len-1];
}

//longest common subsequence memo
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