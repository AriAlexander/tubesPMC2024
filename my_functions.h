#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

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

typedef struct {
    int No;
    char Tanggal[20];
    char ID_Pasien[20];
    char Diagnosis[50];
    char Tindakan[50];
    char Kontrol[20];
    double Biaya;
} Riwayat_Medis_Pasien;

Data_Pasien *readDataPasien(const char* filename, int* count);
char* hapusDataPasien(int n, Data_Pasien* dataPasien, int *count);
char* cariDataPasien(char name[], Data_Pasien *data_pasien, int *count);
void tulisDataPasien(const char* filename, Data_Pasien* dataPasien, int count);
void tulisRiwayatMedisPasien(const char* fileName, Riwayat_Medis_Pasien* riwayatMedisPasien, int count);

#endif