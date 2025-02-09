/*
	Program		: ATM_Sederhana.c
	Author		: - Rizky Khairunisa/2450081093
				  - Mutia Nur Safiqa/2450081092
				  - Rara Winasti Hanifa Agistini/2450081096
				  - Dhela Junita Ananda/2450081113
	Kelas		: D
	Deskripsi	: Tugas Besar Menentukan ATM Sederhana
				  Diketahui ada 2 user, user sebagai nasabah dan user sebagai operator.
				  Setiap user berinteraksi dengan sistem ATM, yaitu input username, 
				  kode user dan PIN. Menu yang muncul tergantung kategori masing-masing user.
	Tanggal		: 27 Desember 2024
*/

// Preprocessor
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Tipe bentukan untuk ATM
typedef struct { 
    char username[20];
    char code[20];
    char pin[10];
    int saldo;
    int lembar100k, lembar50k, lembar20k, lembar10k, lembar5k; // Jumlah lembar    
    char riwayatTransaksi[10][100];
    int jumlahTransaksi;
    int stockUang[5]; 
	} ATM;

// Prototype
void clearScreen();
void menuUtama(ATM *atm);
void loginNasabah(ATM *atm);
void loginOperator(ATM *atm);
void menuNasabah(ATM *atm);
void menuOperator(ATM *atm);
void cekSaldo(ATM *atm);
void tarikTunai(ATM *atm);
void cetakTransaksi(ATM *atm, int Operator);
void tambahSaldoATM(ATM *atm);
void endProgram();

// Main Driver
int main() {
	// Kamus
    ATM atm = {"nasabah", "user123", "245008", 5000000, 10, 20, 50, 100, 200};
    
    // Algoritma
    menuUtama(&atm);
    
    return 0;
}

// Realisasi Prototype

void clearScreen() {	// Fungsi membersihkan layar
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux/MacOS
    #endif
}

// Menu Utama
void menuUtama(ATM *atm) {
    int pilihan;
	clearScreen();
    printf("========================\n");
    printf("===     ATM MENU    ===\n");
    printf("========================\n\n");
    printf("1. Login Nasabah\n");
    printf("2. Login Operator\n");
    printf("3. Keluar\n\n");
    printf("Pilih menu: ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        loginNasabah(atm);
    } else if (pilihan == 2) {
    	loginOperator(atm);
	} else if (pilihan == 3) {
		endProgram();
	} else {
		printf("\n!! Pilihan tidak valid !!\n");
        printf("\nTekan Enter untuk mencoba lagi..");
        getchar();
        getchar();
        menuUtama(atm);	
	}
}

// Login nasabah
void loginNasabah(ATM *atm) {
    char username[20], code[20], pinInput[10];
    clearScreen();
    printf("=== LOGIN NASABAH ===\n\n");
    printf("> Masukkan Username: ");
    scanf("%s", username);
    printf("> Masukkan Code: ");
    scanf("%s", code);

    if (strcmp(username, atm->username) == 0 && strcmp(code, atm->code) == 0) {
    	printf("\n\n=== INPUT PIN ===\n");
        printf("\n> Masukkan PIN: ");
        scanf("%s", pinInput);

        if (strcmp(pinInput, atm->pin) == 0) {
            printf("\n=== Login berhasil! ===\n\n");
            printf("Tekan Enter untuk melanjutkan..");
            getchar();
            getchar();
            menuNasabah(atm);
        } else {
            printf("\n!! PIN salah !!\n\n-- Program keluar --\n");
            exit(0);
        }
    } else {
        printf("\n!! Username atau Code salah !!\n");
        printf("\nTekan Enter untuk mencoba lagi..");
        getchar();
        getchar();
        loginNasabah(atm);
    }
}

// Menu nasabah
void menuNasabah(ATM *atm) {
    int pilihan;
    clearScreen();
    printf("=== MENU NASABAH ===\n\n");
    printf("1. CEK SALDO\n");
    printf("2. TARIK TUNAI\n");
    printf("3. CETAK TRANSAKSI\n");
    printf("4. MENU UTAMA\n");
    printf("5. KELUAR\n\n");
    printf("Pilih menu: ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        cekSaldo(atm);
	} else if ( pilihan == 2) {
		tarikTunai(atm);
	} else if (pilihan == 3) {
		cetakTransaksi(atm, 0); // Argumen 0 untuk nasabah
	} else if (pilihan == 4) {
		menuUtama(atm);
	} else if (pilihan == 5) {
		endProgram();
	} else {
        printf("\n!! Pilihan tidak valid !!\n");
        printf("\nTekan Enter untuk mencoba lagi..");
        getchar();
        getchar();
        menuNasabah(atm);
    }
}

// Login operator
void loginOperator(ATM *atm) {
    char username[20], code[20];
    clearScreen();
    printf("=== LOGIN OPERATOR ===\n\n");
    printf("> Masukkan Username: ");
    scanf("%s", username);
    printf("> Masukkan Code: ");
    scanf("%s", code);

    if (strcmp(username, "operator") == 0 && strcmp(code, "admin123") == 0) {
        printf("\n=== Login berhasil! ===\n\n");
        printf("Tekan Enter untuk melanjutkan..");
        getchar();
    	getchar();
        menuOperator(atm);
    } else {
        printf("!! Username atau code salah !!\n");
        printf("\nTekan Enter untuk mencoba lagi..");
        getchar();
        getchar();
        loginOperator(atm);
    }
}

// Menu operator
void menuOperator(ATM *atm) {
    int pilihan;
    clearScreen();
    printf("=== MENU OPERATOR ===\n\n");
    printf("1. TAMBAH SALDO ATM\n");
    printf("2. LIHAT TRANSAKSI NASABAH\n");
    printf("3. MENU UTAMA\n");
    printf("4. KELUAR\n\n");
    printf("Pilih menu: ");
    scanf("%d", &pilihan);
	
	clearScreen();
    if (pilihan == 1) {
        tambahSaldoATM(atm);
	} else if (pilihan == 2){
		cetakTransaksi(atm, 1);
	} else if (pilihan == 3) {
		menuUtama(atm);
	} else if (pilihan == 4) {
		endProgram();
	} else {
		printf("\nPilihan tidak valid.\n");
        printf("\nTekan Enter untuk mencoba lagi..");
        getchar();            
        getchar();
        menuOperator(atm);
    }
}

// Tambah saldo ATM
void tambahSaldoATM(ATM *atm) {
    int pecahan[5] = {100000, 50000, 20000, 10000, 5000}; // Hanya 5 jenis pecahan yang didukung
    int jumlah, i;
    clearScreen();
    printf("=== TAMBAH SALDO ATM ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("> Masukkan jumlah lembar untuk pecahan Rp %d: ", pecahan[i]);
        scanf("%d", &jumlah);

        if (pecahan[i] == 100000) {
            atm->lembar100k += jumlah;
        } else if (pecahan[i] == 50000) {
            atm->lembar50k += jumlah;
        } else if (pecahan[i] == 20000) {
            atm->lembar20k += jumlah;
        } else if (pecahan[i] == 10000) {
            atm->lembar10k += jumlah;
		} else {
			atm->lembar5k += jumlah;
		}
        atm->saldo += jumlah * pecahan[i];
    }

    printf("\n=== Saldo berhasil ditambahkan ===\n\n");
    printf("Tekan Enter untuk melihat rincian saldo..");
    getchar();
    getchar();
    
    clearScreen();
    printf("* Rincian Total saldo: Rp %d\n", atm->saldo);
    printf("---------------------------------");
    printf("\n| Pecahan\t| Jumlah\t|");
    printf("\n---------------------------------\n");
    printf("| Rp 100.000	| %d lembar\t|\n", atm->lembar100k);
    printf("| Rp 50.000	| %d lembar\t|\n", atm->lembar50k);
    printf("| Rp 20.000	| %d lembar\t|\n", atm->lembar20k);
    printf("| Rp 10.000	| %d lembar\t|\n", atm->lembar10k);
    printf("| Rp 5.000	| %d lembar\t|\n", atm->lembar5k);
	 printf("---------------------------------\n");
	
    printf("\nTekan Enter untuk kembali..");
    getchar();
    getchar();
    menuOperator(atm);
}

// Cek saldo
void cekSaldo(ATM *atm) {
    clearScreen();
    printf("=== CEK SALDO ===\n\n");
    printf("Saldo Anda: Rp %d\n\n", atm->saldo);
    printf("* Rincian uang yang tersedia:\n");
    printf("---------------------------------");
    printf("\n| Pecahan\t| Jumlah\t|");
    printf("\n---------------------------------\n");
    printf("| Rp 100.000	| %d lembar\t|\n", atm->lembar100k);
    printf("| Rp 50.000	| %d lembar\t|\n", atm->lembar50k);
    printf("| Rp 20.000	| %d lembar\t|\n", atm->lembar20k);
    printf("| Rp 10.000	| %d lembar\t|\n", atm->lembar10k);
    printf("| Rp 5.000	| %d lembar\t|\n", atm->lembar5k);
    printf("---------------------------------\n");
    
    printf("\nTekan Enter untuk kembali..");
    getchar();
    getchar();
    menuNasabah(atm);
}

// Tarik tunai
void tarikTunai(ATM *atm) {
    int i, nominal, sisa;
    char transaksi[100];
    int lembar100k, lembar50k, lembar20k, lembar10k, lembar5k;
    clearScreen();
    printf("> Masukkan jumlah penarikan (kelipatan 5.000): ");
    scanf("%d", &nominal);

    if (nominal > atm->saldo) {
        printf("\n!! Saldo tidak mencukupi !!\n");
    } else if (nominal % 5000 != 0) {
        printf("\n - Nominal harus kelipatan Rp 5.000 -\n");
    } else {
        sisa = nominal;
        lembar100k = sisa / 100000;
        if (lembar100k > atm->lembar100k) {
            lembar100k = atm->lembar100k;
        }	sisa -= lembar100k * 100000;

        lembar50k = sisa / 50000;
        if (lembar50k > atm->lembar50k) {
            lembar50k = atm->lembar50k;
        }	sisa -= lembar50k * 50000;

        lembar20k = sisa / 20000;
        if (lembar20k > atm->lembar20k) {
            lembar20k = atm->lembar20k;
        }	sisa -= lembar20k * 20000;
        
        lembar10k = sisa / 10000;
        if (lembar10k > atm->lembar10k) {
        	lembar10k = atm->lembar10k;
		}	sisa -= lembar10k * 10000;
		
		lembar5k = sisa / 5000;
		if (lembar5k > atm->lembar5k) {
			lembar5k = atm->lembar5k;
		}	sisa -= lembar5k * 5000;

        if (sisa == 0) {
            atm->saldo -= nominal;
            atm->lembar100k -= lembar100k;
            atm->lembar50k -= lembar50k;
            atm->lembar20k -= lembar20k;
            atm->lembar10k -= lembar10k;
            atm->lembar5k -= lembar5k;

            printf("\n=== Penarikan berhasil! ===\n\n");
            printf("* Rincian Uang yang ditarik: \n");
            printf("---------------------------------");
   			printf("\n| Pecahan\t| Jumlah\t|");
    		printf("\n---------------------------------\n");
		    printf("| Rp 100.000	| %d lembar\t|\n", lembar100k);
		    printf("| Rp 50.000	| %d lembar\t|\n", lembar50k);
		    printf("| Rp 20.000	| %d lembar\t|\n", lembar20k);
		    printf("| Rp 10.000	| %d lembar\t|\n", lembar10k);
		    printf("| Rp 5.000	| %d lembar\t|\n", lembar5k);
		    printf("---------------------------------\n");
		    
            printf("\n==| Sisa saldo: Rp %d |==\n", atm->saldo);
            printf("\n* Rincian uang yang tersedia:\n");
		    printf("---------------------------------");
		    printf("\n| Pecahan\t| Jumlah\t|");
		    printf("\n---------------------------------\n");
		    printf("| Rp 100.000	| %d lembar\t|\n", atm->lembar100k);
		    printf("| Rp 50.000	| %d lembar\t|\n", atm->lembar50k);
		    printf("| Rp 20.000	| %d lembar\t|\n", atm->lembar20k);
		    printf("| Rp 10.000	| %d lembar\t|\n", atm->lembar10k);
		    printf("| Rp 5.000	| %d lembar\t|\n", atm->lembar5k);
		    printf("---------------------------------\n");

            // Tambahkan transaksi ke riwayat
            sprintf(transaksi, " | Rp %d\t|", nominal);
            if (atm->jumlahTransaksi < 10) {
                strcpy(atm->riwayatTransaksi[atm->jumlahTransaksi], transaksi);
                atm->jumlahTransaksi++;
            } else {
                for (i = 1; i < 10; i++) { // Variabel 'i' digunakan di luar for
                    strcpy(atm->riwayatTransaksi[i - 1], atm->riwayatTransaksi[i]);
                }
                strcpy(atm->riwayatTransaksi[9], transaksi);
            }
        } else {
            printf("Penarikan gagal! Lembar uang tidak mencukupi.\n");
        }
    }

    printf("\nTekan Enter untuk kembali..");
    getchar();
    getchar();
    menuNasabah(atm);
}

// Cetak transaksi
void cetakTransaksi(ATM *atm, int Operator) {
    int i; // Deklarasi variabel di luar loop
    clearScreen();
    printf("=== RIWAYAT TRANSAKSI ===\n\n");
    printf("--- Tarik Tunai ---\n");
    printf("-------------------------\n");
    printf("| No. | Nominal\t\t|\n");
    printf("-------------------------\n");
    if (atm->jumlahTransaksi == 0) {
        printf("\n!! Belum ada transaksi !!\n");
    } else {
        for (i = 0; i < atm->jumlahTransaksi; i++) {
            printf("| %d. %s\n", i + 1, atm->riwayatTransaksi[i]);
            printf("-------------------------\n");
        }
    }
    printf("\nTekan Enter untuk kembali..");
    getchar(); // Mengambil input tambahan
    getchar(); // Mengambil tombol input

    // Kembali ke menu sesuai dengan pengguna
    if (Operator) {
        menuOperator(atm);
    } else {
        menuNasabah(atm);
    }
}

// Mengakhiri program
void endProgram() {
	clearScreen();
    printf("- Terima kasih telah menggunakan program ini -\n");
    exit(0);
}

