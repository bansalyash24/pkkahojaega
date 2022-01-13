//important lecture
#include<bits/stdc++.h>
using namespace std;

bool isSafetoPlaceQueen(vector<vector<bool>>&board,int row,int col){

    // vector<vector<int>>dir{{-1,0},{0,-1},{-1,-1},{-1,1}};  
    //combination m 4 direction dekhni hogi

    vector<vector<int>>dir{{-1,0},{0,-1},{-1,-1},{-1,1},{1,0},{0,1},{1,1},{1,-1}};  
    // permutation m 8 direction dekhni hogi
    int n=board.size();
    for(int d=0;d<dir.size();d++){
        for(int rad=1;rad<n;rad++){

            int x=row+rad*dir[d][0];
            int y=col+rad*dir[d][1];
            if(x>=0 and y>=0 and x<n and y<n){
                if(board[x][y]){
                    return false;
                }
            }
            else{
                break;
            }
        }
    }
    return true;
}

int n_queen_01_comb(vector<vector<bool>>&board,int tnq,int idx,string ans){
    if(tnq==0){
        cout<<ans<<endl;
        return 1;
    }

    int count=0;
    int n=board.size(),m=board[0].size();
    for(int i=idx;i<n*m;i++){
        int ro=i/m;
        int col=i%m;
        if(isSafetoPlaceQueen(board,ro,col)){
            board[ro][col]=true;
            count+=n_queen_01_comb(board,tnq-1,i+1,ans+"("+to_string(ro)+","+to_string(col)+")");
            board[ro][col]=false;
        }
        
    }
    return count;
}

int n_queen_01_comb_seq(vector<vector<bool>>&board,int tnq,int idx,string ans){
    int n=board.size(),m=board[0].size();
    if(tnq==0 || idx==n*m){
        if(tnq==0){
            cout<<ans<<endl;
            return 1;
        }
        return 0;
    }

    int count=0;
    int ro=idx/m;
    int col=idx%m;
    if(isSafetoPlaceQueen(board,ro,col)){
        board[ro][col]=true;
        count+=n_queen_01_comb(board,tnq-1,idx+1,ans+"("+to_string(ro)+","+to_string(col)+")");
        board[ro][col]=false;
    }
    count+=n_queen_01_comb(board,tnq,idx+1,ans);
    return count;
}

int n_queen_01_perm(vector<vector<bool>>&board,int tnq,int idx,string ans){
    if(tnq==0){
        cout<<ans<<endl;
        return 1;
    }

    int count=0;
    int n=board.size(),m=board[0].size();
    for(int i=idx;i<n*m;i++){
        int ro=i/m;
        int col=i%m;
        if(isSafetoPlaceQueen(board,ro,col) and !board[ro][col]){
            board[ro][col]=true;
            count+=n_queen_01_perm(board,tnq-1,0,ans+"("+to_string(ro)+","+to_string(col)+")");
            board[ro][col]=false;
        }
        
    }
    return count;
}

int n_queen_01_perm_seq(vector<vector<bool>>&board,int tnq,int idx,string ans){
    int n=board.size(),m=board[0].size();
    if(tnq==0 || idx==n*m){
        if(tnq==0){
            cout<<ans<<endl;
            return 1;
        }
        return 0;
    }

    int count=0;

    int ro=idx/m;
    int col=idx%m;
    if(isSafetoPlaceQueen(board,ro,col) and !board[ro][col]){
        board[ro][col]=true;
        count+=n_queen_01_perm_seq(board,tnq-1,idx+1,ans+"("+to_string(ro)+","+to_string(col)+")");
        board[ro][col]=false;
    }
    count+=n_queen_01_perm_seq(board,tnq,idx,ans);
    return count;
}

vector<bool>row;
vector<bool>col;
vector<bool>diag;
vector<bool>aDiag;

int n_queen_02_comb(int n,int m,int tnq,int idx,string ans){
    if(tnq==0){
        cout<<ans<<endl;
        return 1;
    }

    int count=0;
    for(int i=idx;i<n*m;i++){
        int r=i/m;
        int c=i%m;
        if(!row[r] && !col[c] && !diag[r+c] && !aDiag[r-c+m-1]){
            row[r]=col[c]=diag[r+c]=aDiag[r-c+m-1]=true;
            count+=n_queen_02_comb(n,m,tnq-1,i+1,ans+"("+to_string(r)+","+to_string(c)+")");
            row[r]=col[c]=diag[r+c]=aDiag[r-c+m-1]=false;
        }
    }
    return count;
}

int n_queen_03_comb(int n,int r,string ans){
    if(r==n){
        cout<<ans<<endl;
        return 1;
    }

    int count=0;
    for(int c=0;c<n;c++){
        if(!col[c] && !diag[r+c] && !aDiag[r-c+n-1]){
            col[c]=diag[r+c]=aDiag[r-c+n-1]=true;
            count+=n_queen_03_comb(n,r+1,ans+"("+to_string(r)+","+to_string(c)+")");
            col[c]=diag[r+c]=aDiag[r-c+n-1]=false;
        }
    }
    return count;
}
int n_queen_03_comb(int n,int tnq,int r,string ans){
    if(tnq==0){
        cout<<ans<<endl;
        return 1;
    }

    int count=0;
    for(int c=0;c<n;c++){
        if(!col[c] && !diag[r+c] && !aDiag[r-c+n-1]){
            col[c]=diag[r+c]=aDiag[r-c+n-1]=true;
            count+=n_queen_03_comb(n,tnq-1,r+1,ans+"("+to_string(r)+","+to_string(c)+")");
            col[c]=diag[r+c]=aDiag[r-c+n-1]=false;
        }
    }
    return count;
}

int n_queen_03_permu(int n,int tnq,int r,string ans){
    if(tnq==0){
        cout<<ans<<endl;
        return 1;
    }

    int count=0;
    for(int c=0;c<n;c++){
        if(!col[c] && !diag[r+c] && !aDiag[r-c+n-1]){
            col[c]=diag[r+c]=aDiag[r-c+n-1]=true;
            count+=n_queen_03_permu(n,tnq-1,0,ans+"("+to_string(r)+","+to_string(c)+") ");
            col[c]=diag[r+c]=aDiag[r-c+n-1]=false;
        }
    }
    count+=n_queen_03_permu(n,tnq,r+1,ans);

    return count;
}

int n_queen_02_perm(int n,int m,int tnq,int idx,string ans){
    if(tnq==0){
        cout<<ans<<endl;
        return 1;
    }

    int count=0;
    for(int i=idx;i<n*m;i++){
        int r=i/m;
        int c=i%m;
        if(!row[r] && !col[c] && !diag[r+c] && !aDiag[r-c+m-1]){
            row[r]=col[c]=diag[r+c]=aDiag[r-c+m-1]=true;
            count+=n_queen_02_perm(n,m,tnq-1,0,ans+"("+to_string(r)+","+to_string(c)+")");
            row[r]=col[c]=diag[r+c]=aDiag[r-c+m-1]=false;
        }
    }
    return count;
}


int main(){
    freopen("../input.txt","r",stdin);
    freopen("../output.txt","w",stdout);
    vector<vector<bool>>board(4,vector<bool>(4,false));
    // cout<<n_queen_01_perm_seq(board,4,0,"");
    // cout<<n_queen_02_comb(4,4,4,0,"");
    int n=4,m=4;
    row.resize(n,false);
    col.resize(m,false);
    diag.resize(n+m-1,false);
    aDiag.resize(n+m-1,false);
    // cout<<n_queen_02_comb(n,m,4,0,"");
    // cout<<n_queen_03_comb(n,0,"");
    cout<<n_queen_03_permu(n,4,0,"");
    return 0;
}