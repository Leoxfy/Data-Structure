#include <iostream>
#include <stack>
using namespace std;
int mg[1200][1200];
int mark[1200][1200];
int a,b,c,d;
bool flag = 0;
int nex[4][2] = {
    {1,0},{0,-1},{-1,0},{0,1}
};

struct Point{
    int x;
    int y;
    Point(int xx, int yy):x(xx),y(yy){}
};

stack<Point> road;
stack<Point> ans;


void dfs(int x,int y){
    if(x==c && y==d){
        flag = 1;
        return ;
    }

    for(int k=0;k<4;k++){
        int tx = x + nex[k][0];
        int ty = y + nex[k][1];

        if(mg[tx][ty]!=1 && mark[tx][ty]==0){
            mark[tx][ty] = 1;
            Point now(tx,ty);
            road.push(now);

            dfs(tx,ty);

            if(flag==0){
                mark[tx][ty] = 0;
                road.pop();
            }else if(flag==1){
                ans.push(road.top());
                road.pop();
                return;
            }
        }
    }
}

int main()
{
    int w, h;
    cin>>w>>h;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            cin>>mg[i][j];
            if(mg[i][j]==3){
                a = i;
                b = j;
            }
            if(mg[i][j]==4){
                c = i;
                d = j;
            }
        }
    }
    mark[a][b] = 1;
    dfs(a,b);
    Point st(a,b);
    ans.push(st);
    while(!ans.empty()){
        cout<<ans.top().y<<" "<<ans.top().x<<endl;
        ans.pop();
    }
    return 0;
}
