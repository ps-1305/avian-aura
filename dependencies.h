#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
// ? #include <ncurses.h>
// ? #include <pbPlots.h>
#include <curl/curl.h>
#include <jansson.h>
// ? #include <sqlite3.h>
#include "extractData_from_JSON.c"

#define XFOR(i,n) for(int i=0; i<n; i++)
#define XFOR_SE(i, start, end) for(int i=start; i<end; i++)
#define FOR(i,n) for(int i=0; i<=n; i++)
#define FOR_SE(i, start, end) for(int i=start; i<=end; i++)
#define SIZE(data, n) sizeof(data)*n
#define max 1024
#define english "en-IN"
#define rupees "INR"
#define India "IND"
#define economy "CABIN_CLASS_ECONOMY"

// * public API key for cURL : sh428739766321522266746152871799

// * considering a struct for user 
typedef struct credential{
    char username[12];
    char password[20];
    char email[100];
    long long int mobile_number;
    char security_question[100];
    char security_answer[20];
} credential;

// * extractData_from_JSON.c
void extractData(__info__ user);
