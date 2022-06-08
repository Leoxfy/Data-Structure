#include <iostream>
using namespace std;
int graph[100][100];
int counts[100];
int books[100];
int n;

void printGraph(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
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
    //ͳ�����еĵ�����
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(graph[j][i]==1){
                counts[i]++;
            }
        }
    }


    while(1){
        int flag = 0;
        for(int i=0;i<n;i++){
            if(counts[i]==0 && books[i]==0){
                //��ͼ����ȥ�����
                for(int j=0;j<n;j++){
                    if(graph[i][j]>0){
                        graph[i][j]--;
                        counts[j]--;
                    }
                }
                //���������Ѿ�����ȥ
                books[i] = 1;
                flag = 1;
                break;
            }
        }
        if(flag==0){
            break;
        }
    }
    int flag2 = 0;
    for(int i=0;i<n;i++){
        if(counts[i]!=0){
            flag2 =1;
            break;
        }
    }
    if(flag2==0){
        cout<<"NO"<<endl;
    }else{
        cout<<"YES"<<endl;
    }
    return 0;
}
