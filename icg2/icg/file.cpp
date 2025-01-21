#include<bits/stdc++.h>

int fun(int x, int y){
    return x+y;
}

int main(){
    int e = 0, a = 10, b = 10 ;
    int f = 20;
    int g;
    g = e*3+f/5-10;

    int arr[100];

    if(a<b) {
         g = g + arr[5];
         if(g > 20){
             g = g + 20;
         }
         else{
             g = g - 20;
         }
    }
    else {
        g = g - 10;
    }

    while(e<g){
        e = e + 1;
    }

    a = b + arr[5] + fun(a,b);

    // for(int i=0;i<10;i++){
    //     e = e + 1;
    // }
    
    e=2;
}