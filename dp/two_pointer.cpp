#include<bits/stdc++.h>
using namespace std;

int dp[101][101];
typedef vector<vector<int>> vvi;
typedef vector<int> vi;

//unique pathsI leetcode 62
int mazePath_memo(int sr, int sc, int er, int ec,vvi &dir) {
    if (er == sr && ec == sc) {
        return dp[sr][sc] = 1;
    }

    if (dp[sr][sc] != -1)
        return dp[sr][sc];

    int count = 0;
    for (auto d : dir) {
        int r = sr + d[0], c = sc + d[1];
        if (r >= 0 && c >= 0 && r < er&& c < ec) {
            count += mazePath_memo(r, c, er, ec, dir);
        }
    }

    return dp[sr][sc] = count;
}

int uniquePaths(int m,int n){
    vvi dir{{1,0},{0,1}};
    return mazePath_memo(0,0,m,n,dir);
}

//uniquePathsII leetcode 63
int mazePath_II_memo(int sr, int sc,vvi &dir,vvi &grid) {
    if (sr==grid.size()-1 && sc==grid[0].size()-1) {
        return dp[sr][sc] = 1;
    }

    if (dp[sr][sc] != -1)
        return dp[sr][sc];

    int count = 0;
    for (auto d : dir) {
        int r = sr + d[0], c = sc + d[1];
        if (r >= 0 && c >= 0 && r < grid.size() && c < grid[0].size() && grid[r][c]!=1) {
            count += mazePath_II_memo(r, c, dir,grid);
        }
    }

    return dp[sr][sc] = count;
}

int uniquePathsWithObstacles(vector<vector<int>>& grid) {
    memset(dp,-1,sizeof(dp));

    vvi dir{{1,0},{0,1}};

    // cases [[1]],[[1],[0]]

    if(grid[0][0]==1) return 0;

    return mazePath_II_memo(0,0,dir,grid);
}


int main(){
    vvi dir{{0,1},{1,0}};
    return 0;
}