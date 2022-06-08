#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;



int n;
int graph[100][100];
int ans[100][100];
int ans2[100][100];
int visited[100];

struct Node{
    int from;
    int to;
    int weight;
    Node(int f, int t, int w){
        from = f;
        to = t;
        weight = w;
    }
    void print(){
        cout<<from<<"-"<<to<<": "<<weight<<endl;
    }
};



class DisjointSet{
private:
    int *parent;
public:
    DisjointSet(int n){
        parent = new int[n];
        for(int i=0;i<n;i++){
            parent[i] = i;
        }
    }
    ~DisjointSet(){
        delete [] parent;
    }
    int Find(int i){
        while(parent[i]!=i){
            i = parent[i];
        }
        return i;
    }
    void Merge(int x, int y){
        int px = Find(x);
        int py = Find(y);
        parent[px] = py;
    }
    void print(){
        for(int i=0;i<n;i++){
            cout<<parent[i]<<" ";
        }
        cout<<endl;
        for(int i=0;i<n;i++){
            cout<<i<<" ";
        }
        cout<<endl;
    }
};


int getlength(int from, int to){
    return graph[from][to];
}

void printAns(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void printAns2(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<ans2[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

struct cmp{
    bool operator()(Node a, Node b){
        if(a.weight==b.weight){
            return a.from < b.from;
        }
        return a.weight < b.weight;
    }
};

//优先队列采用最大堆，不稳定！
priority_queue<Node, vector<Node>, cmp> pq;
priority_queue<Node, vector<Node>, cmp> pq2;

int main()
{

    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>graph[i][j];
        }
    }


    Node nd(0,0,0);
    pq.push(nd);

    //优先队列中选择权值最小的
    //记住visited数组这个资源
    cout<<"Prim:"<<endl;
    printAns();
    for(int k=1;k<n;k++){
        int minWeight = 10000;
        int from = -1;
        int to = -1;
        visited[0] = 1;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(visited[i]==1 && visited[j]==0 && graph[i][j] < minWeight && graph[i][j]!=0){
                    minWeight = graph[i][j];
                    from = i;
                    to = j;
                }
            }
        }
        visited[to] = 1;
        ans[from][to] = minWeight;
        ans[to][from] = minWeight;
        printAns();
    }

    /*
    while(!pq.empty()){
        int u = pq.top().to;
        int from = pq.top().from;
        int to = pq.top().to;
        int weight = pq.top().weight;
        pq.pop();

        if(visited[u]){
            continue;
        }
        visited[u] = 1;
        ans[from][to] = weight;
        ans[to][from] = weight;
        printAns();

        for(int i=0;i<n;i++){
            if(graph[u][i]!=0 && !visited[i]){
                Node newNode(u,i,getlength(u,i));
                pq.push(newNode);
            }
        }
    }
    */

    //*************************
    cout<<"Kruskal:"<<endl;
    printAns2();
    DisjointSet ds(n);
    vector<Node> vec;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(graph[i][j]!=0){
                Node newNode(i,j,graph[i][j]);
                vec.push_back(newNode);
            }
        }
    }
    sort(vec.begin(), vec.end(), cmp());
    //for(auto it = vec.begin();it!=vec.end();it++){
    //    it->print();
    //}
    int cnt = 0;
    while(!vec.empty()){
        if(cnt==n-1){
            break;
        }
        int u = vec.begin()->from;
        int v = vec.begin()->to;
        int weight = vec.begin()->weight;
        vec.erase(vec.begin());

        if(ds.Find(u)!=ds.Find(v)){
            ds.Merge(u,v);

            ans2[u][v] = weight;
            ans2[v][u] = weight;
            printAns2();
            //cout<<u<<"-"<<v<<": "<<weight<<endl;
            //ds.print();
            //cout<<endl;
            cnt++;
        }
    }
    return 0;
}
