#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MOBIL 4
#define MAX_RUTE 4
#define MAX_DATE 11
#define FILENAME "pemakaian.txt"

int generateRandomID() {
    return rand();
}

void checkAvailability(char mobil[MAX_MOBIL][20], char rute[MAX_RUTE][20], int tarif[MAX_MOBIL][MAX_RUTE], int pemakaianID[100], char pemakaianMobil[100][20], char pemakaianDate[100][MAX_DATE], char pemakaianRute[100][20], int pemakaianTarif[100], int pemakaianUsage[100], int *nPemakaian) {
    char mobilChoice[20];
    char date[MAX_DATE];

    // Memasukkan tanggal pemesanan
    printf("Masukkan tanggal pemesanan (format YYYY-MM-DD): ");
    scanf(" %10[^\n]", date);
    getchar();

    // Memasukkan jenis mobil
    printf("Pilih jenis mobil:\n");
    for (int i = 0; i < MAX_MOBIL; i++) {
        printf("%d. %s\n", i + 1, mobil[i]);
    }
    printf("Pilihan: ");
    int mobilIndex;
    scanf("%d", &mobilIndex);

    if (mobilIndex < 1 || mobilIndex > MAX_MOBIL) {
        printf("Pilihan mobil tidak valid.\n");
        return;
    }

    strcpy(mobilChoice, mobil[mobilIndex - 1]);

    // Cek ketersediaan mobil pada tanggal tertentu
    int available = 1;
    for (int i = 0; i < *nPemakaian; i++) {
        if (strcmp(pemakaianMobil[i], mobilChoice) == 0 && strcmp(pemakaianDate[i], date) == 0) {
            available = 0;
            break;
        }
    }

    if (available) {
        printf("Mobil jenis %s tersedia pada tanggal %s.\n", mobilChoice, date);

        // Jika mobil tersedia, lanjutkan dengan meminta pemilihan rute
        printf("Pilih rute:\n");
        for (int i = 0; i < MAX_RUTE; i++) {
            printf("%d. %s\n", i + 1, rute[i]);
        }

        // Memasukkan pilihan rute
        printf("Pilihan rute: ");
        int ruteIndex;
        scanf("%d", &ruteIndex);

        if (ruteIndex < 1 || ruteIndex > MAX_RUTE) {
            printf("Pilihan rute tidak valid.\n");
            return;
        }

        // Menampilkan tarif sesuai dengan rute yang dipilih
        int tarifValue = tarif[mobilIndex - 1][ruteIndex - 1];
        printf("Tarif untuk mobil jenis %s dengan rute %s pada tanggal %s adalah %d.\n",
               mobilChoice, rute[ruteIndex - 1], date, tarifValue);

        // Menyimpan data pemakaian ke dalam array pemakaian
        pemakaianID[*nPemakaian] = generateRandomID();
        strcpy(pemakaianMobil[*nPemakaian], mobilChoice);
        strcpy(pemakaianDate[*nPemakaian], date);
        strcpy(pemakaianRute[*nPemakaian], rute[ruteIndex - 1]);
        pemakaianTarif[*nPemakaian] = tarifValue;

        // Menggunakan nilai acak sebagai jumlah pemakaian
        pemakaianUsage[*nPemakaian] = rand() % 10 + 1;

        // Menampilkan dan menyimpan data pemakaian ke dalam file
        printf("Id Pemakaian Anda Adalah: %d\n", pemakaianID[*nPemakaian]);

        FILE *file = fopen(FILENAME, "a");
        if (file == NULL) {
            printf("Gagal membuka file.\n");
            return;
        }

        fprintf(file, "%d %s %s %s %d %d\n", pemakaianID[*nPemakaian], mobilChoice, date, rute[ruteIndex - 1], pemakaianTarif[*nPemakaian], pemakaianUsage[*nPemakaian]);

        (*nPemakaian)++;
        fclose(file);
    } else {
        printf("Mobil jenis %s tidak tersedia pada tanggal %s.\n", mobilChoice, date);
        printf("Coba pesan pada tanggal yang berbeda atau pilih mobil yang lain :)\n");
    }
}

int main() {
    srand(time(NULL)); // Inisialisasi generator angka acak dengan waktu saat ini

    char mobil[MAX_MOBIL][20] = {"L-300", "Innova", "Mini Bus", "Bus"};
    char rute[MAX_RUTE][20] = {"Del-Porsea", "Del-Balige", "Del-Siborong2", "Del-Tarutung"};
    int tarif[MAX_MOBIL][MAX_RUTE] = {
        {30000, 30000, 50000, 100000},
        {30000, 30000, 50000, 100000},
        {50000, 50000, 100000, 150000},
        {50000, 50000, 150000, 200000}
    };
    int pemakaianID[100];
    char pemakaianMobil[100][20];
    char pemakaianDate[100][MAX_DATE];
    char pemakaianRute[100][20];
    int pemakaianTarif[100];
    int pemakaianUsage[100];
    int nPemakaian = 0;

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Lakukan Pemesanan\n");
        printf("2. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkAvailability(mobil, rute, tarif, pemakaianID, pemakaianMobil, pemakaianDate, pemakaianRute, pemakaianTarif, pemakaianUsage, &nPemakaian);
                break;
            case 2:
                printf("Terima kasih:)\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 2);

    return 0;
}