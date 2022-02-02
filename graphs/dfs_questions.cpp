#include<bits/stdc++.h>
using namespace std;

typedef vector<vector<int>>vvi;
typedef vector<vector<char>>vvc;
typedef vector<vector<bool>>vvb;
typedef vector<int>vi;
typedef vector<char>vi;
typedef vector<bool>vb;

//Ist Method
void dfs(vvc& grid,int i,int j){
    if(i<0 || j<0 || i>=grid.size() || j>=grid[0].size() || grid[i][j]=='0'){
        return;
    }
    grid[i][j]='0';
    dfs(grid,i+1,j);
    dfs(grid,i,j+1);
    dfs(grid,i-1,j);
    dfs(grid,i,j-1);
}

int numIslands(vvc& grid) {
    int ans=0;
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if(grid[i][j]=='1'){
                dfs(grid,i,j);
                ans++;
            } 
        }
    }
    return ans;
}

//IInd method
void dfs(vvc& grid,int i,int j,vvi&dir){
    grid[i][j]='0';
    for(auto &d:dir){
        int nr=i+d[0];
        int nc=j+d[1];
        if(nr>=0 && nc>=0 && nr<grid.size() && nc<grid[0].size() && grid[nr][nc]!='0'){
            dfs(grid,nr,nc,dir);
        }
    }
}

int numIslands(vvc& grid) {
    int ans=0;
    vvi dir{{-1,0},{0,1},{1,0},{0,-1}};
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if(grid[i][j]=='1'){
                dfs(grid,i,j,dir);
                ans++;
            } 
        }
    }
    return ans;
}

int maxAreadfs(vvi &grid,int sr,int sc,vvi &dir){
    grid[sr][sc]=0;
    int count=0;
    for(auto &d:dir){
        int nr=sr+d[0];
        int nc=sc+d[1];
        if(nr>=0 && nc>=0 && nr<grid.size() && nc<grid[0].size() && grid[nr][nc]==1){
            count+=maxAreadfs(grid,nr,nc,dir);
        }
    }
    return count+1;
}

//max area of islands
int maxAreaOfIsland(vector<vector<int>>& grid) {
    int ans=0;
    vvi dir{{-1,0},{0,1},{1,0},{0,-1}};
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if(grid[i][j]==1){
                int count=maxAreadfs(grid,i,j,dir);
                ans=max(ans,count);
            } 
        }
    }
    return ans;
}

int subIslandDfs(vvi &grid1,vvi &grid2,int sr,int sc,vvi &dir){
    bool ans=true;
    
    if(grid2[sr][sc]>grid1[sr][sc]){
        ans=false;
    }
    
    grid2[sr][sc]=0;
    for(auto &d:dir){
        int nr=sr+d[0];
        int nc=sc+d[1];
        if(nr>=0 && nc>=0 && nr<grid1.size() && nc<grid1[0].size() && grid2[nr][nc]==1){
            bool res=subIslandDfs(grid1,grid2,nr,nc,dir);
            ans=(ans && res);
        }
    }

    return ans;
}

//count subisland
int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
    int ans=0;
    vvi dir{{-1,0},{0,1},{1,0},{0,-1}};
    for(int i=0;i<grid2.size();i++){
        for(int j=0;j<grid2[0].size();j++){
            if(grid2[i][j]==1){
                if(subIslandDfs(grid1,grid2,i,j,dir)){
                    ans++;
                }
            }
        }
    }
    return ans;
}

//surrounded regions
void solvedfs(vector<vector<char>>& board,int sr,int sc,vvi &dir){
        board[sr][sc]='A';
        for(auto &d:dir){
            int nr=sr+d[0];
            int nc=sc+d[1];
            if(nr>=0 && nc>=0 && nr<board.size() && nc<board[0].size() && board[nr][nc]=='O'){
                solvedfs(board,nr,nc,dir);
            }
        }
}

void solve(vector<vector<char>>& board) {
    vvi dir{{-1,0},{0,1},{1,0},{0,-1}};
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            if(i==0 || j==0 || i==board.size()-1 || j==board[0].size()-1){
                if(board[i][j]=='O'){
                    solvedfs(board,i,j,dir);
                }
            }
        }
    }
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            if(board[i][j]=='A'){
                board[i][j]='O';
            }else{
                board[i][j]='X';
            }
        }
    }
}

// Number of Enclaves
void enclavedfs(vector<vector<int>>& board,int sr,int sc,vvi &dir){
    board[sr][sc]=0;
    for(auto &d:dir){
        int nr=sr+d[0];
        int nc=sc+d[1];
        if(nr>=0 && nc>=0 && nr<board.size() && nc<board[0].size() && board[nr][nc]==1){
            enclavedfs(board,nr,nc,dir);
        }
    }
}
    
int numEnclaves(vector<vector<int>>& board) {
    int ans=0;
    vvi dir{{-1,0},{0,1},{1,0},{0,-1}};
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            if(i==0 || j==0 || i==board.size()-1 || j==board[0].size()-1){
                if(board[i][j]==1){
                    enclavedfs(board,i,j,dir);
                }
            }
        }
    }
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            if(board[i][j]==1){
                ans++;
            }
        }
    }
    return ans;
}

//perimeter of island
int islandDfs(vvi &grid,int sr,int sc,vvi &dir){
    grid[sr][sc]=-1;
    int count=4;
    for(auto &d:dir){
        int nr=sr+d[0];
        int nc=sc+d[1];
        if(nr>=0 && nc>=0 && nr<grid.size() && nc<grid[0].size()){
            if(grid[nr][nc]==1){
                count=count+maxAreadfs(grid,nr,nc,dir)-1;
            }else if(grid[nr][nc]==-1){
                count-=1;
            }
        }
    }
    return count;
}
int islandPerimeter(vector<vector<int>>& grid) {
    int ans=0;
    vvi dir{{-1,0},{0,1},{1,0},{0,-1}};
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if(grid[i][j]==1){
                ans=maxAreadfs(grid,i,j,dir);
                break;
            } 
        }
    }
    return ans;
}
int main(){
    
    return 0;
}