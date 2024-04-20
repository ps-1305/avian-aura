#include <gtk/gtk.h>
#include <stdbool.h>

#define NEW_GTK_TOPLEVEL "new"
#define DESTROY_OLD_TOPLEVEL "destroy"
#define max 100

GtkWidget* username_entry;
GtkWidget* rec_code_entry;
GtkWidget* forgot_btn;
bool flag = false;
FILE* __db__;

void forgotPasswordcheck(GtkWidget* widget, GdkEvent* event){
    const char* uname =  gtk_entry_get_text(GTK_ENTRY(username_entry));
    const char* rc =  gtk_entry_get_text(GTK_ENTRY(rec_code_entry));

    __db__ = fopen("db.csv", "r");
    char row[max];
    char* token;
    fgets(row, max, __db__);
    while(fgets(row, max, __db__)){
        token = strtok(row, ","); // 1 
        if(strcmp(token,uname) == 0){
            token = strtok(NULL, ", "); // 2
            token = strtok(NULL, ", "); // 3
            token = strtok(NULL, ", "); // 4
            token = strtok(NULL, ", "); // 5
            if(strcmp(token, rc) == 0){
                fclose(__db__);
                flag = true;
                return;
            }
        }
    }
    fclose(__db__);
    flag = false;
    return;
}

bool forgot_password_init(int argc, char* argv[]){
    char* args[] = {NEW_GTK_TOPLEVEL, DESTROY_OLD_TOPLEVEL};
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Avian Aura : Login");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // 3. Username
    GtkWidget *hbox_3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_3);

    GtkWidget *username_label = gtk_label_new("Username: ");
    gtk_box_pack_start(GTK_BOX(hbox_3), username_label, FALSE, FALSE, 0);
    username_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_3), username_entry, FALSE, FALSE, 0);

    // 5. Recovery code
    GtkWidget *hbox_5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_5);

    GtkWidget *recovery_code = gtk_label_new("Recovery code: ");
    gtk_box_pack_start(GTK_BOX(hbox_5), recovery_code, FALSE, FALSE, 0);
    rec_code_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_5), rec_code_entry, FALSE, FALSE, 0);

    // 6. Button
    forgot_btn = gtk_button_new_with_label("Login");
    g_signal_connect(forgot_btn, "clicked", G_CALLBACK(forgotPasswordcheck), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), forgot_btn, FALSE, FALSE, 0);

    // .showall()
    gtk_widget_show_all(window);

    // .mainloop()
    gtk_main();

    return flag;
}