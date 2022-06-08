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
          ThisSum += a[i]; /* 向右累加 */
          if( ThisSum > MaxSum )
                  MaxSum = ThisSum; /* 发现更大和则更新当前结果 */
          else if( ThisSum < 0 ) /* 如果当前子列和为负 */
                  ThisSum = 0; /* 则不可能使后面的部分和增大，抛弃之 */
    }
    return MaxSum;
}
