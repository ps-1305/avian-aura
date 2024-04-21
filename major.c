#include "dependencies.h"

void busDijsktra(GtkWidget* widget, GdkEvent* event){
    const char* ticketingDate = gtk_entry_get_text(GTK_ENTRY(date_b));
    gchar* from = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox_b1));
    gchar* to = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox_b2));
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

    int ecoPrice = (int) dijkstrasAlgorithm(bus, parsedFrom, parsedTo);

    char filename[100];
    sprintf(filename, "%s-to-%s-date-%s.txt", bus_cities[parsedFrom], bus_cities[parsedTo], ticketingDate);
    ticket = fopen(filename, "w");
    fprintf(ticket, "Date : %s\n", ticketingDate);
    fprintf(ticket, "From : %s\n", bus_cities[parsedFrom]);
    fprintf(ticket, "To : %s\n", bus_cities[parsedTo]);
    fprintf(ticket, "Price : Rupees %d /-\n", ecoPrice);
    fclose(ticket);
}

void pad_from_all_sides(GtkWidget *widget, int padding){
    gtk_widget_set_margin_top(widget, padding);
    gtk_widget_set_margin_start(widget, padding);
    gtk_widget_set_margin_end(widget, padding);
    gtk_widget_set_margin_bottom(widget, padding);
}

void trainDijsktra(GtkWidget* widget, GdkEvent* event){
    const char* ticketingDate = gtk_entry_get_text(GTK_ENTRY(date_b));
    gchar* from = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox_b1));
    gchar* to = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox_b2));
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

    int ecoPrice = (int) dijkstrasAlgorithm(trains, parsedFrom, parsedTo);

    char filename[100];
    sprintf(filename, "%s-to-%s-date-%s.txt", train_cities[parsedFrom], train_cities[parsedTo], ticketingDate);
    ticket = fopen(filename, "w");
    fprintf(ticket, "Date : %s\n", ticketingDate);
    fprintf(ticket, "From : %s\n", train_cities[parsedFrom]);
    fprintf(ticket, "To : %s\n", train_cities[parsedTo]);
    fprintf(ticket, "Price : Rupees %d /-\n", ecoPrice);
    fclose(ticket);
}

void flightDijsktra(GtkWidget* widget, GdkEvent* event){
    const char* ticketingDate = gtk_entry_get_text(GTK_ENTRY(date_b));
    gchar* from = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox_b1));
    gchar* to = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox_b2));
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

    int ecoPrice = (int) dijkstrasAlgorithm(flights, parsedFrom, parsedTo);

    char filename[100];
    sprintf(filename, "%s-to-%s-date-%s.txt", bus_cities[parsedFrom], bus_cities[parsedTo], ticketingDate);
    ticket = fopen(filename, "w");
    fprintf(ticket, "Date : %s\n", ticketingDate);
    fprintf(ticket, "From : %s\n", bus_cities[parsedFrom]);
    fprintf(ticket, "To : %s\n", bus_cities[parsedTo]);
    fprintf(ticket, "Price : Rupees %d /-\n", ecoPrice);
    fclose(ticket);
}


int major_init(int argc, char *argv[], char name[]) {
    gtk_init(&argc, &argv);

    // * predefinitions
    GtkAdjustment *adjustment = gtk_adjustment_new (1.0, 0.0, 10.0, 1.0, 1.0, 0.0);
    gdouble cRate = 1;
    guint decimals = 0;

    // * photos
    // flights photo
    GdkPixbuf *flight_image = gdk_pixbuf_new_from_file("img/flights.png", NULL);
    GdkPixbuf *flight_scaled = gdk_pixbuf_scale_simple(flight_image, 400, 500, GDK_INTERP_BILINEAR);
    GtkWidget *image_1 = gtk_image_new_from_pixbuf(flight_scaled);
    
    // trains photo
    GdkPixbuf *train_image = gdk_pixbuf_new_from_file("img/trains.png", NULL);
    GdkPixbuf *train_scaled = gdk_pixbuf_scale_simple(train_image, 400, 500, GDK_INTERP_BILINEAR);
    GtkWidget *image_2 = gtk_image_new_from_pixbuf(train_scaled);
    
    // bus photo
    GdkPixbuf *bus_image = gdk_pixbuf_new_from_file("img/buses.png", NULL);
    GdkPixbuf *bus_scaled = gdk_pixbuf_scale_simple(bus_image, 400, 500, GDK_INTERP_BILINEAR);
    GtkWidget *image_3 = gtk_image_new_from_pixbuf(bus_scaled);

    // profile photo
    GdkPixbuf *profile_image = gdk_pixbuf_new_from_file("img/profile.jpeg", NULL);
    GdkPixbuf *profile_scaled = gdk_pixbuf_scale_simple(profile_image, 200, 300, GDK_INTERP_BILINEAR);
    GtkWidget *image_4 = gtk_image_new_from_pixbuf(profile_scaled);

    // * styling
    // font information
    PangoAttrList* attrs = pango_attr_list_from_string("0 -1 family Menlo, 0 100 weight bold");

    // window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Avian Aura");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // container for stack and stack-switcher
    GtkWidget *major = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), major);

    // * vertical boxes for 4 sections
    GtkWidget *vboxF = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // flights
    GtkWidget *vboxT = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // trains
    GtkWidget *vboxB = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // buses
    GtkWidget *vboxP = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // profile

    // * vertical box P
    GtkWidget *profile_image_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(profile_image_button), image_4);
    gtk_button_set_always_show_image(GTK_BUTTON(profile_image_button), TRUE);
    pad_from_all_sides(profile_image_button, 20);
    gtk_box_pack_start(GTK_BOX(vboxP), profile_image_button, FALSE, FALSE, 0);

    GtkWidget *label_p = gtk_label_new(name);
    pad_from_all_sides(label_p, 20);
    gtk_box_pack_start(GTK_BOX(vboxP), label_p, FALSE, FALSE, 0);
    gtk_label_set_attributes(GTK_LABEL(label_p), attrs);

    // * vertical box F
    GtkWidget *flight_image_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(flight_image_button), image_1);
    gtk_button_set_always_show_image(GTK_BUTTON(flight_image_button), TRUE);
    pad_from_all_sides(flight_image_button, 20);
    gtk_box_pack_start(GTK_BOX(vboxF), flight_image_button, FALSE, FALSE, 0);

    GtkWidget* hbox_f1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_pack_start(GTK_BOX(vboxF), hbox_f1, TRUE, TRUE, 0);

    GtkWidget* from_f = gtk_label_new("From: ");
    gtk_box_pack_start(GTK_BOX(hbox_f1), from_f, TRUE, TRUE, 0);
    gtk_widget_set_margin_bottom(from_f, 10);

    comboBox_f1 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "SXR - Srinagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "IXJ - Jammu");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "ATQ - Ambarsar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "IXC - Chandigarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "DED - Dehradoon");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "DEL - Delhi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "JDH - Jodhpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "JAI - Jaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "LKO - Lucknow");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "AYJ - Ayodhya");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "GAU - Guwahati");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "IMF - Imphal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "PAT - Patna");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "VNS - Varanasi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "AMD - Ahmedabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "BDQ - Vadodra");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "BHO - Bhopal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "CCU - Kolkata");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "STV - Surat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "NAG - Nagpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "BOM - Mumbai");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "PNQ - Pune");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "HYD - Hyderabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "VTZ - Vizag");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "GOI - Goa Intl");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "BLR - Bangalore");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "MAA - Madras");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "IXE - Mangalore");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "COK - Kochi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f1), "TRV - Trivandrum");

    gtk_box_pack_start(GTK_BOX(hbox_f1), comboBox_f1, TRUE, TRUE, 1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox_f1), 15);
    gtk_widget_set_margin_end(comboBox_f1, 20);
    gtk_widget_set_margin_bottom(comboBox_f1, 10);
    
    //

    GtkWidget* hbox_f2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_pack_start(GTK_BOX(vboxF), hbox_f2, TRUE, TRUE, 0);

    GtkWidget* to_f = gtk_label_new("To: ");
    gtk_box_pack_start(GTK_BOX(hbox_f2), to_f, TRUE, TRUE, 0);
    gtk_widget_set_margin_bottom(to_f, 10);
    gtk_widget_set_margin_end(to_f, 12);

    comboBox_f2 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "SXR - Srinagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "IXJ - Jammu");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "ATQ - Ambarsar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "IXC - Chandigarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "DED - Dehradoon");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "DEL - Delhi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "JDH - Jodhpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "JAI - Jaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "LKO - Lucknow");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "AYJ - Ayodhya");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "GAU - Guwahati");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "IMF - Imphal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "PAT - Patna");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "VNS - Varanasi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "AMD - Ahmedabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "BDQ - Vadodra");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "BHO - Bhopal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "CCU - Kolkata");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "STV - Surat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "NAG - Nagpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "BOM - Mumbai");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "PNQ - Pune");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "HYD - Hyderabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "VTZ - Vizag");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "GOI - Goa Intl");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "BLR - Bangalore");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "MAA - Madras");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "IXE - Mangalore");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "COK - Kochi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_f2), "TRV - Trivandrum");

    gtk_box_pack_start(GTK_BOX(hbox_f2), comboBox_f2, TRUE, TRUE, 1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox_f2), 16);
    gtk_widget_set_margin_end(comboBox_f2, 20);
    gtk_widget_set_margin_bottom(comboBox_f2, 10);

    // 

    GtkWidget *hbox_f3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vboxF), hbox_f3);

    GtkWidget *passengers_f = gtk_label_new("Passengers: ");
    gtk_box_pack_start(GTK_BOX(hbox_f3), passengers_f, FALSE, FALSE, 0);
    gtk_widget_set_margin_start(passengers_f, 150);

    qty_f = gtk_spin_button_new(adjustment, cRate, decimals);
    gtk_box_pack_start(GTK_BOX(hbox_f3), qty_f, FALSE, FALSE, 0);

    //

    GtkWidget *hbox_f4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vboxF), hbox_f4);

    GtkWidget *date_label_f = gtk_label_new("Date: ");
    gtk_box_pack_start(GTK_BOX(hbox_f4), date_label_f, FALSE, FALSE, 0);
    gtk_widget_set_margin_start(date_label_f, 70);
    gtk_widget_set_margin_end(date_label_f, 75);

    date_f = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_f4), date_f, TRUE ,TRUE, 0);
    gtk_widget_set_margin_end(date_f, 20);

    GtkWidget* book_f = gtk_button_new_with_label("Book tickets");
    g_signal_connect(book_f, "clicked", G_CALLBACK(flightDijsktra), NULL);
    gtk_box_pack_start(GTK_BOX(vboxF), book_f, FALSE, FALSE, 0);


    // * vertical box T
    GtkWidget *train_image_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(train_image_button), image_2);
    gtk_button_set_always_show_image(GTK_BUTTON(train_image_button), TRUE);
    pad_from_all_sides(train_image_button, 20);
    gtk_box_pack_start(GTK_BOX(vboxT), train_image_button, FALSE, FALSE, 0);

    GtkWidget* hbox_tr1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_pack_start(GTK_BOX(vboxT), hbox_tr1, TRUE, TRUE, 0);
    GtkWidget* from_tr = gtk_label_new("From: ");
    gtk_box_pack_start(GTK_BOX(hbox_tr1), from_tr, TRUE, TRUE, 0);
    gtk_widget_set_margin_bottom(from_tr, 10);

    comboBox_tr1 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Kanpur Central - CNB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "New Delhi - NDLS");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Mumbai - CSMT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Jalandhar City - JUC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Anand Vihar Terminus - ANVT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Vijaywada - BZA");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Jalgaon - JL");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Old Delhi - DLI");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Dadar - DR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Howrah - HWH");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Mughalsarai - DDU");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Patna - PNBE");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Guwahati - GHY");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Lucknow Charbagh - LKO");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Vadodra - BRC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Ahmedabad - ADI");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Varanasi - BSB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Bengaluru - SBC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Vizag - VSKP");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Chennai Central - MAS");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Ambarsar - ASR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Jammu Tawi - JAT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Gwalior - GWL");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Hyderabad - HYB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Coimbatore - CBE");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Kollam - QLN");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Danapur - DNR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Cuttack - CTC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Kota - KOTA");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr1), "Jodhpur - JU");

    gtk_box_pack_start(GTK_BOX(hbox_tr1), comboBox_tr1, TRUE, TRUE, 1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox_tr1), 16);
    gtk_widget_set_margin_end(comboBox_tr1, 20);
    gtk_widget_set_margin_bottom(comboBox_tr1, 10);
    
    //

    GtkWidget* hbox_tr2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_pack_start(GTK_BOX(vboxT), hbox_tr2, TRUE, TRUE, 0);

    GtkWidget* to_tr = gtk_label_new("To: ");
    gtk_box_pack_start(GTK_BOX(hbox_tr2), to_tr, TRUE, TRUE, 0);
    gtk_widget_set_margin_bottom(to_tr, 10);
    gtk_widget_set_margin_end(to_tr, 12);

    comboBox_tr2 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Kanpur Central - CNB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "New Delhi - NDLS");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Mumbai - CSMT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Jalandhar City - JUC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Anand Vihar Terminus - ANVT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Vijaywada - BZA");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Jalgaon - JL");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Old Delhi - DLI");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Dadar - DR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Howrah - HWH");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Mughalsarai - DDU");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Patna - PNBE");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Guwahati - GHY");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Lucknow Charbagh - LKO");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Vadodra - BRC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Ahmedabad - ADI");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Varanasi - BSB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Bengaluru - SBC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Vizag - VSKP");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Chennai Central - MAS");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Ambarsar - ASR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Jammu Tawi - JAT");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Gwalior - GWL");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Hyderabad - HYB");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Coimbatore - CBE");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Kollam - QLN");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Danapur - DNR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Cuttack - CTC");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Kota - KOTA");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_tr2), "Jodhpur - JU");


    gtk_box_pack_start(GTK_BOX(hbox_tr2), comboBox_tr2, TRUE, TRUE, 1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox_tr2), 15);
    gtk_widget_set_margin_end(comboBox_tr2, 20);
    gtk_widget_set_margin_bottom(comboBox_tr2, 10);

    // 

    GtkWidget *hbox_tr3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vboxT), hbox_tr3);

    GtkWidget *passengers_tr = gtk_label_new("Passengers: ");
    gtk_box_pack_start(GTK_BOX(hbox_tr3), passengers_tr, FALSE, FALSE, 0);
    gtk_widget_set_margin_start(passengers_tr, 150);

    qty_tr = gtk_spin_button_new(adjustment, cRate, decimals);
    gtk_box_pack_start(GTK_BOX(hbox_tr3), qty_tr, FALSE, FALSE, 0);

    //

    GtkWidget *hbox_tr4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vboxT), hbox_tr4);

    GtkWidget *date_label_tr = gtk_label_new("Date: ");
    gtk_box_pack_start(GTK_BOX(hbox_tr4), date_label_tr, FALSE, FALSE, 0);
    gtk_widget_set_margin_start(date_label_tr, 70);
    gtk_widget_set_margin_end(date_label_tr, 75);

    date_tr = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_tr4), date_tr, TRUE ,TRUE, 0);
    gtk_widget_set_margin_end(date_tr, 20);

    GtkWidget* book_tr = gtk_button_new_with_label("Book tickets");
    g_signal_connect(book_tr, "clicked", G_CALLBACK(trainDijsktra), NULL);
    gtk_box_pack_start(GTK_BOX(vboxT), book_tr, FALSE, FALSE, 0);

    // * vertical box B
    GtkWidget *bus_image_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(bus_image_button), image_3);
    gtk_button_set_always_show_image(GTK_BUTTON(bus_image_button), TRUE);
    pad_from_all_sides(bus_image_button, 20);
    gtk_box_pack_start(GTK_BOX(vboxB), bus_image_button, FALSE, FALSE, 0);

    GtkWidget* hbox_b1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_pack_start(GTK_BOX(vboxB), hbox_b1, TRUE, TRUE, 0);

    GtkWidget* from_b = gtk_label_new("From: ");
    gtk_box_pack_start(GTK_BOX(hbox_b1), from_b, TRUE, TRUE, 0);
    gtk_widget_set_margin_bottom(from_b, 10);

    comboBox_b1 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Jaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Ajmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Jalore");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Jodhpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Sikar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Aligarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Nagaur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Jaisalmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Udaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Bhilwara");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Mount Abu");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Barmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Alwar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Sri Ganganagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Faridabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Gurugram");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Rohtak");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Sonipat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Panipat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Palwal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Jind");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Karnal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Meerut");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Ghaziabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Gautam Buddha Nagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Panchkula");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Chandigarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Delhi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Bharatpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b1), "Agra");

    gtk_box_pack_start(GTK_BOX(hbox_b1), comboBox_b1, TRUE, TRUE, 1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox_b1), 16);
    gtk_widget_set_margin_end(comboBox_b1, 20);
    gtk_widget_set_margin_bottom(comboBox_b1, 10);
    
    //

    GtkWidget* hbox_b2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_pack_start(GTK_BOX(vboxB), hbox_b2, TRUE, TRUE, 0);

    GtkWidget* to_b = gtk_label_new("To: ");
    gtk_box_pack_start(GTK_BOX(hbox_b2), to_b, TRUE, TRUE, 0);
    gtk_widget_set_margin_bottom(to_b, 10);
    gtk_widget_set_margin_end(to_b, 12);

    comboBox_b2 = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Jaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Ajmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Jalore");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Jodhpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Sikar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Aligarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Nagaur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Jaisalmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Udaipur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Bhilwara");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Mount Abu");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Barmer");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Alwar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Sri Ganganagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Faridabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Gurugram");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Rohtak");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Sonipat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Panipat");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Palwal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Jind");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Karnal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Meerut");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Ghaziabad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Gautam Buddha Nagar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Panchkula");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Chandigarh");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Delhi");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Bharatpur");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox_b2), "Agra");

    gtk_box_pack_start(GTK_BOX(hbox_b2), comboBox_b2, TRUE, TRUE, 1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox_b2), 15);
    gtk_widget_set_margin_end(comboBox_b2, 20);
    gtk_widget_set_margin_bottom(comboBox_b2, 10);

    // 

    GtkWidget *hbox_b3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vboxB), hbox_b3);

    GtkWidget *passengers_b = gtk_label_new("Passengers: ");
    gtk_box_pack_start(GTK_BOX(hbox_b3), passengers_b, FALSE, FALSE, 0);
    gtk_widget_set_margin_start(passengers_b, 150);

    qty_b = gtk_spin_button_new(adjustment, cRate, decimals);
    gtk_box_pack_start(GTK_BOX(hbox_b3), qty_b, FALSE, FALSE, 0);

    //

    GtkWidget *hbox_b4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vboxB), hbox_b4);

    GtkWidget *date_label_b = gtk_label_new("Date: ");
    gtk_box_pack_start(GTK_BOX(hbox_b4), date_label_b, FALSE, FALSE, 0);
    gtk_widget_set_margin_start(date_label_b, 70);
    gtk_widget_set_margin_end(date_label_b, 75);

    date_b = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_b4), date_b, TRUE ,TRUE, 0);
    gtk_widget_set_margin_end(date_b, 20);

    GtkWidget* book_b = gtk_button_new_with_label("Book tickets");
    g_signal_connect(book_b, "clicked", G_CALLBACK(busDijsktra), NULL);
    gtk_box_pack_start(GTK_BOX(vboxB), book_b, FALSE, FALSE, 0);

    // * stack and stack-switcher code 

    // 1. creating the switcher
    switcher = gtk_stack_switcher_new();
    gtk_box_pack_start(GTK_BOX(major), switcher, TRUE, TRUE, 1);

    // 2. creating the stack
    stack = gtk_stack_new();
    gtk_box_pack_start(GTK_BOX(major), stack, TRUE, TRUE, 0); // packing
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack)); // binding the stack with its switcher
    
    // 3. padding
    gtk_widget_set_margin_start(switcher, 15);
    gtk_widget_set_margin_end(switcher, 15);
    gtk_widget_set_margin_top(switcher, 15);

    // 4. adding the children 
    gtk_stack_add_titled(GTK_STACK(stack), vboxP, "box4", "PROFILE");
    gtk_stack_add_titled(GTK_STACK(stack), vboxF, "box1", "FLIGHTS");
    gtk_stack_add_titled(GTK_STACK(stack), vboxT, "box2", "TRAINS");
    gtk_stack_add_titled(GTK_STACK(stack), vboxB, "box3", "BUSES");

    // * ending
    
    // .destroy()
    close;

    // .showall()
    gtk_widget_show_all(window);

    // .mainloop()
    gtk_main();
    return 0;
}
