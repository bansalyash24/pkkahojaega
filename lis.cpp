#include<bits/stdc++.h>
using namespace std;

int fans=0;
int dp[1000];
int LIS(vector<int>&nums,int edx){
    int ans=1;

    for(int i=edx-1;i>=0;i--){
        int recans=LIS(nums,i);
        if(nums[i]<nums[edx]){
            ans=max(ans,recans+1);
        }
    }

    fans=max(fans,ans);
    return ans;
}

int LIS_Memo(vector<int>&nums,int edx){
    int ans=1;

    if(dp[edx]!=-1) return dp[edx];

    for(int i=edx-1;i>=0;i--){
        int recans=LIS(nums,i);
        if(nums[i]<nums[edx]){
            ans=max(ans,recans+1);
        }
    }
    dp[edx]=ans;
    fans=max(fans,ans);
    return ans;
}

// O(n^2)
int LIS_tab(vector<int>&nums){
    int n=nums.size();
    int tab[n]={1};
    int ans=1;
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            if(nums[j]<nums[i]){
                tab[i]=max(tab[i],tab[j]+1);
            }
        }
        ans=max(ans,tab[i]);
    }
    return ans;
}

int LDS_tab(vector<int>&nums){
    int n=nums.size();
    int tab[n]={1};
    int ans=1;
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            if(nums[j]>nums[i]){
                tab[i]=max(tab[i],tab[j]+1);
            }
        }
        ans=max(ans,tab[i]);
    }
    return ans;
}

int binarySearch(vector<int>&nums,int si,int ei,int val){
    while(si<=ei){
        int mid=(si+ei)/2;
        if(nums[mid]==val){
            return mid;
        }
        else if(nums[mid]<val){
            si=mid+1;
        }else{
            ei=mid-1;
        }
    }
    return si;
}

//O(nlogn)
int LIS_tab_optimized(vector<int>&nums){
    int n=nums.size();
    int ans=1;
    for(int i=1;i<n;i++){
        int cidx=binarySearch(nums,0,ans-1,nums[i]);
        if(nums[cidx]==ans){
            ans++;
        }
        nums[cidx]=nums[i];
    }
    return ans;
}

int maxSumIncSubs(vector<int>&nums){
    int n=nums.size(),ans=nums[0];
    vector<int>dp(n,0);
    dp[0]=nums[0];
    for(int i=1;i<n;i++){
        int temp=0;
        for(int j=0;j<i;j++){
            if(nums[j]<nums[i]){
                temp=max(temp,dp[j]);
            }
            dp[i]=temp+nums[i];
        }
        ans=max(ans,dp[i]);
    }
    return ans;
}

int buildingBridges(vector<pair<int,int>>&nums){
    sort(nums.begin(),nums.end());
    return 1;
}

vector<int> largestDivisibleSubset(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    vector<int>dp(nums.size(),1);
    int pre[nums.size()];
    int omax=1,index=0;
    pre[0]=-1;
    vector<int>ans;
    for(int i=1;i<nums.size();i++){
        pre[i]=-1;
        for(int j=0;j<i;j++){
            if(nums[i]%nums[j]==0){
                if(dp[j]+1>dp[i]){
                    dp[i]=dp[j]+1;
                    pre[i]=j;
                }
            }
            if(omax<dp[i]){
                omax=dp[i];
                index=i;
            }
        }
    }
    
    while(index!=-1){
        ans.push_back(nums[index]);
        index=pre[index];
    }
    return ans;
}

//Russian Doll Envelope O(nlogn)
int binarySearchRussian(vector<vector<int>>&nums,int si,int ei,int val){
    while(si<=ei){
        int mid=(si+ei)/2;
        if(nums[mid][1]==val){
            return mid;
        }else if(nums[mid][1]<val){
            si=mid+1;
        }else{
            ei=mid-1;
        }
    }
    return si;
}

int maxEnvelopes(vector<vector<int>>& nums) {
    sort(nums.begin(),nums.end(),[](const vector<int>& v1,const vector<int>& v2){
        if(v1[0]==v2[0]) return v2[1]<v1[1];
        return v1[0] < v2[0];
    });
    int ans=1;
    vector<int>dp(nums.size(),1);
    for(int i=1;i<nums.size();i++){
        int cidx=binarySearchRussian(nums,0,ans-1,nums[i][1]);
        if(cidx==ans){
            ans++;
        }
        nums[cidx]=nums[i];
    }
    return ans;
}

//count no of increasing subsequence with length k
int noOfIncreasingSubsequenceWithk(vector<int>&nums,int a){
    vector<vector<int>>dp(a,vector<int>(nums.size(),0));
    int ans=0;
    for(int j=0;j<nums.size();j++){
        dp[0][j]=1;
    }
    for(int i=1;i<a;i++){
        for (int j = i; j < nums.size(); j++){
            for(int k=0;k<j;k++){
                if(nums[k]<nums[j]){
                    dp[i][j]+=dp[i-1][k];
                }
            }
        }
    }
    for(int i=0;i<nums.size();i++){
       ans+=dp[a-1][i];
    }
    return ans;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    fans=0;
    memset(dp,-1,sizeof(dp));
    // vector<int>nums{1,7,8,3,2,5,9,6,4,2,7,3};
    // LIS(nums,nums.size()-1);
    // LIS_Memo(nums,nums.size()-1);
    // cout<<fans;
    // cout<<LIS_tab(nums);
    // cout<<LIS_tab_optimized(nums);
    // cout<<maxSumIncSubs(nums);
    // cout<<largestDivisibleSubset(nums);

    // vector<vector<int>>nums {{4,5},{4,6},{6,7},{2,3},{1,1}};
    // cout<<maxEnvelopes(nums);

    vector<int>nums{12, 8, 11, 13, 10, 15, 14, 16, 20};
    cout<<noOfIncreasingSubsequenceWithk(nums,4);
    return 0;
}