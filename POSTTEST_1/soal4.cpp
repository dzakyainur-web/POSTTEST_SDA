#include<iostream>
using namespace std;

void tukar(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main(){
    int a,b;
        cout << "Masukkan nilai pertama : ";
    cin >> a;

    cout << "Masukkan nilai kedua: ";
    cin >> b;

    cout << "\nSebelum ditukar:" << endl;
    cout << "pertama = " << a << endl;
    cout << "kedua = " << b << endl;

    tukar(&a, &b); 

    cout << "\nSesudah ditukar:" << endl;
    cout << "pertama = " << a << endl;
    cout << "kedua = " << b << endl;

    return 0;

} 