#include <iostream>
#include <queue>
using namespace std;
int mg[1000][1000];
int mark[1000][1000];
int aa,bb;

int nex[8][2] = {
    {-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}
};
struct Point{
    int x;
    int y;
    Point(int xx=0, int yy=0):x(xx),y(yy){}
};

Point road[1000][1000];
queue<Point> q;
//考虑出界的问题
void bfs(){
    Point st(1,1);
    q.push(st);
    mark[1][1] = 1;
    while(!q.empty()){
        Point now = q.front();
        int x = now.x;
        int y = now.y;
        q.pop();

        for(int i=0;i<8;i++){
            int tx = x + nex[i][0];
            int ty = y + nex[i][1];
            if(mg[tx][ty]==0 && mark[tx][ty]==0){
                if(tx==aa && ty==bb){
                    road[tx][ty] = now;
                    return ;
                }else{
                    Point temp(tx,ty);
                    q.push(temp);
                    mark[tx][ty] = 1;
                    road[tx][ty] = now;
                }
            }
        }
    }
}
int main()
{
    cin>>aa>>bb;
    for(int i=1;i<=aa;i++){
        for(int j=1;j<=bb;j++){
            cin>>mg[i][j];
        }
    }
    //设置边界
    for(int i=0;i<=bb+1;i++){
        mg[0][i] = 1;
        mg[aa+1][i] = 1;
    }
    for(int i=0;i<=aa+1;i++){
        mg[i][0] = 1;
        mg[i][bb+1] = 1;
    }
    bfs();
    int x = road[aa][bb].x;
    int y = road[aa][bb].y;
    cout<<"("<< aa <<","<< bb <<")"<<endl;
    while(1){
        cout<<"("<< x <<","<< y <<")"<<endl;
        int a = x;
        int b = y;
        x = road[a][b].x;
        y = road[a][b].y;
        if(x==0 && y==0){
            break;
        }
    }
    return 0;
}
