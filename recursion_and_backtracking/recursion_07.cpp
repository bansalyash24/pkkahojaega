#include <bits/stdc++.h>
using namespace std;

int row[9];
int col[9];
typedef vector<bool> vb;
int mat[3][3];
bool isitSafetoPlaceNumber(vector<vector<char>> &board, int r, int c, int num)
{

    // row
    for (int i = 0; i < 9; i++)
    {
        if (board[r][i] - '0' == num)
        {
            return false;
        }
    }

    // col
    for (int i = 0; i < 9; i++)
    {
        if (board[i][c] - '0' == num)
        {
            return false;
        }
    }

    // block
    r = (r / 3) * 3;
    c = (c / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[r + i][c + j] - '0' == num)
            {
                return false;
            }
        }
    }

    return true;
}
bool solveSuduko_01(vector<vector<char>> &board, vector<int> &emptyindex, int idx)
{
    if (idx == emptyindex.size())
    {
        return true;
    }
    int r = emptyindex[idx] / 9;
    int c = emptyindex[idx] % 9;

    for (int num = 1; num <= 9; num++)
    {
        if (isitSafetoPlaceNumber(board, r, c, num))
        {
            board[r][c] = char(48 + num);
            if (solveSuduko_01(board, emptyindex, idx + 1))
                return true;
            board[r][c] = '.';
        }
    }
    return false;
}

bool solveSuduko_02(vector<vector<char>> &board, vector<int> &emptyindex, int idx)
{
    if (idx == emptyindex.size())
    {
        return true;
    }
    int r = emptyindex[idx] / 9;
    int c = emptyindex[idx] % 9;

    for (int num = 1; num <= 9; num++)
    {
        int mask = (1 << num);
        if ((row[r] & mask) == 0 and (col[c] & mask) == 0 and (mat[r][c] & mask) == 0)
        {
            row[r] ^= mask;
            col[c] ^= mask;
            mat[r / 3][c / 3] ^= mask;
            board[r][c] = char(num + '0');
            if (solveSuduko_02(board, emptyindex, idx + 1))
                return true;
            board[r][c] = '.';
            row[r] ^= mask;
            col[c] ^= mask;
            mat[r / 3][c / 3] ^= mask;
        }
    }
    return false;
}

void solveSudoku(vector<vector<char>> &board)
{
    vector<int> emptyindex;
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == '.')
            {
                emptyindex.push_back(i * 9 + j);
            }
            else
            {
                int mask = 1 << (board[i][j] - '0');
                row[i] ^= mask;
                col[j] ^= mask;
                mat[i / 3][j / 3] ^= mask;
            }
        }
    }
    solveSuduko_01(board, emptyindex, 0);
    // solveSuduko_02(board,emptyindex,0);
}

int wordBreak(string str, string ans, unordered_set<string> dict, int longestWordLen)
{
    if (str.length() == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = 0; i < str.size(); i++)
    {
        string nstr = str.substr(0, i + 1);
        if (nstr.length() > longestWordLen)
            break;

        if (dict.find(nstr) != dict.end())
        {
            string rstr = str.substr(i + 1);
            count += wordBreak(rstr, ans + nstr + " ", dict, longestWordLen);
        }
    }

    return count;
}

int friendsPairing(string str,string ans,vb &used){

    int single=friendsPairing(str.substr(1),ans+"("+str[0]+")");

    for(int i=1;i<str.size();i++){
        string friend=str[0] +""+str[i];
        used[i]=true;
    }
}

int main()
{
    string str1 = "bz";
    string str2 = "ba";
    cout << str1.compare(str2);
    return 0;
}