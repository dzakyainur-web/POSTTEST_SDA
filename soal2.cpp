#include<iostream>
using namespace std;
struct Mahasiswa
{
    string Nama;
    string Nim;
    float Ipk;

};
int main() {
    Mahasiswa mahasiswa1[5];

    for(int i=0; i < 5; i++){
        cout << "Mahasiswa ke " << i+1 << endl;
        cout << "Nama : ";
        getline(cin, mahasiswa1[i].Nama);
        cout << "NIM : ";
        cin >> mahasiswa1[i].Nim;
        cout << "IPK : ";
        cin >> mahasiswa1[i].Ipk;
        cin.ignore();
    }
    float ipkTinggi = mahasiswa1[0].Ipk;
    int indexTinggi = 0;

    for(int i = 1;i < 5; i++) {
        if(mahasiswa1[i].Ipk > ipkTinggi){
            ipkTinggi = mahasiswa1[i].Ipk;
            indexTinggi = i;
        }
    }
    cout << "Mahasiswa dengan IPK tertinggi:" << endl;
    cout << "NAMA : " << mahasiswa1[indexTinggi].Nama << endl;
    cout << "NIM : " << mahasiswa1[indexTinggi].Nim << endl;
    cout << "IPK : " << mahasiswa1[indexTinggi].Ipk << endl;

    return 0;

}
