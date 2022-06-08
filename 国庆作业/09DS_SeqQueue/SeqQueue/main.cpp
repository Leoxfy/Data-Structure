#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
//循环队列
template <typename T>
class SeqQueue{
public:
	SeqQueue(int sz = 50);
	~SeqQueue(){
		delete[] elements;
	}
	bool EnQueue(const T &x);
	bool DeQueue(T &x);
	bool getFront(T &x)const;
	void makeEmpty();
	bool IsEmpty()const;
	bool IsFull()const;
	int getSize()const;
	friend ostream& operator<<(ostream & os,SeqQueue<T> &Q){
		os << "front = " << Q.front << ", rear = " << Q.rear << endl;
		for (int i = Q.front; i != Q.rear; i = (i+1) % Q.maxSize){
			os << "#" << i <<": " << Q.elements[i] << endl;
		}
		os << "Queue Size: " << Q.getSize() << endl;
		return os;
	}
protected:
	int rear, front;
	T *elements;
	int maxSize;
};


int main(){
	ifstream fin("data.txt");
	assert(fin);
	SeqQueue<int> que;
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
SeqQueue<T>::SeqQueue(int sz){
    maxSize = sz;
    elements = new T[maxSize];
    if(elements==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }
    front = 0;
    rear = 0;
}



template <typename T>
bool SeqQueue<T>::EnQueue(const T &x){
    if( (rear+1)%maxSize ==front ){
        cout<<"队满"<<endl;
        return false;
    }
    elements[rear] = x;
    rear = (rear+1)%maxSize;
    return true;
}



template <typename T>
bool SeqQueue<T>::DeQueue(T &x){
    if(front==rear){
        cout<<"队空"<<endl;
        return false;
    }
    x = elements[front];
    front = (front+1)%maxSize;
    return true;
}



template <typename T>
bool SeqQueue<T>::getFront(T &x)const{
    if(front==rear){
        cout<<"队空"<<endl;
        return false;
    }
    x = elements[front];
    return true;
}



template <typename T>
void SeqQueue<T>::makeEmpty(){
    front = 0;
    rear = 0;
}



template <typename T>
bool SeqQueue<T>::IsEmpty()const{
    return front==rear ? true : false;
}



template <typename T>
bool SeqQueue<T>::IsFull()const{
    return (rear+1)%maxSize==front ? true : false;
}



template <typename T>
int SeqQueue<T>::getSize()const{
    if(rear>=front){
        return rear - front;
    }else{
        return maxSize - (front - rear);
    }
}
