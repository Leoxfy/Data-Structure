#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

template <typename T>
struct StackNode{
	T data;
	StackNode<T> *link;
	StackNode(const T& d, StackNode<T> *next = NULL){
        data = d;
        link = next;
	}
	StackNode(StackNode<T> *next = NULL){
        link = next;
	}
};


template <typename T>
class LinkedStack{
private:
	StackNode<T> *top;
public:
	LinkedStack();
	~LinkedStack();
	void Push(const T &x);
	bool Pop();
	bool GetTop(T &x)const;
	int GetSize()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void MakeEmpty();
	friend ostream& operator << (ostream &os, const LinkedStack<T> &s){
        if(s.top==NULL){
            cout<<"Õ»¿Õ"<<endl;
            return os;
        }
        cout<<"Õ»ÄÚµÄÔªËØÒÀ´ÎÊÇ£º"<<endl;
        StackNode<T> *cur = s.top;
        while(cur!=NULL){
            os<<cur->data<<" ";
            cur = cur->link;
        }
        os<<endl;
        return os;

	}
};

int main()
{
    LinkedStack<int> sta;




	ifstream fin("data.txt");
	assert(fin);
	int data;
	while (!fin.eof()){
		assert(fin >> data);
		sta.Push(data);
	}
	cout << "The initial Stack in the file is:\n" << sta;
	cout << "The current size of the Stack is: " << sta.GetSize() << endl;
	sta.GetTop(data);
	cout << "The current Top of the Stack is : " << data << endl;
	sta.Pop();
	cout << "\nDo a Pop operation, then the stack is:\n" << sta << endl;
	cout << "The data popped is: " << data << endl;
	sta.GetTop(data);
	cout << "The current Top of the Stack is : " << data << endl;

	cout << "\nTest the state of the stack:\n";
	if (sta.IsEmpty())	cout << "The stack is empty now!\n";
	else if (sta.IsFull())	cout << "The stack is full now!\n";
		else	cout << "The stack is not empty and not full now!\n";
	sta.MakeEmpty();
	cout << "Now make the stack empty, then the state of the stack is:\n";
	if (sta.IsEmpty())	cout << "The stack is empty now!\n";
	else if (sta.IsFull())	cout << "The stack is full now!\n";
		else	cout << "The stack is not empty and not full now!\n";

	return 0;


}







template <typename T>
LinkedStack<T>::LinkedStack(){
    top = NULL;
}

template <typename T>
void LinkedStack<T>::MakeEmpty(){
    if(top==NULL){
        return ;
    }
    StackNode<T> *del = top;

    while(top!=NULL){
        top = del->link;
        delete del;
        del = top;
    }
    return ;
}



template <typename T>
LinkedStack<T>::~LinkedStack(){
    MakeEmpty();
}


template <typename T>
void LinkedStack<T>::Push(const T &x){
    StackNode<T> *newNode = new StackNode<T>(x);
    if(newNode==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }

    if(top==NULL){
        newNode->link = NULL;
        top = newNode;
        return ;
    }else{
        newNode->link = top;
        top = newNode;
        return ;
    }
    return ;
}



template <typename T>
bool LinkedStack<T>::Pop(){
    if(top==NULL){
        cout<<"Õ»¿Õ"<<endl;
        return false;
    }
    StackNode<T> *del = top;
    top = del->link;
    delete del;
    return true;
}


template <typename T>
bool LinkedStack<T>::GetTop(T &x)const{
    if(top==NULL){
        cout<<"Õ»¿Õ"<<endl;
        return false;
    }
    x = top->data;
    return true;
}


template <typename T>
int LinkedStack<T>::GetSize()const{
    if(top==NULL){
        return 0;
    }
    StackNode<T> *cur = top;
    int cnt = 0;
    while(cur!=NULL){
        cnt++;
        cur = cur->link;
    }
    return cnt;
}


template <typename T>
bool LinkedStack<T>::IsEmpty()const{
    return top==NULL ? true : false;
}


template <typename T>
bool LinkedStack<T>::IsFull()const{
    return false;
}
