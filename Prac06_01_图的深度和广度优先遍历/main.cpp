#include <iostream>
#include <queue>
using namespace std;

int graph[100][100];
int visited[100];
int n;

void DFS(int from){
    cout<<from<<" ";
    visited[from] = 1;
    for(int i=0;i<n;i++){
        if(graph[from][i]==1 && visited[i]==0){
            DFS(i);
        }
    }
}

void WFS(int from){
    queue<int> q;
    q.push(from);
    visited[from] = 1;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        cout<<cur<<" ";
        for(int i=0;i<n;i++){
            if(graph[cur][i]==1 && visited[i]==0){
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}

void reset(){
    for(int i=0;i<n;i++){
        visited[i] = 0;
    }
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>graph[i][j];
        }
    }
    cout<<"DFS"<<endl;
    for(int i=0;i<n;i++){
        DFS(i);
        cout<<endl;
        reset();
    }
    cout<<"WFS"<<endl;
    for(int i=0;i<n;i++){
        WFS(i);
        cout<<endl;
        reset();
    }
    return 0;
}
