#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

template <typename T>
struct LinkNode{
	T data;
	LinkNode<T> *link;
	LinkNode(LinkNode<T> *ptr = NULL){
		link = ptr;
	}
	LinkNode(const T &item, LinkNode<T> *ptr = NULL){
		data = item;
		link = ptr;
	}
};

template <typename T>
class LinkedQueue{
public:
	LinkedQueue();
	~LinkedQueue();
	bool EnQueue(const T &x);
	bool DeQueue(T &x);
	bool getFront(T &x)const;
	void makeEmpty();
	bool IsEmpty()const;
	int getSize()const;
	friend ostream& operator << (ostream &os, LinkedQueue<T> &Q){
		LinkNode<T> *p = Q.front->link;
		int i = 0;
		while (p){
			os << "#" << ++i << ": " << p->data << endl;
			p = p->link;
		}
		os << "Queue Size: " << Q.getSize() << endl;
		return os;
	}
	void output();
protected:
	LinkNode<T> *front, *rear;
};

template <typename T>
void LinkedQueue<T>::output(){
	LinkNode<T> *p = front->link; int i = 1;
	while (i <= getSize())	{
		cout << p->data << "  "<<endl;
		p = p->link;
        i++;
	}
}

int main(){
	ifstream fin("data.txt");
	assert(fin);
	LinkedQueue<int> que;
	int data;
	while (!fin.eof()){
		assert(fin >> data);
		que.EnQueue(data);
	}
	cout << "The queue in the file is:\n" << que << endl;
	que.getFront(data);
	cout << "The front in the queue is: " << data << endl;

	cout << "Delete the front in turn, the result is:" << endl;
	int len = que.getSize();
	for(int i = 0; i < len; i++){
		que.DeQueue(data);
		cout << "Delete " << data << ", then the queue is:\n";
		cout << que << endl;
	}
	return 0;
}



template <typename T>
LinkedQueue<T>::LinkedQueue(){
    front = new LinkNode<T>;
    if(front==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }
    rear = front;
}

template <typename T>
void LinkedQueue<T>::makeEmpty(){
    LinkNode<T> *del = front->link;
    while(del!=NULL){
        front->link = del->link;
        delete del;
        del = front->link;
    }
    rear = front;
    return ;
}


template <typename T>
LinkedQueue<T>::~LinkedQueue(){
    makeEmpty();
    delete front;
}


template <typename T>
bool LinkedQueue<T>::EnQueue(const T &x){
    LinkNode<T> *newNode = new LinkNode<T>(x);
    if(newNode==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }
    rear->link = newNode;
    rear = rear->link;
    return true;
}




template <typename T>
bool LinkedQueue<T>::DeQueue(T &x){
    if(front==rear){
        cout<<"队空"<<endl;
        return false;
    }
    LinkNode<T> *del = front->link;
    front->link = del->link;
    x = del->data;
    if(del==rear){
        rear = front;
    }
    delete del;
    return true;
}



template <typename T>
bool LinkedQueue<T>::getFront(T &x)const{
    if(front==rear){
        cout<<"队空"<<endl;
        return false;
    }
    x = front->link->data;
    return true;
}


template <typename T>
bool LinkedQueue<T>::IsEmpty()const{
    return (rear==front) ? true : false;
}



template <typename T>
int LinkedQueue<T>::getSize()const{
    LinkNode<T> *cur = front->link;
    int cnt = 0;
    while(cur!=NULL){
        cnt++;
        cur = cur->link;
    }
    return cnt;
}
