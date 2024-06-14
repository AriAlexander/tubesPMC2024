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

// Struktur untuk menyimpan riwayat medis pasien
typedef struct {
    int No;
    char Tanggal[20];
    char ID_Pasien[20];
    char Diagnosis[50];
    char Tindakan[50];
    char Kontrol[20];
    double Biaya;
} Riwayat_Medis_Pasien;

// Struktur untuk menyimpan rincian biaya tindakan
typedef struct {
    int No;
    char Aktivitas[50];
    double Biaya;
} Biaya_Tindakan;

// Deklarasi fungsi-fungsi
Data_Pasien* readDataPasien(const char* filename, int* count);
Riwayat_Medis_Pasien* readRiwayatMedis(const char* filename, int* count);
Biaya_Tindakan* readBiayaTindakan(const char* filename, int* count);
void tampilkanMenuUtama();
void tampilkanDataPasien(Data_Pasien* dataPasien, int count);
void tampilkanRiwayatMedis(Riwayat_Medis_Pasien* dataRiwayatMedi, int count);
void tampilkanBiayaTindakan(Biaya_Tindakan* biayaTindakan, int count);
void clearInputBuffer();
void addData(Data_Pasien* data, int* count);
void modifyData(Data_Pasien* data, int count);
void saveData(char* filename, Data_Pasien* data, int count);
void hapusDataPasien(Data_Pasien* dataPasien, int* count);
void cariDataPasien(Data_Pasien* dataPasien, int count);
void tambahRiwayatMedis(Riwayat_Medis_Pasien* riwayatMedis, int* count);
void ubahRiwayatMedis(Riwayat_Medis_Pasien* riwayatMedis, int count);
void hapusRiwayatMedis();
void cariRiwayatMedis();
void laporanKeuangan(Riwayat_Medis_Pasien *riwayatMedisPasien, int sizeRiwayatMedis);
void analisisPasienPenyakit();
void informasiKontrolPasien();
void tulisDataPasien(const char* filename, Data_Pasien* dataPasien, int count);
void tulisRiwayatMedisPasien(const char* fileName, Riwayat_Medis_Pasien* riwayatMedisPasien, int count);

int main() {
    // Load data pasien dari file CSV
    char* filename = "Data Pasien.csv";
    int sizeDataPasien, sizeRiwayatMedis, sizeBiayaTindakan;
    Data_Pasien* dataPasien = readDataPasien("Data Pasien.csv", &sizeDataPasien);
    Riwayat_Medis_Pasien* riwayatMedisPasien = readRiwayatMedis("Riwayat Datang, Diagnosis, dan Tindakan.csv", &sizeRiwayatMedis);    
    Biaya_Tindakan* biayaTindakan = readBiayaTindakan("Biaya Tindakan.csv", &sizeBiayaTindakan);

    int pilihan;
    while (1) {
        tampilkanMenuUtama();
        printf("Masukkan pilihan fitur yang ingin digunakan: ");
        scanf("%d", &pilihan);
        getchar();
        printf("\n");

        switch (pilihan) {
            case 1:
                tampilkanDataPasien(dataPasien, sizeDataPasien);
                break;
            case 2:
                tampilkanRiwayatMedis(riwayatMedisPasien, sizeRiwayatMedis);
                break;
            case 3:
                tampilkanBiayaTindakan(biayaTindakan, sizeBiayaTindakan);
            case 4:
                addData(dataPasien, &sizeDataPasien);
                saveData(filename, dataPasien, sizeDataPasien);
                break;
            case 5:
                modifyData(dataPasien, sizeDataPasien);
                saveData(filename, dataPasien, sizeDataPasien);
                break;
            case 6:
                hapusDataPasien(dataPasien, &sizeDataPasien);
                break;
            case 7:
                cariDataPasien(dataPasien, sizeDataPasien);
                break;
            case 8:
                tambahRiwayatMedis(riwayatMedisPasien, &sizeRiwayatMedis);
                break;
            case 9:
                ubahRiwayatMedis(riwayatMedisPasien, sizeRiwayatMedis);
                break;
            case 10:
                hapusRiwayatMedis();
                break;
            case 11:
                cariRiwayatMedis();
                break;
            case 12:
                laporanKeuangan(riwayatMedisPasien, sizeRiwayatMedis);
                break;
            case 13:
                analisisPasienPenyakit();
                break;
            case 14:
                informasiKontrolPasien();
                break;
            case 15:
                tulisDataPasien("Data Pasien.csv", dataPasien, sizeDataPasien);
                tulisRiwayatMedisPasien("Riwayat Datang, Diagnosis, dan Tindakan.csv", riwayatMedisPasien, sizeRiwayatMedis);
                free(dataPasien);
                free(riwayatMedisPasien);
                printf("Terima kasih telah menggunakan aplikasi ini.\n");
                free(dataPasien);
                exit(0);
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
    return 0;
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenuUtama() {
    printf("\n");
    printf("=== Sistem Pencatatan Pasien Klinik X ===\n");
    printf("\n");
    printf("Selamat datang! Berikut adalah rincian fitur yang dapat digunakan:\n");
    printf("1. Tampilkan Data Pasien\n");
    printf("2. Tampilkan Riwayat Medis Pasien\n");
    printf("3. Tampilkan Rincian Biaya Tindakan\n");
    printf("4. Tambah Data Pasien\n");
    printf("5. Ubah Data Pasien\n");
    printf("6. Hapus Data Pasien\n");
    printf("7. Cari Data Pasien\n");
    printf("8. Tambah Riwayat Medis\n");
    printf("9. Ubah Riwayat Medis\n");
    printf("10. Hapus Riwayat Medis\n");
    printf("11. Cari Riwayat Medis\n");
    printf("12. Laporan Keuangan\n");
    printf("13. Analisis Pasien dan Penyakit\n");
    printf("14. Informasi Kontrol Pasien\n");
    printf("15. Keluar\n");
    printf("\n");
}

// Placeholder functions for other features (need implementation)

// Fungsi untuk menampilkan data pasien
void tampilkanDataPasien(Data_Pasien* dataPasien, int sizeDataPasien) {
    printf("=== Data Pasien ===\n");
    for (int i = 0; i < sizeDataPasien; i++) {
        printf("No.: %d | Nama Lengkap: %s | Alamat: %s | Kota: %s | Tempat Lahir: %s | Tanggal Lahir: %s | Umur: %d | No. BPJS: %lld | ID Pasien: %s\n",
         dataPasien[i].No, dataPasien[i].Nama_Lengkap, dataPasien[i].Alamat, dataPasien[i].Kota, dataPasien[i].Tempat_Lahir, dataPasien[i].Tanggal_Lahir,
          dataPasien[i].Umur, dataPasien[i].No_BPJS, dataPasien[i].ID_Pasien);
    }
}

// Fungsi untuk menampilkan riwayat medis pasien
void tampilkanRiwayatMedis(Riwayat_Medis_Pasien* riwayatMedisPasien, int sizeRiwayatMedis) {
    printf("=== Riwayat Medis Pasien ===\n");
    for (int i = 0; i < sizeRiwayatMedis; i++) {
        printf("No.: %d | Tanggal: %s | ID Pasien: %s | Diagnosis: %s | Tindakan: %s | Kontrol: %s | Biaya (Rp): %.2lf\n", 
        riwayatMedisPasien[i].No, riwayatMedisPasien[i].Tanggal, riwayatMedisPasien[i].ID_Pasien, riwayatMedisPasien[i].Diagnosis, riwayatMedisPasien[i].Tindakan, 
        riwayatMedisPasien[i].Kontrol, riwayatMedisPasien[i].Biaya);
    }
}

// Fungsi untuk menampilkan rincian biaya tindakan
void tampilkanBiayaTindakan(Biaya_Tindakan* biayaTindakanPasien, int sizeBiayaTindakan) {
    printf("=== Rincian Biaya Tindakan ===\n");
    for (int i = 0; i < sizeBiayaTindakan; i++) {
        printf("No.: %d | Aktivitas: %s | Biaya (Rp): %.2lf\n", biayaTindakanPasien[i]. No, biayaTindakanPasien[i].Aktivitas, biayaTindakanPasien[i].Biaya);
    }
}

// Fungsi untuk membersihkan buffer input
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

// Fungsi untuk membaca file CSV "Riwayat Medis Pasien.csv"
Riwayat_Medis_Pasien* readRiwayatMedis(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    Riwayat_Medis_Pasien* riwayatMedis = (Riwayat_Medis_Pasien*)malloc(sizeof(Riwayat_Medis_Pasien) * MAX_PASIEN);
    *count = 0;

    char line[1024];
    fgets(line, 1024, file); // skip header
    while (fgets(line, 1024, file)) {
        char* token = strtok(line, ";");
        Riwayat_Medis_Pasien riwayat;
        riwayat.No = atoi(token);
        token = strtok(NULL, ";");
        strcpy(riwayat.Tanggal, token);
        token = strtok(NULL, ";");
        strcpy(riwayat.ID_Pasien, token);
        token = strtok(NULL, ";");
        strcpy(riwayat.Diagnosis, token);
        token = strtok(NULL, ";");
        strcpy(riwayat.Tindakan, token);
        token = strtok(NULL, ";");
        strcpy(riwayat.Kontrol, token);
        token = strtok(NULL, "\n");
        riwayat.Biaya = atof(token);

        riwayatMedis[(*count)++] = riwayat;
    }

    fclose(file);
    return riwayatMedis;
}

// Fungsi untuk membaca file CSV "Biaya Tindakan.csv"
Biaya_Tindakan* readBiayaTindakan(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    Biaya_Tindakan* biayaTindakan = (Biaya_Tindakan*)malloc(sizeof(Biaya_Tindakan) * MAX_PASIEN); // allocate memory for 100 records
    *count = 0;

    char line[1024];
    fgets(line, 1024, file); // skip header
    while (fgets(line, 1024, file)) {
        char* token = strtok(line, ";");
        Biaya_Tindakan biaya;
        biaya.No = atoi(token);
        token = strtok(NULL, ";");
        strcpy(biaya.Aktivitas, token);
        token = strtok(NULL, "\n");
        biaya.Biaya = atof(token);

        biayaTindakan[(*count)++] = biaya;
    }

    fclose(file);
    return biayaTindakan;
} // test

// Awal Bagian Dhika
// Function to add data to the array
void addData(Data_Pasien* data, int* count) {
    if (*count < MAX_PASIEN) {
        data[*count].No = *count + 1;

        printf("Enter Nama Lengkap: ");
        fgets(data[*count].Nama_Lengkap, sizeof(data[*count].Nama_Lengkap), stdin);
        data[*count].Nama_Lengkap[strcspn(data[*count].Nama_Lengkap, "\n")] = 0;  // remove trailing newline

        printf("Enter Alamat: ");
        fgets(data[*count].Alamat, sizeof(data[*count].Alamat), stdin);
        data[*count].Alamat[strcspn(data[*count].Alamat, "\n")] = 0;  // remove trailing newline

        printf("Enter Kota: ");
        fgets(data[*count].Kota, sizeof(data[*count].Kota), stdin);
        data[*count].Kota[strcspn(data[*count].Kota, "\n")] = 0;  // remove trailing newline

        printf("Enter Tempat Lahir: ");
        fgets(data[*count].Tempat_Lahir, sizeof(data[*count].Tempat_Lahir), stdin);
        data[*count].Tempat_Lahir[strcspn(data[*count].Tempat_Lahir, "\n")] = 0;  // remove trailing newline

        printf("Enter Tanggal Lahir: ");
        fgets(data[*count].Tanggal_Lahir, sizeof(data[*count].Tanggal_Lahir), stdin);
        data[*count].Tanggal_Lahir[strcspn(data[*count].Tanggal_Lahir, "\n")] = 0;  // remove trailing newline

        printf("Enter Umur (th): ");
        char temp[50];
        fgets(temp, sizeof(temp), stdin);
        sscanf(temp, "%d", &data[*count].Umur);

        printf("Enter No BPJS: ");
        char temp2[50];
        fgets(temp2, sizeof(temp2), stdin);
        sscanf(temp2, "%lld", &data[*count].No_BPJS);

        printf("Enter ID Pasien: ");
        fgets(data[*count].ID_Pasien, sizeof(data[*count].ID_Pasien), stdin);
        data[*count].ID_Pasien[strcspn(data[*count].ID_Pasien, "\n")] = 0;  // remove trailing newline

        (*count)++;
    } else {
        printf("The array is full.\n");
    }
}

// Function to modify data in the array
void modifyData(Data_Pasien* data, int count) {
    char name[50];

    printf("Enter the name of the data to modify: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  // remove trailing newline

    for (int i = 0; i < count; i++) {
        if (strcmp(data[i].Nama_Lengkap, name) == 0) {
            printf("Enter new data:\n");

            printf("Enter Nama Lengkap: ");
            fgets(data[i].Nama_Lengkap, sizeof(data[i].Nama_Lengkap), stdin);
            data[i].Nama_Lengkap[strcspn(data[i].Nama_Lengkap, "\n")] = 0;  // remove trailing newline

            printf("Enter Alamat: ");
            fgets(data[i].Alamat, sizeof(data[i].Alamat), stdin);
            data[i].Alamat[strcspn(data[i].Alamat, "\n")] = 0;  // remove trailing newline

            printf("Enter Kota: ");
            fgets(data[i].Kota, sizeof(data[i].Kota), stdin);
            data[i].Kota[strcspn(data[i].Kota, "\n")] = 0;  // remove trailing newline

            printf("Enter Tempat Lahir: ");
            fgets(data[i].Tempat_Lahir, sizeof(data[i].Tempat_Lahir), stdin);
            data[i].Tempat_Lahir[strcspn(data[i].Tempat_Lahir, "\n")] = 0;  // remove trailing newline

            printf("Enter Tanggal Lahir: ");
            fgets(data[i].Tanggal_Lahir, sizeof(data[i].Tanggal_Lahir), stdin);
            data[i].Tanggal_Lahir[strcspn(data[i].Tanggal_Lahir, "\n")] = 0;  // remove trailing newline

            printf("Enter Umur (th): ");
            char temp[50];
            fgets(temp, sizeof(temp), stdin);
            sscanf(temp, "%d", &data[i].Umur);

            printf("Enter No BPJS: ");
            char temp2[50];
            fgets(temp2, sizeof(temp2), stdin);
            sscanf(temp2, "%lld", &data[i].No_BPJS);

            printf("Enter ID Pasien: ");
            fgets(data[i].ID_Pasien, sizeof(data[i].ID_Pasien), stdin);
            data[i].ID_Pasien[strcspn(data[i].ID_Pasien, "\n")] = 0;  // remove trailing newline

            break;
        }
    }
}

// Function to save data from an array to the CSV file
void saveData(char* filename, Data_Pasien* data, int count) {
    FILE* file = fopen(filename, "w");

    if (file != NULL) {
        // Write the header line
        fprintf(file, "No;Nama Lengkap;Alamat;Kota;Tempat Lahir;Tanggal Lahir;Umur (th);No BPJS;ID Pasien\n");

        // Write the data
        for (int i = 0; i < count; i++) {
            // Remove any trailing newline character from the data strings
            data[i].Nama_Lengkap[strcspn(data[i].Nama_Lengkap, "\n")] = 0;
            data[i].Alamat[strcspn(data[i].Alamat, "\n")] = 0;
            data[i].Kota[strcspn(data[i].Kota, "\n")] = 0;
            data[i].Tempat_Lahir[strcspn(data[i].Tempat_Lahir, "\n")] = 0;
            data[i].Tanggal_Lahir[strcspn(data[i].Tanggal_Lahir, "\n")] = 0;
            data[i].ID_Pasien[strcspn(data[i].ID_Pasien, "\n")] = 0;

            fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%lld;%s\n", data[i].No, data[i].Nama_Lengkap, data[i].Alamat, data[i].Kota, data[i].Tempat_Lahir, data[i].Tanggal_Lahir, data[i].Umur, data[i].No_BPJS, data[i].ID_Pasien);
        }
        fclose(file);
    } else {
        printf("Unable to open the file.\n");
    }
}
// Akhir Bagian Dhika

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

void cariDataPasien(Data_Pasien* dataPasien, int count) {
    char nama_pasien[50];
    printf("Masukkan nama pasien yang ingin dicari! ");
    clearInputBuffer();  // Membersihkan buffer input
    fgets(nama_pasien, sizeof(nama_pasien), stdin);

    nama_pasien[strcspn(nama_pasien, "\n")] = '\0'; // remove newline character

    Data_Pasien* foundPasien = NULL;
    for (int i = 0; i < count; i++) {
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

void tambahRiwayatMedis(Riwayat_Medis_Pasien* riwayatMedis, int* count) {
    Riwayat_Medis_Pasien riwayatBaru;

    printf("== Riwayat Medis Baru ==\n\n");
    riwayatBaru.No = *count+1;
    printf("No: %d\n", riwayatBaru.No);
    
    printf("Tanggal: ");
    fgets(riwayatBaru.Tanggal, sizeof(riwayatBaru.Tanggal), stdin);
    riwayatBaru.Tanggal[strcspn(riwayatBaru.Tanggal, "\n")] = '\0';

    printf("ID Pasien: ");
    fgets(riwayatBaru.ID_Pasien, sizeof(riwayatBaru.ID_Pasien), stdin);
    riwayatBaru.ID_Pasien[strcspn(riwayatBaru.ID_Pasien, "\n")] = '\0';

    printf("Diagnosis: ");
    fgets(riwayatBaru.Diagnosis, sizeof(riwayatBaru.Diagnosis), stdin);
    riwayatBaru.Diagnosis[strcspn(riwayatBaru.Diagnosis, "\n")] = '\0';

    printf("Tindakan: ");
    fgets(riwayatBaru.Tindakan, sizeof(riwayatBaru.Tindakan), stdin);
    riwayatBaru.Tindakan[strcspn(riwayatBaru.Tindakan, "\n")] = '\0';

    printf("Kontrol: ");
    fgets(riwayatBaru.Kontrol, sizeof(riwayatBaru.Kontrol), stdin);
    riwayatBaru.Kontrol[strcspn(riwayatBaru.Kontrol, "\n")] = '\0';

    printf("Biaya: ");
    scanf("%lf", &riwayatBaru.Biaya);

    riwayatMedis[(*count)++] = riwayatBaru;

    printf("Riwayat baru telah berhasil ditambahkan.\n");
}

void ubahRiwayatMedis(Riwayat_Medis_Pasien* riwayatMedis, int count) {
    Riwayat_Medis_Pasien perubahan; int no; 
    printf("Masukkan nomor riwayat medis yang akan diubah: ");
    scanf("%d", &no);
    clearInputBuffer();

    if (no <= 0 || no > count) {
        printf("Nomor riwayat medis tidak valid.\n");
        return;
    }

    perubahan.No = no;
    
    printf("Tanggal: ");
    fgets(perubahan.Tanggal, sizeof(perubahan.Tanggal), stdin);
    perubahan.Tanggal[strcspn(perubahan.Tanggal, "\n")] = '\0';

    printf("ID Pasien: ");
    fgets(perubahan.ID_Pasien, sizeof(perubahan.ID_Pasien), stdin);
    perubahan.ID_Pasien[strcspn(perubahan.ID_Pasien, "\n")] = '\0';

    printf("Diagnosis: ");
    fgets(perubahan.Diagnosis, sizeof(perubahan.Diagnosis), stdin);
    perubahan.Diagnosis[strcspn(perubahan.Diagnosis, "\n")] = '\0';

    printf("Tindakan: ");
    fgets(perubahan.Tindakan, sizeof(perubahan.Tindakan), stdin);
    perubahan.Tindakan[strcspn(perubahan.Tindakan, "\n")] = '\0';

    printf("Kontrol: ");
    fgets(perubahan.Kontrol, sizeof(perubahan.Kontrol), stdin);
    perubahan.Kontrol[strcspn(perubahan.Kontrol, "\n")] = '\0';

    printf("Biaya: ");
    scanf("%lf", &perubahan.Biaya);
    clearInputBuffer();

    riwayatMedis[no-1] = perubahan;

    printf("Riwayat medis pada nomor ke-%d telah berhasil diubah.\n", no);
}
void hapusRiwayatMedis() {}
void cariRiwayatMedis() {}

void laporanKeuangan(Riwayat_Medis_Pasien* riwayatMedisPasien, int sizeRiwayatMedis) {
    // Struktur untuk menyimpan pendapatan per bulan dan per tahun
    typedef struct {
        int tahun;
        double pendapatanBulanan[12];
        int jumlahDataBulanan[12];
    } PendapatanTahunan;
    
    PendapatanTahunan* pendapatan = NULL;
    int jumlahTahun = 0;

    for (int i = 0; i < sizeRiwayatMedis; i++) {
        char* token = strtok(riwayatMedisPasien[i].Tanggal, " ");
        int hari = atoi(token);
        token = strtok(NULL, " ");
        char* namaBulan = token;
        token = strtok(NULL, " ");
        int tahun = atoi(token);
        token="";

        int bulan = 0;
        if (strcmp(namaBulan, "Januari") == 0) bulan = 0;
        else if (strcmp(namaBulan, "Februari") == 0) bulan = 1;
        else if (strcmp(namaBulan, "Maret") == 0) bulan = 2;
        else if (strcmp(namaBulan, "April") == 0) bulan = 3;
        else if (strcmp(namaBulan, "Mei") == 0) bulan = 4;
        else if (strcmp(namaBulan, "Juni") == 0) bulan = 5;
        else if (strcmp(namaBulan, "Juli") == 0) bulan = 6;
        else if (strcmp(namaBulan, "Agustus") == 0) bulan = 7;
        else if (strcmp(namaBulan, "September") == 0) bulan = 8;
        else if (strcmp(namaBulan, "Oktober") == 0) bulan = 9;
        else if (strcmp(namaBulan, "November") == 0) bulan = 10;
        else if (strcmp(namaBulan, "Desember") == 0) bulan = 11;

        // Cari apakah tahun sudah ada dalam array
        int tahunDitemukan = -1;
        for (int j = 0; j < jumlahTahun; j++) {
            if (pendapatan[j].tahun == tahun) {
                tahunDitemukan = j;
                break;
            }
        }

        // Jika tahun belum ada, tambahkan tahun baru ke array
        if (tahunDitemukan == -1) {
            jumlahTahun++;
            pendapatan = (PendapatanTahunan*)realloc(pendapatan, jumlahTahun * sizeof(PendapatanTahunan));
            pendapatan[jumlahTahun - 1].tahun = tahun;
            memset(pendapatan[jumlahTahun - 1].pendapatanBulanan, 0, 12 * sizeof(double));
            memset(pendapatan[jumlahTahun - 1].jumlahDataBulanan, 0, 12 * sizeof(int));
            tahunDitemukan = jumlahTahun - 1;
        }

        // Tambahkan biaya ke pendapatan bulanan dan tahunan
        pendapatan[tahunDitemukan].pendapatanBulanan[bulan] += riwayatMedisPasien[i].Biaya;
        pendapatan[tahunDitemukan].jumlahDataBulanan[bulan]++;
    }

    char* monthNames[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    // Hitung dan tampilkan rata-rata pendapatan per bulan dan per tahun
    for (int i = 0; i < jumlahTahun; i++) {
        double totalPendapatanTahunan = 0;
        int totalDataTahunan = 0;
        printf("Tahun %d:\n", pendapatan[i].tahun);
        for (int j = 0; j < 12; j++) {
            double rataRataBulanan = 0;
            if (pendapatan[i].jumlahDataBulanan[j] > 0) {
                rataRataBulanan = pendapatan[i].pendapatanBulanan[j] / pendapatan[i].jumlahDataBulanan[j];
            }
            printf("  Bulan %s: Total = %.2f, Rata-rata = %.2f\n", monthNames[j], pendapatan[i].pendapatanBulanan[j], rataRataBulanan);
            totalPendapatanTahunan += pendapatan[i].pendapatanBulanan[j];
            totalDataTahunan += pendapatan[i].jumlahDataBulanan[j];
        }
        double rataRataTahunan = 0;
        if (totalDataTahunan > 0) {
            rataRataTahunan = totalPendapatanTahunan / totalDataTahunan;
        }
        printf("  Total Pendapatan Tahunan: %.2f\n  Rata-rata Pendapatan Tahunan: %.2f\n\n", totalPendapatanTahunan, rataRataTahunan);
    }

    // Bersihkan memori
    free(pendapatan);
}
void analisisPasienPenyakit() {}
void informasiKontrolPasien() {}

// Fungsi untuk menulis kembali data pasien ke file CSV
void tulisDataPasien(const char* filename, Data_Pasien* dataPasien, int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Tulis header
    fprintf(file, "No;Nama Lengkap;Alamat;Kota;Tempat Lahir;Tanggal Lahir;Umur (th);No BPJS;ID Pasien\n");

    // Tulis setiap data pasien
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%lld;%s\n",
                dataPasien[i].No,
                dataPasien[i].Nama_Lengkap,
                dataPasien[i].Alamat,
                dataPasien[i].Kota,
                dataPasien[i].Tempat_Lahir,
                dataPasien[i].Tanggal_Lahir,
                dataPasien[i].Umur,
                dataPasien[i].No_BPJS,
                dataPasien[i].ID_Pasien);
    }

    fclose(file);
}

// Fungsi untuk menulis kembali riwayat medis pasien ke file CSV
void tulisRiwayatMedisPasien(const char* filename, Riwayat_Medis_Pasien* riwayatMedisPasien, int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Tulis header
    fprintf(file, "No;Tanggal;ID Pasien;Diagnosis;Tindakan;Kontrol;Biaya (Rp)\n");

    // Tulis setiap data pasien
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d;%s;%s;%s;%s;%s;%.2lf\n",
                riwayatMedisPasien[i].No,
                riwayatMedisPasien[i].Tanggal,
                riwayatMedisPasien[i].ID_Pasien,
                riwayatMedisPasien[i].Diagnosis,
                riwayatMedisPasien[i].Tindakan,
                riwayatMedisPasien[i].Kontrol,
                riwayatMedisPasien[i].Biaya);
    }

    fclose(file);
}