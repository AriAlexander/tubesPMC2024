#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Maksimal jumlah pasien yang bisa di-load
#define MAX_PASIEN 100

// Struktur untuk menyimpan data pasien
typedef struct {
    int No;
    char Nama_Lengkap[50];
    char Alamat[100];
    char Kota[50];
    char Tempat_Lahir[50];
    char Tanggal_Lahir[30];
    int Umur;
    long long No_BPJS;
    char ID_Pasien[20];
} Data_Pasien;

Data_Pasien* readDataPasien(const char* filename, int* count);
void hapusDataPasien(Data_Pasien* dataPasien, int* count);

int main() {
    // Load data pasien dari file CSV
    int sizeDataPasien;
    Data_Pasien* dataPasien = readDataPasien("Data Pasien.csv", &sizeDataPasien);
    hapusDataPasien(dataPasien, &sizeDataPasien);
    return 0;
}

// Fungsi untuk membaca file CSV "Data Pasien.csv"
Data_Pasien* readDataPasien(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    Data_Pasien* dataPasien = (Data_Pasien*)malloc(sizeof(Data_Pasien) * MAX_PASIEN);
    *count = 0;

    char line[1024];
    fgets(line, 1024, file); // skip header
    while (fgets(line, 1024, file)) {
        char* token = strtok(line, ";");
        Data_Pasien pasien;
        if (token) pasien.No = atoi(token);
        token = strtok(NULL, ";");
        if (token) strncpy(pasien.Nama_Lengkap, token, sizeof(pasien.Nama_Lengkap) - 1);
        token = strtok(NULL, ";");
        if (token) strncpy(pasien.Alamat, token, sizeof(pasien.Alamat) - 1);
        token = strtok(NULL, ";");
        if (token) strncpy(pasien.Kota, token, sizeof(pasien.Kota) - 1);
        token = strtok(NULL, ";");
        if (token) strncpy(pasien.Tempat_Lahir, token, sizeof(pasien.Tempat_Lahir) - 1);
        token = strtok(NULL, ";");
        if (token) strncpy(pasien.Tanggal_Lahir, token, sizeof(pasien.Tanggal_Lahir) - 1);
        token = strtok(NULL, ";");
        if (token) pasien.Umur = atoi(token);
        token = strtok(NULL, ";");
        if (token) pasien.No_BPJS = atoll(token);
        token = strtok(NULL, "\n");
        if (token) strncpy(pasien.ID_Pasien, token, sizeof(pasien.ID_Pasien) - 1);

        // Ensure null-termination
        pasien.Nama_Lengkap[sizeof(pasien.Nama_Lengkap) - 1] = '\0';
        pasien.Alamat[sizeof(pasien.Alamat) - 1] = '\0';
        pasien.Kota[sizeof(pasien.Kota) - 1] = '\0';
        pasien.Tempat_Lahir[sizeof(pasien.Tempat_Lahir) - 1] = '\0';
        pasien.Tanggal_Lahir[sizeof(pasien.Tanggal_Lahir) - 1] = '\0';
        pasien.ID_Pasien[sizeof(pasien.ID_Pasien) - 1] = '\0';

        dataPasien[(*count)++] = pasien;
    }

    fclose(file);
    return dataPasien;
}

void hapusDataPasien(Data_Pasien* dataPasien, int* count) {
    int no_pasien;
    printf("Masukkan nomor pasien yang ingin dihapus datanya! ");
    scanf("%d", &no_pasien);

    int i;
    for (i = 0; i < *count; i++) {
        if (dataPasien[i].No == no_pasien) {
            char nama_pasien[50] = "";
            strcpy(nama_pasien, dataPasien[i].Nama_Lengkap);

            // Shift elements to the left
            for (int j = i; j < *count - 1; j++) {
                dataPasien[j] = dataPasien[j + 1];
            }
            (*count)--;
            printf("Data pasien nomor %d dengan nama %s telah dihapus.", no_pasien, nama_pasien);
            return;
        }
    }
    printf("Data pasien tidak ditemukan\n");
}