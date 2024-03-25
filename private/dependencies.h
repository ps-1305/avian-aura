#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// ? #include <ncurses.h>
// ? #include <pbPlots.h>
#include <curl/curl.h>
#include <jnasson.h>
// ? #include <sqlite3.h>

#define FOR(i,n) for(int i=0; i<n; i++)

// * considering a struct for user 
typedef struct credential{
    char username[12];
    char password[20];
    char email[100];
    long long int mobile_number;
    char security_question[100];
    char security_answer[20];
} credential;
