#include <iostream>
using namespace std;

void calSquare(int* x, int*y){
    *x = *x * *x;
    *y = *y * *y;
}


int main(){
    int a=10;
    int *p;
    char c;
    char *po;
    double d;
    double *p1;
    double m = 100.1, n;
    double *k;
    k = &m;

    n=*k;
    //cout << n;

    a=10;
    p = &a;
    printf("%d\n",p); // outputs address of a
    printf("%d\n",*p); // outputs a
    printf("%d\n", &a); //outputs address of a
    //*p = 12; // value at the address of a changes to 12
    //int x = 2;
    //int y =3;
    //calSquare(&x, &y);
    //cout << x << " " << y;

}