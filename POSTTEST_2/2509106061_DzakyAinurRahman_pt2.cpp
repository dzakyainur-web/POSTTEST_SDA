#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
using namespace std;

struct Hewan {
    int idHewan;
    string namaPemilik;
    string namaHewan;
    string jenisHewan;
    int umurHewan;
    string namaLayanan;
    double hargaLayanan;
};

#define MAX_HEWAN 100
Hewan daftarHewan[MAX_HEWAN];
int jumlahHewan = 0;

void hapusLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void enter() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void tampilkanMenu() {
    cout << "=====================================\n";
    cout << "|            MENU UTAMA             |\n";
    cout << "=====================================\n";
    cout << "|1. Tambah Data Hewan               |\n";
    cout << "|2. Lihat Semua Data                |\n";
    cout << "|3. Urutkan Data Hewan              |\n";
    cout << "|4. Cari Data Hewan                 |\n";
    cout << "|5. Keluar                          |\n";
    cout << "=====================================\n";
}

void swap(Hewan *a, Hewan *b) {
    Hewan temp = *a;
    *a = *b;
    *b = temp;
}
void TampilkanData(Hewan* arr, int n) {
    if (n == 0) {
        cout << "\n[!] Data hewan masih kosong.\n";
        return;
    }
    cout<< "\n==========================================================================================================================\n";
    cout<< "| " << left << setw(8)  << "ID" 
        << "| " << setw(18) << "Nama Pemilik" 
        << "| " << setw(18) << "Nama Hewan" 
        << "| " << setw(18) << "Jenis Hewan" 
        << "| " << setw(10) << "Umur" 
        << "| " << setw(18) << "Layanan" 
        << "| " << setw(14) << "Harga" << " |" << endl;
    cout << "==========================================================================================================================\n";
    
    for (int i = 0; i < n; i++) {
        cout<< "| " << left << setw(8)  << (arr + i)->idHewan
            << "| " << setw(18) << (arr + i)->namaPemilik
            << "| " << setw(18) << (arr + i)->namaHewan
            << "| " << setw(18) << (arr + i)->jenisHewan
            << "| " << setw(10) << (arr + i)->umurHewan
            << "| " << setw(18) << (arr + i)->namaLayanan
            << "| " << setw(14) << (arr + i)->hargaLayanan << " |" << endl;
    }
    cout << "==========================================================================================================================\n";
}

void sortID(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->idHewan > (arr + j + 1)->idHewan) {
                swap((arr + j), (arr + j + 1));
            }
        }
    }
}

int CariID(Hewan* arr, int n, int target) {
    int fib2 = 0;
    int fib1 = 1;
    int fib = fib1 + fib2;

    while(fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }
    int offset = -1;
    int iterasi = 1;

    while(fib > 1) {
        int i = min(offset + fib2, n - 1);
        cout << "iterasi ke-" << iterasi++ << ": Mengecek indeks " << i << " dengan ID Hewan " << (arr + i)->idHewan << endl;
        if((arr + i)->idHewan < target) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if((arr + i)->idHewan > target) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else return i;   
    }
    if (fib1 && (arr + offset + 1)->idHewan == target) return offset + 1;
    return -1;
}

void UrutNama(Hewan* arr, int n){
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if((arr + j)->namaHewan > (arr + j + 1)->namaHewan) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

void UrutHarga(Hewan* arr, int n) {
    for(int i = 0; i < n-1; i++) {
        int minIndex = i;
        for(int j = i+1; j < n; j++) {
            if((arr + j)->hargaLayanan < (arr + minIndex)->hargaLayanan) {
                minIndex = j;
            }
        }
        swap(arr + i, arr + minIndex);
    }
}

void tambahHewan(int &n) {
    if (n >= MAX_HEWAN) {
        cout << "Data hewan sudah penuh!" << endl;
        return;
    }
    cout << "Masukkan ID Hewan: ";
    cin >> daftarHewan[n].idHewan;
    cin.ignore();
    cout << "Masukkan Nama Pemilik: ";
    getline(cin, daftarHewan[n].namaPemilik);
    cout << "Masukkan Nama Hewan: ";
    getline(cin, daftarHewan[n].namaHewan);
    cout << "Masukkan Jenis Hewan: ";
    getline(cin, daftarHewan[n].jenisHewan);
    cout << "Masukkan Umur Hewan: ";
    cin >> daftarHewan[n].umurHewan;
    cin.ignore();
    cout << "Masukkan Nama Layanan: ";
    getline(cin, daftarHewan[n].namaLayanan);
    cout << "Masukkan Harga Layanan: ";
    cin >> daftarHewan[n].hargaLayanan;
    n++;
    cout << "Data hewan berhasil ditambahkan!" << endl; 
}

int CariNama(Hewan* arr, int n, string target) {
    for(int i = 0; i < n; i++) {
        cout << "Mengecek indeks " << i << " dengan Nama Hewan: " << (arr + i)->namaHewan << endl;
        if((arr + i)->namaHewan == target) return i; 
    }
    return -1;
}
int main() {
    int pilihan, subPilihan;
    string cariNama;
    int cariID;

    do {
        tampilkanMenu(); 
        cout << "Pilihan: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                hapusLayar();
                tambahHewan(jumlahHewan); 
                enter();
                break;
            case 2:
                hapusLayar();
                TampilkanData(daftarHewan, jumlahHewan); 
                enter();
                break;
            case 3:
                hapusLayar();
                cout << "1. Urut Nama" << endl;
                cout << "2. Urut Harga" << endl;
                cout << "Pilih: ";
                cin >> subPilihan;
                if(subPilihan == 1) UrutNama(daftarHewan, jumlahHewan);
                else UrutHarga(daftarHewan, jumlahHewan);
                cout << "Data berhasil diurutkan!\n";
                enter();
                break;
            case 4:
                hapusLayar();
                cout << "1. Cari Nama" << endl;
                cout << "2. Cari ID" << endl;
                cout << "Pilih: ";
                cin >> subPilihan;
                if(subPilihan == 1) {
                    cout << "Nama Hewan: "; cin.ignore(); getline(cin, cariNama);
                    int hasil = CariNama(daftarHewan, jumlahHewan, cariNama);
                    if(hasil != -1) cout << "Ditemukan di indeks " << hasil << endl;
                    else cout << "Data Tidak Ada.\n";
                } else {
                    sortID(daftarHewan, jumlahHewan); 
                    cout << "ID Hewan: "; cin >> cariID;
                    int hasil = CariID(daftarHewan, jumlahHewan, cariID);
                    if(hasil != -1) cout << "Ditemukan di indeks " << hasil << endl;
                    else cout << "Data Tidak Ada.\n";
                }
                enter();
                break;
            case 5:
                cout << "Program selesai. Terima kasih!\n";
                break;
        }
    } while(pilihan != 5);
    return 0;
}