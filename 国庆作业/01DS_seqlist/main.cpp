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
    T* data;//ָ��̬�ڴ���������ָ��
    int maxSize;//��̬�ڴ�������������
    int last;//��ʶ˳��������һ��Ԫ�ص�λ��(��ӳ˳����е�Ԫ�ظ���)
    void Resize(int newSize);
public:
    SeqList(int sz=defaultSize);//���캯��
    SeqList(const SeqList& L);//�������캯��
    SeqList& operator=(const SeqList& L);//��ֵ���������

    ~SeqList();//��������

    int Size() const;//����˳��������
    int Length() const;//����˳�����Ԫ�صĸ���
    bool IsEmpty() const;//˳����Ƿ�Ϊ��
    bool IsFull() const;//˳����Ƿ�Ϊ��
    int Locate(int i) const;//����˳������Ƿ���ڵ�i��Ԫ��
    bool GetData(int i, T& x) const;//��ȡ˳����е�i��λ�õ�Ԫ��
    void SetData(int i, T& x);//��˳����е�i��λ�õ�Ԫ�ظ�ֵΪx

    int Search(T & x) const;//��˳���������x
    bool Insert(int i, const T& x) ;//��˳���ĵ�i��Ԫ�ص�λ�ò���x
    bool Remove(int i, T&x) ;//ɾ��˳����i��λ�õ�Ԫ��

    void Sort() ;//��˳�����Ԫ�ؽ�������
    void Reverse ();//����˳����е�Ԫ��

    friend istream& operator>>(istream& in, SeqList & L);//�������������
    friend ostream& operator<<(ostream& out, const SeqList& L);//������������

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
    cout<<"������Ҫ�����λ�ü����ݣ�"<<endl;
    cin>>i>>val;
    cout<<"������ϡ�"<<endl;
    sList.Insert(i,val);
    cout<<sList;
    cout<<"������Ҫɾ�����ݵ�������"<<endl;
    cin>>i;
    sList.Remove(i,val);
    cout<<"ɾ����ϡ�"<<endl;
    cout<<sList;
    cout<<"������Ҫ���������ݣ�"<<endl;
    cin>>val;
    i=sList.Search(val);
    if(i==-1){
        cout<<"Not found"<<endl;
    }
    else{
        cout<<"�����ݵ�λ���ǣ�"<<i<<endl;
    }
    cout<<"��ת���˳����ǣ�"<<endl;
    sList.Reverse();
    cout<<sList;
}


SeqList::SeqList(int sz){
    if(sz>0){
        maxSize = sz;
        last = -1;
        data = new T[maxSize];
        if(data==NULL){
            cerr<<"�洢�������"<<endl;
            exit(1);
        }
    }else{
        cout<<"���캯���Ĳ���������������"<<endl;
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
            cerr<<"�洢�������"<<endl;
            exit(1);
    }
    for(int i=0;i<last;i++){
        data[i] = L.data[i];
    }
}
void SeqList::Resize(int newSize){
    if(newSize<=0){
        cout<<"������һ��������"<<endl;
        return;
    }else if(newSize<=last+1){
        cout<<"�����С���㣡"<<endl;
        return;
    }else if(newSize!=maxSize){
        T* newarray = new T[newSize];
        if(newarray==NULL){
            cerr<<"�洢�������"<<endl;
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
    //�Ը�ֵ��⣡����
    if(&L==this){
        return *this;
    }
    maxSize = L.maxSize;
    last = L.last;
    data = new T[maxSize];
    if(data==NULL){
            cerr<<"�洢�������"<<endl;
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
        cout<<"λ�ò���ȷ��"<<endl;
        return -1;
    }
}

bool SeqList::GetData(int i, T& x) const{
    if(i>=0 && i<=last){
        x = data[i];
        return true;
    }else{
        cout<<"λ�ò���ȷ��"<<endl;
        return false;
    }
}

void SeqList::SetData(int i, T& x){
    if(i>=0 && i<=last){
        data[i] = x;
        return;
    }else{
        cout<<"λ�ò���ȷ��"<<endl;
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
        cout<<"˳�����������"<<endl;
        return false;
    }else if(i>=0 && i<=last){
        for(int j=last+1;j>=i+1;j--){
            data[j] = data[j-1];
        }
        data[i] = x;
        last++;
        return true;
    }else if(i<0){
        cout<<"������һ��������";
        return false;
    }else if(i>last){
        cout<<"�޷��ڴ��ڳ��ȵ������в������ݣ�";
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
        cout<<"������һ��������"<<endl;
        return false;
    }else if(i>last){
        cout<<"�޷�ɾ�����ڳ��ȵ�����������"<<endl;
        return false;
    }
    return false;
}

//��û��ϸ��飡��
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
    cout<<"������˳�������������"<<endl;
    int m,n;
    cin>>m;
    if(m<=0){
        cout<<"������һ��������";
        return in;
    }
    L.maxSize = m;
    cout<<"���������ݵĳ��ȣ�"<<endl;
    cin>>n;
    if(n>m){
        cout<<"�������㣡"<<endl;
        return in;
    }else if(n<=0){
        cout<<"������һ������"<<endl;
        return in;
    }
    cout<<"������������ݣ�"<<endl;
    L.last = n-1;
    for(int i=0;i<=L.last;i++){
        in>>L.data[i];
    }
    cout<<"������ϡ�"<<endl;
    return in;
}

ostream& operator<<(ostream& out, const SeqList& L){
    cout<<"˳���������ǣ�"<<L.maxSize<<endl;
    cout<<"˳���ĳ����ǣ�"<<L.last+1<<endl;
    cout<<"˳���ĸ��������ǣ�"<<endl;
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
        cout<<"˳���ռ䲻��"<<endl;
        return;
    }else{
        last++;
        data[last] = x;
        return;
    }
}

void SeqList::Pop_Back(){
    if(last==-1){
        cout<<"˳����ѿգ�"<<endl;
    }else{
        last--;
    }
    return;
}
