#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<char>> vvc;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;

//crossword
bool isPossibleToPlace_H(vvc &board,string &word,int r,int c){
    int l=word.length(),m=board[0].size();

    if(c+l>m) return false;
    if(c==0 && c+l<m && board[r][c+l]!='+') return false;

    if(c!=0 && c+l==m && board[r][c-1]!='+') return false;

    if(c!=0 && c+l<m && board[r][c-1]!='+' && board[r][c+l]!='+') return false;

    for(int i=0;i<word.size();i++){
        if(c+i>=m) return false;

        if(board[r][c+i]!='-' && word[i]!=board[r][c+i]){
            return false;
        }
    }
    return true;
}

int place_H(vvc &board, string &word, int r, int c)
{
    int loc = 0;
    for (int i = 0; i < word.length(); i++)
    {
        if (board[r][c + i] == '-')
        {
            loc ^= (1 << i);
            board[r][c + i] = word[i];
        }
    }
    return loc;
}

void unplace_H(vvc &board, string &word, int r, int c, int loc)
{
    for (int i = 0; i < word.length(); i++)
    {
        int mask = (1 << i);
        if ((loc & mask) != 0)
        {
            board[r][c + i] = '-';
        }
    }
}

bool isPossibleToPlace_V(vvc &board,string word,int r,int c){
    int l=word.length(),n=board.size();

    if(c+l>n) return false;
    if(r==0 && r+l<n && board[r+l][c]!='+') return false;

    if(r!=0 && r+l==n && board[r-1][c]!='+') return false;

    if(r!=0 && r+l<n && board[r-1][c]!='+' && board[r+l][c]!='+') return false;

    int n=board.size(),m=board[0].size();
    for(int i=0;i<word.size();i++){
        if(r+i>=n) return false;

        if(board[r+i][c]!='-' && word[i]!=board[r+i][c]){
            return false;
        }
    }
    return true;
}


int place_V(vvc &board, string &word, int r, int c)
{
    int loc = 0;
    for (int i = 0; i < word.length(); i++)
    {
        if (board[r + i][c] == '-')
        {
            loc ^= (1 << i);
            board[r + i][c] = word[i];
        }
    }
    return loc;
}

void unplace_V(vvc &board, string &word, int r, int c, int loc)
{
    for (int i = 0; i < word.length(); i++)
    {
        int mask = (1 << i);
        if ((loc & mask) != 0)
        {
            board[r + i][c] = '-';
        }
    }
}

int crossWord(vvc &board,vector<string>&words,int idx){

    if(idx==words.size()){
        return 1;
    }

    string word=words[idx];
    int count=0;
    int n=board.size(),m=board[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(board[i][j]=='-' || board[i][j]==word[0]){

                if(isPossibleToPlace_H(board,word,i,j)){
                    int loc=place_H(board,word,i,j);
                    count+=crossWord(board,words,idx+1);
                    unplace_H(board,word,i,j,loc);
                }

                if(isPossibleToPlace_V(board,word,i,j)){
                    int loc=place_V(board,word,i,j);
                    count+=crossWord(board,words,idx+1);
                    unplace_V(board,word,i,j,loc);
                }
            }
        }
    }
    return count;
}


//goldmine
int goldmine(vvi &arr,int r,int c,vvi &dir){
    int n=arr.size(),m=arr[0].size();
    if(c==m-1){
        return arr[r][c];
    }

    int maxAns=0;

    for(int d=0;d<dir.size();d++){
        int x=r+dir[0][0];
        int y=c+dir[0][1];

        if(x>=0 && y>=0 && x<n && y<m){
            int recAns=goldmine(arr,x,y,dir);
            if(recAns+arr[r][c]>maxAns){
                maxAns=recAns+arr[r][c];
            }
        }
        
    }
    return maxAns;
}


void printvec(vi &arr){
    for(auto &i:arr){
        cout<<i;
    }
}

//k Subset with equal sum
//ye waala permutations print krega
int kSubsetSum(vi &arr,int idx,vi &setSum,vvi &sets){
    if(idx==arr.size()){
        for(int i=1;i<setSum.size();i++){
            if(setSum[i-1]!=setSum[i]) return 0;
        }

        for(auto &x:sets){
            cout<<printvec(x)<<" ";
        }
        return 1;
    }
    
    int count=0;
    int k=setSum.size();
    for(int i=0;i<k;i++){
        setSum[i]+=arr[idx];
        sets[i].push_back(arr[idx]);

        count+=kSubsetSum(arr,idx+1,setSum,sets);

        setSum[i]-=arr[idx];
        sets[i].pop_back();
    }
    return count;
}

void find(int arr[],int n){
    int first=INT_MIN;
    int second=INT_MIN;
    for(int i=0;i<n;i++){
        if(arr[i]>first){
            second=first;
            first=arr[i];
        }else if(arr[i]>second && arr[i]<first){
            second=arr[i];
        }
    }
    cout<<first<<" "<<second;
}
int main(){
    vvi dir{{-1,1},{0,1},{1,1}};
    vvi arr;
    int maxAns=0;
    for(int i=0;i<arr.size();i++){
        maxAns=max(maxAns,goldmine(arr,i,0,dir));
    }
    cout<<maxAns;

    int k=3;
    vvi sets(k);
    vi arr{1,2,3,4,5,6};
    vi setSum(k,0);
    kSubsetSum(arr,0,setSum,sets);
    return 0;
}