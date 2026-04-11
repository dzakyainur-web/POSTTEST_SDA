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
int queue[MAX_HEWAN];
int depan = -1, rear = -1;
int stack[MAX_HEWAN];
int atas = -1;




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
    cout << "|6. Masukkan ke Antrian DARURAT (Sisip Depan) |\n";
    cout << "|7. Panggil Pasien dari Antrian Hewan         |\n";
    cout << "|8. Lihat Antrian Hewan                       |\n";
    cout << "|9. Batalkan Riwayat Terakhir                 |\n";
    cout << "|10. Lihat Pasien Terdepan & Riwayat Terakhir  |\n";
    cout << "|11. Keluar                                   |\n";
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

bool isFullQueue() {
    return rear == MAX_HEWAN - 1;
}
bool isEmptyQueue() {
    return depan == -1 || depan > rear;
}

void enqueue() {
    if(isFullQueue()) {
        cout << "Antrian penuh! Tidak bisa menambahkan ke antrian." << endl;
        return;
    }
    int idCari;
    cout << "Masukkan ID Hewan untuk dimasukkan ke antrian: ";
    cin >> idCari;
    int index = CariID(daftarHewan, jumlahHewan, idCari);
    if(index == -1) {
        cout << "ID Hewan tidak ditemukan! Tidak bisa menambahkan ke antrian." << endl;
        return;
    }
    if (depan == -1) {
        depan = 0;
    }
    rear++;
    queue[rear] = idCari;
    cout << "Hewan dengan ID " << idCari << " ditambahkan ke antrian." << endl;
}

void enqueueDarurat() {
    if(isFullQueue()) { 
        cout << "Antrian penuh!" << endl; 
        return; 
    }
    int idCari; 
        cout << "Masukkan ID Hewan untuk antrian DARURAT: "; 
        cin >> idCari;
    int index = CariID(daftarHewan, jumlahHewan, idCari);
    if(index == -1) { 
        cout << "ID Hewan tidak ditemukan!" << endl; 
        return; }
    if (isEmptyQueue()) {
        depan = 0; 
        rear = 0;
        queue[depan] = idCari;
    } else if (depan > 0) {
        depan--;
        queue[depan] = idCari;
    } else {
        for(int i = rear; i >= depan; i--) queue[i+1] = queue[i];
        rear++;
        queue[depan] = idCari;
    }
    cout << "Hewan " << (daftarHewan + index)->namaHewan << " masuk ke ANTRIAN DARURAT (Paling Depan)!" << endl;
}

int dequeue(){
    if(isEmptyQueue()) {
        cout << "Antrian kosong! Tidak ada yang bisa dipanggil." << endl;
        return -1;
    }
    int idPanggil = queue[depan];
    depan++;
    if (isEmptyQueue()) {
        depan = rear = -1; 
    }
    cout << "Hewan dengan ID " << idPanggil << " dipanggil dari antrian." << endl;
    return idPanggil;
}

void push(int id) {
    if(atas >= MAX_HEWAN -1) {
        cout << "Riwayat penuh! Tidak bisa menyimpan riwayat lagi." << endl;
    }
    else {
        atas++;
        stack[atas] = id;
        cout << "Riwayat dengan ID " << id << " disimpan ke stack." << endl;
    }
}

int pop(){
    if (atas < 0) {
        cout << "Riwayat kosong! Tidak ada yang bisa dibatalkan." << endl;
        return -1;
    }
    else {
        int idBatal = stack[atas];
        atas--;
        cout << "Riwayat dengan ID " << idBatal << " dibatalkan." << endl;
        return idBatal;
    }
}

int peek(){
    if (atas < 0) {
        return -1; 
    }
    else {
        return stack[atas];
    }
}
void tampilAntrian(){
    if(isEmptyQueue()) {
        cout << "Antrian kosong! Tidak ada yang bisa ditampilkan." << endl;
        return;
    }
    cout << "=== Antrian Hewan ===" << endl;
    int* ptr = queue + depan;
    for(int i = depan; i <= rear; i++) {
        int index = CariID(daftarHewan, jumlahHewan, *ptr);
        if (index != -1) {
            cout << "ID Hewan: " << *ptr << " - Nama Hewan: " << (daftarHewan + index)->namaHewan << endl;
        } else {
            cout << "ID Hewan: " << *ptr << " - Data tidak ditemukan!" << endl;
        }
        ptr++;
    }
    cout << "=====================" << endl;
}

void tampilRiwayat() {
    if (atas < 0) {
        cout << "Riwayat kosong! Tidak ada yang bisa ditampilkan." << endl;
        return;
    }
    cout << "=== Riwayat Pasien ===" << endl;
    int* ptr = stack + atas;
    for(int i = atas; i >= 0; i--) {
        int index = CariID(daftarHewan, jumlahHewan, *ptr);
        if (index != -1) {
            cout << "ID Hewan: " << *ptr << " - Nama Hewan: " << (daftarHewan + index)->namaHewan << endl;
        } else {
            cout << "ID Hewan: " << *ptr << " - Data tidak ditemukan!" << endl;
        }
        ptr--;
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
                if(subPilihan == 1)
                    UrutNama(daftarHewan, jumlahHewan);
                    else 
                        UrutHarga(daftarHewan, jumlahHewan);
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
                enqueueDarurat(); 
                enter(); 
                break;
            case 7:
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
            case 8:
                hapusLayar();
                tampilAntrian();
                enter();
                break;
            case 9:
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
            case 10:
                hapusLayar();
                cout << "=== Pasien Terdepan (Antrian) ===" << endl;
                if(!isEmptyQueue()) {
                    int idDepan = queue[depan];
                    int indexDepan = CariID(daftarHewan, jumlahHewan, idDepan);
                    cout << "ID Hewan: " << idDepan << endl;
                    if (indexDepan != -1) {
                        cout << "Nama Hewan: " << (daftarHewan + indexDepan)->namaHewan << endl;
                        cout << "Layanan: " << (daftarHewan + indexDepan)->namaLayanan << endl;
                    } else {
                        cout << "Nama Hewan: [Data Tidak Ditemukan]" << endl;
                    }
                } else {
                    cout << "Antrian kosong! Tidak ada pasien terdepan." << endl;
                }
                cout << "\n=== Tindakan Terakhir (Riwayat) ===" << endl;
                if(atas >= 0) { 
                    int idRiwayat = peek(); 
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
            case 11:
                hapusLayar();
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                break;
            default:
                hapusLayar();
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
                enter();
        }
    } while(pilihan != 11);
    return 0;
}