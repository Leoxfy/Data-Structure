#include <iostream>

using namespace std;
struct Node{
    int k;
    int exp;
};
Node a[1000];
int main()
{
    int k, exp;
    int n = 0;
    while(cin>>k){
        cin>>exp;
        a[n].k = k;
        a[n].exp = exp;
        n++;
    }
    for(int i=0;i<n;i++){
        a[i].k = a[i].k * a[i].exp;
        if(a[i].exp!=0){
            a[i].exp--;
        }
        //还没考虑负数！
    }
    for(int i=0;i<n;i++){
        if(a[i+1].k==0){
            break;
        }
        cout<<a[i].k<<" "<<a[i].exp<<" ";
    }
    cout<<a[n-2].k<<" "<<a[n-2].exp;
    return 0;
}
