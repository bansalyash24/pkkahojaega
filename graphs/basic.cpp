#include<bits/stdc++.h>
using namespace std;

typedef vector<vector<int>>vvi;
typedef vector<vector<char>>vvc;
typedef vector<vector<bool>>vvb;
typedef vector<int>vi;
typedef vector<char>vi;
typedef vector<bool>vb;

class Edge{
    public:
    int src,dest,weight;
    Edge(int x,int y,int z){
        this->src=x;
        this->dest=y;
        this->weight=z;
    }
};

//Connected Component




// hamiltonian path src dependent hota h
void hamiltonian(int src,vb &vis,int count){
    if(count==n){
        cout<<"Hamiltonian Path"<<psf<<src;
    }

    vis[src]=true;
    for(Edge e:graph[src]){
        if(!vis[e.v]){
            hamiltonian(e.v,vis,count+1);
        }
    }
    vis[src]=false;
}

void hamiltonian_cycle(int orgsrc,int src,vb &vis,int count,string psf){
    if(count==n){
        int idx=findEdge(src,orgsrc);
        if(idx==-1){
            cout<<"Hamiltonian Path"<<psf<<src; 
        }else{
            cout<<"Hamiltonian Cycle"<<psf<<src<<orgsrc;
        }
    }

    vis[src]=true;
    for(Edge e:graph[src]){
        if(!vis[e.v]){
            hamiltonian(orgsrc,e.v,vis,count+1,psf+to_string(e.v));
        }
    }
    vis[src]=false;
}

//cycle detection using dfs

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