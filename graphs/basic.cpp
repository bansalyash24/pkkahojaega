#include<bits/stdc++.h>
using namespace std;

class Edge{
    public:
    int src,dest,weight;
    Edge(int x,int y,int z){
        this->src=x;
        this->dest=y;
        this->weight=z;
    }
};

int main(){
    vector<vector<Edge *>>vt;
    vt.push_back({new Edge(0,1,2),new Edge(0,2,3)});
    for(auto it:vt){
        for(auto x:it){
            cout<<"("<<x->src<<","<<x->dest<<","<<x->weight<<") ";
        }
    }
    return 0;
}