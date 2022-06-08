#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef  int T;
const int defaultSize = 100;

class SeqList
{
private:
    T* data;//指向动态内存分配数组的指针
    int maxSize;//动态内存分配数组的容量
    int last;//标识顺序表中最后一个元素的位置(反映顺序表中的元素个数)
    void Resize(int newSize);
public:
    SeqList(int sz=defaultSize);//构造函数
    SeqList(const SeqList& L);//拷贝构造函数
    SeqList& operator=(const SeqList& L);//赋值运算符函数

    ~SeqList();//析构函数

    int Size() const;//返回顺序表的容量
    int Length() const;//返回顺序表中元素的个数
    bool IsEmpty() const;//顺序表是否为空
    bool IsFull() const;//顺序表是否为满
    int Locate(int i) const;//检验顺序表中是否存在第i个元素
    bool GetData(int i, T& x) const;//获取顺序表中第i个位置的元素
    void SetData(int i, T& x);//将顺序表中第i个位置的元素赋值为x

    int Search(T & x) const;//在顺序表中搜索x
    bool Insert(int i, const T& x) ;//在顺序表的第i个元素的位置插入x
    bool Remove(int i, T&x) ;//删除顺序表第i个位置的元素

    void Sort() ;//对顺序表中元素进行排序
    void Reverse ();//逆置顺序表中的元素

    friend istream& operator>>(istream& in, SeqList & L);//输入运算符重载
    friend ostream& operator<<(ostream& out, const SeqList& L);//输出运算符重载

    T & operator[] ( int index );
    const T & operator[] ( int index ) const;
    void Push_Back ( const T& x);
    void Pop_Back( );
    typedef T * iterator;
    typedef const T * const_iterator;
    iterator Begin( )
    {
        return &data[0];
    }
    const_iterator Begin( ) const
    {
        return &data[0];
    }
    iterator End( )
    {
        return &data[ Length()-1 ];
    }
    const_iterator End( ) const
    {
        return &data[ Length()-1 ];
    }
};

int main()
{
    SeqList sList;

    cin>>sList;
    int i, val;
    cout<<"请输入要插入的位置及数据："<<endl;
    cin>>i>>val;
    cout<<"输入完毕。"<<endl;
    sList.Insert(i,val);
    cout<<sList;
    cout<<"请输入要删除数据的索引："<<endl;
    cin>>i;
    sList.Remove(i,val);
    cout<<"删除完毕。"<<endl;
    cout<<sList;
    cout<<"请输入要搜索的数据："<<endl;
    cin>>val;
    i=sList.Search(val);
    if(i==-1){
        cout<<"Not found"<<endl;
    }
    else{
        cout<<"该数据的位置是："<<i<<endl;
    }
    cout<<"反转后的顺序表是："<<endl;
    sList.Reverse();
    cout<<sList;
}


SeqList::SeqList(int sz){
    if(sz>0){
        maxSize = sz;
        last = -1;
        data = new T[maxSize];
        if(data==NULL){
            cerr<<"存储分配错误！"<<endl;
            exit(1);
        }
    }else{
        cout<<"构造函数的参数必须是正数！"<<endl;
    }
}
SeqList::~SeqList(){
    delete[] data;
}
SeqList::SeqList(const SeqList& L){
    maxSize = L.maxSize;
    last = L.last;
    data = new T[maxSize];
    if(data==NULL){
            cerr<<"存储分配错误！"<<endl;
            exit(1);
    }
    for(int i=0;i<last;i++){
        data[i] = L.data[i];
    }
}
void SeqList::Resize(int newSize){
    if(newSize<=0){
        cout<<"请输入一个正数！"<<endl;
        return;
    }else if(newSize<=last+1){
        cout<<"分配大小不足！"<<endl;
        return;
    }else if(newSize!=maxSize){
        T* newarray = new T[newSize];
        if(newarray==NULL){
            cerr<<"存储分配错误！"<<endl;
            exit(1);
        }
        T* src = data;
        T* des = newarray;
        for(int i=0;i<=last;i++){
            *des++ = *src++;
        }
        delete []data;
        data = newarray;
        maxSize = newSize;
        return;
    }
}

SeqList& SeqList::operator=(const SeqList& L){
    //自赋值检测！！！
    if(&L==this){
        return *this;
    }
    maxSize = L.maxSize;
    last = L.last;
    data = new T[maxSize];
    if(data==NULL){
            cerr<<"存储分配错误！"<<endl;
            exit(1);
    }
    for(int i=0;i<last;i++){
        data[i] = L.data[i];
    }
    return *this;
}

int SeqList::Size() const{
    return maxSize;
}
int SeqList::Length() const{
    return last+1;
}
bool SeqList::IsEmpty() const{
    if(last==-1){
        return true;
    }else{
        return false;
    }
}

bool SeqList::IsFull() const{
    if(last+1==maxSize){
        return true;
    }else{
        return false;
    }
}

int SeqList::Locate(int i) const{
    if(i>=0 && i<=last){
        return i;
    }else{
        cout<<"位置不正确！"<<endl;
        return -1;
    }
}

bool SeqList::GetData(int i, T& x) const{
    if(i>=0 && i<=last){
        x = data[i];
        return true;
    }else{
        cout<<"位置不正确！"<<endl;
        return false;
    }
}

void SeqList::SetData(int i, T& x){
    if(i>=0 && i<=last){
        data[i] = x;
        return;
    }else{
        cout<<"位置不正确！"<<endl;
        return;
    }
}

int SeqList::Search(T & x) const{
    for(int i=0;i<=last;i++){
        if(x==data[i]){
            return i;
        }
    }
    return -1;
}

bool SeqList::Insert(int i, const T& x){
    if(this->IsFull()){
        cout<<"顺序表容量不足"<<endl;
        return false;
    }else if(i>=0 && i<=last){
        for(int j=last+1;j>=i+1;j--){
            data[j] = data[j-1];
        }
        data[i] = x;
        last++;
        return true;
    }else if(i<0){
        cout<<"请输入一个正数！";
        return false;
    }else if(i>last){
        cout<<"无法在大于长度的索引中插入数据！";
        return false;
    }
    return false;
}

bool SeqList::Remove(int i, T&x){
    if(i>=0 && i<=last){
        for(int j=i;j<=last-1;j++){
            data[j] = data[j+1];
        }
        last--;
        return true;
    }else if(i<0){
        cout<<"请输入一个正数！"<<endl;
        return false;
    }else if(i>last){
        cout<<"无法删除大于长度的索引的数据"<<endl;
        return false;
    }
    return false;
}

//还没仔细检查！！
void SeqList::Sort(){
    for(int i=0;i<=last;i++){
        for(int j=0;j<last-i;j++){
            if(data[j]>data[j+1]){
                T temp;
                temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
    return;
}

void SeqList::Reverse(){
    T temp;
    for(int i=0;i<=last/2;i++){
        temp = data[i];
        data[i] = data[last-i];
        data[last-i] = temp;
    }
    return;
}

istream& operator>>(istream& in, SeqList & L){
    cout<<"请输入顺序表的最大容量："<<endl;
    int m,n;
    cin>>m;
    if(m<=0){
        cout<<"请输入一个正数！";
        return in;
    }
    L.maxSize = m;
    cout<<"请输入数据的长度："<<endl;
    cin>>n;
    if(n>m){
        cout<<"容量不足！"<<endl;
        return in;
    }else if(n<=0){
        cout<<"请输入一个正数"<<endl;
        return in;
    }
    cout<<"请输入各项数据："<<endl;
    L.last = n-1;
    for(int i=0;i<=L.last;i++){
        in>>L.data[i];
    }
    cout<<"输入完毕。"<<endl;
    return in;
}

ostream& operator<<(ostream& out, const SeqList& L){
    cout<<"顺序表的容量是："<<L.maxSize<<endl;
    cout<<"顺序表的长度是："<<L.last+1<<endl;
    cout<<"顺序表的各项数据是："<<endl;
    for(int i=0;i<=L.last;i++){
        out<<L.data[i]<<" ";
    }
    cout<<endl;
    return out;
}

T& SeqList::operator[]( int index ){
    return data[index];
}

const T& SeqList::operator[] ( int index ) const{
    return data[index];
}

void SeqList::Push_Back(const T& x){
    if(last+1==maxSize){
        cout<<"顺序表空间不足"<<endl;
        return;
    }else{
        last++;
        data[last] = x;
        return;
    }
}

void SeqList::Pop_Back(){
    if(last==-1){
        cout<<"顺序表已空！"<<endl;
    }else{
        last--;
    }
    return;
}
