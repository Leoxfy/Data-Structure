#include <iostream>
using namespace std;
int MaxSubseqSum1(int *a, int N);
int MaxSubseqSum2(int *a, int N);
int MaxSubseqSum4(int *a, int N);
int data[100000];
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>data[i];
    }
    int res = MaxSubseqSum1(data,n);
    cout<<res;
    return 0;
}

int MaxSubseqSum1(int *a, int N){
    int ThisSum = 0;
    int MaxSum = 0;
    for(int i=0;i<N;i++){
        for(int j=i;j<N;j++){
            ThisSum = 0;
            for(int k=i;k<=j;k++){
                ThisSum += a[k];
            }
            if(ThisSum>MaxSum){
                MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}

int MaxSubseqSum2(int *a, int N){
    int ThisSum = 0;
    int MaxSum = 0;
    for(int i=0;i<N;i++){
        ThisSum = 0;
        for(int j=i;j<N;j++){
            ThisSum += a[j];
            if(ThisSum>MaxSum){
                MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}


int MaxSubseqSum4( int *a, int N )
{   int ThisSum, MaxSum;
    int i;
    ThisSum = MaxSum = 0;
    for( i = 0; i < N; i++ ) {
          ThisSum += a[i]; /* �����ۼ� */
          if( ThisSum > MaxSum )
                  MaxSum = ThisSum; /* ���ָ��������µ�ǰ��� */
          else if( ThisSum < 0 ) /* �����ǰ���к�Ϊ�� */
                  ThisSum = 0; /* �򲻿���ʹ����Ĳ��ֺ���������֮ */
    }
    return MaxSum;
}
