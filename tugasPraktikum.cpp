#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
using namespace std;

class TokoElektronik {
private:
    array<string, 3> rak;
public:
    TokoElektronik() {
        rak[0] = "Kipas Angin";
        rak[1] = "Rice Cooker";
        rak[2] = "Setrika";
    }
    string ambilProduk(size_t nomorRak) {
        try {
            return rak.at(nomorRak);
        } catch (const out_of_range &) {
            throw runtime_error("Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!");
        }
    }
};

vector<string> bacaFile() {
    vector<string> isi;
    ifstream file("gudang.txt");
    string baris;
    while (getline(file, baris)) {
        if (!baris.empty()) isi.push_back(baris);
    }
    file.close();
    return isi;
}

void simpanFile(vector<string> isi) {
    ofstream file("gudang.txt");
    for (int i = 0; i < (int)isi.size(); i++) {
        file << isi[i] << endl;
    }
    file.close();
}

void tampil() {
    vector<string> data = bacaFile();
    cout << "\n===== STOK BARANG =====\n";
    if (data.size() == 0) {
        cout << "Belum ada barang.\n";
    } else {
        for (int i = 0; i < (int)data.size(); i++) {
            cout << i + 1 << ". " << data[i] << endl;
        }
    }
    cout << "=======================\n";
}

void tambah() {
    string nama, harga, stok;
    cin.ignore();
    cout << "Nama barang : "; getline(cin, nama);
    cout << "Harga       : "; getline(cin, harga);
    cout << "Stok        : "; getline(cin, stok);

    ofstream file("gudang.txt", ios::app);
    file << nama << " | Harga: " << harga << " | Stok: " << stok << endl;
    file.close();
    cout << "Barang ditambahkan.\n";
}

void ubah() {
    tampil();
    vector<string> data = bacaFile();
    if (data.empty()) return;

    int no;
    cout << "Pilih nomor barang : ";
    cin >> no;

    if (no < 1 || no > (int)data.size()) {
        cout << "Nomor salah!\n";
        return;
    }

    string nama, harga, stok;
    cin.ignore();
    cout << "Nama baru  : "; getline(cin, nama);
    cout << "Harga baru : "; getline(cin, harga);
    cout << "Stok baru  : "; getline(cin, stok);

    data[no - 1] = nama + " | Harga: " + harga + " | Stok: " + stok;
    simpanFile(data);
    cout << "Barang diubah.\n";
}

void hapus() {
    tampil();
    vector<string> data = bacaFile();
    if (data.empty()) return;

    int no;
    cout << "Pilih nomor barang : ";
    cin >> no;

    if (no < 1 || no > (int)data.size()) {
        cout << "Nomor salah!\n";
        return;
    }

    data.erase(data.begin() + (no - 1));
    simpanFile(data);
    cout << "Barang dihapus.\n";
}

void simulasi() {
    TokoElektronik toko;
    cout << "\n===== SIMULASI ETALASE =====\n";

    cout << "Skenario 1 (rak ke-1):\n";
    try {
        cout << "  Barang: " << toko.ambilProduk(1) << endl;
    } catch (const exception &e) {
        cout << "  " << e.what() << endl;
    }

    cout << "Skenario 2 (rak ke-5):\n";
    try {
        cout << "  Barang: " << toko.ambilProduk(5) << endl;
    } catch (const exception &e) {
        cout << "  " << e.what() << endl;
    }
}

int main() {
    int pilih;
    do {
        tampil();
        cout << "\n## TOKO ELEKTRONIK GIBRAN JAYA ##\n";
        cout << "1. Tambah\n";
        cout << "2. Lihat\n";
        cout << "3. Ubah\n";
        cout << "4. Hapus\n";
        cout << "5. Simulasi Etalase\n";
        cout << "0. Keluar\n";
        cout << "Pilihan : ";
        cin >> pilih;

        if (pilih == 1) tambah();
        else if (pilih == 2) tampil();
        else if (pilih == 3) ubah();
        else if (pilih == 4) hapus();
        else if (pilih == 5) simulasi();
        else if (pilih == 0) cout << "Program selesai.\n";
        else cout << "Pilihan salah!\n";

    } while (pilih != 0);

    return 0;
}