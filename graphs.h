#include "dijsktra.c"
#include <glib.h>
#include <stdlib.h>

#define V 30

int bus[V][V];
int trains[V][V];

#ifndef GRAPHS_H

// * buses 
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

const char* train_cities[V]{
    "Kanpur Central - CNB",
    "New Delhi - NDLS",
    "Mumbai - CSMT",
    "Jalandhar City - JUC",
    "Anand Vihar Terminus - ANVT",
    "Vijaywada - BZA",
    "Jalgaon - JL",
    "Old Delhi - DLI",
    "Dadar - DR",
    "Howrah - HWH",
    "Mughalsarai - DDU",
    "Patna - PNBE",
    "Guwahati - GHY",
    "Lucknow Charbagh - LKO",
    "Vadodra - BRC",
    "Ahmedabad - ADI",
    "Varanasi - BSB",
    "Bengaluru - SBC",
    "Vizag - VSKP",
    "Chennai Central - MAS",
    "Ambarsar - ASR",
    "Jammu Tawi - JAT",
    "Gwalior - GWL",
    "Hyderabad - HYB",
    "Coimbatore - CBE",
    "Kollam - QLN",
    "Danapur - DNR",
    "Cuttack - CTC",
    "Kota - KOTA",
    "Jodhpur - JU"
};

int minDistance(int dist[], bool sptSet[]);
int dijkstrasAlgorithm(int graph[VERTICES][VERTICES], int src, int dest);

#endif