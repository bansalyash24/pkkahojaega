#include<bits/stdc++.h>
using namespace std;

    int subsequence(string str,string asf,int idx,vector<string>&res){
        if(idx==str.length()){
            res.push_back(asf);
            return 1;
        }
        int count=0;
        count+=subsequence(str,asf,idx+1,res);
        count+=subsequence(str,asf+str[idx],idx+1,res);

        return count;
    }

    // int mazePath(int sr,int sc,int er,int ec,vector<string>&ans,string asf){
    //     if(sr==er-1 and sc==ec-1){
    //         ans.push_back(asf);
    //         return 1;
    //     }
    //     else if(sr>=er || sc>=ec){
    //         return 0;
    //     }
    //     int count=0;
    //     count+=mazePath(sr,sc+1,er,ec,ans,asf+"H");
    //     count+=mazePath(sr+1,sc,er,ec,ans,asf+"V");
    //     count+=mazePath(sr+1,sc+1,er,ec,ans,asf+"B");
    //     return count;
    // }

    int mazePath(int sr,int sc,int er,int ec,vector<string>&ans,string asf){
        if(sr==er and sc==ec){
            ans.push_back(asf);
            return 1;
        }
        int count=0;
        if(sr+1<=er){
            count+=mazePath(sr+1,sc,er,ec,ans,asf+"H");
        }
        if(sr+1<=er and sc+1<=ec){
            count+=mazePath(sr+1,sc+1,er,ec,ans,asf+"B");
        }
        if(sc+1<=ec){
            count+=mazePath(sr,sc+1,er,ec,ans,asf+"V");           
        }
        return count;
    }

    int mazePath_HVD2(int sr,int sc,int er,int ec, vector<vector<int>>&dir,vector<string>&dirS,vector<string>&ans,string asf){
        if(sr==er and sc==ec){
            ans.push_back(asf);
            return 1;
        }
        int count=0;
        for(int d=0;d<dir.size();d++){
            int x=sr + dir[d][0];
            int y=sc + dir[d][1];
            if(x>=0 and y>=0 and x<=er and y<=ec)
                count+=mazePath_HVD2(x,y,er,ec,dir,dirS,ans,asf+dirS[d]);
        }
        return count;
    }
    void mazePathC(vector<string>&ans){
        vector<vector<int>>dir{{0,1},{1,0},{1,1}};
        vector<string>dirS{"H","V","D"};
        mazePath_HVD2(0,0,2,2,dir,dirS,ans,"");
    }

    int floodFill(int sr,int sc,vector<vector<bool>>&matrix,vector<vector<int>>&dir,vector<string>&dirS,vector<string>&ans,string asf){
        if(sr==matrix.size()-1 and sc==matrix[0].size()-1){
            ans.push_back(asf);
            return 1;
        }

        int count=0;
        matrix[sr][sc]=true;

        for(int d=0;d<dir.size();d++){
            int x=sr+dir[d][0];
            int y=sc+dir[d][1];
            if(x>=0 and y>=0 and x<matrix.size() && y<matrix[0].size() and !matrix[x][y])
                count+=floodFill(x,y,matrix,dir,dirS,ans,asf+dirS[d]);
        }

        matrix[sr][sc]=false;
        return count;
    }
    
    int floodFill_Multi1(int sr,int sc,vector<vector<bool>>&matrix,vector<vector<int>>&dir,vector<string>&dirS,vector<string>&ans,string asf){
        if(sr==matrix.size()-1 and sc==matrix[0].size()-1){
            ans.push_back(asf);
            return 1;
        }

        int count=0;
        matrix[sr][sc]=true;
        for(int rad=1;rad<=max(matrix.size(),matrix[0].size());rad++){
            for(int d=0;d<dir.size();d++){
                int x=sr+rad*dir[d][0];
                int y=sc+rad*dir[d][1];
                if(x>=0 and y>=0 and x<matrix.size() && y<matrix[0].size() and !matrix[x][y])
                    count+=floodFill_Multi1(x,y,matrix,dir,dirS,ans,asf+dirS[d]+to_string(rad));
            }
        }
        

        matrix[sr][sc]=false;
        return count;
    }

    int floodFill_Multi2(int sr,int sc,vector<vector<bool>>&matrix,vector<vector<int>>&dir,vector<string>&dirS,vector<string>&ans,string asf){
        if(sr==matrix.size()-1 and sc==matrix[0].size()-1){
            ans.push_back(asf);
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
                        count+=floodFill_Multi2(x,y,matrix,dir,dirS,ans,asf+dirS[d]+to_string(rad));
                }else{
                    break;
                }
            }
        }
        matrix[sr][sc]=false;
        return count;
    }

    void floodFill_(vector<string>&ans){
        vector<vector<bool>>matrix(3,vector<bool>(3,false));
        vector<vector<int>>dir{{0,1},{1,0},{1,1},{-1,1}};
        vector<string>dirS{"H","V","D","E"};
        // cout<<floodFill(0,0,matrix,dir,dirS,ans,"")<<" ";
        cout<<floodFill_Multi1(0,0,matrix,dir,dirS,ans,"")<<endl;
        cout<<endl;
        // cout<<floodFill_Multi2(0,0,matrix,dir,dirS,ans,"")<<' ';
    }

int main(){
    vector<string>ans;
    freopen("../input.txt","r",stdin);
    freopen("../output.txt","w",stdout);
    // mazePathC(ans);
    floodFill_(ans);
    cout<<"[";
    for(auto x:ans) cout<<x<<",";
    cout<<"]";
    return 0;
}