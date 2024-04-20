#include "secondary.h"

GtkWidget* airways_button;
GtkWidget* railways_button;
GtkWidget* bus_button;
GtkWidget* wayfarer_button;
GtkWidget* logout_button;

char* arguments = {PLACEHOLDER_ARGS};

static void destroy_window(GtkWidget *window, gpointer data){
    gtk_main_quit();
}

void airways_callback(GtkWidget *widget, GdkEvent *event){
  return;
}

void railways_callback(GtkWidget *widget, GdkEvent *event){
  railTicket_init(0, &arguments);
}

void bus_callback(GtkWidget *widget, GdkEvent *event){
  busTicket_init(0, &arguments);
}

void wayfarer_callback(GtkWidget *widget, GdkEvent *event){
  return;
}

void main_fn_init(int argc, char* argv[]){
  gtk_init(&argc, &argv);

  // window
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Avian Aura");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  // airways
  airways_button = gtk_button_new_with_label("Flights");
  g_signal_connect(airways_button, "clicked", G_CALLBACK(airways_callback), NULL);
  gtk_box_pack_start(GTK_BOX(vbox), airways_button, FALSE, FALSE, 0);
  
  // railways
  railways_button = gtk_button_new_with_label("Trains");
  g_signal_connect(railways_button, "clicked", G_CALLBACK(railways_callback), NULL);
  gtk_box_pack_start(GTK_BOX(vbox), railways_button, FALSE, FALSE, 0);

  // buses
  bus_button = gtk_button_new_with_label("Buses");
  g_signal_connect(bus_button, "clicked", G_CALLBACK(bus_callback), NULL);
  gtk_box_pack_start(GTK_BOX(vbox), bus_button, FALSE, FALSE, 0);

  // wayfarer 
  wayfarer_button = gtk_button_new_with_label("Wayfarer");
  g_signal_connect(wayfarer_button, "clicked", G_CALLBACK(wayfarer_callback), NULL);
  gtk_box_pack_start(GTK_BOX(vbox), wayfarer_button, FALSE, FALSE, 0);
  
  // logout
  logout_button = gtk_button_new_with_label("Logout");
  g_signal_connect(logout_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
  gtk_box_pack_start(GTK_BOX(vbox), logout_button, FALSE, FALSE, 0);

  // __exit__
  g_signal_connect(window, "destroy", G_CALLBACK(destroy_window), NULL);

  // .showall()
  gtk_widget_show_all(window);

  // .mainloop()
  gtk_main();
}