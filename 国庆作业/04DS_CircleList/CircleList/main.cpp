#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

enum InsMod {INF, INR};//头插还是尾插

template <typename T>
class CircLinkNode{
public:
	T data;
	CircLinkNode<T> *link;
	CircLinkNode(CircLinkNode<T> *ptr = NULL){//建立空结点
		link = ptr;
	}
	CircLinkNode(const T &item, CircLinkNode<T> *ptr = NULL){//建立非空结点
		data = item;
		link = ptr;
	}
};

template <typename T>
class CircList{
public:
	CircList();
	CircList(CircList<T> &L);//复制一个环链表
	~CircList();
	void makeEmpty();
	int Length()const;
	CircLinkNode<T> *Search(T x);
	CircLinkNode<T> *Locate(int i);
	bool getData(int i,T&x)const;
	void setData(int i, T &x);
	bool Insert(int i, T &x);
	bool Remove(int i, T &x);
	bool IsEmpty()const;
	bool IsFull()const;
	void Sort();
	void Inverse();//不要返回
	void input(T endTag, InsMod im = INR);
	void output();
	CircList<T> &operator = (CircList<T> &L);
	friend ostream& operator << (ostream &out, CircList<T> &L){
		CircLinkNode<T> *current = L.first->link;
		while (current != L.first){
			out << current->data <<'\t';
			current = current->link;
		}
		out<<endl;
		return out;
	}
	friend istream& operator >> (istream &in, CircList<T> &L){//重新输入数据，向后生成
		T val;
		L.makeEmpty();//先清空
		while (!in.eof()){
			in >> val;
			L.last->link = new CircLinkNode<T>(val);
			assert(L.last->link);
			L.last = L.last->link;
		}
		L.last->link = L.first;
		in.clear();//当以ctrl_Z结束，流关闭，必须重新打开
		return in;
	}
protected:
	CircLinkNode<T> *first, *last;
	void inputFront(T endTag);
	void inputRear(T endTag);
};


int main(){
	CircList<int> list;
	ifstream fin("list.txt");
	assert(fin);
	fin >> list;
	cout << "The initial list in the file is:\n" << list << endl;
	list.Inverse();
	cout << "Inverse the list, then the list is:\n" << list << endl;

	cout << "========================================\n";
	int i, elem;
	cout << "Test the Insert, Remove and Search function:\n";
	cout << "Each test will terminate by an invaid input.";
	cout << "\n----------------------------------------\n";

	cout << "1. Test the Insert(int i, T &elem):\n";
	while (1){
		cout << "Input the index i and data elem to insert: ";
		cin >> i >> elem;
		if (!cin){//流不正常

			cin.clear();//恢复正常
			cin.ignore(100,'\n');
			break;
		}
		if (i < 0)	break;
		if (list.Insert(i, elem)) cout << "Insert successful!\n";
		else	cout << "Insert failed!\n";
	}
	cout << "\nAfter inserted\n" << list << endl;

	cout << "----------------------------------------\n";
	cout << "2. Test the Remove(int i, T &elem):\n";
	while (1){
		cout << "Input the index i in which you want to remove: ";
		cin >> i;
		if (!cin){
			cin.clear();
			cin.ignore(100,'\n');
			break;
		}
		if (i < 0)	break;
		if (list.Remove(i, elem))	cout << "The element " << elem << " has been removed!\n";
		else	cout << "Remove failed!\n";
	}
	cout << "\nAfter removed\n" << list << endl;

	cout << "----------------------------------------\n";
	cout << "3. Test the Search(T &elem):\n";
	while (1){
		cout << "Input the element you want to search: ";
		cin >> elem;
		if (!cin){
			cin.clear();
			cin.ignore(100,'\n');
			break;
		}
		if (elem < 0)	break;
		CircLinkNode<int> *p = list.Search(elem);
		if (p)	cout << "The element " << elem << " is in the list.\n";
		else cout << "The element is not exist!\n";
	}
	cout << "\n----------------------------------------\n";
	cout << "End test!" << endl;

	return 0;
}



template<typename T>
CircList<T>::CircList(){
    first = new CircLinkNode<T>;
    if(first==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }
    last = first;
    last->link = first;
}




template<typename T>
void CircList<T>::makeEmpty(){
    CircLinkNode<T> *del = first->link;
    while(del!=first){
        first->link = del->link;
        delete del;
        del = first->link;
    }
    last = first;
    return;
}



template<typename T>
CircList<T>::~CircList(){
    makeEmpty();
    delete first;
}


template<typename T>
CircList<T>::CircList(CircList<T> &L){
    first = new CircLinkNode<T>;
    if(first==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }

    last = first;
    last->link = first;

    CircLinkNode<T> *src = L.first->link;

    while(src!=L.first){
        CircLinkNode<T> *newNode = new CircLinkNode<T>(src->data);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }

        newNode->link = first;
        last->link = newNode;
        last = newNode;

        src = src->link;
    }

}

template<typename T>
int CircList<T>::Length()const{
    CircLinkNode<T> *cur = first->link;
    int cnt = 0;
    while(cur!=first){
        cnt++;
        cur = cur->link;
    }
    return cnt;
}

template<typename T>
CircLinkNode<T>* CircList<T>::Search(T x){
    CircLinkNode<T> *cur = first->link;
    while(cur!=first){
        if(x==cur->data){
            return cur;
        }
        cur = cur->link;
    }
    return NULL;
}



template<typename T>
CircLinkNode<T>* CircList<T>::Locate(int i){
    if(i<=0 || first==last){
        return NULL;
    }
    CircLinkNode<T> *cur = first->link;
    for(int j=1;j<i;j++){
        if(cur==first){
            return NULL;
        }
        cur = cur->link;
    }
    return cur;
}



template<typename T>
bool CircList<T>::getData(int i,T&x)const{
    if(i<=0 || first==last){
        return false;
    }
    CircLinkNode<T> *cur = first->link;
    for(int j=1;j<i;j++){
        if(cur==first){
            return false;
        }
        cur = cur->link;
    }
    x = cur->data;
    return true;
}



template<typename T>
void CircList<T>::setData(int i, T &x){
    if(i<=0 || first==last){
        return ;
    }
    CircLinkNode<T> *cur = first->link;
    for(int j=1;j<i;j++){
        if(cur==first){
            return ;
        }
        cur = cur->link;
    }
    cur->data = x;
    return ;
}




template<typename T>
bool CircList<T>::Insert(int i, T &x){
    if(i<=0){
        return false;
    }
    CircLinkNode<T> *cur = first;
    int flag = 0;
    for(int j=1;j<i;j++){

        //if(cur==first){
        //循环链表中有问题，单链表没问题
        if(cur==first && flag==1){
            return false;
        }
        flag = 1;
        cur = cur->link;
    }
    CircLinkNode<T> *newNode = new CircLinkNode<T>(x);
    if(newNode==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }

    newNode->link = cur->link;
    cur->link = newNode;

    if(cur==last){
        last = cur->link;
    }
    return true;
}

template<typename T>
bool CircList<T>::Remove(int i, T &x){
    if(i<=0 || first==last){
        return false;
    }
    CircLinkNode<T> *cur = first;
    int flag = 0;
    for(int j=1;j<i;j++){
        //if(cur==first){
        //循环链表中有问题，单链表没问题
        if(cur==first && flag==1){
            return false;
        }
        flag = 1;
        cur = cur->link;
    }
    if(cur->link==first){
        return false;
    }
    CircLinkNode<T> *del = cur->link;
    if(del==last){
        last = cur;
    }

    x = del->data;
    cur->link = del->link;
    delete del;

    return true;
}


template<typename T>
bool CircList<T>::IsEmpty()const{
    return last==first ? true:false;
}


template<typename T>
bool CircList<T>::IsFull()const{
    return false;
}
template<typename T>
void CircList<T>::input(T endTag, InsMod im){
    T temp;
    cin>>temp;
    while(temp!=endTag){
        CircLinkNode<T> *newNode = CircLinkNode<T>(temp);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }

        if(im==INF){
            newNode->link = first->link;
            first->link = newNode;
            if(last==first){
                last = newNode;
            }
        }else{
            newNode->link = first;
            last->link = newNode;
            last = newNode;
        }
        cin>>temp;
    }
    return ;
}


template<typename T>
void CircList<T>::output(){
    CircLinkNode<T> *cur = first->link;
    if(cur==first){
        cout<<"循环链表为空"<<endl;
        return ;
    }
    cout<<"循环链表内的元素依次为："<<endl;
    while(cur!=first){
        cout<<cur->data<<" ";
        cur = cur->link;
    }
    cout<<endl;
    return ;
}





template<typename T>
CircList<T>& CircList<T>::operator=(CircList<T> &L){
    if(this==&L){
        return *this;
    }
    makeEmpty();
    CircLinkNode<T> *src = L.first->link;

    while(src!=L.first){
        CircLinkNode<T> *newNode = new CircLinkNode<T>(src->data);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }

        newNode->link = first;
        last->link = newNode;
        last = newNode;
    }

    return *this;
}


template<typename T>
void CircList<T>::inputFront(T endTag){
    T temp;
    cin>>temp;
    while(temp!=endTag){
        CircLinkNode<T> *newNode = CircLinkNode<T>(temp);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }


        newNode->link = first->link;
        first->link = newNode;
        if(last==first){
            last = newNode;
        }
        cin>>temp;
    }
    return;
}




template<typename T>
void CircList<T>::inputRear(T endTag){
    T temp;
    cin>>temp;
    while(temp!=endTag){
        CircLinkNode<T> *newNode = CircLinkNode<T>(temp);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }
        newNode->link = first;
        last->link = newNode;
        last = newNode;
        cin>>temp;
    }
    return ;

}

template<typename T>
void CircList<T>::Sort(){
    int len = Length();
    if(len>=2){
        for(int i=1;i<len;i++){
            CircLinkNode<T> *pre = first->link;
            CircLinkNode<T> *cur = pre->link;
            while(cur!=first){
                if(cur->data < pre->data){
                    T t;
                    t = cur->data;
                    cur->data = pre->data;
                    pre->data = t;
                }
                pre = cur;
                cur = cur->link;
            }
        }
    }
    return ;
}




template<typename T>
void CircList<T>::Inverse(){
    int len = Length();
    if(len<=1){
        return ;
    }
    CircLinkNode<T> *pre = first;
    CircLinkNode<T> *cur = pre->link;
    CircLinkNode<T> *suc = cur->link;
    while(pre!=suc){
        cur->link = pre;
        pre = cur;
        cur = suc;
        suc = suc->link;
    }
    last = cur;
    return ;
}
