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
void cariDataPasien(Data_Pasien* dataPasien, int* count);
void clearInputBuffer();

int main() {
    // Load data pasien dari file CSV
    int sizeDataPasien;
    Data_Pasien* dataPasien = readDataPasien("Data Pasien.csv", &sizeDataPasien);
    cariDataPasien(dataPasien, &sizeDataPasien);
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

void cariDataPasien(Data_Pasien* dataPasien, int* count) {
    char nama_pasien[50];
    printf("Masukkan nama pasien yang ingin dicari! ");
    fflush(stdout);

    // int c;
    // int i = 0;
    // while ((c = getchar()) != '\n' && c != EOF) {
    //     nama_pasien[i++] = c;
    // }
    // nama_pasien[i] = '\0';

    Data_Pasien* foundPasien = NULL;
    for (int i = 0; i < *count; i++) {
        if (strcmp(dataPasien[i].Nama_Lengkap, nama_pasien) == 0) {
            foundPasien = &dataPasien[i];
            break;
        }
    }

    if (foundPasien) {
        printf("Data pasien ditemukan: %s\n", foundPasien->Nama_Lengkap);
        printf("No.: %d| Nama Lengkap: %s| Alamat: %s| Kota: %s| Tempat Lahir: %s| Tanggal Lahir: %s| Umur: %d| No. BPJS: %lld| ID Pasien: %s\n",
         foundPasien->No, foundPasien->Nama_Lengkap, foundPasien->Alamat, foundPasien->Kota, foundPasien->Tempat_Lahir, foundPasien->Tanggal_Lahir, 
         foundPasien->Umur, foundPasien->No_BPJS, foundPasien->ID_Pasien);
    } else {
        printf("Data pasien tidak ditemukan\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}