#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
const int defaultSize=20000;


template<typename T>
class Stack;


template<typename T>
ostream& operator<< (ostream& out, const Stack<T>& s);


template<typename T>
class Stack
{
private:
      T* data;
      int maxSize;
      int top;
public:
      Stack(int sz=defaultSize);
      Stack(const Stack<T>& s);
      Stack<T>& operator=(const Stack<T>& s);
      ~Stack();
      void Push(const T &x);
      bool Pop();
      bool GetTop(T &x)const;
      bool IsEmpty()const;
      bool IsFull()const;
      int GetSize()const;
      void MakeEmpty();
      friend ostream& operator<< <T>(ostream& out, const Stack<T>& s);

};

int main()
{
    Stack<int> sta;
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

	sta.GetTop(data);
	cout << "The current Top of the Stack is : " << data << endl;

	cout << "\nTest the state of the stack:\n";
	if (sta.IsEmpty())	cout << "The stack is empty now!\n";
	else if (sta.IsFull())	cout << "The stack is full now!\n";
		else	cout << "The stack is not empty and not full now!\n";
	cout << "Now make the stack empty, then the state of the stack is:\n";
	sta.MakeEmpty();
	if (sta.IsEmpty())	cout << "The stack is empty now!\n";
	else if (sta.IsFull())	cout << "The stack is full now!\n";
		else	cout << "The stack is not empty and not full now!\n";
	return 0;
    return 0;
}






template<typename T>
Stack<T>::Stack(int sz){
    maxSize = sz;
    data = new T[maxSize];
    top = -1;
}




template<typename T>
Stack<T>::Stack(const Stack<T>& s){
    delete data;
    maxSize = s.maxSize;
    data = new T[maxSize];
    top = s.top;
    for(int i=0;i<=top;i++){
        data[i] = s.data[i];
    }
}



template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s){
    if(&s==this){
        return *this;
    }
    delete data;
    maxSize = s.maxSize;
    data = new T[maxSize];
    top = s.top;
    for(int i=0;i<=top;i++){
        data[i] = s.data[i];
    }
    return *this;
}




template<typename T>
Stack<T>::~Stack(){
    delete data;
}

template<typename T>
void Stack<T>::Push(const T &x){
    if(top==maxSize-1){
        cout<<"Õ»ÒÑÂú"<<endl;
        return ;
    }
    top++;
    data[top] = x;
    return ;
}



template<typename T>
bool Stack<T>::Pop(){
    if(top==-1){
        cout<<"Õ»ÒÑ¿Õ"<<endl;
        return false;
    }
    top--;
    return true;
}





template<typename T>
bool Stack<T>::GetTop(T &x)const{
    if(top==-1){
        cout<<"Õ»ÒÑ¿Õ"<<endl;
        return false;
    }
    x = data[top];
    return true;
}




template<typename T>
bool Stack<T>::IsEmpty()const{
    return top==-1 ? true : false;
}


template<typename T>
bool Stack<T>::IsFull()const{
    return top==(maxSize-1) ? true : false;
}


template<typename T>
int Stack<T>::GetSize()const{
    return top+1;
}


template<typename T>
void Stack<T>::MakeEmpty(){
    top = -1;
}



template<typename T>
ostream& operator<<(ostream& out, const Stack<T>& s){
    if(s.top==-1){
        cout<<"Õ»¿Õ"<<endl;
        return out;
    }
    cout<<"Õ»ÄÚÔªËØÒÀ´ÎÎª£º"<<endl;
    for(int i=0;i<=s.top;i++){
        cout<<s.data[i]<<" ";
    }
    cout<<endl;
    return out;
}

