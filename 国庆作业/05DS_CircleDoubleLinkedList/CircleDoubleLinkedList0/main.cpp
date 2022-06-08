#include <iostream>

using namespace std;

template<typename Type>
struct DoubleLinkNode
{
      Type data;
      DoubleLinkNode<Type>* lLink;
      DoubleLinkNode<Type>* rLink;
      DoubleLinkNode(DoubleLinkNode<Type>* pre=NULL,DoubleLinkNode<Type>*suc=NULL)
      {
            lLink=pre;
            rLink=suc;
      }
      DoubleLinkNode(const Type& elem, DoubleLinkNode<Type>* pre=NULL,DoubleLinkNode<Type>* suc=NULL)
      {
            data=elem;
            lLink=pre;
            rLink=suc;
      }
};

template<typename Type>
class CircleDoubleLinkedList
{
private:
      DoubleLinkNode<Type>* first;
public:
      CircleDoubleLinkedList();
      void MakeEmpty();
      ~CircleDoubleLinkedList();
      void InputRear(const Type& elem);
      void CopyList(const CircleDoubleLinkedList<Type>& lst);
      CircleDoubleLinkedList(const CircleDoubleLinkedList<Type>& lst);
      CircleDoubleLinkedList<Type>& operator=(const CircleDoubleLinkedList<Type>& lst);
      DoubleLinkNode<Type>* Locate(int loc, int sign);
      bool Insert(int loc, const Type& elem,int sign);
      bool Remove(int loc, Type& elem, int sign);
      DoubleLinkNode<Type>* Search(const Type& elem, int sign) const;
      bool GetData(int loc, Type& elem, int sign) const;
      bool SetData(int loc, const Type& elem, int sign);
      void OutPut(int sign=0);
};
int main()
{
    CircleDoubleLinkedList<int> lst;
    for(int i=1;i<=10;i++)
    {
          lst.Insert(i,i,1);
    }
    lst.OutPut(0);
    lst.OutPut(1);
    if(lst.Search(5,0))
    {
          cout<<"yes"<<endl;
    }
    else
    {
          cout<<"no"<<endl;
    }
    lst.SetData(10,100,0);
    int val;
    for(int i=10;i>0;i--)
    {
          lst.Remove(i,val,1);
          lst.OutPut(0);
    }
    return 0;
}




template<typename Type>
CircleDoubleLinkedList<Type>::CircleDoubleLinkedList(){
    first = new DoubleLinkNode<Type>;
    if(first==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }

    first->rLink = first;
    first->lLink = first;
}


template<typename Type>
void CircleDoubleLinkedList<Type>::MakeEmpty(){
    DoubleLinkNode<Type> *del = first->rLink;

    while(del!=first){
        first->rLink = del->rLink;
        delete del;
        del = first->rLink;
    }
    first->lLink = first;
    return ;
}


template<typename Type>
CircleDoubleLinkedList<Type>::~CircleDoubleLinkedList(){
    MakeEmpty();
    delete first;
}


template<typename Type>
void CircleDoubleLinkedList<Type>::InputRear(const Type& elem){
    Type temp;
    cin>>temp;
    while(temp!=elem){
        DoubleLinkNode<Type> *newNode = DoubleLinkNode<Type>(temp);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }

        DoubleLinkNode<Type> *suc = first->lLink;
        newNode->lLink = suc;
        suc->rLink = newNode;
        newNode->rLink = first;
        first->lLink = newNode;

        cin>>temp;
    }
    return ;
}



template<typename Type>
void CircleDoubleLinkedList<Type>::CopyList(const CircleDoubleLinkedList<Type>& lst){
    if(&lst==this){
        return ;
    }
    MakeEmpty();
    DoubleLinkNode<Type> *src = lst.first->rLink;

    while(src!=lst.first){
        DoubleLinkNode<Type> *newNode = new DoubleLinkNode<Type>(src->data);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }

        DoubleLinkNode<Type> *suc = first->lLink;
        newNode->lLink = suc;
        suc->rLink = newNode;
        newNode->rLink = first;
        first->lLink = newNode;

        src = src->rLink;
    }
    return ;
}




template<typename Type>
CircleDoubleLinkedList<Type>::CircleDoubleLinkedList(const CircleDoubleLinkedList<Type>& lst){
    first = new DoubleLinkNode<Type>;
    if(first==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }

    first->rLink = first;
    first->lLink = first;
    CopyList(lst);
}



template<typename Type>
CircleDoubleLinkedList<Type>& CircleDoubleLinkedList<Type>::operator=(const CircleDoubleLinkedList<Type>& lst){
    if(&lst==this){
        return *this;
    }
    CopyList(lst);
    return *this;
}



//考虑空表但是没有进入for循环的情况
template<typename Type>
DoubleLinkNode<Type>* CircleDoubleLinkedList<Type>::Locate(int loc, int sign){
    if(loc<=0 || first->rLink==first){
        return NULL;
    }
    DoubleLinkNode<Type> *cur = (sign==0) ? first->rLink : first->lLink;
    for(int j=1;j<loc;j++){
        if(cur==first){
            return NULL;
        }
        cur = (sign==0) ? cur->rLink : cur->lLink;
    }
    return cur;
}



template<typename Type>
bool CircleDoubleLinkedList<Type>::Insert(int loc, const Type& elem,int sign){
    if(loc<=0){
        return false;
    }
    DoubleLinkNode<Type> *cur = (sign==0) ? first->rLink : first->lLink;
    for(int j=1;j<loc;j++){
        if(cur==first){
            return false;
        }
        cur = (sign==0) ? cur->rLink : cur->lLink;
    }
    DoubleLinkNode<Type> *newNode = new DoubleLinkNode<Type>(elem);
    if(newNode==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }

    if(sign==0){
        DoubleLinkNode<Type> *suc = cur;
        DoubleLinkNode<Type> *pre = suc->lLink;

        newNode->rLink = suc;
        suc->lLink = newNode;
        newNode->lLink = pre;
        pre->rLink = newNode;
    }else{
        DoubleLinkNode<Type> *suc = cur;
        DoubleLinkNode<Type> *pre = suc->rLink;

        newNode->lLink = suc;
        suc->rLink = newNode;
        newNode->rLink = pre;
        pre->lLink = newNode;
    }
    return true;
}



//考虑空表但是没有进入循环的情况
template<typename Type>
bool CircleDoubleLinkedList<Type>::Remove(int loc, Type& elem, int sign){
    if(loc<=0 || first->rLink == first){
        return false;
    }
    DoubleLinkNode<Type> *del = (sign==0) ? first->rLink : first->lLink;
    for(int j=1;j<loc;j++){
        if(del==first){
            return false;
        }
        del = (sign==0) ? del->rLink : del->lLink;
    }
    if(sign==0){
        DoubleLinkNode<Type> *pre = del->lLink;
        DoubleLinkNode<Type> *suc = del->rLink;
        pre->rLink = suc;
        suc->lLink = pre;
        delete del;
    }else{
        DoubleLinkNode<Type> *pre = del->rLink;
        DoubleLinkNode<Type> *suc = del->lLink;
        pre->lLink = suc;
        suc->rLink = pre;
        delete del;
    }
    return true;
}



template<typename Type>
DoubleLinkNode<Type>* CircleDoubleLinkedList<Type>::Search(const Type& elem, int sign) const{
    DoubleLinkNode<Type> *cur = (sign==0) ? first->rLink : first->lLink;
    while(cur!=first){
        if(elem==cur->data){
            return cur;
        }
        cur = (sign==0) ? cur->rLink : cur->lLink;
    }
    return NULL;
}



template<typename Type>
bool CircleDoubleLinkedList<Type>::GetData(int loc, Type& elem, int sign) const{
    if(loc<=0 || first->rLink==first){
        return false;
    }
    DoubleLinkNode<Type> *cur = (sign==0) ? first->rLink : first->lLink;
    for(int j=1;j<loc;j++){
        if(cur==first){
            return false;
        }
        cur = (sign==0) ? cur->rLink : cur->lLink;
    }
    elem = cur->data;
    return true;
}



template<typename Type>
bool CircleDoubleLinkedList<Type>::SetData(int loc, const Type& elem, int sign){
    if(loc<=0 || first->rLink==first){
        return false;
    }
    DoubleLinkNode<Type> *cur = (sign==0) ? first->rLink : first->lLink;
    for(int j=1;j<loc;j++){
        if(cur==first){
            return false;
        }
        cur = (sign==0) ? cur->rLink : cur->lLink;
    }
    cur->data = elem;
    return true;
}


template<typename Type>
void CircleDoubleLinkedList<Type>::OutPut(int sign){
    DoubleLinkNode<Type> *cur = (sign==0) ? first->rLink : first->lLink;
    if(cur==first){
        cout<<"双向循环链表为空"<<endl;
        return ;
    }else{
        cout<<"双向循环链表的数据如下："<<endl;
    }
    while(cur!=first){
        cout<<cur->data<<" ";
        cur = (sign==0) ? cur->rLink :cur->lLink;
    }
    cout<<endl;
    return;
}
