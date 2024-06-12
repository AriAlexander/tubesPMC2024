#include <stdio.h>
#include <string.h>

typedef struct {
    int no;
    char nama[50];
    char alamat[100];
    char kota[50];
    char tempat_lahir[50];
    char tanggal_lahir[20];
    int umur;
    char no_bpjs[20];
    char id_pasien[20];
} Data;

// Function to add data to the CSV file
void addData(char* filename, Data data) {
    // Open the file in append mode to ensure it exists
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fclose(file);
    } else {
        printf("Unable to open the file.\n");
        return;
    }

    // Now open the file in read mode to check the last character
    file = fopen(filename, "r");
    if (file != NULL) {
        // Move the file pointer to the end of the file
        fseek(file, -1, SEEK_END);

        // Check if the last character is a newline
        if (fgetc(file) != '\n') {
            // If not, close the file and reopen in append mode to add a newline
            fclose(file);
            file = fopen(filename, "a");
            fprintf(file, "\n");
        }
        fclose(file);
    } else {
        printf("Unable to open the file.\n");
        return;
    }

    // open the file again in append mode to the new data
    file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%s;%s\n", data.no, data.nama, data.alamat, data.kota, data.tempat_lahir, data.tanggal_lahir, data.umur, data.no_bpjs, data.id_pasien);
        fclose(file);
    } else {
        printf("Unable to open the file.\n");
    }
}



// Function to modify data in the CSV file
void modifyData(char* filename, Data oldData, Data newData) {
    FILE* file = fopen(filename, "r");
    FILE* temp = fopen("temp.csv", "w");
    char buffer[1024];
    char oldDataStr[256];
    char newDataStr[256];

    sprintf(oldDataStr, "%d;%s;%s;%s;%s;%s;%d;%s;%s", oldData.no, oldData.nama, oldData.alamat, oldData.kota, oldData.tempat_lahir, oldData.tanggal_lahir, oldData.umur, oldData.no_bpjs, oldData.id_pasien);
    sprintf(newDataStr, "%d;%s;%s;%s;%s;%s;%d;%s;%s", newData.no, newData.nama, newData.alamat, newData.kota, newData.tempat_lahir, newData.tanggal_lahir, newData.umur, newData.no_bpjs, newData.id_pasien);

    if (file != NULL && temp != NULL) {
        while (fgets(buffer, sizeof(buffer), file)) {
            if (strstr(buffer, oldDataStr)) {
                fprintf(temp, "%s\n", newDataStr);
            } else {
                fprintf(temp, "%s", buffer);
            }
        }
        fclose(file);
        fclose(temp);
        remove(filename);
        rename("temp.csv", filename);
    } else {
        printf("Unable to open the file.\n");
    }
}

int main() {
    char* filename = "data_pasien.csv";
    Data data;
    char input[256];
    printf("Enter data (No;Nama Lengkap;Alamat;Kota;Tempat Lahir;Tanggal Lahir;Umur (th);No BPJS;ID Pasien):\n");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;]", &data.no, data.nama, data.alamat, data.kota, data.tempat_lahir, data.tanggal_lahir, &data.umur, data.no_bpjs, data.id_pasien);
    addData(filename, data);

    Data oldData, newData;
    printf("Enter old data to modify:\n");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;]", &oldData.no, oldData.nama, oldData.alamat, oldData.kota, oldData.tempat_lahir, oldData.tanggal_lahir, &oldData.umur, oldData.no_bpjs, oldData.id_pasien);
    printf("Enter new data:\n");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;]", &newData.no, newData.nama, newData.alamat, newData.kota, newData.tempat_lahir, newData.tanggal_lahir, &newData.umur, newData.no_bpjs, newData.id_pasien);
    modifyData(filename, oldData, newData);

    return 0;
}
