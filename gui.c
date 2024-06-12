#include <gtk/gtk.h>

typedef struct dataParam {
    GtkWidget *stack;
    GtkWidget *child;
} dataParam;

static void tekan(GtkWidget *widget, gpointer data) {
    dataParam *param = (dataParam*) data;
    gtk_stack_set_visible_child(GTK_STACK(param->stack), param->child);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *judul;

    window = gtk_application_window_new(app);

    GtkWidget *stack = gtk_stack_new();
    gtk_window_set_child(GTK_WINDOW(window), stack);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box);

    judul = gtk_label_new("Sistem Pencatatan Pasien Klinik X");
    gtk_box_append(GTK_BOX(box), judul);

    GtkWidget *dialog = gtk_label_new("Selamat datang! Berikut adalah rincian fitur yang dapat digunakan:");
    gtk_box_append(GTK_BOX(box), dialog);

    GtkWidget *button = gtk_button_new_with_label("Tekan Ini");
    gtk_box_append(GTK_BOX(box), button);

    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_stack_add_child(GTK_STACK(stack), box2);

    GtkWidget *entahapa = gtk_label_new("Ini halaman 2");
    gtk_box_append(GTK_BOX(box2), entahapa);

    dataParam  *param1 = malloc(sizeof(dataParam));
    param1->stack = stack;
    param1->child = box2;

    g_signal_connect(button, "clicked", G_CALLBACK(tekan),(gpointer) param1);

    GtkStringList *stringlist = gtk_string_list_new(NULL);
    gtk_string_list_append(stringlist, "Ini yang pertama anjim");

    GtkWidget *dropDown = gtk_drop_down_new(G_LIST_MODEL(stringlist), NULL);
    gtk_box_append(GTK_BOX(box2), dropDown);


    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    
    GtkApplication *app = gtk_application_new("ini.apa.aja", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}