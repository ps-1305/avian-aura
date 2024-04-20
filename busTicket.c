#include <stdio.h>
#include <gtk/gtk.h>
#include "graphs.h"

GtkWidget *qty;
GtkWidget *date;
GtkWidget *comboBox_1;
GtkWidget *comboBox_2;
int parsedFrom, parsedTo;
int ecoPrice;
FILE* bus_ticket;

void dijsktra_bus(GtkWidget *widget, GdkEvent* event){
    gchar* from = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox_1));
    gchar* to = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox_2));
    if(g_strcmp0(from, to) == 0){
        GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(gtk_widget_get_toplevel(widget)),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_CLOSE,
        "You cannot travel to the same city!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    for(int i=0; i<30; i++){
        if(g_strcmp0(from, bus_cities[i]) == 0){
            parsedFrom = i;
        }
        if(g_strcmp0(to, bus_cities[i]) == 0){
            parsedTo = i;
        }     
    }

    int ecoPrice = dijkstrasAlgorithm(bus, parsedFrom, parsedTo);

    char filename[100];
    sprintf(filename, "%s-to-%s-date-%s.txt", bus_cities[parsedFrom], buscities[parsedTo], ticketingDate);
    bus_ticket = fopen(filename, "w");
    fprintf(bus_ticket, "Date : %s\n", ticketingDate);
    fprintf(bus_ticket, "From : %s\n", bus_cities[parsedFrom]);
    fprintf(bus_ticket, "To : %s\n", bus_cities[parsedTo]);
    fprintf(rail_ticket, "Price : Rupees %s /-\n", ecoPrice);
    fclose(bus_ticket);
}

void busTicket_init(int argc, char* argv[]){
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Roadways");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 75);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *hbox_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_1);

    GtkWidget *from_label = gtk_label_new("From: ");
    gtk_box_pack_start(GTK_BOX(hbox_1), from_label, FALSE, FALSE, 0);

    comboBox_1 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Ajmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jalore");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jodhpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Sikar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Aligarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Nagaur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jaisalmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Udaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Bhilwara");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Mount Abu");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Barmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Alwar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Sri Ganganagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Faridabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Gurugram");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Rohtak");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Sonipat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Panipat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Palwal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jind");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Karnal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Meerut");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Ghaziabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Gautam Buddha Nagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Panchkula");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Chandigarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Delhi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Bharatpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Agra");

    gtk_box_pack_start(GTK_BOX(hbox_1), comboBox_1, TRUE, TRUE, 0);    
    
    //

    GtkWidget *hbox_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_2);

    GtkWidget *to_label = gtk_label_new("To: ");
    gtk_box_pack_start(GTK_BOX(hbox_2), to_label, FALSE, FALSE, 0);

    comboBox_2 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Jaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Ajmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Jalore");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Jodhpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Sikar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Aligarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Nagaur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Jaisalmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Udaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Bhilwara");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Mount Abu");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Barmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Alwar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Sri Ganganagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Faridabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Gurugram");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Rohtak");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Sonipat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Panipat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Palwal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Jind");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Karnal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Meerut");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Ghaziabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Gautam Buddha Nagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Panchkula");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Chandigarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Delhi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Bharatpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_2), "Agra");

    gtk_box_pack_start(GTK_BOX(hbox_2), comboBox_2, TRUE, TRUE, 0);

    GtkWidget *hbox_3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_3);

    GtkWidget *people = gtk_label_new("Passengers: ");
    gtk_box_pack_start(GTK_BOX(hbox_3), people, FALSE, FALSE, 0);

    GtkAdjustment *adjustment = gtk_adjustment_new (1.0, 0.0, 10.0, 1.0, 1.0, 0.0);
    gdouble cRate = 1;
    guint decimals = 0;
    qty = gtk_spin_button_new(adjustment, cRate, decimals);
    gtk_box_pack_start(GTK_BOX(hbox_3), qty, FALSE, FALSE, 0);

    GtkWidget *hbox_4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_4);

    GtkWidget *date_label = gtk_label_new("Date: ");
    gtk_box_pack_start(GTK_BOX(hbox_4), date_label, FALSE, FALSE, 0);

    date = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_4), date, TRUE, TRUE, 0);

    GtkWidget* login_button = gtk_button_new_with_label("Book tickets");
    g_signal_connect(login_button, "clicked", G_CALLBACK(dijsktra_bus), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, FALSE, FALSE, 0);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}