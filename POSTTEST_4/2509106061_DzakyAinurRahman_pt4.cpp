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

struct Node {
    int idHewan;
    Node* next;
};

#define MAX_HEWAN 100
Hewan daftarHewan[MAX_HEWAN];
int jumlahHewan = 0;
Node* head = nullptr;
Node* tail = nullptr;
Node* Stack = nullptr;

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
    cout << "===============================================\n";
    cout << "|                    MENU UTAMA               |\n";
    cout << "===============================================\n";
    cout << "|1. Tambah Data Hewan                         |\n";
    cout << "|2. Lihat Semua Data                          |\n";
    cout << "|3. Urutkan Data Hewan                        |\n";
    cout << "|4. Cari Data Hewan                           |\n";
    cout << "|5. Masukkan ke Antrian Hewan                 |\n";
    cout << "|6. Panggil Pasien dari Antrian Hewan         |\n";
    cout << "|7. Lihat Antrian Hewan                       |\n";
    cout << "|8. Batalkan Riwayat Terakhir                 |\n";
    cout << "|9. Lihat Pasien Terdepan & Riwayat Terakhir  |\n";
    cout << "|10. Keluar                                   |\n";
    cout << "==============================================\n";
}

void swap(Hewan *a, Hewan *b) {
    Hewan temp = *a;
    *a = *b;
    *b = temp;
}
void TampilkanData(Hewan* arr, int n) {
    if (n == 0) {
        cout << "\nData hewan masih kosong.\n";
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
    for(int i = 0; i < n; i++) {
        if((arr + i)->idHewan == target) {
            return i; 
        }
    }
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


bool isEmptyQueue() {
    return head == nullptr;
}

void enqueue() {
    int idCari;
    cout << "Masukkan ID Hewan untuk dimasukkan ke antrian: ";
    cin >> idCari;
    int index = CariID(daftarHewan, jumlahHewan, idCari);
        if(index == -1) {
            cout << "ID Hewan tidak ditemukan! Tidak bisa menambahkan ke antrian." << endl;
            return;
        }
    Node* newNode = new Node();
    newNode->idHewan = idCari;
    newNode->next = nullptr;
    if (head == nullptr) head = tail = newNode;
        else { 
            tail->next = newNode; tail = newNode;    
    }
    cout << "Hewan dengan ID " << idCari << " ditambahkan ke antrian." << endl;
}

int dequeue(){
    if(isEmptyQueue()) {
        cout << "Antrian kosong! Tidak ada yang bisa dipanggil." << endl;
        return -1;
    }
    Node* temp = head;
    int idPanggil = head->idHewan;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr; 
    }
    delete temp;
    cout << "Hewan dengan ID " << idPanggil << " dipanggil dari antrian." << endl;
    return idPanggil;
}

void push(int id) {
    Node* newNode = new Node();
    newNode->idHewan = id;
    newNode->next = Stack;
    Stack = newNode;
    cout << "Riwayat dengan ID " << id << " disimpan ke stack." << endl;
}

int pop(){
    if (Stack == nullptr) {
        cout << "Riwayat kosong! Tidak ada yang bisa dibatalkan." << endl;
        return -1;
    }
    Node* temp = Stack;
    int idBatal = Stack->idHewan;
    Stack = Stack->next;
    delete temp;
    cout << "Riwayat dengan ID " << idBatal << " dibatalkan." << endl;
    return idBatal;
}

int peek(){
    if (Stack == nullptr) {
        return -1; 
    }
        return Stack->idHewan;
}

void tampilAntrian(){
    if(isEmptyQueue()) {
        cout << "Antrian kosong! Tidak ada yang bisa ditampilkan." << endl;
        return;
    }
    cout << "=== Antrian Hewan ===" << endl;
    Node* temp = head;
    while(temp != nullptr) {
        int index = CariID(daftarHewan, jumlahHewan, temp->idHewan);
        if (index != -1) {
            cout << "ID Hewan: " << temp->idHewan << " - Nama Hewan: " << (daftarHewan + index)->namaHewan << endl;
        } 
        temp = temp->next;
    }
    cout << "=====================" << endl;
}

void tampilRiwayat() {
    if (Stack == nullptr) {
        cout << "Riwayat kosong! Tidak ada yang bisa ditampilkan." << endl;
        return;
    }
    cout << "=== Riwayat Pasien ===" << endl;
    Node* temp = Stack;
    while(temp != nullptr) {
        int index = CariID(daftarHewan, jumlahHewan, temp->idHewan);
                if (index != -1) {
            cout << "ID Hewan: " << temp->idHewan << " - Nama Hewan: " << (daftarHewan + index)->namaHewan << endl;
        }
        temp = temp->next;
    }
    cout << "=====================" << endl;
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
                if(subPilihan == 1) {
                    UrutNama(daftarHewan, jumlahHewan);
                    cout << "Data berhasil diurutkan berdasarkan Nama!\n";
                } else {
                    UrutHarga(daftarHewan, jumlahHewan);
                    cout << "Data berhasil diurutkan berdasarkan Harga!\n";
                }
                enter();
                break;
            case 4:
                hapusLayar();
                cout << "1. Cari Nama" << endl;
                cout << "2. Cari ID" << endl;
                cout << "Pilih: ";
                cin >> subPilihan;
                if(subPilihan == 1) {
                    cout << "Nama Hewan: "; 
                    cin.ignore(); 
                    getline(cin, cariNama);
                    int hasil = CariNama(daftarHewan, jumlahHewan, cariNama);
                    if(hasil != -1) 
                        cout << "Ditemukan di indeks " << hasil << endl;
                        else 
                            cout << "Data Tidak Ada.\n";
                } else {
                    sortID(daftarHewan, jumlahHewan); 
                    cout << "ID Hewan: "; 
                    cin >> cariID;
                    int hasil = CariID(daftarHewan, jumlahHewan, cariID);
                    if(hasil != -1) cout << "Ditemukan di indeks " << hasil << endl;
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
                    int idPanggil = dequeue();
                    if (idPanggil != -1) { 
                        int indexPanggil = CariID(daftarHewan, jumlahHewan, idPanggil);
                        cout << "=== Pasien yang Dipanggil ===" << endl;
                        cout << "Pasien dengan ID " << idPanggil << endl;
                        if (indexPanggil != -1) { 
                            cout << "Nama Hewan: " << (daftarHewan + indexPanggil)->namaHewan << endl;
                            cout << "dipanggil untuk layanan: " << (daftarHewan + indexPanggil)->namaLayanan << endl;
                        } else {
                            cout << "Nama Hewan: [Data Tidak Ditemukan]" << endl;
                        }
                        cout << "==============================" << endl;
                        push(idPanggil);
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
                {
                    int idBatal = pop();
                    if (idBatal != -1) {
                        int indexBatal = CariID(daftarHewan, jumlahHewan, idBatal);
                        cout << "=== Pasien yang Dibatalkan ===" << endl;
                        cout << "Pasien dengan ID " << idBatal << endl;
                        if (indexBatal != -1) {
                            cout << "Nama Hewan: " << (daftarHewan + indexBatal)->namaHewan << endl;
                            cout << "dibatalkan dari layanan: " << (daftarHewan + indexBatal)->namaLayanan << endl;
                        } else {
                            cout << "Nama Hewan: [Data Tidak Ditemukan]" << endl;
                        }
                        cout << "==============================" << endl;
                    }
                }
                enter();
                break;
            case 9: {
                hapusLayar();
                cout << "=== Pasien Terdepan (Antrian) ===" << endl;
                if(!isEmptyQueue()) {
                    int idDepan = head->idHewan;
                    int indexDepan = CariID(daftarHewan, jumlahHewan, idDepan);
                    cout << "ID Hewan: " << idDepan << endl;
                    if (indexDepan != -1) {
                        cout << "Nama Hewan: " << (daftarHewan + indexDepan)->namaHewan << endl;
                        cout << "Layanan: " << (daftarHewan + indexDepan)->namaLayanan << endl;
                    }
                } else {
                    cout << "Antrian kosong! Tidak ada pasien terdepan." << endl;
                }
                cout << "\n=== Tindakan Terakhir (Riwayat) ===" << endl;
                int idRiwayat = peek();
                if( idRiwayat != -1) { 
                    int indexRiwayat = CariID(daftarHewan, jumlahHewan, idRiwayat);
                    if (indexRiwayat != -1) {
                        cout << "Nama Hewan: " << (daftarHewan + indexRiwayat)->namaHewan << endl;
                        cout << "Layanan: " << (daftarHewan + indexRiwayat)->namaLayanan << endl;
                    } else {
                        cout << "Nama Hewan: [Data Tidak Ditemukan]" << endl;
                    }
                } else {
                    cout << "Riwayat kosong! Tidak ada tindakan terakhir." << endl;
                }
                enter();
                break;
            }
            case 10:
                hapusLayar();
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                break;
            default:
                hapusLayar();
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
                enter();
        }
    } while(pilihan != 10);
    return 0;
}
