#include<bits/stdc++.h>
using namespace std;

typedef vector<vector<string>> vvs;
typedef vector<vector<bool>> vvb;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<string> vs;

// substr c++ m first (index,length) se niklti h

void printvvs(vvs &vec){
    for(vs &x:vec){
        for(auto &y:x){
            if(y.size()==0) cout<<"\"\"";
            cout<<y<<" ";
        }
        cout<<endl;
    }
}
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
    return helperIII(s,k,0,dp,palin);
}

                                // MCM --> memo,tabu,printing

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
    int len=nums.size();
    vvi dp(len,vi(len,0));

    for(int g=2;g<len;g++){
        int si=0;
        int ei=g;
        while(ei<len){
            dp[si][ei]=int(1e9);
            for(int cut=si+1;cut<ei;cut++){
                int left=dp[si][cut];
                int right=dp[cut][ei];
                int own=left+right+(nums[si]*nums[cut]*nums[ei]);
                dp[si][ei]=min(dp[si][ei],own);
            }
            si++;
            ei++;
        }
    }
    return dp[0][len-1];
}

//print mcm
string print_mcm(vi &nums){
    int len=nums.size();

    vvi dp(len,vi(len,0));
    vvs sdp(len,vs(len,""));

    for(int g=1;g<len;g++){
        int si=0;
        int ei=g;
        while(ei<len){
            if(g==1){
                dp[si][ei]=0;
                string temp;
                temp.append(1,char(si+65));
                sdp[si][ei]=temp;
            }
            else{
                dp[si][ei]=int(1e9);
                for(int cut=si+1;cut<ei;cut++){
                    int left=dp[si][cut];
                    int right=dp[cut][ei];
                    int own=left+right+(nums[si]*nums[cut]*nums[ei]);
                    if(own<dp[si][ei]){
                        dp[si][ei]=own;
                        sdp[si][ei]="("+sdp[si][cut]+sdp[cut][ei]+")";
                    }
                }
            }
            
            si++;
            ei++;
        }
    }
    printvvs(sdp);
    return sdp[0][len-1];
}

//burst ballons memo
int burst_balloons(vi &nums,int si,int ei,vvi &dp){
    int len=nums.size();
    if(si+1==ei){
        return 0;
    }

    if(dp[si+1][ei+1]!=-1) return dp[si+1][ei+1];

    int ans=int(-1e9);
    for(int cut=si+1;cut<ei;cut++){
        int left=burst_balloons(nums,si,cut,dp);
        int right=burst_balloons(nums,cut,ei,dp);
        int l=(si==-1)?1:nums[si];
        int r=(ei==len)?1:nums[ei];
        if(ans>(left+right+(l*r*nums[cut]))){
            ans=left+right+(l*r*nums[cut]);
        }
    }
    return dp[si+1][ei+1]=ans;
}

// burst balloons tabu
int burst_balloons_(vi &arr){
    int len=arr.size();
    vvi dp(len,vi(len,0));
    for(int g=0;g<len;g++){
        int si=0;
        int ei=len;
        while(ei<len){
            
            for(int k=si;k<=ei;k++){
                int left=(k==si)?0:dp[si][k-1];
                int right=(k==ei)?0:dp[k+1][ei];
                int val=((si==0)?arr[si-1]:1)*arr[k]*(ei==len)?arr[ei+1]:1;
                if(si>0){
                    val=1;
                }
            }
        }
    }
}

void caller(vi &nums){
    vvi dp(nums.size()+2,vi(nums.size()+2,-1));
    cout<<burst_balloons(nums,-1,nums.size(),dp);
}

//boolean parenthiazation memo
// gfg ka question solve karne k liye modulo lgaya taaki overflow na jaaye
int dpb[47][47][2]; 
vi booleanpar(vc &tf,vc &oper,int si,int ei){
    if(si==ei){
        if(tf[si]=='T') return {1,0};
        else return {0,1};
    }

    if(dpb[si][ei][0]!=-1) return {dpb[si][ei][0],dpb[si][ei][1]};
    vi ans(2,0);

    for(int i=si;i<ei;i++){
        vi left=booleanpar(tf,oper,si,i);
        vi right=booleanpar(tf,oper,i+1,ei);
        int lt=left[0];
        int lf=left[1];
        int rt=right[0];
        int rf=right[1];
        if(oper[i]=='&'){
            ans[0]+=lt*rt;
            ans[1]+=lt*rf+lf*rt+lf*rf;
        }
        else if(oper[i]=='|'){
            ans[0]+=lt*rt+lt*rf+lf*rt;
            ans[1]+=lf*rf;
        }else{
            ans[0]+=lt*rf+lf*rt;
            ans[1]+=lf*rf+lt*rt;
        }
    }
    ans[0]%=1003;
    ans[1]%=1003;
    dpb[si][ei][0]=ans[0];
    dpb[si][ei][1]=ans[1];
    return ans;
}


//boolean parenthiazation tabu
int booleanpar_(){
    return 1;
}

int dp[201][201];
int min_expression(vc &tf,vc &oper,int si,int ei){
    if(si==ei){
        return int(tf[si]-48);
    }

    if(dp[si][ei]!=-1) return dp[si][ei];

    int ans=int(1e9);

    for(int i=si;i<ei;i++){
        int left=min_expression(tf,oper,si,i);
        int right=min_expression(tf,oper,i+1,ei);
        int tans=0;
        if(oper[i]=='+'){
            tans=left+right;
        }
        else {
            tans=left*right;
        }
        ans=min(ans,tans);
    }
    return dp[si][ei]=ans;
}

int max_expression(vc &tf,vc &oper,int si,int ei){
    if(si==ei){
        return int(tf[si]-48);
    }

    if(dp[si][ei]!=-1) return dp[si][ei];

    int ans=int(-1e9);

    for(int i=si;i<ei;i++){
        int left=max_expression(tf,oper,si,i);
        int right=max_expression(tf,oper,i+1,ei);
        int tans=0;
        if(oper[i]=='+'){
            tans=left+right;
        }
        else {
            tans=left*right;
        }
        ans=max(ans,tans);
    }
    return dp[si][ei]=ans;
}

//leetcode 241
vi diffWays(vi &tf,vc &oper,int si,int ei){
    if(si==ei){
        return {tf[si]};
    }

    vi ans;
    for(int i=si;i<ei;i++){
        vi left=diffWays(tf,oper,si,i);
        vi right=diffWays(tf,oper,i+1,ei);

        for(auto &x:left){
            for(auto &y:right){
                if(oper[i]=='-'){
                    ans.push_back(x-y);
                }else if(oper[i]=='+'){
                    ans.push_back(x+y);
                }else{
                    ans.push_back(x*y);
                }
            }
        }
    }
    return ans;
}

vector<int> diffWaysToCompute(string s) {
    vc oper;
    vi tf;
    string temp="";
    int i=0;
    while(i<s.length()){
        temp="";
        if(i!=s.length()-1 && s[i]!='-' && s[i]!='*' && s[i]!='+' && s[i+1]!='-' && s[i+1]!='*' && s[i+1]!='+'){
            tf.push_back(stoi(s.substr(i,2)));
            i+=2;
            continue;
        }
        if(s[i]=='-' || s[i]=='*' || s[i]=='+'){
            oper.push_back(s[i]);
        }else{
            tf.push_back(stoi(s.substr(i,1)));
        }
        i++;
    }
    return diffWays(tf,oper,0,tf.size()-1);
}

long long helper_(vector<vector<int>>&arr,int i,int len){
        if(i>=len){
            return 0;
        }

        // cout<<"hello";
        int t=arr[i][1]-i+1;
        cout<<t<<" ";
        long long inc=arr[i][0]+helper_(arr,t,len);
        long long exc=helper_(arr,i+1,len);
        
        return max(inc,exc);
    }
long long mostPoints(vector<vector<int>> &questions) {
        // cout<<questions.size();
        // return 1;
        return helper_(questions,0,4);
    }

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    // partition("aba");
    // vi nums{3,1,5,8};
    // vvi dp(nums.size(),vi(nums.size(),-1));
    // cout<<mcm(nums,0,nums.size()-1,dp);
    // cout<<mcm_tabu(nums);
    // caller(nums);
    vc tf,oper;
    memset(dpb,-1,sizeof(dpb));
    memset(dp,-1,sizeof(dp));
    // string s="T&T|F|F^F^T^T^T&T^F^T&F|F^F^F&F&F|F|F^F^T|T&T";
    string s="1+2*3+4*5" ;
    for(int i=0;i<s.length();i++){
        if(s[i]=='+' || s[i]=='*'){
            oper.push_back(s[i]);
        }else{
            tf.push_back(s[i]);
        }
    }
    // vi ans=booleanpar(tf,oper,0,tf.size()-1);
    // cout<<ans[0]<<" "<<ans[1];
    // cout<<min_expression(tf,oper,0,tf.size()-1);
    // cout<<max_expression(tf,oper,0,tf.size()-1);
    // vi ans=diffWaysToCompute("2*3-4*5");
    // for(auto x:ans) cout<<x<<" ";
    // nums={10,20,30,40,50};
    // cout<<mcm_tabu(nums);
    vvi nums{{3,2},{4,3},{4,4},{2,5}};
    cout<<mostPoints(nums);
    return 0;
}