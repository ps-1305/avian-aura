#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <limits.h>

#define V 30
#define VERTICES 30
#define INF INT_MAX

int minDistance(double dist[], bool sptSet[]){
	double min = INF;
	int min_index;

	for (int v = 0; v < VERTICES; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

double dijkstrasAlgorithm_BUS(double graph[VERTICES][VERTICES],int src, int dest){
	double dist[VERTICES]; 

	bool sptSet[VERTICES]; 

	for (int i = 0; i < VERTICES; i++)
		dist[i] = INF, sptSet[i] = false;

	dist[src] = 0;

	for (int count = 0; count < VERTICES - 1; count++) {
		int u = minDistance(dist, sptSet);

		sptSet[u] = true;

		for (int v = 0; v < VERTICES; v++)

			if (!sptSet[v] && graph[u][v]
				&& dist[u] != INF
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

    return dist[dest];
}


double bus[V][V] = {{INF,278,299,450,555,INF,707,600,449,800,950,600,554,555,1699,369,699,648,748,920,949,1136,599,476,450,599,699,428,416,400},
    {278,INF,336,400,463,INF,450,600,600,463,550,527,950,600,INF,500,1098,INF,1097,1100,INF,849,1018,925,950,949,1197,950,1048,431},
    {299,336,INF,278,649,INF,555,INF,295,INF,INF,INF,INF,INF,INF,1149,INF,INF,INF,INF,INF,INF,INF,INF,1400,INF,INF,1149,714.29,INF},
    {450,400,278,INF,550,INF,650,350,475,500,INF,200,611,650,INF,950,800,INF,1100,850,INF,1100,1300,1300,1511,1100,1200,1511,550,750},
    {555,463,649,550,INF,INF,264,849,650,648,INF,800,INF,697,INF,648,800,INF,949,INF,INF,699,850,800,500,699,699,500,1050,550.48},
    {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
    {707,450,555,650,264,INF,INF,705,460,500,INF,447,INF,500,INF,598,899,INF,1099,INF,INF,1099,INF,INF,598,1149,1149,598,849,849},
    {600,600,INF,350,849,INF,705,INF,711,INF,INF,220,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1200,INF,INF,1200,INF,INF},
    {449,600,295,475,650,INF,460,711,INF,1000,INF,479,691,900,INF,1000,INF,INF,INF,INF,INF,INF,1400,1400,1444,3600,INF,1000,1600,INF},
    {800,463,INF,500,648,INF,500,INF,1000,INF,INF,700,1000,800,INF,857.14,1298,INF,INF,1915,INF,1298,1400,1400,1000,1598,1598,857.14,1430,569},
    {950,550,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
    {600,527,INF,200,800,INF,447,220,479,700,INF,INF,INF,800,INF,1000,INF,INF,INF,INF,INF,INF,INF,INF,1000,INF,INF,1000,800,800},
    {554,950,INF,611,INF,INF,INF,INF,691,1000,INF,INF,INF,699,INF,449,INF,INF,INF,INF,INF,INF,INF,INF,449,INF,INF,449,INF,INF},
    {555,600,INF,650,697,INF,500,INF,900,800,INF,800,699,INF,INF,905,851,INF,INF,INF,INF,INF,INF,INF,871,905,666,871,799,949},
    {1699,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1573,INF,1573,1573,INF,443},
    {369,500,1149,950,648,INF,598,INF,1000,857.14,INF,1000,449,905,INF,INF,990,744,539,1500,INF,744,540,897,499,847,847,462,INF,525},
    {699,1098,INF,800,800,INF,899,INF,INF,1298,INF,INF,INF,851,INF,990,INF,INF,1000,INF,INF,INF,INF,INF,INF,990,1600,INF,INF,849},
    {648,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,744,INF,INF,217,INF,INF,INF,INF,INF,500,500,450,500,INF,1399},
    {748,1097,INF,1100,949,INF,1099,INF,INF,INF,INF,INF,INF,INF,INF,539,1000,217,INF,INF,INF,1749,INF,INF,500,450,500,500,INF,2899},
    {920,1100,INF,850,INF,INF,INF,INF,INF,1915,INF,INF,INF,INF,INF,1500,INF,INF,INF,INF,INF,1573,INF,INF,1910.48,1979,1979,1573,INF,443},
    {949,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
    {1136,849,INF,1100,699,INF,1099,INF,INF,1298,INF,INF,INF,INF,INF,744,INF,INF,1749,1573,INF,INF,INF,INF,500,538,450,500,INF,1399},
    {599,1018,INF,1300,850,INF,INF,INF,1400,1400,INF,INF,INF,INF,INF,540,INF,INF,INF,INF,INF,INF,INF,279,362,INF,INF,299,INF,699},
    {476,925,INF,1300,800,INF,INF,INF,1400,1400,INF,INF,INF,INF,INF,897,INF,INF,INF,INF,INF,INF,279,INF,1000,INF,INF,1000,INF,999},
    {450,950,1400,1511,500,INF,598,1200,1444,1000,INF,1000,449,871,1573,499,INF,500,500,1910.48,INF,500,362,1000,INF,865,615,99,288,345},
    {599,949,INF,1100,699,INF,1149,INF,3600,1598,INF,INF,INF,905,INF,847,990,500,450,1979,INF,538,INF,INF,865,INF,INF,676,INF,731.43},
    {699,1197,INF,1200,699,INF,1149,INF,INF,1598,INF,INF,INF,666,1573,847,1600,450,500,1979,INF,450,INF,INF,615,INF,INF,554,INF,INF},
    {428,950,1149,1511,500,INF,598,1200,1000,857.14,INF,1000,449,871,1573,462,INF,500,500,1573,INF,500,299,1000,99,676,554,INF,288,345},
    {416,1048,714.29,550,1050,INF,849,1071,1600,1430,INF,800,INF,799,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,288,INF,INF,288,INF,900},
    {400,431,INF,750,550.48,INF,849,INF,INF,569,INF,800,INF,949,443,525,849,1399,2899,443,INF,1399,699,999,345,731.43,INF,345,900,INF}
};

const char* bus_cities[V] = {
    "Jaipur",
    "Ajmer",
    "Jalore",
    "Jodhpur",
    "Sikar",
    "Aligarh",
    "Nagaur",
    "Jaisalmer",
    "Udaipur",
    "Bhilwara",
    "Mount Abu",
    "Barmer",
    "Alwar",
    "Sri Ganganagar",
    "Faridabad",
    "Gurugram",
    "Rohtak",
    "Sonipat",
    "Panipat",
    "Palwal",
    "Jind",
    "Karnal",
    "Meerut",
    "Ghaziabad",
    "Gautam Buddha Nagar",
    "Panchkula",
    "Chandigarh",
    "Delhi",
    "Bharatpur",
    "Agra"
};

GtkWidget *qty;
GtkWidget *date;
GtkWidget *comboBox_1;
GtkWidget *comboBox_2;
int parsedFrom, parsedTo;
FILE* bus_ticket;
int eco_price = 0;

void dijsktra_bus(GtkWidget *widget, GdkEvent* event){
    const char* ticketingDate = gtk_entry_get_text(GTK_ENTRY(date));
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

    int eco_price = (int) dijkstrasAlgorithm_BUS(bus, parsedFrom, parsedTo);

    char filename[100];
    sprintf(filename, "%s-to-%s-date-%s.txt", bus_cities[parsedFrom], bus_cities[parsedTo], ticketingDate);
    bus_ticket = fopen(filename, "w");
    fprintf(bus_ticket, "Date : %s\n", ticketingDate);
    fprintf(bus_ticket, "From : %s\n", bus_cities[parsedFrom]);
    fprintf(bus_ticket, "To : %s\n", bus_cities[parsedTo]);
    fprintf(bus_ticket, "Price : Rupees %d /-\n", eco_price);
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