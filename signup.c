#include <gtk/gtk.h>

GtkWidget* fname_entry;
GtkWidget* lname_entry;
GtkWidget* username_entry;
GtkWidget* password_entry;
GtkWidget* rec_code_entry;
GtkWidget* signup_btn;
FILE* __db__;

void signupTodb(GtkWidget* widget, GdkEvent* event){
    __db__ = fopen("db.csv", "a");
    const char* fname =  gtk_entry_get_text(GTK_ENTRY(fname_entry));
    const char* lname =  gtk_entry_get_text(GTK_ENTRY(lname_entry));
    const char* uname =  gtk_entry_get_text(GTK_ENTRY(username_entry));
    const char* pass =  gtk_entry_get_text(GTK_ENTRY(password_entry));
    const char* rc =  gtk_entry_get_text(GTK_ENTRY(rec_code_entry));
    fprintf(__db__, "%s, %s, %s, %s, %s\n", uname, pass, fname, lname, rc);
    fclose(__db__);
}

void signup_init(int argc, char* argv[]){
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Avian Aura : Login");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // 1. First name 
    GtkWidget *hbox_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_1);

    GtkWidget *fname_label = gtk_label_new("First Name: ");
    gtk_box_pack_start(GTK_BOX(hbox_1), fname_label, FALSE, FALSE, 0);
    fname_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_1), fname_entry, FALSE, FALSE, 0);

    // 2. Last name
    GtkWidget *hbox_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_2);

    GtkWidget *lname_label = gtk_label_new("Last name: ");
    gtk_box_pack_start(GTK_BOX(hbox_2), lname_label, FALSE, FALSE, 0);
    lname_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_2), lname_entry, FALSE, FALSE, 0);

    // 3. Username
    GtkWidget *hbox_3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_3);

    GtkWidget *username_label = gtk_label_new("Username: ");
    gtk_box_pack_start(GTK_BOX(hbox_3), username_label, FALSE, FALSE, 0);
    username_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_3), username_entry, FALSE, FALSE, 0);


    // 4. Password 
    GtkWidget *hbox_4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_4);

    GtkWidget *password_label = gtk_label_new("Password: ");
    gtk_box_pack_start(GTK_BOX(hbox_4), password_label, FALSE, FALSE, 0);
    password_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_4), password_entry, FALSE, FALSE, 0);

    // 5. Recovery code
    GtkWidget *hbox_5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_5);

    GtkWidget *recovery_code = gtk_label_new("Recovery code: ");
    gtk_box_pack_start(GTK_BOX(hbox_5), recovery_code, FALSE, FALSE, 0);
    rec_code_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_5), rec_code_entry, FALSE, FALSE, 0);

    signup_btn = gtk_button_new_with_label("Signup");
    g_signal_connect(signup_btn, "clicked", G_CALLBACK(signupTodb), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), signup_btn, FALSE, FALSE, 0);

    // .showall()
    gtk_widget_show_all(window);

    // .mainloop()
    gtk_main();
}