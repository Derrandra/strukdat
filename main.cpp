#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;

    do{
        cout << endl << "==============================================" << endl;
        cout << "Menu Heldesk:\n";
        cout << "1. Buat Tiket\n";
        cout << "2. Lihat Semua Tiket\n";
        cout << "3. Lihat Antrean\n";
        cout << "4. Lihat Tiket Selesai\n";
        cout << "5. Selesaikan Tiket\n";
        cout << "6. Hapus Tiket\n";
        cout << "7. Sortir tiket berdasarkan prioritas\n";
        cout << "0. Keluar\n";
        cout << "Pilih: "; cin >> n;

        switch(n){
            case 1:
                // createTicket();
                break;
            case 2:
                // viewAllTickets();
                break;
            case 3:
                // viewQueue();
                break;
            case 4:
                // viewClosedTickets();
                break;
            case 5:
                // resolveTicket();
                break;
            case 6:
                // deleteTicketById();
                break;
            case 7:
                // sortTicketsByPriority();
                break;
            case 0:
                cout << "Keluar dari program\n";
                break;
            default:
                cout << "Hanya masukkan angka yang ada pada menu helpdesk\n";
        }
    } while(n != 0);
}
