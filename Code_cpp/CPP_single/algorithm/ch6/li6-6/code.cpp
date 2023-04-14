#include <iostream>
#include <cmath>
using namespace std;

const int maxn=20;

int main(){
    int D,I;
    while(scanf("%d%d",&D,&I)){
        int k=1;
        for(int i=0;i<D-1;i++){
            if(I%2){
                I=(I+1)/2;
                k=2*k;
            }
            else {
                I/=2;
                k=2*k+1;
            }
        }
        cout<<k;
    }
    return 0;
}
