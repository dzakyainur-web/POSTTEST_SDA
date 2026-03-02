#include<iostream>
using namespace std;

void reverseArray(int *Prima, int n)
{
    int *kiri = Prima;         
    int *kanan = Prima + n - 1; 
    int temp;

    while(kiri < kanan)
    {
        temp = *kiri;
        *kiri = *kanan;
        *kanan = temp;
        kiri++;   
        kanan--;  
    }
}

int main(){
    int Prima[7] = {2,3,5,7,11,13,17};
    int *p = Prima;
    cout << "Sebelum dibalik : "<<endl;
    for(int i = 0;i < 7; i++){
        cout << *p << " | " << p << endl;
        p++;
    }
    reverseArray(Prima, 7);
    p = Prima;
    cout << "Sesudah dibalik : "<<endl;
    for(int i = 0;i < 7; i++){
        cout << *p << " | " << p <<endl;
        p++;
    }
    return 0;

}

