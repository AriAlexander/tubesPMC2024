#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASIEN 100

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

Data_Pasien* readDataPasien(const char *filename, int *count) {
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

char* cariDataPasien(char name[], Data_Pasien *data_pasien, int *count) {
    Data_Pasien *foundPasien = NULL;
    for (int i = 0; i < *count; i++) {
        if (strcmp(data_pasien[i].Nama_Lengkap, name) == 0) {
            foundPasien = &data_pasien[i];
            break;
        }
    }

    if (foundPasien) {
        char buffer[1024];
        sprintf(buffer, "Data pasien ditemukan!\nNo.: %d\nNama Lengkap: %s\nAlamat: %s\nKota: %s\nTempat Lahir: %s\nTanggal Lahir: %s\nUmur: %d\nNo. BPJS: %lld\nID Pasien: %s\n", 
                foundPasien->No, foundPasien->Nama_Lengkap, foundPasien->Alamat, 
                foundPasien->Kota, foundPasien->Tempat_Lahir, foundPasien->Tanggal_Lahir, 
                foundPasien->Umur, foundPasien->No_BPJS, 
                foundPasien->ID_Pasien);
        return strdup(buffer);
    } else {
        return strdup("Data pasien tidak ditemukan!\n");
    }
}

char* hapusDataPasien(int n, Data_Pasien* dataPasien, int *count) {
    for (int i = 0; i < *count; i++) {
        if (dataPasien[i].No == n) {
            char nama_pasien[50] = "";
            strcpy(nama_pasien, dataPasien[i].Nama_Lengkap);

            // Shift elements to the left
            for (int j = i; j < *count - 1; j++) {
                dataPasien[j] = dataPasien[j + 1];
                dataPasien[j].No -= 1;
            }
            (*count)--;
            char buffer[1024];
            sprintf(buffer, "Data pasien nomor %d dengan nama %s telah dihapus.", n, nama_pasien);
            return strdup(buffer);
        }
    }
    return strdup("Data pasien tidak ditemukan\n");
}

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

char* capture_output(void (*func)()) {
    FILE *fp;
    char *output = NULL;
    size_t size = 0;

    /* Redirect stdout to a temporary file */
    fp = freopen("temp_output.txt", "w+", stdout);
    if (fp == NULL) {
        perror("freopen");
        return NULL;
    }

    /* Call the function */
    func();

    /* Flush and rewind the file */
    fflush(fp);
    fseek(fp, 0, SEEK_SET);

    /* Read the output from the file */
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    output = (char*)malloc(size + 1);
    fread(output, 1, size, fp);
    output[size] = '\0';

    /* Close the file and restore stdout */
    fclose(fp);
    freopen("/dev/tty", "w", stdout);

    return output;
}