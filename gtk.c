#include <gtk/gtk.h>
#include "my_functions.h"

int size_data_pasien, size_riwayat_medis_pasien;
Data_Pasien *data_pasien;
Riwayat_Medis_Pasien *riwayat_medis_pasien;

typedef struct dataParam {
  GtkWidget *stack;
  GtkWidget *child;
} dataParam;

static char *copy_str(const gchar *const_str) {
  // Allocate memory for the copy
  char *modifiable_str = strdup(const_str);
  if (modifiable_str == NULL)
      // Handle memory allocation failure
      return NULL;
  return modifiable_str;
}

static void press(GtkWidget *widget, gpointer user_data) {
  dataParam *param = (dataParam*)user_data;
  gtk_stack_set_visible_child(GTK_STACK(param->stack), param->child);
}

static void tambah_data_pasien(GtkButton *button, gpointer user_data) {
  GtkWidget **entries = (GtkWidget **)user_data;
  const gchar *name_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[0]));
  const gchar *address_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[1]));
  const gchar *city_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[2]));
  const gchar *birthplace_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[3]));
  const gchar *birthdate_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[4]));
  const gchar *age_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[5]));
  const gchar *bpjs_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[6]));
  const gchar *id_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[7]));
  const char* message = tambahDataPasien(copy_str(name_gchar), copy_str(address_gchar), copy_str(city_gchar), copy_str(birthplace_gchar), copy_str(birthdate_gchar), 
  copy_str(age_gchar), copy_str(bpjs_gchar), copy_str(id_gchar), data_pasien, &size_data_pasien);
  tulisDataPasien("Data Pasien.csv", data_pasien, size_data_pasien);
  GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(entries[7]));
  GtkWidget *child = gtk_widget_get_last_child(GTK_WIDGET(box));
  gtk_label_set_text(GTK_LABEL(child), message);
}

static void ubah_data_pasien(GtkButton *button, gpointer user_data) {
  GtkWidget **entries = (GtkWidget **)user_data;
  const gchar *name_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[0]));
  const gchar *address_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[1]));
  const gchar *city_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[2]));
  const gchar *birthplace_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[3]));
  const gchar *birthdate_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[4]));
  const gchar *age_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[5]));
  const gchar *bpjs_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[6]));
  const gchar *id_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[7]));
  const char* message = ubahDataPasien(copy_str(name_gchar), copy_str(address_gchar), copy_str(city_gchar), copy_str(birthplace_gchar), copy_str(birthdate_gchar), 
  copy_str(age_gchar), copy_str(bpjs_gchar), copy_str(id_gchar), data_pasien, &size_data_pasien);
  tulisDataPasien("Data Pasien.csv", data_pasien, size_data_pasien);
  GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(entries[7]));
  GtkWidget *child = gtk_widget_get_last_child(GTK_WIDGET(box));
  gtk_label_set_text(GTK_LABEL(child), message);
}

static void cari_data_pasien(GtkButton *button, gpointer user_data) {
  GtkEntry *entry = GTK_ENTRY(user_data);
  const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
  const char* message = cariDataPasien(copy_str(text), data_pasien, &size_data_pasien);
  GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *child = gtk_widget_get_last_child(GTK_WIDGET(box));
  gtk_label_set_text(GTK_LABEL(child), message);
};

static void hapus_data_pasien(GtkButton *button, gpointer user_data) {
  GtkEntry *entry = GTK_ENTRY(user_data);
  const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
  const char* message = hapusDataPasien(atoi(copy_str(text)), data_pasien, &size_data_pasien);
  tulisDataPasien("Data Pasien.csv", data_pasien, size_data_pasien);
  GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *child = gtk_widget_get_last_child(GTK_WIDGET(box));
  gtk_label_set_text(GTK_LABEL(child), message);
}

static void tambah_riwayat_medis_pasien(GtkButton *button, gpointer user_data) {
  GtkWidget **entries = (GtkWidget **)user_data;
  const gchar *date_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[0]));
  const gchar *id_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[1]));
  const gchar *diagnosis_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[2]));
  const gchar *action_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[3]));
  const gchar *control_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[4]));
  const gchar *bill_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[5]));
  const char* message = tambahRiwayatMedisPasien(copy_str(date_gchar), copy_str(id_gchar), copy_str(diagnosis_gchar), copy_str(action_gchar), copy_str(control_gchar), 
  copy_str(bill_gchar), data_pasien, &size_data_pasien);
  tulisRiwayatMedisPasien("Riwayat Datang, Diagnosis, dan Tindakan", riwayat_medis_pasien, size_riwayat_medis_pasien);
  GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(entries[5]));
  GtkWidget *child = gtk_widget_get_last_child(GTK_WIDGET(box));
  gtk_label_set_text(GTK_LABEL(child), message);
}

static void ubah_riwayat_medis_pasien(GtkButton *button, gpointer user_data) {
  GtkWidget **entries = (GtkWidget **)user_data;
  const gchar *date_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[0]));
  const gchar *id_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[1]));
  const gchar *diagnosis_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[2]));
  const gchar *action_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[3]));
  const gchar *control_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[4]));
  const gchar *bill_gchar = gtk_editable_get_text(GTK_EDITABLE(entries[5]));
  const char* message = ubahRiwayatMedisPasien(copy_str(date_gchar), copy_str(id_gchar), copy_str(diagnosis_gchar), copy_str(action_gchar), copy_str(control_gchar), 
  copy_str(bill_gchar), data_pasien, &size_data_pasien);
  tulisRiwayatMedisPasien("Riwayat Datang, Diagnosis, dan Tindakan", riwayat_medis_pasien, size_riwayat_medis_pasien);
  GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(entries[5]));
  GtkWidget *child = gtk_widget_get_last_child(GTK_WIDGET(box));
  gtk_label_set_text(GTK_LABEL(child), message);
}

static void cari_riwayat_medis_pasien(GtkButton *button, gpointer user_data) {
  GtkEntry *entry = GTK_ENTRY(user_data);
  const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
  const char* message = cariDataPasien(copy_str(text), data_pasien, &size_data_pasien);
  GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *child = gtk_widget_get_last_child(GTK_WIDGET(box));
  gtk_label_set_text(GTK_LABEL(child), message);
}

static void hapus_riwayat_medis_pasien(GtkButton *button, gpointer user_data) {
  GtkEntry *entry = GTK_ENTRY(user_data);
  const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
  const char* message = cariDataPasien(copy_str(text), data_pasien, &size_data_pasien);
  GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *child = gtk_widget_get_last_child(GTK_WIDGET(box));
  gtk_label_set_text(GTK_LABEL(child), message);
}

static void laporan_keuangan();
static void analisis_pasien_penyakit();
static void informasi_kontrol_pasien();

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *stack;
  GtkWidget *title;
  GtkWidget *subtitle1;
  GtkWidget *subtitle2;
  GtkWidget *subtitle3;
  GtkWidget *new_line;
  GtkWidget *grid1;
  GtkWidget *grid2;
  GtkWidget *grid3;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;
  GtkWidget *button4;
  GtkWidget *button5;
  GtkWidget *button6;
  GtkWidget *button7;
  GtkWidget *button8;
  GtkWidget *button9;
  GtkWidget *button10;
  GtkWidget *button11;
  GtkWidget *button12;

  // window utama
    window = gtk_application_window_new(GTK_APPLICATION(app));
    stack = gtk_stack_new();
    gtk_window_set_child(GTK_WINDOW(window), stack);
    gtk_window_set_title(GTK_WINDOW(window), "Sistem Pencatatan Pasien Klinik X");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

  // menu utama
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box);
    title = gtk_label_new("Selamat datang. Silakan pilih fitur yang telah disediakan:");
    gtk_box_append(GTK_BOX(box), title);
    subtitle1 = gtk_label_new("Manajemen Data Pasien");
    gtk_box_append(GTK_BOX(box), subtitle1);
    grid1 = gtk_grid_new();
    gtk_box_append(GTK_BOX(box), grid1);
    button1 = gtk_button_new_with_label("Tambah Data Pasien");
    gtk_grid_attach(GTK_GRID(grid1), button1, 0, 1, 1, 1);
    button2 = gtk_button_new_with_label("Ubah Data Pasien");
    gtk_grid_attach(GTK_GRID(grid1), button2, 1, 1, 1, 1);
    button3 = gtk_button_new_with_label("Cari Data Pasien");
    gtk_grid_attach(GTK_GRID(grid1), button3, 0, 0, 1, 1);
    button4 = gtk_button_new_with_label("Hapus Data Pasien");
    gtk_grid_attach(GTK_GRID(grid1), button4, 1, 0, 1, 1);
    subtitle2 = gtk_label_new("Manajemen Riwayat Medis Pasien");
    gtk_box_append(GTK_BOX(box), subtitle2);
    grid2 = gtk_grid_new();
    gtk_box_append(GTK_BOX(box), grid2);
    button5 = gtk_button_new_with_label("Tambah Riwayat Medis Pasien");
    gtk_grid_attach(GTK_GRID(grid2), button5, 0, 1, 1, 1);
    button6 = gtk_button_new_with_label("Ubah Riwayat Medis Pasien");
    gtk_grid_attach(GTK_GRID(grid2), button6, 1, 1, 1, 1);
    button7 = gtk_button_new_with_label("Cari Riwayat Medis Pasien");
    gtk_grid_attach(GTK_GRID(grid2), button7, 0, 0, 1, 1);
    button8 = gtk_button_new_with_label("Hapus Riwayat Medis Pasien");
    gtk_grid_attach(GTK_GRID(grid2), button8, 1, 0, 1, 1);
    subtitle3 = gtk_label_new("Lain-lain");
    gtk_box_append(GTK_BOX(box), subtitle3);
    grid3 = gtk_grid_new();
    gtk_box_append(GTK_BOX(box), grid3);
    button9 = gtk_button_new_with_label("Laporan Keuangan");
    gtk_grid_attach(GTK_GRID(grid3), button9, 0, 1, 1, 1);
    button10 = gtk_button_new_with_label("Analisis Pasien dan Penyakit");
    gtk_grid_attach(GTK_GRID(grid3), button10, 1, 1, 1, 1);
    button11 = gtk_button_new_with_label("Informasi Kontrol Pasien");
    gtk_grid_attach(GTK_GRID(grid3), button11, 0, 0, 2, 1);
    new_line = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box), new_line);
    button12 = gtk_button_new_with_label("Keluar");
    g_signal_connect_swapped(button12, "clicked", G_CALLBACK(gtk_window_destroy), window);
    gtk_box_append(GTK_BOX(box), button12);

  // Tambah Data Pasien
    GtkWidget *box_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_1);
    GtkWidget *child_1 = gtk_label_new("== Tambah Data Pasien ==");
    gtk_box_append(GTK_BOX(box_1), child_1);
    dataParam *param_1 = malloc(sizeof(dataParam));
    param_1->stack = stack;
    param_1->child = box_1;
    g_signal_connect(button1, "clicked", G_CALLBACK(press), (gpointer)param_1);
    GtkWidget *entries_1[8];  
    GtkWidget *new_line_1a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1a);    
    GtkWidget *input_name_label_1 = gtk_label_new("Masukkan nama pasien yang ingin ditambahkan! ");
    gtk_box_append(GTK_BOX(box_1), input_name_label_1);
    entries_1[0] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_1), entries_1[0]);    
    GtkWidget *new_line_1b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1b);
    GtkWidget *input_address_label_1 = gtk_label_new("Masukkan alamat pasien yang ingin ditambahkan! ");
    gtk_box_append(GTK_BOX(box_1), input_address_label_1);
    entries_1[1] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_1), entries_1[1]);    
    GtkWidget *new_line_1c = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1c);
    GtkWidget *input_city_label_1 = gtk_label_new("Masukkan kota pasien yang ingin ditambahkan! ");
    gtk_box_append(GTK_BOX(box_1), input_city_label_1);
    entries_1[2] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_1), entries_1[2]);    
    GtkWidget *new_line_1d = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1d);
    GtkWidget *input_birthplace_label_1 = gtk_label_new("Masukkan tempat lahir pasien yang ingin ditambahkan! ");
    gtk_box_append(GTK_BOX(box_1), input_birthplace_label_1);
    entries_1[3] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_1), entries_1[3]);    
    GtkWidget *new_line_1e = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1e);
    GtkWidget *input_birthdate_label_1 = gtk_label_new("Masukkan tanggal lahir pasien yang ingin ditambahkan! ");
    gtk_box_append(GTK_BOX(box_1), input_birthdate_label_1);
    entries_1[4] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_1), entries_1[4]);    
    GtkWidget *new_line_1f = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1f);
    GtkWidget *input_age_label_1 = gtk_label_new("Masukkan umur pasien yang ingin ditambahkan! ");
    gtk_box_append(GTK_BOX(box_1), input_age_label_1);
    entries_1[5] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_1), entries_1[5]);    
    GtkWidget *new_line_1g = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1g);
    GtkWidget *input_BPJS_label_1 = gtk_label_new("Masukkan nomor BPJS pasien yang ingin ditambahkan! ");
    gtk_box_append(GTK_BOX(box_1), input_BPJS_label_1);
    entries_1[6] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_1), entries_1[6]);    
    GtkWidget *new_line_1h = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1h);
    GtkWidget *input_ID_label_1 = gtk_label_new("Masukkan ID pasien yang ingin ditambahkan! ");
    gtk_box_append(GTK_BOX(box_1), input_ID_label_1);
    entries_1[7] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_1), entries_1[7]);    
    GtkWidget *new_line_1i = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1i);
    GtkWidget *submit_button_1 = gtk_button_new_with_label("Submit");
    gtk_box_append(GTK_BOX(box_1), submit_button_1);
    g_signal_connect(submit_button_1, "clicked", G_CALLBACK(tambah_data_pasien), entries_1);    
    GtkWidget *new_line_1j = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_1), new_line_1j);
    GtkWidget *result_label_1 = gtk_label_new("");
    gtk_box_append(GTK_BOX(box_1), result_label_1);
    GtkWidget *back_1 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_1), back_1);
    dataParam *param_1_back = malloc(sizeof(param_1_back));
    param_1_back->stack = stack;
    param_1_back->child = box;
    g_signal_connect(back_1, "clicked", G_CALLBACK(press), (gpointer)param_1_back);

  // Ubah Data Pasien
    GtkWidget *box_2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_2);
    GtkWidget *child_2 = gtk_label_new("== Ubah Data Pasien ==");
    gtk_box_append(GTK_BOX(box_2), child_2);
    dataParam *param_2 = malloc(sizeof(dataParam));
    param_2->stack = stack;
    param_2->child = box_2;
    g_signal_connect(button2, "clicked", G_CALLBACK(press), (gpointer)param_2);
    GtkWidget *entries_2[8];  
    GtkWidget *new_line_2a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2a);    
    GtkWidget *input_name_label_2 = gtk_label_new("Masukkan nama pasien yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_2), input_name_label_2);
    entries_2[0] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_2), entries_2[0]);    
    GtkWidget *new_line_2b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2b);
    GtkWidget *input_address_label_2 = gtk_label_new("Masukkan alamat pasien yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_2), input_address_label_2);
    entries_2[1] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_2), entries_2[1]);    
    GtkWidget *new_line_2c = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2c);
    GtkWidget *input_city_label_2 = gtk_label_new("Masukkan kota pasien yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_2), input_city_label_2);
    entries_2[2] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_2), entries_2[2]);    
    GtkWidget *new_line_2d = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2d);
    GtkWidget *input_birthplace_label_2 = gtk_label_new("Masukkan tempat lahir pasien yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_2), input_birthplace_label_2);
    entries_2[3] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_2), entries_2[3]);    
    GtkWidget *new_line_2e = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2e);
    GtkWidget *input_birthdate_label_2 = gtk_label_new("Masukkan tanggal lahir pasien yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_2), input_birthdate_label_2);
    entries_2[4] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_2), entries_2[4]);    
    GtkWidget *new_line_2f = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2f);
    GtkWidget *input_age_label_2 = gtk_label_new("Masukkan umur pasien yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_2), input_age_label_2);
    entries_2[5] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_2), entries_2[5]);    
    GtkWidget *new_line_2g = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2g);
    GtkWidget *input_BPJS_label_2 = gtk_label_new("Masukkan nomor BPJS pasien yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_2), input_BPJS_label_2);
    entries_2[6] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_2), entries_2[6]);    
    GtkWidget *new_line_2h = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2h);
    GtkWidget *input_ID_label_2 = gtk_label_new("Masukkan ID pasien yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_2), input_ID_label_2);
    entries_2[7] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_2), entries_2[7]);    
    GtkWidget *new_line_2i = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2i);
    GtkWidget *submit_button_2 = gtk_button_new_with_label("Submit");
    gtk_box_append(GTK_BOX(box_2), submit_button_2);
    g_signal_connect(submit_button_2, "clicked", G_CALLBACK(ubah_data_pasien), entries_2);    
    GtkWidget *new_line_2j = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_2), new_line_2j);
    GtkWidget *result_label_2 = gtk_label_new("");
    gtk_box_append(GTK_BOX(box_2), result_label_2);
    GtkWidget *back_2 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_2), back_2);
    dataParam *param_2_back = malloc(sizeof(param_2_back));
    param_2_back->stack = stack;
    param_2_back->child = box;
    g_signal_connect(back_2, "clicked", G_CALLBACK(press), (gpointer)param_2_back);
  
  // Cari Data Pasien
    GtkWidget *box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box3);
    GtkWidget *child3 = gtk_label_new("== Cari Data Pasien ==");
    gtk_box_append(GTK_BOX(box3), child3);
    dataParam *param3 = malloc(sizeof(dataParam));
    param3->stack = stack;
    param3->child = box3;
    g_signal_connect(button3, "clicked", G_CALLBACK(press), (gpointer)param3);
    GtkWidget *new_line_3a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box3), new_line_3a);    
    GtkWidget *input_label_3 = gtk_label_new("Masukkan nama pasien yang ingin dicari! ");
    gtk_box_append(GTK_BOX(box3), input_label_3);
    GtkWidget *input_3 = gtk_entry_new();
    gtk_box_append(GTK_BOX(box3), input_3);
    GtkWidget *submit_button_3 = gtk_button_new_with_label("Submit");
    gtk_box_append(GTK_BOX(box3), submit_button_3);
    g_signal_connect(submit_button_3, "clicked", G_CALLBACK(cari_data_pasien), input_3);
    GtkWidget *new_line_3b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box3), new_line_3b);
    GtkWidget *result_label_3 = gtk_label_new("");
    gtk_box_append(GTK_BOX(box3), result_label_3);
    GtkWidget *back_3 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box3), back_3);
    dataParam *param_3_back = malloc(sizeof(param_3_back));
    param_3_back->stack = stack;
    param_3_back->child = box;
    g_signal_connect(back_3, "clicked", G_CALLBACK(press), (gpointer)param_3_back);

  // Hapus Data Pasien
    GtkWidget *box_4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_4);
    GtkWidget *child_4 = gtk_label_new("== Hapus Data Pasien ==");
    gtk_box_append(GTK_BOX(box_4), child_4);
    dataParam *param_4 = malloc(sizeof(dataParam));
    param_4->stack = stack;
    param_4->child = box_4;
    g_signal_connect(button4, "clicked", G_CALLBACK(press), (gpointer)param_4);
    GtkWidget *new_line_4a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box3), new_line_4a);    
    GtkWidget *input_label_4 = gtk_label_new("Masukkan nomor pasien yang ingin dihapus! ");
    gtk_box_append(GTK_BOX(box_4), input_label_4);
    GtkWidget *input_4 = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_4), input_4);
    GtkWidget *submit_button_4 = gtk_button_new_with_label("Submit");
    gtk_box_append(GTK_BOX(box_4), submit_button_4);
    g_signal_connect(submit_button_4, "clicked", G_CALLBACK(cari_data_pasien), input_4);
    GtkWidget *new_line_4b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_4), new_line_4b);
    GtkWidget *result_label_4 = gtk_label_new("");
    gtk_box_append(GTK_BOX(box_4), result_label_4);
    GtkWidget *back_4 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_4), back_4);
    dataParam *param_4_back = malloc(sizeof(dataParam));
    param_4_back->stack = stack;
    param_4_back->child = box;
    g_signal_connect(back_4, "clicked", G_CALLBACK(press), (gpointer)param_4_back);

  // Tambah Riwayat Medis Pasien
    GtkWidget *box_5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_5);
    GtkWidget *child_5 = gtk_label_new("== Tambah Riwayat Medis Pasien ==");
    gtk_box_append(GTK_BOX(box_5), child_5);
    dataParam *param_5 = malloc(sizeof(dataParam));
    param_5->stack = stack;
    param_5->child = box_5;
    g_signal_connect(button5, "clicked", G_CALLBACK(press), (gpointer)param_5);
    GtkWidget *entries_5[6];  
    GtkWidget *new_line_5a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_5), new_line_5a);    
    GtkWidget *input_name_label_5 = gtk_label_new("Masukkan tanggal! ");
    gtk_box_append(GTK_BOX(box_5), input_name_label_5);
    entries_5[0] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_5), entries_5[0]);    
    GtkWidget *new_line_5b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_5), new_line_5b);
    GtkWidget *input_address_label_5 = gtk_label_new("Masukkan ID pasien! ");
    gtk_box_append(GTK_BOX(box_5), input_address_label_5);
    entries_5[1] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_5), entries_5[1]);    
    GtkWidget *new_line_5c = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_5), new_line_5c);
    GtkWidget *input_city_label_5 = gtk_label_new("Masukkan diagnosis! ");
    gtk_box_append(GTK_BOX(box_5), input_city_label_5);
    entries_5[2] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_5), entries_5[2]);    
    GtkWidget *new_line_5d = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_5), new_line_5d);
    GtkWidget *input_birthplace_label_5 = gtk_label_new("Masukkan tindakan! ");
    gtk_box_append(GTK_BOX(box_5), input_birthplace_label_5);
    entries_5[3] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_5), entries_5[3]);    
    GtkWidget *new_line_5e = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_5), new_line_5e);
    GtkWidget *input_birthdate_label_5 = gtk_label_new("Masukkan kontrol! ");
    gtk_box_append(GTK_BOX(box_5), input_birthdate_label_5);
    entries_5[4] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_5), entries_5[4]);    
    GtkWidget *new_line_5f = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_5), new_line_5f);
    GtkWidget *input_age_label_5 = gtk_label_new("Masukkan biaya (Rp)! ");
    gtk_box_append(GTK_BOX(box_5), input_age_label_5);
    entries_5[5] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_5), entries_5[5]);    
    GtkWidget *new_line_5g = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_5), new_line_5g);
    GtkWidget *submit_button_5 = gtk_button_new_with_label("Submit");
    gtk_box_append(GTK_BOX(box_5), submit_button_5);
    g_signal_connect(submit_button_5, "clicked", G_CALLBACK(tambah_riwayat_medis_pasien), entries_5);    
    GtkWidget *new_line_5h = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_5), new_line_5h);
    GtkWidget *result_label_5 = gtk_label_new("");
    gtk_box_append(GTK_BOX(box_5), result_label_5);
    GtkWidget *back_5 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_5), back_5);
    dataParam *param_5_back = malloc(sizeof(param_5_back));
    param_5_back->stack = stack;
    param_5_back->child = box;
    g_signal_connect(back_5, "clicked", G_CALLBACK(press), (gpointer)param_5_back);

  // Ubah Riwayat Medis Pasien
    GtkWidget *box_6 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_6);
    GtkWidget *child_6 = gtk_label_new("== Ubah Riwayat Medis Pasien ==");
    gtk_box_append(GTK_BOX(box_6), child_6);
    dataParam *param_6 = malloc(sizeof(dataParam));
    param_6->stack = stack;
    param_6->child = box_6;
    g_signal_connect(button6, "clicked", G_CALLBACK(press), (gpointer)param_6);
    GtkWidget *entries_6[6];  
    GtkWidget *new_line_6a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_6), new_line_6a);    
    GtkWidget *input_name_label_6 = gtk_label_new("Masukkan tanggal yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_6), input_name_label_6);
    entries_6[0] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_6), entries_6[0]);    
    GtkWidget *new_line_6b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_6), new_line_6b);
    GtkWidget *input_address_label_6 = gtk_label_new("Masukkan ID pasien yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_6), input_address_label_6);
    entries_6[1] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_6), entries_6[1]);    
    GtkWidget *new_line_6c = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_6), new_line_6c);
    GtkWidget *input_city_label_6 = gtk_label_new("Masukkan diagnosis yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_6), input_city_label_6);
    entries_6[2] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_6), entries_6[2]);    
    GtkWidget *new_line_6d = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_6), new_line_6d);
    GtkWidget *input_birthplace_label_6 = gtk_label_new("Masukkan tindakan yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_6), input_birthplace_label_6);
    entries_6[3] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_6), entries_6[3]);    
    GtkWidget *new_line_6e = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_6), new_line_6e);
    GtkWidget *input_birthdate_label_6 = gtk_label_new("Masukkan kontrol yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_6), input_birthdate_label_6);
    entries_6[4] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_6), entries_6[4]);    
    GtkWidget *new_line_6f = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_6), new_line_6f);
    GtkWidget *input_age_label_6 = gtk_label_new("Masukkan biaya (Rp) yang ingin diubah! ");
    gtk_box_append(GTK_BOX(box_6), input_age_label_6);
    entries_6[5] = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_6), entries_6[5]);    
    GtkWidget *new_line_6g = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_6), new_line_6g);
    GtkWidget *submit_button_6 = gtk_button_new_with_label("Submit");
    gtk_box_append(GTK_BOX(box_6), submit_button_6);
    g_signal_connect(submit_button_6, "clicked", G_CALLBACK(tambah_riwayat_medis_pasien), entries_6);    
    GtkWidget *new_line_6h = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_6), new_line_6h);
    GtkWidget *result_label_6 = gtk_label_new("");
    gtk_box_append(GTK_BOX(box_6), result_label_6);
    GtkWidget *back_6 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_6), back_6);
    dataParam *param_6_back = malloc(sizeof(param_6_back));
    param_6_back->stack = stack;
    param_6_back->child = box;
    g_signal_connect(back_6, "clicked", G_CALLBACK(press), (gpointer)param_6_back);

  // Cari Riwayat Medis Pasien
    GtkWidget *box_7 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_7);
    GtkWidget *child_7 = gtk_label_new("== Cari Riwayat Medis Pasien ==");
    gtk_box_append(GTK_BOX(box_7), child_7);
    dataParam *param_7 = malloc(sizeof(dataParam));
    param_7->stack = stack;
    param_7->child = box_7;
    g_signal_connect(button7, "clicked", G_CALLBACK(press), (gpointer)param_7);
    GtkWidget *new_line_7a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_7), new_line_7a);    
    GtkWidget *input_label_7 = gtk_label_new("Masukkan riwayat medis pasien yang ingin dicari! ");
    gtk_box_append(GTK_BOX(box_7), input_label_7);
    GtkWidget *input_7 = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_7), input_7);
    GtkWidget *submit_button_7 = gtk_button_new_with_label("Submit");
    gtk_box_append(GTK_BOX(box_7), submit_button_7);
    g_signal_connect(submit_button_7, "clicked", G_CALLBACK(cari_data_pasien), input_7);
    GtkWidget *new_line_7b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_7), new_line_7b);
    GtkWidget *result_label_7 = gtk_label_new("");
    gtk_box_append(GTK_BOX(box_7), result_label_7);
    GtkWidget *back_7 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_7), back_7);
    dataParam *param_7_back = malloc(sizeof(dataParam));
    param_7_back->stack = stack;
    param_7_back->child = box;
    g_signal_connect(back_7, "clicked", G_CALLBACK(press), (gpointer)param_7_back);

  // Hapus Riwayat Medis Pasien
    GtkWidget *box_8 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_8);
    GtkWidget *child_8 = gtk_label_new("== Hapus Riwayat Medis Pasien ==");
    gtk_box_append(GTK_BOX(box_8), child_8);
    dataParam *param_8 = malloc(sizeof(dataParam));
    param_8->stack = stack;
    param_8->child = box_8;
    g_signal_connect(button8, "clicked", G_CALLBACK(press), (gpointer)param_8);
    GtkWidget *new_line_8a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_8), new_line_8a);    
    GtkWidget *input_label_8 = gtk_label_new("Masukkan nomor riwayat yang ingin dihapus! ");
    gtk_box_append(GTK_BOX(box_8), input_label_8);
    GtkWidget *input_8 = gtk_entry_new();
    gtk_box_append(GTK_BOX(box_8), input_8);
    GtkWidget *submit_button_8 = gtk_button_new_with_label("Submit");
    gtk_box_append(GTK_BOX(box_8), submit_button_8);
    g_signal_connect(submit_button_8, "clicked", G_CALLBACK(cari_data_pasien), input_8);
    GtkWidget *new_line_8b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_8), new_line_8b);
    GtkWidget *result_label_8 = gtk_label_new("");
    gtk_box_append(GTK_BOX(box_8), result_label_8);
    GtkWidget *back_8 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_8), back_8);
    dataParam *param_8_back = malloc(sizeof(dataParam));
    param_8_back->stack = stack;
    param_8_back->child = box;
    g_signal_connect(back_8, "clicked", G_CALLBACK(press), (gpointer)param_8_back);

  // Laporan Keuangan
    GtkWidget *box_9 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_9);
    GtkWidget *child_9 = gtk_label_new("== Laporan Keuangan ==");
    gtk_box_append(GTK_BOX(box_9), child_9);
    dataParam *param_9 = malloc(sizeof(dataParam));
    param_9->stack = stack;
    param_9->child = box_9;
    g_signal_connect(button9, "clicked", G_CALLBACK(press), (gpointer)param_9);
    GtkWidget *new_line_9a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_9), new_line_9a);
    GtkWidget *result_label_9 = gtk_label_new(NULL);
    gtk_box_append(GTK_BOX(box_9), result_label_9);
    laporan_keuangan();    
    GtkWidget *new_line_9b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_9), new_line_9b);
    GtkWidget *back_9 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_9), back_9);
    dataParam *param_9_back = malloc(sizeof(dataParam));
    param_9_back->stack = stack;
    param_9_back->child = box;
    g_signal_connect(back_9, "clicked", G_CALLBACK(press), (gpointer)param_9_back);

  // Analisis Pasien dan Penyakit
    GtkWidget *box_10 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_10);
    GtkWidget *child_10 = gtk_label_new("== Analisis Pasien dan Penyakit ==");
    gtk_box_append(GTK_BOX(box_10), child_10);
    dataParam *param_10 = malloc(sizeof(dataParam));
    param_10->stack = stack;
    param_10->child = box_10;
    g_signal_connect(button10, "clicked", G_CALLBACK(press), (gpointer)param_10);
    GtkWidget *new_line_10a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_10), new_line_10a);
    GtkWidget *result_label_10 = gtk_label_new(NULL);
    gtk_box_append(GTK_BOX(box_10), result_label_10);
    analisis_pasien_penyakit();    
    GtkWidget *new_line_10b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_10), new_line_10b);
    GtkWidget *back_10 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_10), back_10);
    dataParam *param_10_back = malloc(sizeof(dataParam));
    param_10_back->stack = stack;
    param_10_back->child = box;
    g_signal_connect(back_10, "clicked", G_CALLBACK(press), (gpointer)param_10_back);

  // Informasi Kontrol
    GtkWidget *box_11 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box_11);
    GtkWidget *child_11 = gtk_label_new("== Informasi Kontrol Pasien ==");
    gtk_box_append(GTK_BOX(box_11), child_11);
    dataParam *param_11 = malloc(sizeof(dataParam));
    param_11->stack = stack;
    param_11->child = box_11;
    g_signal_connect(button11, "clicked", G_CALLBACK(press), (gpointer)param_11);
    GtkWidget *new_line_11a = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_11), new_line_11a);
    GtkWidget *result_label_11 = gtk_label_new(NULL);
    gtk_box_append(GTK_BOX(box_11), result_label_11);
    informasi_kontrol_pasien;    
    GtkWidget *new_line_11b = gtk_label_new("\n");
    gtk_box_append(GTK_BOX(box_11), new_line_11b);
    GtkWidget *back_11 = gtk_button_new_with_label("Kembali ke Menu Utama");
    gtk_box_append(GTK_BOX(box_11), back_11);
    dataParam *param_11_back = malloc(sizeof(dataParam));
    param_11_back->stack = stack;
    param_11_back->child = box;
    g_signal_connect(back_11, "clicked", G_CALLBACK(press), (gpointer)param_11_back);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  data_pasien = readDataPasien("Data Pasien.csv", &size_data_pasien);

  app = gtk_application_new("tubes.pmc", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}