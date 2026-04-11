#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

struct Kereta {
    int nomorKereta;
    string namaPenumpang; 
    string namaKereta;
    string asal;
    string tujuan;
    int hargaTiket;
};

#define MAX_KERETA 100
Kereta daftarKereta[MAX_KERETA]; 
int jumlahKereta = 0;

int queue[MAX_KERETA];
int depan = -1, rear = -1;

int stack[MAX_KERETA];
int atas = -1;

int redoStack[MAX_KERETA];
int redoAtas = -1;

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

void swapData(Kereta *a, Kereta *b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void TampilkanData(Kereta* arr, int n) {
    if (n == 0) {
        cout << "\nData masih kosong.\n";
        return;
    }
    cout<< "\n===================================================================================================================\n";
    cout<< "| " << left << setw(10) << "No KA" 
        << "| " << setw(18) << "Nama Penumpang" 
        << "| " << setw(18) << "Nama Kereta" 
        << "| " << setw(15) << "Asal" 
        << "| " << setw(15) << "Tujuan" 
        << "| " << setw(15) << "Harga" << " |" << endl;
    cout << "===================================================================================================================\n";
    
    for (int i = 0; i < n; i++) {
        cout<< "| " << left << setw(10) << (arr + i)->nomorKereta
            << "| " << setw(18) << (arr + i)->namaPenumpang
            << "| " << setw(18) << (arr + i)->namaKereta
            << "| " << setw(15) << (arr + i)->asal
            << "| " << setw(15) << (arr + i)->tujuan
            << "| Rp" << setw(13) << (arr + i)->hargaTiket << " |" << endl;
    }
    cout << "===================================================================================================================\n";
}

void tambahKereta(int &n) { 
    if (n >= MAX_KERETA) {
        cout << "Data sudah penuh!" << endl;
        return;
    }
    cout << "Masukkan Nomor KA      : ";
    cin >> daftarKereta[n].nomorKereta;
    cin.ignore();
    cout << "Masukkan Nama Penumpang: ";
    getline(cin, daftarKereta[n].namaPenumpang);
    cout << "Masukkan Nama Kereta   : ";
    getline(cin, daftarKereta[n].namaKereta);
    cout << "Masukkan Kota Asal     : ";
    getline(cin, daftarKereta[n].asal);
    cout << "Masukkan Kota Tujuan   : ";
    getline(cin, daftarKereta[n].tujuan);
    cout << "Masukkan Harga Tiket   : ";
    cin >> daftarKereta[n].hargaTiket;
    n++;
    cout << "Data pesanan tiket berhasil ditambahkan!" << endl; 
}

void cariRute(Kereta* arr, int n, string asal, string tujuan) {
    bool ketemu = false;
    for (int i = 0; i < n; i++) {
        cout << "Iterasi ke-" << i + 1 << ": Mengecek Rute " << (arr + i)->asal << " - " << (arr + i)->tujuan << endl;
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "\nRute ditemukan pada indeks ke-" << i << endl;
            if (i > 0) swapData((arr + i), (arr + 0)); 
            ketemu = true;
            break;
        }
    }
    if (!ketemu) cout << "\nRute tidak ditemukan.\n";
}

int jumpSearchNo(Kereta* arr, int n, int target) {
    if (n == 0) return -1;
    int step = sqrt(n);
    int prev = 0;
    int iterasi = 1;

    cout << "\n=== Proses Jump Search ===" << endl;
    while ((arr + min(step, n) - 1)->nomorKereta < target) {
        cout << "Iterasi " << iterasi++ << ": Lompat ke indeks " << min(step, n) - 1 << " (No KA: " << (arr + min(step, n)-1)->nomorKereta << ")" << endl;
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

    while ((arr + prev)->nomorKereta < target) {
        cout << "Iterasi " << iterasi++ << ": Linear search di indeks " << prev << " (No KA: " << (arr + prev)->nomorKereta << ")" << endl;
        prev++;
        if (prev == min(step, n)) return -1;
    }

    if ((arr + prev)->nomorKereta == target) {
        cout << "Iterasi " << iterasi << ": Ditemukan pada indeks " << prev << endl;
        if (prev > 0) swapData((arr + prev), (arr + 0));
        return 0;
    }
    return -1;
}

void merge(Kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    Kereta *L = new Kereta[n1], *R = new Kereta[n2];
    for (int i = 0; i < n1; i++) *(L + i) = *(arr + l + i);
    for (int j = 0; j < n2; j++) *(R + j) = *(arr + m + 1 + j);
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if ((L + i)->namaKereta <= (R + j)->namaKereta) *(arr + k++) = *(L + i++);
        else *(arr + k++) = *(R + j++);
    }
    while (i < n1) *(arr + k++) = *(L + i++);
    while (j < n2) *(arr + k++) = *(R + j++);
    delete[] L; delete[] R;
}

void mergeSortNama(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortNama(arr, l, m);
        mergeSortNama(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void sortHarga(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int indexmin = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->hargaTiket < (arr + indexmin)->hargaTiket) indexmin = j;
        }
        swapData((arr + indexmin), (arr + i));
    }
}

void sortNomorKA(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->nomorKereta > (arr + j + 1)->nomorKereta) swapData((arr + j), (arr + j + 1));
        }
    }
}

int CariNomorKA(Kereta* arr, int n, int target) {
    for(int i = 0; i < n; i++) {
        if((arr + i)->nomorKereta == target) return i; 
    }
    return -1;
}


bool isFullQueue() {
    return rear == MAX_KERETA - 1; 
}
bool isEmptyQueue() { 
    return depan == -1 || depan > rear; 
}

void enqueue() {
    if(isFullQueue()) {
        cout << "[Underflow/Overflow] Antrian penuh! Tidak bisa memesan tiket lagi." << endl;
        return;
    }
    int noCari;
    cout << "Masukkan Nomor KA untuk antrian beli tiket: ";
    cin >> noCari;
    int index = CariNomorKA(daftarKereta, jumlahKereta, noCari);
    if(index == -1) {
        cout << "Nomor KA tidak ditemukan! Gagal masuk antrian." << endl;
        return;
    }
    if (depan == -1) depan = 0;
    rear++;
    queue[rear] = noCari;
    cout << "Penumpang " << (daftarKereta + index)->namaPenumpang << " (KA " << noCari << ") masuk ke antrian." << endl;
}

int dequeue(){
    if(isEmptyQueue()) {
        cout << "Antrian kosong! Tidak ada tiket yang diproses." << endl;
        return -1;
    }
    int noPanggil = queue[depan];
    depan++;
    if (isEmptyQueue()) depan = rear = -1; 
    return noPanggil;
}

void push(int no) {
    if(atas >= MAX_KERETA - 1) {
        cout << "Riwayat penuh!" << endl;
    } else {
        atas++;
        stack[atas] = no;
        redoAtas = -1; 
        cout << "-> Transaksi KA " << no << " disimpan ke riwayat." << endl;
    }
}

void undoRiwayat(){
    if (atas < 0) {
        cout << "Riwayat kosong! Tidak ada transaksi yang bisa di-Undo." << endl;
    } else {
        int noBatal = stack[atas];
        atas--; 
        redoAtas++;
        redoStack[redoAtas] = noBatal;
        cout << "Riwayat transaksi KA " << noBatal << " berhasil di-UNDO." << endl;
    }
}

void redoRiwayat() {
    if (redoAtas < 0) {
        cout << "Tidak ada transaksi yang bisa di-Redo (Kembalikan)!" << endl;
    } else {
        int noKembali = redoStack[redoAtas];
        redoAtas--; 
        atas++;
        stack[atas] = noKembali; 
        cout << "Riwayat transaksi KA " << noKembali << " berhasil di-REDO (Dikembalikan)." << endl;
    }
}

int peek(){
    if (atas < 0) return -1; 
    return stack[atas];
}

void tampilAntrian(){
    if(isEmptyQueue()) {
        cout << "Antrian kosong!" << endl;
        return;
    }
    cout << "=== Antrean Pembelian Tiket ===" << endl;
    int* ptr = queue + depan;
    for(int i = depan; i <= rear; i++) {
        int index = CariNomorKA(daftarKereta, jumlahKereta, *ptr);
        if (index != -1) {
            cout << "No KA: " << *ptr << " | Penumpang: " << (daftarKereta + index)->namaPenumpang 
                << " (" << (daftarKereta + index)->asal << " - " << (daftarKereta + index)->tujuan << ")" << endl;
        }
        ptr++;
    }
    cout << "===============================" << endl;
}

void tampilRiwayat() {
    if (atas < 0) {
        cout << "Riwayat kosong!" << endl;
        return;
    }
    cout << "=== Riwayat Transaksi Berhasil ===" << endl;
    int* ptr = stack + atas;
    for(int i = atas; i >= 0; i--) {
        int index = CariNomorKA(daftarKereta, jumlahKereta, *ptr);
        if (index != -1) {
            cout<< "No KA: " << *ptr << " | Penumpang: " << (daftarKereta + index)->namaPenumpang 
                << " (" << (daftarKereta + index)->asal << " - " << (daftarKereta + index)->tujuan << ")" << endl;
        }
        ptr--;
    }
    cout << "==================================" << endl;
}

void tampilkanMenu() {
    cout << "===============================================\n";
    cout << "|         SISTEM INFORMASI KERETA API         |\n";
    cout << "===============================================\n";
    cout << "| 1. Tambah Data Penumpang & Tiket            |\n";
    cout << "| 2. Lihat Semua Data                         |\n";
    cout << "| 3. Urutkan Data Kereta                      |\n";
    cout << "| 4. Cari Data Kereta                         |\n";
    cout << "| 5. Masukkan ke Antrian Beli Tiket           |\n";
    cout << "| 6. Proses Tiket dari Antrian                |\n";
    cout << "| 7. Lihat Antrian Tiket                      |\n";
    cout << "| 8. Undo (Batalkan Riwayat Terakhir)         |\n";
    cout << "| 9. Redo (Kembalikan Riwayat Batal)          |\n";
    cout << "| 10. Lihat Antrian Depan & Riwayat Terakhir  |\n";
    cout << "| 11. Keluar                                  |\n";
    cout << "===============================================\n";
}

int main() {
    int pilihan, subPilihan;
    string Asal, Tujuan;
    int No;

    do {
        tampilkanMenu(); 
        cout << "Pilihan: "; cin >> pilihan;
        switch(pilihan) {
            case 1: 
                hapusLayar();
                tambahKereta(jumlahKereta); 
                enter(); 
                break;
            case 2: 
                hapusLayar(); 
                TampilkanData(daftarKereta, jumlahKereta); 
                enter();
                break;
            case 3:
                hapusLayar();
                cout << "1. Urut Nama Kereta" << endl;
                cout << "2. Urut Harga Tiket" << endl;
                cout << "Pilih: ";
                cin >> subPilihan;
                if(subPilihan == 1) { mergeSortNama(daftarKereta, 0, jumlahKereta - 1); cout << "Diurutkan!\n"; }
                else if (subPilihan == 2) { sortHarga(daftarKereta, jumlahKereta); cout << "Diurutkan!\n"; }
                enter(); break;
            case 4:
                hapusLayar();
                cout << "1. Cari Rute" << endl;
                cout << "2. Cari No KA " << endl;
                cout << "Pilih: ";
                cin >> subPilihan;
                if(subPilihan == 1) {
                    cout << "Asal: "; 
                    cin.ignore(); 
                    getline(cin, Asal);
                    cout << "Tujuan: "; 
                    getline(cin, Tujuan);
                    cariRute(daftarKereta, jumlahKereta, Asal, Tujuan);
                } else if (subPilihan == 2) {
                    sortNomorKA(daftarKereta, jumlahKereta);
                    cout << "Nomor KA: ";
                    cin >> No;
                    int hasil = jumpSearchNo(daftarKereta, jumlahKereta, No);
                    if(hasil != -1) cout << "Proses Selesai.\n";
                        else cout << "Data Tidak Ada.\n";
                }
                enter(); 
                break;
            case 5: 
                hapusLayar(); 
                enqueue(); 
                enter(); 
                break;
            case 6:
                hapusLayar();
                {
                    int noProses = dequeue();
                    if (noProses != -1) { 
                        int index = CariNomorKA(daftarKereta, jumlahKereta, noProses);
                        cout << "=== Memproses Pemesanan Tiket ===\n";
                        if (index != -1) {
                            cout << "Nama Penumpang: " << (daftarKereta + index)->namaPenumpang << endl;
                            cout << "Rute Kereta   : " << (daftarKereta + index)->asal << " -> " << (daftarKereta + index)->tujuan << endl;
                            cout << "Kereta        : " << (daftarKereta + index)->namaKereta << endl;
                        }
                        push(noProses);
                    }
                }
                enter(); 
                break;
            case 7: 
                hapusLayar(); 
                tampilAntrian();
                enter();
                break;
            case 8: 
                hapusLayar(); 
                undoRiwayat();
                enter(); 
                break;
            case 9:
                hapusLayar();
                redoRiwayat();
                enter();
                break;
            case 10:
                hapusLayar();
                cout << "=== Penumpang Terdepan di Antrian ===" << endl;
                if(!isEmptyQueue()) {
                    int idDepan = queue[depan];
                    int indexDepan = CariNomorKA(daftarKereta, jumlahKereta, idDepan);
                    if (indexDepan != -1) {
                        cout << "Nama Penumpang: " << (daftarKereta + indexDepan)->namaPenumpang << endl;
                        cout << "Rute          : " << (daftarKereta + indexDepan)->asal << " -> " << (daftarKereta + indexDepan)->tujuan << endl;
                    }
                } else 
                    cout << "Antrian kosong!" << endl;
                cout << "\n=== Transaksi Terakhir (Riwayat) ===" << endl;
                if(atas >= 0) {
                    int idRiwayat = peek();
                    int indexRiwayat = CariNomorKA(daftarKereta, jumlahKereta, idRiwayat);
                    if (indexRiwayat != -1) {
                        cout << "Nama Penumpang: " << (daftarKereta + indexRiwayat)->namaPenumpang << endl;
                        cout << "Rute          : " << (daftarKereta + indexRiwayat)->asal << " -> " << (daftarKereta + indexRiwayat)->tujuan << endl;
                    }
                } else 
                cout << "Riwayat kosong!" << endl;
                enter(); 
                break;
            case 11:
                hapusLayar(); 
                cout << "Program Selesai.\n";
                break;
            default: hapusLayar();
                cout << "Pilihan tidak valid!\n";
                enter();
        }
    } while(pilihan != 11);
    return 0;
}