#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>

using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    TokoElektronik() {
        etalase[0] = "Laptop";
        etalase[1] = "Smartphone";
        etalase[2] = "Headset";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw string("Gagal Mengambil Barang : Rak nomor " +
                         to_string(nomorRak) +
                         " kosong atau tidak tersedia!");
        }
    }
};

class Gudang {
private:
    string namaFile;

public:
    Gudang(string file = "gudang.txt") {
        namaFile = file;
    }

    void tampilkanBarang() {
        ifstream file(namaFile);

        cout << "\n===== DAFTAR BARANG GUDANG =====\n";

        string data;
        int nomor = 1;

        while (getline(file, data)) {
            cout << nomor++ << ". " << data << endl;
        }

        if (nomor == 1) {
            cout << "Belum ada data barang.\n";
        }

        file.close();
    }

    void tambahBarang() {
        ofstream file(namaFile, ios::app);

        string barang;
        cin.ignore();

        cout << "Masukkan nama barang: ";
        getline(cin, barang);

        file << barang << endl;

        file.close();

        cout << "Data berhasil ditambahkan.\n";
    }

    void updateBarang() {
        ifstream file(namaFile);

        vector<string> data;
        string baris;

        while (getline(file, baris)) {
            data.push_back(baris);
        }

        file.close();

        if (data.empty()) {
            cout << "Tidak ada data untuk diperbarui.\n";
            return;
        }

        tampilkanBarang();

        int index;
        cout << "Pilih nomor barang yang akan diubah: ";
        cin >> index;

        if (index < 1 || index > data.size()) {
            cout << "Nomor tidak valid.\n";
            return;
        }

        cin.ignore();

        string barangBaru;
        cout << "Masukkan nama barang baru: ";
        getline(cin, barangBaru);

        data[index - 1] = barangBaru;

        ofstream outFile(namaFile);

        for (const auto& item : data) {
            outFile << item << endl;
        }

        outFile.close();

        cout << "Data berhasil diperbarui.\n";
    }

    void hapusBarang() {
        ifstream file(namaFile);

        vector<string> data;
        string baris;

        while (getline(file, baris)) {
            data.push_back(baris);
        }

        file.close();

        if (data.empty()) {
            cout << "Tidak ada data untuk dihapus.\n";
            return;
        }

        tampilkanBarang();

        int index;
        cout << "Pilih nomor barang yang akan dihapus: ";
        cin >> index;

        if (index < 1 || index > data.size()) {
            cout << "Nomor tidak valid.\n";
            return;
        }

        data.erase(data.begin() + (index - 1));

        ofstream outFile(namaFile);

        for (const auto& item : data) {
            outFile << item << endl;
        }

        outFile.close();

        cout << "Data berhasil dihapus.\n";
    }
};

int main() {
    Gudang gudang;
    TokoElektronik toko;

    int pilihan;

    do {
        cout << "\n=================================\n";
        cout << "   SISTEM TOKO ELEKTRONIK\n";
        cout << "        GIBRAN JAYA\n";
        cout << "=================================\n";

        gudang.tampilkanBarang();

        cout << "\nMenu:\n";
        cout << "1. Tambah Barang \n";
        cout << "2. Lihat Barang \n";
        cout << "3. Update Barang \n";
        cout << "4. Hapus Barang \n";
        cout << "5. Simulasi Etalase\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            gudang.tambahBarang();
            break;

        case 2:
            gudang.tampilkanBarang();
            break;

        case 3:
            gudang.updateBarang();
            break;

        case 4:
            gudang.hapusBarang();
            break;

        case 5:
            cout << "\n=== SIMULASI ETALASE ===\n";

            try {
                cout << "Skenario 1 (Rak 1): "
                     << toko.ambilProduk(1)
                     << endl;
            }
            catch (const string& pesan) {
                cout << pesan << endl;
            }

            try {
                cout << "Skenario 2 (Rak 5): "
                     << toko.ambilProduk(5)
                     << endl;
            }
            catch (const string& pesan) {
                cout << pesan << endl;
            }

            break;

        case 0:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak tersedia.\n";
        }

    } while (pilihan != 0);

    return 0;
}