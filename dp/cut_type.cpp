#include<bits/stdc++.h>
using namespace std;

typedef vector<vector<string>> vvs;
typedef vector<vector<bool>> vvb;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<string> vs;

// substr c++ m first (index,length) se niklti h

bool isPalindrome(string &str,int st,int end){
    int i=st;
    int j=end;
    while(i<=j){
        if(str[i]!=str[j]) return false;
        i++;
        j--;
    }
    return true;
}

void palindrome_partioning_01_base(vvs &ans,vs &temp,string &s,int st){
    if(st==s.length()){
        ans.push_back(temp);
        return;
    }
    for(int i=st;i<s.length();i++){
        if(isPalindrome(s,st,i)){
            int len=i-st+1;
            temp.push_back(s.substr(st,len));
            palindrome_partioning_01_base(ans,temp,s,i+1);
            temp.pop_back();
        }
    }
}

//all palindrome in O(1);
vvb allpalin(string &str){
    int len=str.length();

    vvb dp(len,vb(len,false));
    //gap strategy
    for(int g=0;g<len;g++){
        int si=0;
        int ei=g;
        while(ei<len){
            if(g==0){
                dp[si][ei]=true;
            }else if(g==1){
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

void palindrome_partioning_01_opti(vvs &ans,vs &temp,string &s,int st,vvb &palin){
    if(st==s.length()){
        ans.push_back(temp);
        return;
    }
    for(int i=st;i<s.length();i++){
        if(palin[st][i]){
            int len=i-st+1;
            temp.push_back(s.substr(st,len));
            palindrome_partioning_01_opti(ans,temp,s,i+1,palin);
            temp.pop_back();
        }
    }
}

//iterative
void palindrome_partioning_tab(string &str){
    vvs fans;
    int olen=str.length();
    vvs ans;
    vvb palin=allpalin(str);
    vvs dp[olen];
    for(int i=olen-1;i>=0;i--){
        if(palin[i][olen]){
            int len=olen-i;
            dp[i].push_back({str.substr(i,len)});
        }
        for (int j = i; j < olen-1; j++)
        {
            if(palin[i][j]){
                vvs temp=dp[j+1];
                for(vs x:temp){
                    int len=j-i+1;
                    vs cur=x;
                    cur.push_back(str.substr(i,len));
                    dp[i].push_back(cur);
                }
            }
        }
    }
    vvs pans=dp[0];
    for(int i=0;i<pans.size();i++){
        for(int j=0;j<pans[0].size();j++){
            cout<<pans[i][j]<<' ';
        }
        cout<<endl;
    }
    // return ans;
}
vector<vector<string>> partition(string str) {
    vvs ans;
    vs temp;
    vvb palin=allpalin(str);
    // palindrome_partioning_01_opti(ans,temp,str,0,palin);
    palindrome_partioning_tab(str);
    return ans;
}

int minCut(string &s) {
    int len=s.length();
    vvb palin=allpalin(s);
    vector<int>dp(len,0);
    for(int i=len-1;i>=0;i--){
        if(palin[i][len-1]){
            dp[i]=0;
        }else{
            dp[i]=int(1e9);
            for(int j=i;j<len-1;j++){
                if(palin[i][j]){
                    dp[i]=min(dp[i],dp[j+1]+1);
                }
            }
        }
    }
    return dp[0];
}

//palindrome partioning III --> "https://leetcode.com/problems/palindrome-partitioning-iii/"
vvi mincost(string &str){
    int len=str.length();

    vvi dp(len,vi(len,0));
    //gap strategy
    for(int g=0;g<len;g++){
        int si=0;
        int ei=g;
        while(ei<len){
            if(g==1){
                if(str[si]!=str[ei]){
                    dp[si][ei]=1;
                }
            }else{
                if(str[si]==str[ei]){
                    dp[si][ei]=dp[si+1][ei-1];
                }else{
                    dp[si][ei]=dp[si+1][ei-1]+1;
                }
            }
            si++;
            ei++;
        }
    }
    return dp;
}

int store[101][101];
int helperIII(string &str,int k,int st,vvi &mincost,vvb &palin){
    int len=str.length();
    if(st==str.length()){
        return 0;
    }
    if(k==1){
        return mincost[st][len-1];
    }

    if(store[k][st]!=-1) return store[k][st];
    int ans=int(1e9);
    for(int i=st;i<=len-k;i++){
        if(palin[st][i]){
            ans=min(ans,(helperIII(str,k-1,i+1,mincost,palin)+mincost[st][i]));
        }
    }
    return store[k][st]=ans;
}
int palindromePartitionIII(string s, int k) {
    vvi dp=mincost(s);
    vvb palin=allpalin(s);
    memset(store,-1,sizeof(store));
    helperIII(s,k,0,dp,palin);
}

//memo
int mcm(vi &nums,int si,int ei,vvi &dp){
    if(ei-si<=1) return 0;

    if(dp[si][ei]!=-1) return dp[si][ei];
    int ans=int(1e9);

    for(int cut=si+1;cut<ei;cut++){
        int left=mcm(nums,si,cut,dp);
        int right=mcm(nums,cut,ei,dp);
        ans=min(ans,(left+right+nums[si]*nums[cut]*nums[ei]));
    }
    return dp[si][ei]=ans;
}

//tabu
int mcm_tabu(vi &nums){
    
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    // partition("aba");
    vi nums{40, 20, 30, 10, 30};
    vvi dp(nums.size(),vi(nums.size(),-1));
    cout<<mcm(nums,0,nums.size()-1,dp);
    return 0;
}