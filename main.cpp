#include <bits/stdc++.h>
#include <ctime>
using namespace std;

struct Tiket
{
    string id;
    string nama;
    string deskripsi;
    string status; // "open" atau "closed"
    int prioritas; // 1 = tinggi, 2 = sedang, 3 = rendah
    string masalah;
    string solusi;
};

// Struktur data utama
vector<Tiket> semuaTiket;
queue<Tiket> antreanTiket;
stack<Tiket> tiketSelesai;

// Fungsi hashing ID tiket
string generateID(const string &nama)
{
    time_t now = time(0);
    string waktu = to_string(now);
    hash<string> hasher;
    size_t hashed = hasher(nama + waktu);
    return to_string(hashed).substr(0, 8); // ID 8 digit
}

// Membuat tiket baru
void createTicket()
{
    Tiket t;
    cout << "Masukkan nama: ";
    cin.ignore();
    getline(cin, t.nama);
    cout << "Masukkan deskripsi masalah: ";
    getline(cin, t.deskripsi);
    cout << "Masukkan masalah Anda (penjelasan lebih lanjut, isi '-' jika tidak ada): \n";
    getline(cin, t.masalah);
    cout << "Masukkan tingkat prioritas (1 = tinggi, 2 = sedang, 3 = rendah): ";
    cin >> t.prioritas;
    t.status = "open";
    t.id = generateID(t.nama);

    semuaTiket.push_back(t);
    antreanTiket.push(t);
    cout << "Tiket berhasil dibuat dengan ID: " << t.id << endl;
}

// Menampilkan semua tiket
void viewAllTickets()
{
    if (semuaTiket.empty())
    {
        cout << "Belum ada tiket.\n";
        return;
    }

    cout << "Daftar Semua Tiket:\n";
    for (const auto &t : semuaTiket)
    {
        cout << "ID: " << t.id << ", Nama: " << t.nama
             << ", Prioritas: " << t.prioritas
             << ", Status: " << t.status << endl;
    }
}

// Menampilkan antrean tiket
void viewQueue()
{
    if (antreanTiket.empty())
    {
        cout << "Antrean kosong.\n";
        return;
    }

    // Ambil isi antrean ke vector
    vector<Tiket> temp;
    queue<Tiket> q = antreanTiket; // salin antrean asli

    while (!q.empty())
    {
        temp.push_back(q.front());
        q.pop();
    }

    // Urutkan berdasarkan prioritas (1=tinggi, 2=sedang, 3= rendah)
    sort(temp.begin(), temp.end(), [](const Tiket &a, const Tiket &b)
         { return a.prioritas < b.prioritas; });

    cout << "Antrean Tiket (urut berdasarkan prioritas):\n";
    for (const auto &t : temp)
    {
        cout << "ID: " << t.id << ", Nama: " << t.nama
             << ", Prioritas: " << t.prioritas << endl;
    }
}


// Menampilkan tiket selesai (stack)
void viewClosedTickets()
{
    if (tiketSelesai.empty())
    {
        cout << "Belum ada tiket yang diselesaikan.\n";
        return;
    }

    stack<Tiket> s = tiketSelesai;
    cout << "Riwayat Tiket Selesai:\n";
    while (!s.empty())
    {
        Tiket t = s.top();
        s.pop();
        cout << "ID: " << t.id << ", Nama: " << t.nama
             << ", Solusi: " << t.solusi << endl;
    }
}

// Menyelesaikan tiket
void resolveTicket()
{
    if (antreanTiket.empty())
    {
        cout << "Tidak ada tiket untuk diselesaikan.\n";
        return;
    }

    // Pindahkan antrean ke vector untuk sorting
    vector<Tiket> temp;
    while (!antreanTiket.empty())
    {
        temp.push_back(antreanTiket.front());
        antreanTiket.pop();
    }

    // Urutkan berdasarkan prioritas
    sort(temp.begin(), temp.end(), [](const Tiket &a, const Tiket &b)
         { return a.prioritas < b.prioritas; });

    // Ambil tiket dengan prioritas tertinggi (index 0)
    Tiket t = temp.front();
    temp.erase(temp.begin());

    cout << "Menyelesaikan tiket ID: " << t.id << ", Nama: " << t.nama << endl;
    cout << "Kategori masalah: " << t.masalah << endl;
    cout << "Masukkan solusi: ";
    cin.ignore();
    getline(cin, t.solusi);

    t.status = "closed";

    // Update di vector semuaTiket
    for (auto &ticket : semuaTiket)
    {
        if (ticket.id == t.id)
        {
            ticket.status = "closed";
            ticket.solusi = t.solusi;
            break;
        }
    }

    tiketSelesai.push(t);

    // Masukkan kembali sisa tiket ke antreanTiket
    for (const auto &tk : temp)
        antreanTiket.push(tk);

    cout << "Tiket berhasil diselesaikan.\n";
}


// Menghapus tiket berdasarkan ID
void deleteTicketById()
{
    string id;
    cout << "Masukkan ID tiket yang akan dihapus: ";
    cin >> id;

    auto it = remove_if(semuaTiket.begin(), semuaTiket.end(),
                        [&](Tiket &t)
                        { return t.id == id; });

    if (it != semuaTiket.end())
    {
        semuaTiket.erase(it, semuaTiket.end());
        cout << "Tiket berhasil dihapus dari daftar semua tiket.\n";
    }
    else
    {
        cout << "Tiket tidak ditemukan.\n";
    }

    // Tidak menghapus dari queue/stack karena non-trivial dalam queue/stack
}

// Menghadapi case sensitive
string toLower(const string &s)
{
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Search Ticket by Id atau nama
void searchTicket()
{
    if (semuaTiket.empty())
    {
        cout << "Belum ada tiket.\n";
        return;
    }

    int pilihan;
    cout << "Cari berdasarkan:\n";
    cout << "1. ID\n";
    cout << "2. Nama\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    cin.ignore();
    if (pilihan == 1)
    {
        string id;
        cout << "Masukkan ID tiket: ";
        getline(cin, id);
        bool found = false;
        for (const auto &t : semuaTiket)
        {
            if (t.id == id)
            {
                cout << "\nTiket ditemukan:\n";
                cout << "ID: " << t.id << "\nNama: " << t.nama
                     << "\nDeskripsi: " << t.deskripsi
                     << "\nMasalah: " << t.masalah
                     << "\nPrioritas: " << t.prioritas
                     << "\nStatus: " << t.status
                     << "\nSolusi: " << t.solusi << endl;
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Tiket dengan ID tersebut tidak ditemukan.\n";
    }
    else if (pilihan == 2)
    {
        string namaInput;
        cout << "Masukkan nama: ";
        getline(cin, namaInput);
        namaInput = toLower(namaInput);

        bool found = false;
        for (const auto &t : semuaTiket)
        {
            if (toLower(t.nama) == namaInput)
            {
                cout << "\nTiket ditemukan:\n";
                cout << "ID: " << t.id << "\nNama: " << t.nama
                     << "\nDeskripsi: " << t.deskripsi
                     << "\nMasalah: " << t.masalah
                     << "\nPrioritas: " << t.prioritas
                     << "\nStatus: " << t.status
                     << "\nSolusi: " << t.solusi << endl;
                found = true;
            }
        }
        if (!found)
            cout << "Tidak ada tiket dengan nama tersebut.\n";
    }
    else
    {
        cout << "Pilihan tidak valid.\n";
    }
}

// Menampilkan open atau closed
void filterTicketsByStatus()
{
    if (semuaTiket.empty())
    {
        cout << "Belum ada tiket.\n";
        return;
    }

    string status;
    cout << "Masukkan status (open/closed): ";
    cin >> status;

    bool found = false;
    for (const auto &t : semuaTiket)
    {
        if (t.status == status)
        {
            cout << "\nID: " << t.id << ", Nama: " << t.nama
                 << ", Prioritas: " << t.prioritas
                 << ", Status: " << t.status << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "Tidak ada tiket dengan status \"" << status << "\".\n";
    }
}

// Menu utama
int main()
{
    int n;

    do
    {
        cout << "\n==============================================\n";
        cout << "Menu Helpdesk:\n";
        cout << "1. Buat Tiket\n";
        cout << "2. Lihat Semua Tiket\n";
        cout << "3. Lihat Antrean\n";
        cout << "4. Lihat Tiket Selesai\n";
        cout << "5. Selesaikan Tiket\n";
        cout << "6. Hapus Tiket\n";
        cout << "7. Cari Tiket\n";
        cout << "8. Tampilkan Tiket berdasarkan Status\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> n;

        switch (n)
        {
        case 1:
            createTicket();
            break;
        case 2:
            viewAllTickets();
            break;
        case 3:
            viewQueue();
            break;
        case 4:
            viewClosedTickets();
            break;
        case 5:
            resolveTicket();
            break;
        case 6:
            deleteTicketById();
            break;
        case 7:
            searchTicket();
            break;
        case 8:
            filterTicketsByStatus();
            break;
        case 0:
            cout << "Keluar dari program\n";
            break;
        default:
            cout << "Pilihan tidak valid\n";
            break;
        }

    } while (n != 0);

    return 0;
}
