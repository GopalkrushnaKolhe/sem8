#include<bits/stdc++.h>

using namespace std::chrono;
using namespace std;

class Graph{
    int V;
    vector<vector<int>> adj;

public:
Graph(int V){
    this->V=V;
    adj.resize(V);
}

void addedge(int u,int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void sequentialBFS(int startindex){
    vector<bool> visited(V,false);
    queue<int> q;
    visited[startindex]=true;
    q.push(startindex);
    while(!q.empty()){
        int v=q.front();
        q.pop();
        cout<<v<<" ";
        for(int i=0;i<adj[v].size();i++){
            int n=adj[v][i];
            if(visited[n]==false){
                visited[n]=true;
                q.push(n);
            }

        }
    }
}

void sequentialDFS(int startindex){
    vector<bool> visited(V,false);
    sequentialDFSUtil(startindex,visited);
}

void sequentialDFSUtil(int startindex,vector<bool> &visited){
    visited[startindex]=true;
    cout<<startindex<<" ";
    for(int i=0;i<adj[startindex].size();i++){
        int curr=adj[startindex][i];
        if(visited[curr]==false){
            sequentialDFSUtil(curr,visited);
        }
    }
}

void parallelDFS(int startindex){
    vector<bool> visited(V,false);
    sequentialDFSUtil(startindex,visited);
}

void parallelDFSUtil(int startindex,vector<bool> &visited){
    visited[startindex]=true;
    cout<<startindex<<" ";

    #pragma omp parallel for
    for(int i=0;i<adj[startindex].size();i++){
        int curr=adj[startindex][i];
        if(visited[curr]==false){
            sequentialDFSUtil(curr,visited);
        }
    }
}

void ParallelBFS(int startindex){
    vector<bool> visited(V,false);
    queue<int> q;
    visited[startindex]=true;
    q.push(startindex);

    while(!q.empty()){
        int v;
#pragma omp single

        v=q.front();
        q.pop();
        cout<<v<<" ";

#pragma omp parallel for

        for(int i=0;i<adj[v].size();i++){
            int n=adj[v][i];
            if(visited[n]==false){

#pragma omp critical

                visited[n]=true;
                q.push(n);
            }

        }
    }
}


};

int main(){
    int n,edges;
    int startindex;
    //cin>>n;
    //cout<<"Enter the number of vertices"<<" ";
    Graph g(0);
    int choice;

 
            cout<<"Enter the number of vertices"<<" ";
            cin>>n;
            cout<<"enter the no of edges ";
            cin>>edges;
            g= Graph(n);
            for(int i=0;i<edges;i++){
                int src,dest;
                cout<<"Enter source ";
                cin>>src;
                cout<<"Enter Destination ";
                cin>>dest;
                g.addedge(src,dest);
            }

            //int startindex;
            cout<<"Enter the starting index ";
            cin>>startindex;
            auto start = high_resolution_clock::now();
            cout<<"BFS is "<<endl;
            g.ParallelBFS(startindex);
            cout<<endl;
            auto stop = high_resolution_clock::now();
            auto duration= duration_cast<microseconds>(stop - start);
            cout<<"Parallel BFS time "<<duration.count()<<" microseconds"<<endl;

            start = high_resolution_clock::now();
            cout<<" Sequential BFS is "<<endl;
            g.sequentialBFS(startindex);
            cout<<endl;
            stop = high_resolution_clock::now();
            duration= duration_cast<microseconds>(stop - start);
            cout<<"Sequential BFS time "<<duration.count()<<" microseconds"<<endl;
                       
  
            start = high_resolution_clock::now();
            cout<<"DFS is "<<endl;
            g.parallelDFS(startindex);
            cout<<endl;
            stop = high_resolution_clock::now();
            duration= duration_cast<microseconds>(stop - start);
            cout<<"Parallel DFS time "<<duration.count()<<" microseconds"<<endl;

            start = high_resolution_clock::now();
            cout<<" Sequential DFS is "<<endl;
            g.sequentialDFS(startindex);
            cout<<endl;
            stop = high_resolution_clock::now();
            duration= duration_cast<microseconds>(stop - start);
            cout<<"Sequential DFS time "<<duration.count()<<" microseconds"<<endl;

    return 0;
}