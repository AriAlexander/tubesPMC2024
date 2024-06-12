#include <stdio.h>
#include <string.h>

// Define a struct to hold the data
typedef struct {
    int No;
    char Nama_Lengkap[50];
    char Alamat[100];
    char Kota[50];
    char Tempat_Lahir[50];
    char Tanggal_Lahir[20];
    int Umur;
    long long No_BPJS;
    char ID_Pasien[20];
} Data_Pasien;

// Define a maximum number of records
#define MAX_PASIEN 100
// Function to load data from the CSV file into an array
int countData(char* filename, Data_Pasien* data) {
    FILE* file = fopen(filename, "r");
    int count = 0;
    char buffer[1024];

    if (file != NULL) {
        // Skip the header line
        fgets(buffer, sizeof(buffer), file);

        while (fgets(buffer, sizeof(buffer), file) && count < MAX_PASIEN) {
            sscanf(buffer, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%lld;%[^;]", &data[count].No, data[count].Nama_Lengkap, data[count].Alamat, data[count].Kota, data[count].Tempat_Lahir, data[count].Tanggal_Lahir, &data[count].Umur, &data[count].No_BPJS, data[count].ID_Pasien);
            count++;
        }
        fclose(file);
    } else {
        printf("Unable to open the file.\n");
    }

    return count;
}

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
        // fgets(data[*count].No_BPJS, sizeof(data[*count].No_BPJS), stdin);
        // data[*count].No_BPJS[strcspn(data[*count].No_BPJS, "\n")] = 0;  // remove trailing newline

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
            // fgets(data[i].No_BPJS, sizeof(data[i].No_BPJS), stdin);
            // data[i].No_BPJS[strcspn(data[i].No_BPJS, "\n")] = 0;  // remove trailing newline

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
            // data[i].No_BPJS[strcspn(data[i].No_BPJS, "\n")] = 0;
            data[i].ID_Pasien[strcspn(data[i].ID_Pasien, "\n")] = 0;

            fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%lld;%s\n", data[i].No, data[i].Nama_Lengkap, data[i].Alamat, data[i].Kota, data[i].Tempat_Lahir, data[i].Tanggal_Lahir, data[i].Umur, data[i].No_BPJS, data[i].ID_Pasien);
        }
        fclose(file);
    } else {
        printf("Unable to open the file.\n");
    }
}
void tambahDataPasien() {
    char* filename = "Data Pasien.csv";
    Data_Pasien data[MAX_PASIEN];
    int count = countData(filename, data);
    addData(data, &count);
    saveData(filename, data, count);
}

void ubahDataPasien() {
    char* filename = "Data Pasien.csv";
    Data_Pasien data[MAX_PASIEN];
    int count = countData(filename, data);
    modifyData(data, count);
    saveData(filename, data, count);
}



int main() {
    while (1) {
    char choice[10];
    printf("1. Add data\n2. Modify data\nEnter your choice: ");
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;  // remove trailing newline

    if (strcmp(choice, "1") == 0) {
        tambahDataPasien();
    } else if (strcmp(choice, "2") == 0) {
        ubahDataPasien();
    } else {
        printf("Invalid choice.\n");
    }
    }

    return 0;
}
