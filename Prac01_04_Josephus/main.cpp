#include <iostream>
#include <string>
using namespace std;
struct Data{
    string name;
    string no;
    string gen;
    int age;
    string cla;
    string hea;
    Data(){
    }
    Data(string na,string nn,string gg,int aa,string cc,string hh){
        name = na;
        no = nn;
        gen = gg;
        age = aa;
        cla = cc;
        hea = hh;
    }
    friend ostream& operator<<(ostream& out, Data& data);
};
struct Node{
    Data data;
    Node *next;
    Node(Data& dd):data(dd){
        next = NULL;
    }
};

class CircleList{
private:
    Node *first;
public:
    CircleList();
    void Input(int n);
    void Solve(int n, int i);
};

int main(){
    int n,i;
    cin>>n>>i;
    CircleList cst;
    cst.Input(n);
    cst.Solve(n,i);
    return 0;
}

CircleList::CircleList(){
    first = NULL;
}


void CircleList::Input(int n){
    string name;
    string no;
    string gen;
    int age;
    string cla;
    string hea;
    Node *last = NULL;
    for(int i=0;i<n;i++){
        cin>>name>>no>>gen>>age>>cla>>hea;
        Data d(name,no,gen,age,cla,hea);
        Node *newNode = new Node(d);

        if(i==0){
            first = newNode;
            newNode->next = first;
            last = first;
        }else{
            newNode->next = first;
            last->next = newNode;
            last = newNode;
        }
    }
}



void CircleList::Solve(int n, int i){
    Node *pre = first;//first可以丢掉了
    for(int j=0;j<n;j++){
        if(i!=1){
            for(int k=1;k<i-1;k++){
                pre = pre->next;
            }
            Node* del = pre->next;
            pre->next = del->next;
            //最后一个貌似能行
            cout<<del->data<<endl;
            delete del;
            pre = pre->next;
        }else{//暂时先不考虑
            ;
        }
    }
}


ostream& operator<<(ostream& out, Data& data){
        out<<data.name<<" "<<data.no<<" "<<data.gen<<" "<<data.age<<" "<<data.cla<<" "<<data.hea;
        return out;
}
