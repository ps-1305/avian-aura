#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *qty;
GtkWidget *date;
GtkWidget *comboBox_1;
GtkWidget *comboBox_2;
int parsedFrom, parsedTo;
int ecoPrice;
FILE* rail_ticket;

void dijsktra_rail(GtkWidget *widget, GdkEvent* event){
    char* ticketingDate = gtk_entry_get_text(GTK_ENTRY(date));
    gchar* from = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(GTK_COMBO_BOX_TEXT(comboBox_1)));
    gchar* to = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(GTK_COMBO_BOX_TEXT(comboBox_2)));
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
        if(g_strcmp0(from, train_cities[i]) == 0){
            parsedFrom = i;
        }
        if(g_strcmp0(to, train_cities[i]) == 0){
            parsedTo = i;
        }     
    }

    int ecoPrice = dijkstrasAlgorithm(bus, parsedFrom, parsedTo);

    char filename[100];
    sprintf(filename, "railwayTkt-date-%s.txt", ticketingDate);
    rail_ticket = fopen(filename, "w");
    fprintf(rail_ticket, "Date : %s\n", ticketingDate);
    fprintf(rail_ticket, "From : %s\n", train_cities[parsedFrom]);
    fprintf(rail_ticket, "To : %s\n", train_cities[parsedTo]);
    fprintf(rail_ticket, "Price : Rupees %s /-\n", ecoPrice);
    fclose(rail_ticket);
}

void railTicket_init(int argc, char* argv[]){
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Railways");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 75);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *hbox_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_1);

    GtkWidget *from_label = gtk_label_new("From: ");
    gtk_box_pack_start(GTK_BOX(hbox_1), from_label, FALSE, FALSE, 0);

    comboBox_1 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Kanpur Central - CNB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "New Delhi - NDLS");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Mumbai - CSMT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jalandhar City - JUC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Anand Vihar Terminus - ANVT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Vijaywada - BZA");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jalgaon - JL");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Old Delhi - DLI");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Dadar - DR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Howrah - HWH");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Mughalsarai - DDU");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Patna - PNBE");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Guwahati - GHY");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Lucknow Charbagh - LKO");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Vadodra - BRC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Ahmedabad - ADI");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Varanasi - BSB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Bengaluru - SBC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Vizag - VSKP");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Chennai Central - MAS");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Ambarsar - ASR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jammu Tawi - JAT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Gwalior - GWL");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Hyderabad - HYB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Coimbatore - CBE");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Kollam - QLN");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Danapur - DNR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Cuttack - CTC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Kota - KOTA");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jodhpur - JU");

    gtk_box_pack_start(GTK_BOX(hbox_1), comboBox_1, TRUE, TRUE, 0);    
    
    //

    GtkWidget *hbox_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_2);

    GtkWidget *to_label = gtk_label_new("From: ");
    gtk_box_pack_start(GTK_BOX(hbox_2), to_label, FALSE, FALSE, 0);

    comboBox_2 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Kanpur Central - CNB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "New Delhi - NDLS");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Mumbai - CSMT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jalandhar City - JUC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Anand Vihar Terminus - ANVT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Vijaywada - BZA");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jalgaon - JL");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Old Delhi - DLI");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Dadar - DR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Howrah - HWH");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Mughalsarai - DDU");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Patna - PNBE");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Guwahati - GHY");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Lucknow Charbagh - LKO");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Vadodra - BRC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Ahmedabad - ADI");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Varanasi - BSB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Bengaluru - SBC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Vizag - VSKP");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Chennai Central - MAS");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Ambarsar - ASR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jammu Tawi - JAT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Gwalior - GWL");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Hyderabad - HYB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Coimbatore - CBE");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Kollam - QLN");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Danapur - DNR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Cuttack - CTC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Kota - KOTA");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_1), "Jodhpur - JU");

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
    g_signal_connect(login_button, "clicked", G_CALLBACK(dijsktra_rail), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, FALSE, FALSE, 0);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}