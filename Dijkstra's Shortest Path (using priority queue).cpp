#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int n;
    vector<vector<pair<int,int>>> gp;
    public:
    Graph(int n)
    {
        this->n=n;
        gp.resize(n);
    }
    void addedge(int a, int b, int w)
    {
        gp[a].push_back(make_pair(b,w));
        gp[b].push_back(make_pair(a,w));
    }
    vector<pair<int,int>> adj(int c)
    {
        return gp[c];
    }
};

vector<int> DijkstraShortestPath(int n, vector<vector<int>> edges, int start)
{
    Graph g(n);
    for(auto i:edges)
    {
        g.addedge(i[0]-1,i[1]-1,i[2]);
    }
    vector<bool> removed(n,false);
    vector<int> dist(n,-1);
    int z=n;
    auto cmp = [](pair<int,int>& a, pair<int,int>& b) {
        return a.second>b.second;
    };
    priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> pq(cmp);
    dist[start-1]=0;
    pq.push(make_pair(start-1,0));
    while ((!pq.empty())&&(z)) {
        pair<int,int> k=pq.top();
        pq.pop();
        if(!removed[k.first]) {
            z--;
            removed[k.first]=true;
            for(pair<int,int> i:g.adj(k.first)) {
                if(dist[i.first]!=-1) {
                    if(k.second+i.second<dist[i.first]) {
                        dist[i.first]=k.second+i.second;
                        pq.push(make_pair(i.first,k.second+i.second));
                    }
                }
                else {
                    dist[i.first]=k.second+i.second;
                    pq.push(make_pair(i.first,k.second+i.second));
                }
            }
        }
    }
    for(int h=start-1;h<n-1;h++)
    {
        dist[h]=dist[h+1];
    }
    dist.pop_back();
    return dist;
}