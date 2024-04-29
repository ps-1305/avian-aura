#include <gtk/gtk.h>
#include <gdk/gdkpixbuf.h>
#include <pango/pango.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#include "dependencies.c"

#define close g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
#define VERTICES 30
#define INF INT_MAX

#ifndef DEPENDENCIES_H

FILE* ticket;
int count = 0;
int parsedFrom, parsedTo;
int ecoPrice = 0;

// * global widgets
GtkWidget* stack;
GtkWidget* switcher;

GtkWidget* comboBox_b1;
GtkWidget* comboBox_b2;
GtkWidget* comboBox_f1;
GtkWidget* comboBox_f2;
GtkWidget* comboBox_tr1;
GtkWidget* comboBox_tr2;

GtkWidget* qty_b;
GtkWidget* qty_f;
GtkWidget* qty_tr;

GtkWidget* date_b;
GtkWidget* date_f;
GtkWidget* date_tr;

double bus[VERTICES][VERTICES] = {{INF,278,299,450,555,INF,707,600,449,800,950,600,554,555,1699,369,699,648,748,920,949,1136,599,476,450,599,699,428,416,400},
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

double trains[VERTICES][VERTICES] = {{INF,665,295,INF,695,550,INF,665,635,445,650,750,295,510,540,440,865,810,820,310,365,245,700,905,965,510,725,310,375},
{615,INF,750,745,520,325,745,INF,780,650,710,960,635,395,350,620,530,620,595,770,770,580,445,635,730,679,730,555,465},
{265,750,INF,580,INF,650,265,740,715,535,595,INF,435,635,INF,505,INF,875,INF,145,200,515,INF,INF,1055,565,INF,460,420},
{620,240,INF,715,550,INF,620,635,455,510,765,340,510,465,450,920,805,795,275,370,210,700,905,985,480,INF,325,385},
{725,525,INF,715,INF,490,INF,525,580,810,875,820,695,615,640,INF,440,225,295,INF,INF,635,260,490,590,765,455,655,INF},
{555,285,640,550,490,INF,550,285,665,540,565,INF,520,295,350,540,595,590,615,660,680,425,460,885,INF,595,INF,INF,INF},
{INF,665,235,INF,900,525,INF,620,635,445,480,740,290,510,490,445,INF,INF,INF,270,360,210,INF,INF,INF,480,INF,310,INF},
{665,385,750,INF,525,285,INF,INF,780,650,INF,INF,INF,INF,INF,655,525,620,590,765,INF,580,445,625,720,INF,INF,555,INF},
{635,780,715,INF,580,665,635,780,INF,400,350,520,505,785,805,405,INF,475,695,735,INF,595,INF,INF,INF,325,285,INF,INF},
{445,795,520,440,885,510,420,795,400,INF,165,520,235,670,810,175,875,INF,INF,535,570,INF,INF,905,INF,190,505,490,560},
{520,710,565,510,940,595,480,710,350,160,INF,450,315,730,755,175,1085,600,INF,590,650,INF,INF,940,INF,145,435,545,INF},
{795,1055,800,INF,820,INF,740,INF,475,580,450,INF,610,INF,INF,INF,INF,745,INF,815,835,INF,INF,1170,1055,590,615,INF,805},
{325,INF,405,285,740,INF,290,INF,525,225,315,605,INF,720,565,230,INF,INF,INF,435,475,245,INF,INF,INF,315,INF,525,445},
{510,INF,635,INF,615,295,INF,INF,785,670,INF,INF,605,INF,145,815,INF,710,730,635,670,555,INF,730,775,730,INF,345,355},
{540,320,INF,INF,665,350,470,INF,805,700,715,INF,760,175,INF,605,685,740,760,INF,695,505,INF,995,790,905,INF,480,305},
{415,655,505,400,605,505,415,655,405,175,205,525,230,INF,605,INF,895,600,810,530,570,355,685,905,INF,200,INF,480,535},
{860,530,INF,INF,400,590,INF,525,780,1000,910,INF,INF,735,665,895,INF,520,365,INF,INF,805,385,265,410,1240,INF,INF,INF},
{495,620,875,INF,255,590,INF,620,475,590,600,905,INF,710,740,600,520,INF,440,895,INF,740,385,565,675,INF,315,INF,770},
{820,595,INF,INF,275,615,INF,590,695,INF,850,INF,INF,730,760,810,235,440,INF,INF,910,750,420,325,585,1170,580,770,INF},
{300,765,145,INF,INF,670,270,765,735,580,590,815,465,655,INF,555,INF,895,INF,INF,165,435,INF,INF,1065,970,INF,505,445},
{365,INF,170,INF,820,670,390,INF,INF,595,655,825,505,670,695,590,INF,INF,900,165,INF,450,INF,970,INF,585,INF,525,490},
{245,550,400,INF,635,455,INF,545,595,385,INF,INF,245,465,505,430,805,685,750,425,450,INF,615,840,910,650,680,255,INF},
{700,445,INF,INF,230,460,INF,410,665,690,INF,INF,INF,555,580,685,INF,385,420,INF,INF,815,INF,INF,INF,INF,535,INF,INF},
{905,INF,INF,INF,475,885,INF,675,INF,905,940,995,INF,730,755,905,265,590,325,INF,980,815,685,INF,225,INF,715,INF,1085},
{965,INF,1055,INF,590,INF,INF,INF,INF,INF,INF,1055,INF,805,940,INF,415,645,465,1065,1045,910,800,255,INF,INF,800,905,INF},
{510,INF,565,505,940,565,480,INF,355,160,145,INF,315,730,725,170,1085,INF,1025,585,650,INF,745,INF,INF,INF,INF,550,INF},
{725,725,INF,700,455,INF,INF,INF,415,460,555,615,600,INF,INF,520,665,315,580,INF,INF,680,555,700,805,INF,INF,730,INF},
{310,480,480,INF,655,INF,INF,INF,INF,490,555,780,505,405,480,490,810,625,770,505,535,255,635,865,905,555,730,INF,325},
{INF,INF,420,INF,765,510,325,465,740,610,665,INF,445,325,275,535,795,770,INF,445,560,INF,INF,INF,INF,INF,850,355,INF}
};

double flights[VERTICES][VERTICES] = {{INF,2625,5929,6101,INF ,6525,INF,8585,7260,INF,12179,10391,10752,8979,10920,10524,INF,10084,INF,10911,10678,11671,11218,12080,8661,11173,12289,INF,14790,13595},
{2625,INF,INF,3399,7801,5469,INF,5890,8662,INF,9808,INF,7631,10081,10146,INF,INF,8416,INF,10115,10452,10725,INF,INF,10922,10621,9348,INF,INF,12946},
{5929,INF,INF,INF,6260,3294,INF,5196,5005,6556,6446,8444,7513,6165,5088,6203,5719,8197,5334,6370,7143,7216,4998,INF,6218,7038,6931,INF,INF,INF},
{6101,3399,INF,INF,INF,2609,6608,3926,4505,7082,7491,9132,5219,6518,6302,6169,5371,7779,7393,7653,6613,7019,7061,INF,7565,7757,7880,8922,10931,9679},
{INF ,7801,6260,INF,INF,3016,INF,5120,4039,7249,8438,INF,INF,7470,7149,INF,INF,8371,INF,INF,7658,7899,6867,INF,8183,9497,8150,INF,10355,10691},
{6525,5469,3294,2609,3016,INF,4193,2201,3117,3827,6137,7337,4798,4771,3999,3899,3119,5589,5188,5638,4610,4950,5017,5500,5105,6130,5754,7303,7530,7070},
{INF,INF,INF,6608,INF,4193,INF,INF,INF,8015,8754,INF,5875,INF,3757,INF,INF,8534,7330,7003,5585,5122,6762,8598,5750,8538,8155,9137,INF,9815},
{8585,5890,5196,3926,5120,2201,INF,INF,3768,6160,7321,8678,6865,6547,4022,INF,5112,5962,4221,5584,4244,4489,5119,5456,5823,6291,6478,7149,8112,6110},
{7260,8662,5005,4505,4039,3117,INF,3768,INF,6956,6977,8514,3759,3558,5544,6384,6147,4675,9096,5138,5152,6299,5526,7135,6249,6592,7830,8880,8866,7563},
{INF,INF,6556,7082,7249,3827,8015,6160,6956,INF,INF,INF,INF,INF,5908,INF,7282,9611,INF,INF,6813,8749,6768,7148,8349,6880,5999,10476,10387,10514},
{12179,9808,6446,7491,8438,6137,8754,7321,6977,INF,INF,2978,6239,6589,8348,8289,7519,3339,7763,INF,7249,7628,6409,6989,6974,7209,6889,10037,10823,9937},
{10391,INF,8444,9132,INF,7337,INF,8678,8514,INF,2978,INF,6098,INF,9064,11490,INF,4272,18523,INF,8188,7487,7406,7148,8678,6873,6402,INF,9925,9855},
{10752,7631,7513,5219,INF,4798,5875,6865,3759,INF,6239,6098,INF,11022,7536,6977,8030,4900,7190,15556,8985,8239,8449,9983,9546,8661,8890,INF,11270,8457},
{8979,10081,6165,6518,7470,4771,INF,6547,3558,INF,6589,INF,11022,INF,6907,7655,8930,3577,5300,14425,6612,7024,5328,5448,5234,5343,6631,8682,8951,6502},
{10920,10146,5088,6302,7149,3999,3757,4022,5544,5908,8348,9064,7536,6907,INF,5132,3497,8945,INF,5057,2863,3723,4800,6607,3600,4775,5552,INF,6437,7022},
{10524,INF,6203,6169,INF,3899,INF,INF,6384,INF,8289,11490,6977,7655,5132,INF,INF,8142,INF,INF,3383,4948,4643,5296,4962,6145,6008,8924,8728,6629},
{INF,INF,5719,5371,INF,3119,INF,5112,6147,7282,7519,INF,8030,8930,3497,INF,INF,7904,14807,10925,5137,6612,5981,5878,5442,6691,7090,INF,9326,8665},
{10084,8416,8197,7779,8371,5589,8534,5962,4675,9611,3339,4272,4900,3577,8945,8142,7904,INF,5987,6672,5715,7015,5281,4862,5697,5602,5800,7393,6692,6506},
{INF,INF,5334,7393,INF,5188,7330,4221,9096,INF,7763,18523,7190,5300,INF,INF,14807,5987,INF,INF,18850,3434,6281,INF,4927,5324,6137,8266,8617,INF},
{10911,10115,6370,7653,INF,5638,7003,5584,5138,INF,INF,INF,15556,14425,5057,INF,10925,6672,INF,INF,5721,5091,4881,6555,5360,6876,6237,INF,INF,INF},
{10678,10452,7143,6613,7658,4610,5585,4244,5152,6813,7249,8188,8985,6612,2863,3383,5137,5715,18850,5721,INF,2799,3600,4981,2887,3597,3999,4811,3999,4150},
{11671,10725,7216,7019,7899,4950,5122,4489,6299,8749,7628,7487,8239,7024,3723,4948,6612,7015,3434,5091,2799,INF,2877,4505,3331,3302,3302,4816,5850,5041},
{11218,INF,4998,7061,6867,5017,6762,5119,5526,6768,6409,7406,8449,5328,4800,4643,5981,5281,6281,4881,3600,2877,INF,4559,2769,3509,2758,5885,6160,4691},
{12080,INF,INF,INF,INF,5500,8598,5456,7135,7148,6989,7148,9983,5448,6607,5296,5878,4862,INF,6555,4981,4505,4559,INF,INF,4240,4424,INF,INF,INF},
{8661,10922,6218,7565,8183,5105,5750,5823,6249,8349,6974,8678,9546,5234,3600,4962,5442,5697,4927,5360,2887,3331,2769,INF,INF,2400,5279,INF,5719,INF},
{11173,10621,7038,7757,9497,6130,8538,6291,6592,6880,7209,6873,8661,5343,4775,6145,6691,5602,5324,6876,3597,3302,3509,4240,2400,INF,1839,3000,2775,2977},
{12289,9348,6931,7880,8150,5754,8155,6478,7830,5999,6889,6402,8890,6631,5552,6008,7090,5800,6137,6237,3999,3302,2758,4424,5279,1839,INF,4416,6477,5903},
{INF,INF,INF,8922,INF,7303,9137,7149,8880,10476,10037,INF,INF,8682,INF,8924,INF,7393,8266,INF,4811,4816,5885,INF,INF,3000,4416,INF,5790,5029},
{14790,INF,INF,10931,10355,7530,INF,8112,8866,10387,10823,9925,11270,8951,6437,8728,9326,6692,8617,INF,3999,5850,6160,INF,5719,2775,6477,5790,INF,3915},
{13595,12946,INF,9679,10691,7070,9815,6110,7563,10514,9937,9855,8457,6502,7022,6629,8665,6506,INF,INF,4150,5041,4691,INF,INF,2977,5903,5029,3915,INF}
};

const char* bus_cities[VERTICES] = {
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

const char* train_cities[VERTICES] = {
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

const char* flight_cities[VERTICES] = {
    "SXR - Srinagar",
    "IXJ - Jammu",
    "ATQ - Ambarsar",
    "IXC - Chandigarh",
    "DED - Dehradoon",
    "DEL - Delhi",
    "JDH - Jodhpur",
    "JAI - Jaipur",
    "LKO - Lucknow",
    "AYJ - Ayodhya",
    "GAU - Guwahati",
    "IMF - Imphal",
    "PAT - Patna",
    "VNS - Varanasi",
    "AMD - Ahmedabad",
    "BDQ - Vadodra",
    "BHO - Bhopal",
    "CCU - Kolkata",
    "STV - Surat",
    "NAG - Nagpur",
    "BOM - Mumbai",
    "PNQ - Pune",
    "HYD - Hyderabad",
    "VTZ - Vizag",
    "GOI - Goa Intl",
    "BLR - Bangalore",
    "MAA - Madras",
    "IXE - Mangalore",
    "COK - Kochi",
    "TRV - Trivandrum"
};

int minDistance(double dist[], bool sptSet[]);
double dijkstrasAlgorithm(double graph[VERTICES][VERTICES],int src, int dest, int parent[VERTICES]);

#endif
