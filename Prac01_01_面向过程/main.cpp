#include <iostream>
#include <algorithm>
using namespace std;
int a[1000];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int x, i;
    cin>>x>>i;
    for(int j=n+1;j>=i+1;j--){
        a[j] = a[j-1];
    }
    a[i] = x;
    n++;
    for(int i=1;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<a[n]<<endl;
    cin>>i;
    for(int j=i;j<=n-1;j++){
        a[j] = a[j+1];
    }
    n--;
    for(int i=1;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<a[n]<<endl;
    cin>>x;
    int flag = 0;
    int index;
    for(int i=0;i<=n;i++){
        if(a[i]==x){
            flag = 1;
            index = i;
            break;
        }
    }
    if(flag==0){
        cout<<"Not found"<<endl;
    }else{
        cout<<index<<endl;
    }
    for(int i=1;i<=n/2;i++){
        int t = a[i];
        a[i] = a[n-i+1];
        a[n-i+1] = t;
    }
    for(int i=1;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<a[n]<<endl;
    int m;
    cin>>m;
    for(int i=n+1;i<=n+m;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+m+1);
    for(int i=1;i<n+m;i++){
        cout<<a[i]<<" ";
    }
    cout<<a[n+m]<<endl;
    return 0;
}
