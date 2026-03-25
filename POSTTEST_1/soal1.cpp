#include <iostream>
using namespace std;

int A[8] = {1,1,2,3,5,8,13,21};
int FindMin(int A[], int n, int &indexMin) {
    int minim = A[0];
    indexMin = 0;
    for (int i = 1; i < n; i++){
        if (A[i] < minim){
            minim = A[i];
            indexMin = i;
        }
    }
    return minim;
}

int main() {
    int indexMin;
    int minim = FindMin(A, 8, indexMin);
    cout << "Nilai minimum: " << minim << endl;
    cout << "Index minimum: " << indexMin << endl;
    return 0;
}

/*
Hasil analisis kompleksitas algoritma FindMin:
Hitung Tmin dan Tmax secara manual    Tmin   Tmax
procedure FindMin                  C1   1      1
min ← A[0]                         C2   1      1
for i ← 1 to n - 1 do              C3   n      n
if A[i] < min then                 C4  n-1    n-1
min ← A[i]                         C5   0     n-1
end if                             C6  n-1    n-1 
end for                            C7   n      n
return min                         C8   1      1
end procedure                      C9   1      1

Best Case : Terjadi ketika elemen pertama sudah merupakan nilai minimum,
sehingga kondisi A[i] < min selalu false dan tidak pernah
masuk ke dalam perintah pembaruan nilai minimum.


Tmin= C1 + C2 + C3n + C4(n-1) + 0 + C6(n-1) + C7n + C8 + C9
    = C1 + C2 + C3n + C4n - C4 + C6n - C6 + C7n + C8 + C9  
    =(C3n + C4n + C6n + C7n) + (C1 + C2 - C4 - C6 + C8 + C9)
Tmin(n) = an + b
Big-O = O(n)

Wrost Case : Terjdi ketika setiap elemen berikutnya lebih kecil dari sebelumnya
(sehingga kondisi A[i] < min selalu true), sehingga C5 = n-1

Tmax= C1 + C2 + C3n + C4(n-1) + C5(n-1) + C6(n-1) + C7n + C8 + C9
    = C1 + C2 + C3n + C4n - C4 + C5n - C5 + C6n - C6 + C7n + C8 + C9  
    =(C3n + C4n + C5n + C6n + C7n) + (C1 + C2 - C4 - C5 - C6 + C8 + C9)
Tmax(n) = cn + d
Big-O = O(n)

Best Case  : O(n)
Worst Case : O(n)
*/