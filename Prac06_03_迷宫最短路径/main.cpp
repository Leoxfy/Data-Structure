#include <iostream>
#include <queue>
#include <stack>
using namespace std;
struct Pointt{
    int x;
    int y;
    Pointt(int xx, int yy){
        x = xx;
        y = yy;
    }
    Pointt(){
        x = -1;
        y = -1;
    }
    void print(){
        cout<<"("<<x<<","<<y<<")"<<" ";
    }
};

int graph[100][100];
int book[100][100];
Pointt path[100][100];
int startX, startY;
int endX, endY;
int h, w;
int flag = 0;
int nextPath[4][2] = {
    {-1,0},{0,1},{1,0},{0,-1}
};


queue<Pointt> q;

void testPath(){
    for(int i=1;i<=w;i++){
        for(int j=1;j<=h;j++){
            path[i][j].print();
        }
        cout<<endl;
    }
}
void printGraph(){
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    cin>>h>>w;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cin>>graph[i][j];
            if(graph[i][j]==3){
                startX = i;
                startY = j;
            }
            if(graph[i][j]==4){
                endX = i;
                endY = j;
            }
        }
    }

    Pointt start(startX,startY);
    book[startX][startY] = 1;
    q.push(start);

    while(!q.empty()){
        if(flag==1){
            break;
        }
        int curX = q.front().x;
        int curY = q.front().y;
        Pointt curNode = q.front();
        q.pop();

        for(int i=0;i<4;i++){
            int nextX = curX + nextPath[i][0];
            int nextY = curY + nextPath[i][1];
            if(graph[nextX][nextY]==0 || book[nextX][nextY]==1){
                continue;
            }
            if(graph[nextX][nextY]==4){
                path[nextX][nextY] = curNode;
                flag = 1;
                break;
            }
            if(graph[nextX][nextY]==1){
                path[nextX][nextY] = curNode;
                book[nextX][nextY] = 1;
                Pointt newPoint(nextX,nextY);
                q.push(newPoint);
            }
        }
    }


    //testPath();
    int x = endX;
    int y = endY;
    stack<Pointt> s;
    while(1){
        Pointt now(x-1, y-1);
        s.push(now);
        int a = x;
        int b = y;
        x = path[a][b].x;
        y = path[a][b].y;
        if(x==-1 && y==-1){
            break;
        }
    }
    while(!s.empty()){
        cout<<s.top().x<<" "<<s.top().y<<endl;
        s.pop();
    }
    return 0;
}
