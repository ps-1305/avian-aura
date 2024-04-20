#include "dependencies.h"

GtkWidget *username_entry;
GtkWidget *password_entry;
GtkWidget *login_button;
GtkWidget *signup_button;
GtkWidget *forgot_password;

gboolean login_attempt(GtkWidget *widget, GdkEvent *event) {
  char* args[] = {NEW_GTK_TOPLEVEL, DESTROY_OLD_TOPLEVEL};

  const char *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
  const char *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

  if(login(username,password) == true){
    gtk_widget_destroy(gtk_widget_get_toplevel(widget)); 
    main_fn_init(0, args);
    return TRUE;

  } else {

    GtkWidget *dialog = gtk_message_dialog_new(
    GTK_WINDOW(gtk_widget_get_toplevel(widget)),
    GTK_DIALOG_DESTROY_WITH_PARENT,
    GTK_MESSAGE_ERROR,
    GTK_BUTTONS_CLOSE,
    "Invalid username or password");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return FALSE;

  }
}

gboolean signup(GtkWidget *widget, GdkEvent *event){
  char* args[] = {NEW_GTK_TOPLEVEL, DESTROY_OLD_TOPLEVEL};
  signup_init(0, args);
  gtk_main_quit();
  return TRUE;
}

gboolean forgot_attempt(GtkWidget *widget, GdkEvent *event){
  char* args[] = {NEW_GTK_TOPLEVEL, DESTROY_OLD_TOPLEVEL};
  bool res = forgot_password_init(0, args);
  if(res){
    main_fn_init(0, args);
    return TRUE;
  }
  return FALSE;
}

int main(int argc, char *argv[]){
  gtk_init(&argc, &argv);

  // * main window
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Avian Aura : Login");
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  // * now we create 2 horizontal windows for username and password
  // 1. This is for username
  GtkWidget *hbox_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  gtk_container_add(GTK_CONTAINER(vbox), hbox_1);
  
  GtkWidget *username_label = gtk_label_new("Username: ");
  gtk_box_pack_start(GTK_BOX(hbox_1), username_label, FALSE, FALSE, 0);
  username_entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(hbox_1), username_entry, FALSE, FALSE, 0);

  // 2. This is for password 
  GtkWidget *hbox_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  gtk_container_add(GTK_CONTAINER(vbox), hbox_2);

  GtkWidget *password_label = gtk_label_new("Password: ");
  gtk_box_pack_start(GTK_BOX(hbox_2), password_label, FALSE, FALSE, 0);
  password_entry = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
  gtk_box_pack_start(GTK_BOX(hbox_2), password_entry, FALSE, FALSE, 0);

  // 3. Login button
  login_button = gtk_button_new_with_label("Login");
  g_signal_connect(login_button, "clicked", G_CALLBACK(login_attempt), NULL);
  gtk_box_pack_start(GTK_BOX(vbox), login_button, FALSE, FALSE, 0);
  
  // 4. Signup button
  signup_button = gtk_button_new_with_label("Signup");
  g_signal_connect(signup_button, "clicked", G_CALLBACK(signup), NULL);
  gtk_box_pack_start(GTK_BOX(vbox), signup_button, FALSE, FALSE, 0);
  
  // 5. Forgot password  button
  forgot_password = gtk_button_new_with_label("Forgot Password");
  g_signal_connect(forgot_password, "clicked", G_CALLBACK(forgot_attempt), NULL);
  gtk_box_pack_start(GTK_BOX(vbox), forgot_password, FALSE, FALSE, 0);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Show all widgets and run the main loop
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
