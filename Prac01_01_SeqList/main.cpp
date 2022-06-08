#include <iostream>
#include <algorithm>
using namespace std;
const int defaultsize = 100;

typedef int T;
class SeqList{
private:
    T *elem;
    int maxsize;
    int last;
public:
    SeqList(int sz=defaultsize);
    ~SeqList();
    void input(int n);
    void output();
    bool Insert(int i, const T& x);
    bool Remove(int i, T& x);
    int Search(const T& x);
    void Reverse();
    void Sort();
    void add(const SeqList& L);
};
int main()
{
    int n;
    cin>>n;
    SeqList seql;
    seql.input(n);
    T x;
    int i;
    cin>>x>>i;
    seql.Insert(i-1,x);
    seql.output();
    cin>>i;
    seql.Remove(i-1,x);
    seql.output();
    cin>>x;
    i = seql.Search(x);
    if(i==-1){
        cout<<"Not found"<<endl;
    }else{
        cout<<i+1<<endl;
    }
    seql.Reverse();
    seql.output();
    cin>>n;
    SeqList b;
    b.input(n);
    seql.add(b);
    seql.Sort();
    seql.output();
    return 0;
}
SeqList::SeqList(int sz){
    if(sz>0){
        maxsize = sz;
        elem = new T[sz];
        if(elem==NULL){
            cerr<<"error"<<endl;
            exit(1);
        }
        last = -1;
    }
}

SeqList::~SeqList(){
    delete elem;
}

void SeqList::input(int n){
    for(int i=0;i<n;i++){
        cin>>elem[i];
        last++;
    }
    return ;
}
bool SeqList::Insert(int i, const T& x){
    if(i<0 || i>last+1 || last+1==maxsize){
        return false;
    }
    last++;
    for(int j=last;j>i;j--){
        elem[j] = elem[j-1];
    }
    elem[i] = x;
    return true;
}
bool SeqList::Remove(int i, T& x){
    if(i<0 || i>last){
        return false;
    }
    x = elem[i];
    for(int j=i;j<last;j++){
        elem[j] = elem[j+1];
    }
    last--;
    return true;
}

int SeqList::Search(const T& x){
    if(last==-1){
        return -1;
    }
    for(int i=0;i<=last;i++){
        if(elem[i]==x){
            return i;
        }
    }
    return -1;
}


void SeqList::Reverse(){
    if(last<=0){
        return ;
    }
    for(int i=0;i<=last/2;i++){
        T t;
        t = elem[i];
        elem[i] = elem[last-i];
        elem[last-i] = t;
    }
    return ;
}

void SeqList::add(const SeqList& L){
    if(L.last==-1){
        return ;
    }
    for(int i=0;i<=L.last;i++){
        if(last+1==maxsize){
            return ;
        }
        last++;
        elem[last] = L.elem[i];
    }
    return ;
}

void SeqList::output(){
    for(int i=0;i<last;i++){
        cout<<elem[i]<<" ";
    }
    cout<<elem[last]<<endl;
}


void SeqList::Sort(){
    sort(elem,elem+last+1);
    return;
}
