#include <iostream>
#include <string.h>

using namespace std;

struct Kamar
{
  int id;
  char tipe[50];
  int harga;
  char status[20];        // "tersedia", "sudah di reservasi", "dihuni"
  char namaPelanggan[50]; // Nama pelanggan yang mereservasi kamar
  int jumlahHari;         // Jumlah hari menginap
};

struct Reservasi
{
  char namaPelanggan[50];
  char tipeKamar[50];
  int jumlahHari;
};

Kamar daftarKamar[100];
Reservasi antrianReservasi[100];
int jumlahKamar = 0;
int jumlahReservasi = 0;

bool cekIDKamar(int id)
{
  for (int i = 0; i < jumlahKamar; ++i)
  {
    if (daftarKamar[i].id == id)
    {
      return true;
    }
  }
  return false;
}

void tambahKamar()
{
  int id;
  cout << "\n=== Tambah Kamar ===" << endl;
  cout << "ID kamar: ";
  cin >> id;

  if (cekIDKamar(id))
  {
    cout << "ID kamar sudah ada. Kamar tidak ditambahkan." << endl;
    return;
  }

  daftarKamar[jumlahKamar].id = id;

  int pilihan;
  cout << "Pilih tipe kamar:\n1. Suite\n2. Deluxe\n3. Reguler\nPilih: ";
  cin >> pilihan;
  switch (pilihan)
  {
  case 1:
    strcpy(daftarKamar[jumlahKamar].tipe, "Suite");
    daftarKamar[jumlahKamar].harga = 1000000; // Harga tetap untuk Suite
    break;
  case 2:
    strcpy(daftarKamar[jumlahKamar].tipe, "Deluxe");
    daftarKamar[jumlahKamar].harga = 750000; // Harga tetap untuk Deluxe
    break;
  case 3:
    strcpy(daftarKamar[jumlahKamar].tipe, "Reguler");
    daftarKamar[jumlahKamar].harga = 500000; // Harga tetap untuk Reguler
    break;
  default:
    cout << "Pilihan tidak valid, kamar tidak ditambahkan." << endl;
    return;
  }

  strcpy(daftarKamar[jumlahKamar].status, "tersedia");
  jumlahKamar++;
  cout << "Kamar berhasil ditambahkan!" << endl;
}

void hapusKamar()
{
  cout << "\n=== Hapus Kamar ===" << endl;
  bool adaKamarTersedia = false;
  for (int i = 0; i < jumlahKamar; ++i)
  {
    if (strcmp(daftarKamar[i].status, "tersedia") == 0)
    {
      adaKamarTersedia = true;
      break;
    }
  }

  if (!adaKamarTersedia)
  {
    cout << "Tidak ada kamar yang bisa dihapus." << endl;
    return;
  }

  cout << "Daftar kamar yang tersedia:" << endl;
  for (int i = 0; i < jumlahKamar; ++i)
  {
    if (strcmp(daftarKamar[i].status, "tersedia") == 0)
    {
      cout << "ID: " << daftarKamar[i].id << ", Tipe: " << daftarKamar[i].tipe << ", Harga: " << daftarKamar[i].harga << endl;
    }
  }

  int id;
  cout << "ID kamar yang akan dihapus (0 untuk batal): ";
  cin >> id;

  if (id == 0)
  {
    cout << "Proses penghapusan dibatalkan." << endl;
    return;
  }

  for (int i = 0; i < jumlahKamar; ++i)
  {
    if (daftarKamar[i].id == id && strcmp(daftarKamar[i].status, "tersedia") == 0)
    {
      for (int j = i; j < jumlahKamar - 1; ++j)
      {
        daftarKamar[j] = daftarKamar[j + 1];
      }
      jumlahKamar--;
      cout << "Kamar berhasil dihapus!" << endl;
      return;
    }
  }

  cout << "Kamar tidak ditemukan atau sedang tidak tersedia." << endl;
}

void cariKamar()
{
  if (jumlahKamar == 0)
  {
    cout << "Tidak ada kamar yang tersedia." << endl;
    return;
  }

  int choice;
  cout << "\n=== Cari Kamar ===" << endl;
  cout << "Urutkan berdasarkan:\n1. ID\n2. Harga\n3. List Kamar Tersedia\n4. Tipe\nPilih: ";
  cin >> choice;

  switch (choice)
  {
  case 1: // Berdasarkan ID
    for (int i = 0; i < jumlahKamar - 1; ++i)
    {
      for (int j = 0; j < jumlahKamar - i - 1; ++j)
      {
        if (daftarKamar[j].id > daftarKamar[j + 1].id)
        {
          Kamar temp = daftarKamar[j];
          daftarKamar[j] = daftarKamar[j + 1];
          daftarKamar[j + 1] = temp;
        }
      }
    }
    break;
  case 2: // Berdasarkan Harga
    for (int i = 0; i < jumlahKamar - 1; ++i)
    {
      for (int j = 0; j < jumlahKamar - i - 1; ++j)
      {
        if (daftarKamar[j].harga > daftarKamar[j + 1].harga)
        {
          Kamar temp = daftarKamar[j];
          daftarKamar[j] = daftarKamar[j + 1];
          daftarKamar[j + 1] = temp;
        }
      }
    }
    break;
  case 3: // List Kamar Tersedia
    for (int i = 0; i < jumlahKamar; ++i)
    {
      if (strcmp(daftarKamar[i].status, "tersedia") == 0)
      {
        cout << "ID: " << daftarKamar[i].id << ", Tipe: " << daftarKamar[i].tipe << ", Harga: " << daftarKamar[i].harga << endl;
      }
    }
    return;
  case 4: // Berdasarkan Tipe
    char tipe[50];
    cout << "Masukkan tipe kamar (Suite/Deluxe/Reguler): ";
    cin >> tipe;
    for (int i = 0; i < jumlahKamar; ++i)
    {
      if (strcmp(daftarKamar[i].tipe, tipe) == 0)
      {
        cout << "ID: " << daftarKamar[i].id << ", Tipe: " << daftarKamar[i].tipe << ", Harga: " << daftarKamar[i].harga;
        cout << ", Status: " << daftarKamar[i].status;

        if (strcmp(daftarKamar[i].status, "sudah di reservasi") == 0 || strcmp(daftarKamar[i].status, "dihuni") == 0)
        {
          cout << ", Nama Pelanggan: " << daftarKamar[i].namaPelanggan << ", Jumlah Hari: " << daftarKamar[i].jumlahHari;
        }
        cout << endl;
      }
    }
    return;
  default:
    cout << "Pilihan tidak valid." << endl;
    return;
  }

  for (int i = 0; i < jumlahKamar; ++i)
  {
    cout << "ID: " << daftarKamar[i].id << ", Tipe: " << daftarKamar[i].tipe << ", Harga: " << daftarKamar[i].harga;
    cout << ", Status: " << daftarKamar[i].status;
    
    if (strcmp(daftarKamar[i].status, "sudah di reservasi") == 0 || strcmp(daftarKamar[i].status, "dihuni") == 0)
    {
      cout << ", Nama Pelanggan: " << daftarKamar[i].namaPelanggan << ", Jumlah Hari: " << daftarKamar[i].jumlahHari;
    }
    cout << endl;
  }
}

void tambahReservasi()
{
  if (jumlahKamar == 0)
  {
    cout << "Tidak ada kamar yang tersedia untuk reservasi." << endl;
    return;
  }

  cout << "\n=== Tambah Reservasi ===" << endl;
  cout << "Nama pelanggan: ";
  cin.ignore();
  cin.getline(antrianReservasi[jumlahReservasi].namaPelanggan, 50);

  int pilihan;
  cout << "Pilih tipe kamar:\n1. Suite\n2. Deluxe\n3. Reguler\nPilih: ";
  cin >> pilihan;

  switch (pilihan)
  {
  case 1:
    strcpy(antrianReservasi[jumlahReservasi].tipeKamar, "Suite");
    break;
  case 2:
    strcpy(antrianReservasi[jumlahReservasi].tipeKamar, "Deluxe");
    break;
  case 3:
    strcpy(antrianReservasi[jumlahReservasi].tipeKamar, "Reguler");
    break;
  default:
    cout << "Pilihan tidak valid." << endl;
    return;
  }

  cout << "Jumlah hari menginap: ";
  cin >> antrianReservasi[jumlahReservasi].jumlahHari;

  int totalHarga = 0;
  for (int i = 0; i < jumlahKamar; ++i)
  {
    if (strcmp(daftarKamar[i].tipe, antrianReservasi[jumlahReservasi].tipeKamar) == 0 && strcmp(daftarKamar[i].status, "tersedia") == 0)
    {
      totalHarga = daftarKamar[i].harga * antrianReservasi[jumlahReservasi].jumlahHari;
      strcpy(daftarKamar[i].status, "sudah di reservasi");
      strcpy(daftarKamar[i].namaPelanggan, antrianReservasi[jumlahReservasi].namaPelanggan);
      daftarKamar[i].jumlahHari = antrianReservasi[jumlahReservasi].jumlahHari;
      break;
    }
  }

  if (totalHarga > 0)
  {
    cout << "Reservasi berhasil ditambahkan! Total harga: " << totalHarga << endl;
    jumlahReservasi++;
  }
  else
  {
    cout << "Tidak ada kamar yang tersedia untuk tipe tersebut." << endl;
  }
}

void prosesCheckIn()
{
  if (jumlahReservasi > 0)
  {
    cout << "\n=== Proses Check-In ===" << endl;
    cout << "Daftar antrian reservasi:" << endl;
    for (int i = 0; i < jumlahReservasi; ++i)
    {
      cout << i + 1 << ". " << antrianReservasi[i].namaPelanggan << ", Kamar: " << antrianReservasi[i].tipeKamar << ", Jumlah Hari: " << antrianReservasi[i].jumlahHari << endl;
    }

    int pilihan;
    cout << "Pilih: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahReservasi)
    {
      cout << "Pilihan tidak valid." << endl;
      return;
    }

    pilihan--; // Sesuaikan dengan indeks array

    for (int i = 0; i < jumlahKamar; ++i)
    {
      if (strcmp(daftarKamar[i].tipe, antrianReservasi[pilihan].tipeKamar) == 0 &&
          strcmp(daftarKamar[i].namaPelanggan, antrianReservasi[pilihan].namaPelanggan) == 0 &&
          strcmp(daftarKamar[i].status, "sudah di reservasi") == 0)
      {
        strcpy(daftarKamar[i].status, "dihuni");
        break;
      }
    }

    for (int i = pilihan; i < jumlahReservasi - 1; ++i)
    {
      antrianReservasi[i] = antrianReservasi[i + 1];
    }
    jumlahReservasi--;
    cout << "Check-In berhasil!" << endl;
  }
  else
  {
    cout << "Tidak ada antrian reservasi." << endl;
  }
}

void listKamarDihuni()
{
  bool adaKamarDihuni = false;
  cout << "\n=== Kamar yang Dihuni ===" << endl;
  for (int i = 0; i < jumlahKamar; ++i)
  {
    if (strcmp(daftarKamar[i].status, "dihuni") == 0)
    {
      cout << "ID: " << daftarKamar[i].id << ", Tipe: " << daftarKamar[i].tipe << ", Harga: " << daftarKamar[i].harga;
      cout << ", Nama Pelanggan: " << daftarKamar[i].namaPelanggan << ", Jumlah Hari: " << daftarKamar[i].jumlahHari << endl;
      adaKamarDihuni = true;
    }
  }

  if (!adaKamarDihuni)
  {
    cout << "Tidak ada kamar yang dihuni." << endl;
  }
}

void listKamarReservasi()
{
  bool adaKamarReservasi = false;
  cout << "\n=== Kamar yang Sudah di Reservasi ===" << endl;
  for (int i = 0; i < jumlahKamar; ++i)
  {
    if (strcmp(daftarKamar[i].status, "sudah di reservasi") == 0)
    {
      cout << "ID: " << daftarKamar[i].id << ", Tipe: " << daftarKamar[i].tipe << ", Harga: " << daftarKamar[i].harga;
      cout << ", Nama Pelanggan: " << daftarKamar[i].namaPelanggan << ", Jumlah Hari: " << daftarKamar[i].jumlahHari << endl;
      adaKamarReservasi = true;
    }
  }

  if (!adaKamarReservasi)
  {
    cout << "Tidak ada kamar yang sudah di reservasi." << endl;
  }
}

int main()
{
  int choice;

  do
  {
    cout << "\n=== Daftar Menu ===" << endl;
    cout << "1. Tambah Kamar" << endl;
    cout << "2. Hapus Kamar" << endl;
    cout << "3. Cari Kamar" << endl;
    cout << "4. Tambah Reservasi" << endl;
    cout << "5. Proses Check-In" << endl;
    cout << "6. List Kamar Dihuni" << endl;
    cout << "7. List Kamar Reservasi" << endl;
    cout << "8. Keluar" << endl;

    cout << "Pilih menu: ";
    cin >> choice;

    cout << "==============================" << endl; // Pemisah tampilan

    switch (choice)
    {
    case 1:
      tambahKamar();
      break;
    case 2:
      hapusKamar();
      break;
    case 3:
      cariKamar();
      break;
    case 4:
      tambahReservasi();
      break;
    case 5:
      prosesCheckIn();
      break;
    case 6:
      listKamarDihuni();
      break;
    case 7:
      listKamarReservasi();
      break;
    case 8:
      cout << "Keluar dari program." << endl;
      break;
    default:
      cout << "Pilihan tidak valid." << endl;
    }

    cout << "==============================" << endl; // Pemisah tampilan
  } while (choice != 8);

  return 0;
}
