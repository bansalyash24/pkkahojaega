#include<bits/stdc++.h>
using namespace std;

    int floodFill_Multi2(int sr,int sc,vector<vector<bool>>&matrix,vector<vector<int>>&dir){
        if(sr==matrix.size()-1 and sc==matrix[0].size()-1){
            return 1;
        }

        int count=0;
        matrix[sr][sc]=true;
        for(int d=0;d<dir.size();d++){
            for(int rad=1;rad<max(matrix.size(),matrix[0].size());rad++){
                int x=sr+rad*dir[d][0];
                int y=sc+rad*dir[d][1];
                if(x>=0 and y>=0 and x<matrix.size() && y<matrix[0].size()){
                    if(!matrix[x][y])
                        count=max(count,floodFill_Multi2(x,y,matrix,dir));
                }else{
                    break;
                }
            }
        }
        matrix[sr][sc]=false;
        return count+1;
    }

    pair<string,int> longestPath(int sr,int sc,vector<vector<bool>>&vis,vector<vector<int>>&dir,vector<string>dirS){
        int n=vis.size(),m=vis[0].size();
        if(sr==n-1 && sc==m-1){
            return {"",0};
        }

        pair<string,int> ans={"",-1}; //impp step
        vis[sr][sc]=true;
        for(int d=0;d<dir.size();d++){
            for(int rad=1;rad<max(n,m);rad++){
                int x=sr+rad*dir[d][0];
                int y=sc+rad*dir[d][1];
                if(x>=0 and y>=0 and x<vis.size() && y<vis[0].size()){
                    if(!vis[x][y]){
                        pair<string,int> recAns=longestPath(x,y,vis,dir,dirS);
                        if(recAns.second !=-1 and recAns.second+1>ans.second){
                            ans.first=dirS[d]+recAns.first;
                            ans.second=recAns.second+1;
                        }
                    }
                }else{
                    break;
                }
            }
        }
        vis[sr][sc]=false;
        return ans;
    }

    int equalSet_wrong(vector<int>&arr,int idx,int sum1,int sum2,string set1,string set2){
        if(idx==arr.size()){
            if(sum1==sum2){
                cout<<set1<<"= "<<set2<<endl;
                return 1;
            }
            return 0;
        }
        int count=0;

        count+=equalSet_wrong(arr,idx+1,sum1+arr[idx],sum2,set1+to_string(arr[idx])+" ",set2);
        count+=equalSet_wrong(arr,idx+1,sum1,sum2+arr[idx],set1,set2+to_string(arr[idx])+" ");

        return count;
    }

    // mirror image print karege
    // notebook m ek baar dry run karalo

    //  output
    //  10 20 30 40 80 = 50 60 70
    //  10 20 30 50 70 = 40 60 80
    //  10 20 40 50 60 = 30 70 80
    //  10 20 70 80 = 30 40 50 60
    //  10 30 60 80 = 20 40 50 70
    //  10 40 50 80 = 20 30 60 70
    //  10 40 60 70 = 20 30 50 80
    //  20 30 50 80 = 10 40 60 70
    //  20 30 60 70 = 10 40 50 80
    //  20 40 50 70 = 10 30 60 80
    //  30 40 50 60 = 10 20 70 80
    //  30 70 80 = 10 20 40 50 60
    //  40 60 80 = 10 20 30 50 70
    //  50 60 70 = 10 20 30 40 80
    //           14

    void equalSetRight(){
        vector<int>arr{10,20,30,40,50,60,70,80};
        // 10 ko ek set m pehle hi daldo
        cout<<equalSet_wrong(arr,1,arr[0],0,to_string(arr[0]),"");
    }

    int permutationUnique1(string str,string ans){
        if(str.length()==0){
            cout<<ans<<endl;
            return 1;
        }

        int count=0;
        vector<bool>vis(26,false);
        for(int i=0;i<str.length();i++){
            
            char ch=str[i];
            if(!vis[ch-'a']){
                vis[ch]=true;
                string ros=str.substr(0,i)+str.substr(i+1);
                count+=permutationUnique1(ros,ans+ch);
            }
        }
        return count;
    }

    int permutationUnique2(string str,string ans){
        if(str.length()==0){
            cout<<ans<<endl;
            return 1;
        }

        int count=0;
        vector<bool>vis(26,false);
        for(int i=0;i<str.length();i++){
            
            char ch=str[i];
            if(!vis[ch-'a']){
                vis[ch]=true;
                string ros=str.substr(0,i)+str.substr(i+1);
                count+=permutationUnique2(ros,ans+ch);
            }
        }
        return count;
    }
int main(){
    freopen("../input.txt","r",stdin);
    freopen("../output.txt","w",stdout);
    // vector<vector<int>>dir{{-1,0},{0,-1},{0,1},{1,0}};
    // vector<string>dirS{"T","L","R","D"};
    // vector<vector<bool>>vis(3,vector<bool>(3,false));
    // pair<string,int>ans=longestPath(0,0,vis,dir,dirS);
    // cout<<ans.first<<" "<<ans.second;
    // vector<int>arr{10,20,30,40,50,60,70,80};
    // cout<<equalSet(arr,0,0,0,"","");

    cout<<permutationUnique1("abca","");
    return 0;
}