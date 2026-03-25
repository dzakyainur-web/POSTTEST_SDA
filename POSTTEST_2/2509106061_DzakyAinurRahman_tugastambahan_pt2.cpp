#include <iostream>
#include <string>

using namespace std;


struct pelanggan {
    int id;
    string nama;
};

void insertSort(pelanggan arr[], int n) {
    for (int i = 1; i < n; i++) {
        pelanggan key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

#define ALFABET 256
void preProcess(string pattern, int badChar[ALFABET]) {
    for (int i = 0; i < ALFABET; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < pattern.length(); i++) {
        badChar[(int)pattern[i]] = i;
    }
}

void boyerMoore(string text, string pattern, string nama) {
    int n = text.length();
    int m = pattern.length();
    int badChar[ALFABET];

    preProcess(pattern, badChar);

    int s = 0;
    bool ketemu = false;

    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            cout << "Pola ditemukan pada: " << nama << endl;
            ketemu = true;
            if (s + m < n) {
                s += m - badChar[(int)text[s + m]];
            } else {
                s++;
            }
        } else {
            int geser = j - badChar[(int)text[s + j]];
            if (geser < 1) geser = 1;
            s += geser;
        }
    }
    if (!ketemu) 
        cout << "Pola tidak ditemukan pada: " << nama << endl;
}

int main() {
    pelanggan daftar[] = {
        {105, "Rania"}, {102, "Bagas"}, {107, "Salsa"},
        {101, "Hendra"}, {104, "Nadia"}, {106, "Gilang"}, {103, "Putri"}
    };
    int n = 7;
    string pola = "an";
    insertSort(daftar, n);
    cout << "=== Daftar Pelanggan (Terurut ID) ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << daftar[i].id << " - " << daftar[i].nama << endl;
    }
    cout << "\n=== Hasil Pencarian Boyer-Moore ===" << endl;
    for (int i = 0; i < n; i++) {
        boyerMoore(daftar[i].nama, pola, daftar[i].nama);
    }

    return 0;
}