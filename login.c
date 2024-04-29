#include "signup.c"
#include "forgot_password.c"
#include "authenticateUser.c"
#include "major.c"
#define NEW_GTK_TOPLEVEL "new"
#define DESTROY_OLD_TOPLEVEL "destroy"

GtkWidget *username_entry;
GtkWidget *password_entry;
GtkWidget *login_button;
GtkWidget *signup_button;
GtkWidget *forgot_password;
GtkWidget *window;

/*
__CALLBACK__
args = widget pointer and event pointer (G_CALLBACK)
returns = gboolean (not of any use, only signifies whether a user has valid credentials or not)
function = logs a user in using the login() function of authenticateUser.c
*/
gboolean login_attempt(GtkWidget *widget, GdkEvent *event){
  char* args[] = {NEW_GTK_TOPLEVEL, DESTROY_OLD_TOPLEVEL};

  const char *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
  const char *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
  char name[100];

  if(login(username,password, name) == true){
    gtk_main_quit();
    gtk_widget_hide(window);
    major_init(0, args, name);
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

/*
__CALLBACK__
args = widget pointer and event pointer (G_CALLBACK)
returns = gboolean (only signifies whether a user has signed up or not)
function = 
*/
gboolean signup(GtkWidget *widget, GdkEvent *event){
  gtk_main_quit();
  char* args[] = {NEW_GTK_TOPLEVEL, DESTROY_OLD_TOPLEVEL};
  signup_init(0, args);
  return TRUE;
}

/*
__CALLBACK__
args = widget pointer and event pointer (G_CALLBACK)
returns = gboolean (not of any use)
function = calls a function forgot_password_init (from forgot_password.c) and logs in a user if 
the function returns back true (line 157 :: forgot_password.c)
*/
gboolean forgot_attempt(GtkWidget *widget, GdkEvent *event){
  char* args[] = {NEW_GTK_TOPLEVEL, DESTROY_OLD_TOPLEVEL};
  char security[20] = "**** ****";
  bool res = forgot_password_init(0, args, security);
  
  if(res){
    gtk_widget_hide(window);
    major_init(0, args, security);
    return TRUE;
  }
  return FALSE;
}

int main(int argc, char *argv[]){
  // __init__ 
  gtk_init(&argc, &argv);

  // * photos
  GdkPixbuf *logo = gdk_pixbuf_new_from_file("img/logo.png", NULL);
  GdkPixbuf *logo_scaled = gdk_pixbuf_scale_simple(logo, 200, 200, GDK_INTERP_BILINEAR);
  GtkWidget *image_logo = gtk_image_new_from_pixbuf(logo_scaled);
  
  GdkPixbuf *btn_1 = gdk_pixbuf_new_from_file("img/login_button.png", NULL);
  GdkPixbuf *btn_1_scaled = gdk_pixbuf_scale_simple(btn_1, 225, 50, GDK_INTERP_BILINEAR);
  GtkWidget *image_btn_1 = gtk_image_new_from_pixbuf(btn_1_scaled);
  
  GdkPixbuf *btn_2 = gdk_pixbuf_new_from_file("img/signup_button.png", NULL);
  GdkPixbuf *btn_2_scaled = gdk_pixbuf_scale_simple(btn_2, 225, 50, GDK_INTERP_BILINEAR);
  GtkWidget *image_btn_2 = gtk_image_new_from_pixbuf(btn_2_scaled);
  
  GdkPixbuf *btn_3 = gdk_pixbuf_new_from_file("img/forgot_button.png", NULL);
  GdkPixbuf *btn_3_scaled = gdk_pixbuf_scale_simple(btn_3, 225, 50, GDK_INTERP_BILINEAR);
  GtkWidget *image_btn_3 = gtk_image_new_from_pixbuf(btn_3_scaled);

  // * main window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Avian Aura : Login");
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  // ! gtk window can only handle 1 widget inside it, so we keep it a vertical box
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  // * adding the photo first
  GtkWidget *logo_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(logo_button), image_logo);
  gtk_button_set_always_show_image(GTK_BUTTON(logo_button), TRUE);
  gtk_widget_set_margin_top(logo_button, 20);
  gtk_widget_set_margin_start(logo_button, 20);
  gtk_widget_set_margin_end(logo_button, 20);
  gtk_box_pack_start(GTK_BOX(vbox), logo_button, FALSE, FALSE, 0);

  // * now we create 2 horizontal windows for username and password
  // 1. This is for username
  GtkWidget *hbox_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  gtk_container_add(GTK_CONTAINER(vbox), hbox_1);
  pad_from_all_sides(hbox_1, 20);
  
  // label
  GtkWidget *username_label = gtk_label_new("Username: ");
  gtk_box_pack_start(GTK_BOX(hbox_1), username_label, FALSE, FALSE, 0);
  // entry
  username_entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(hbox_1), username_entry, FALSE, FALSE, 0);

  // 2. This is for password 
  GtkWidget *hbox_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  gtk_container_add(GTK_CONTAINER(vbox), hbox_2);
  gtk_widget_set_margin_bottom(hbox_1, 20);
  gtk_widget_set_margin_start(hbox_2, 20);
  gtk_widget_set_margin_end(hbox_2, 20);

  // label
  GtkWidget *password_label = gtk_label_new("Password: ");
  gtk_box_pack_start(GTK_BOX(hbox_2), password_label, FALSE, FALSE, 0);
  // entry
  password_entry = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE); // we set the visibility false for password
  gtk_box_pack_start(GTK_BOX(hbox_2), password_entry, FALSE, FALSE, 0);

  // 3. Login button
  login_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(login_button), image_btn_1);
  gtk_button_set_always_show_image(GTK_BUTTON(login_button), TRUE); // img
  g_signal_connect(login_button, "clicked", G_CALLBACK(login_attempt), NULL); // calling our login function
  gtk_box_pack_start(GTK_BOX(vbox), login_button, FALSE, FALSE, 0);
  gtk_widget_set_margin_start(login_button, 20);
  gtk_widget_set_margin_end(login_button, 20);

  // 4. Signup button
  signup_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(signup_button), image_btn_2);
  gtk_button_set_always_show_image(GTK_BUTTON(signup_button), TRUE);  // img
  g_signal_connect(signup_button, "clicked", G_CALLBACK(signup), NULL); // calling our signup function
  gtk_box_pack_start(GTK_BOX(vbox), signup_button, FALSE, FALSE, 0);
  gtk_widget_set_margin_start(signup_button, 20);
  gtk_widget_set_margin_end(signup_button, 20);
  
  // 5. Forgot password  button
  forgot_password = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(forgot_password), image_btn_3);
  gtk_button_set_always_show_image(GTK_BUTTON(forgot_password), TRUE);  // img
  g_signal_connect(forgot_password, "clicked", G_CALLBACK(forgot_attempt), NULL); // calling our forgot attempt function
  gtk_box_pack_start(GTK_BOX(vbox), forgot_password, FALSE, FALSE, 0);
  gtk_widget_set_margin_bottom(forgot_password, 20);
  gtk_widget_set_margin_start(forgot_password, 20);
  gtk_widget_set_margin_end(forgot_password, 20);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // .showall()
  gtk_widget_show_all(window);

  // .mainloop()
  gtk_main();

  return 0;
}
