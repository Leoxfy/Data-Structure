#ifndef STATICLIST_H
#define STATICLIST_H
#include <cassert>
#include <iostream>
using namespace std;

const int defaultSize = 100;
template <typename T>
struct SLinkNode{
	T data;
	int link;
};

template <typename T>
class StaticList{
	SLinkNode<T> *elem;
	int maxSize;
	int avil;//���ý���������±�
public:
	StaticList(int sz = defaultSize);
	~StaticList();
	int Length();//���ر�
	int Search(T x);//����x
	int Locate(int i);//��λ��i��Ԫ��
	bool getData(int i, T &x);//��ȡ��i��Ԫ�ص�ֵ
	bool Append(T x);          //�ڱ�β����½��
	bool Insert(int i, T x);   //�ڵ�i��λ���ϲ���Ԫ��x
	bool Remove(int i);//ɾ����i��λ����Ԫ��
	bool IsEmpty();//�жϱ��Ƿ�Ϊ��
	void output(int type = 0);//��ָ����ʽ���
    friend istream& operator >> (istream& in, StaticList<T> &stl){
		T data;
		while (!in.eof()){//��ԭ�������ӣ����������Ա�ͬ
			in >> data;
			stl.Append(data);
		}
		return in;
	}
	friend ostream & operator<<(ostream &out, StaticList <T> &stl){
		int p = stl.elem[0].link;//elem[0]Ϊ����ͷ���
		while(p != -1){
			cout << stl.elem[p].data << endl;
			p = stl.elem[p].link;
		}
		cout << endl;
		return out;
	}
};


#endif

int main(){
	StaticList<int> list(10);
	list.Append(25);
	list.Append(92);
	list.Append(57);
	list.Append(36);
	list.Append(78);
	list.Insert(3, 11);
	list.Insert(1, 49);

	// Print the list
	list.output();
	list.output(1);

	cout << "search 36: " << list.Search(36) << endl;
	cout << "search 25: " << list.Search(25) << endl;
	cout << "search 78: " << list.Search(78) << endl;
	cout << "search 50: " << list.Search(50) << endl;
	cout << endl;

	if (list.Remove(5)){
		cout << "Remove the 5th data:\n";
		list.output();
		list.output(1);
	}

	list.Append(11);
	cout << "After Insert 11 in the rear:\n";
	list.output();
	list.output(1);
	return 0;
}






template <typename T>
StaticList<T>::StaticList(int sz){
    maxSize = sz;
    elem = new SLinkNode<T>[maxSize];

    for(int i=1;i<maxSize-1;i++){
        elem[i].link = i+1;
    }
    elem[maxSize-1].link = -1;
    elem[0].link = -1;
    avil = 1;
}



template <typename T>
StaticList<T>::~StaticList(){
    delete elem;
}

template <typename T>
int StaticList<T>::Length(){
    int cur = elem[0].link;
    int cnt = 0;

    while(cur!=-1){
        cnt++;
        cur = elem[cur].link;
    }
    return cnt;
}



//
template <typename T>
int StaticList<T>::Search(T x){
    if(elem[0].link==-1){
        return -1;
    }
    int cur = elem[0].link;
    int cnt = 1;
    while(cur!=-1){
        if(x==elem[cur].data){
            return cnt;
        }
        cur = elem[cur].link;
        cnt++;
    }
    return -1;
}


//
template <typename T>
int StaticList<T>::Locate(int i){
    if(i<=0 || elem[0].link==-1){
        return -1;
    }
    int cur = elem[0].link;
    for(int j=1;j<i;j++){
        if(cur==-1){
            return -1;
        }
        cur = elem[cur].link;
    }
    return cur;
}


//
template <typename T>
bool StaticList<T>::getData(int i, T &x){
    if(i<=0 || elem[0].link==-1){
        return false;
    }
    int cur = elem[0].link;
    for(int j=1;j<i;j++){
        if(cur==-1){
            return false;
        }
        cur = elem[cur].link;
    }
    x = elem[cur].data;
    return true;
}




//
template <typename T>
bool StaticList<T>::Append(T x){
    int cur = 0;
    while(elem[cur].link!=-1){
        cur = elem[cur].link;
    }
    int newNode = avil;
    if(newNode==-1){
        cout<<"��̬��������"<<endl;
        return false;
    }

    avil = elem[avil].link;
    elem[newNode].data = x;
    elem[newNode].link = -1;
    elem[cur].link = newNode;
    return true;
}



//
template <typename T>
bool StaticList<T>::Insert(int i, T x){
    if(i<=0){
        return false;
    }

    int cur = 0;
    for(int j=1;j<i;j++){
        if(cur==-1){
            return false;
        }
        cur = elem[cur].link;
    }
    int newNode = avil;
    if(newNode==-1){
        cout<<"��̬��������"<<endl;
        return false;
    }

    avil = elem[avil].link;

    elem[newNode].data = x;
    elem[newNode].link = elem[cur].link;
    elem[cur].link = newNode;
    return true;
}





//
template <typename T>
bool StaticList<T>::Remove(int i){
    if(i<=0 || elem[0].link==-1){
        return false;
    }
    int cur = 0;
    for(int j=1;j<i;j++){
        if(cur==-1){
            return false;
        }
        cur = elem[cur].link;
    }
    if(elem[cur].link==-1){
        return false;
    }
    int del = elem[cur].link;
    elem[cur].link = elem[del].link;

    elem[del].link = avil;
    avil = del;
    return true;
}



//
template <typename T>
bool StaticList<T>::IsEmpty(){
    return elem[0].link==-1 ? true : false;
}



//
template <typename T>
void StaticList<T>::output(int type){
    if(elem[0].link==-1){
        cout<<"��̬����Ϊ��"<<endl;
        return ;
    }
    int cur = elem[0].link;
    cout<<"��̬�������£�"<<endl;
    if(type==0){
        cout<<"����0��";
        while(cur!=-1){
            cout<<elem[cur].data<<" ";
            cur = elem[cur].link;
        }
        cout<<endl;
        return ;
    }else{
        cout<<"����1��";
        while(cur!=-1){
            cout<<elem[cur].data<<" ";
            cur = elem[cur].link;
        }
        cout<<endl;
        return ;
    }
}
