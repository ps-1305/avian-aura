#include <stdbool.h>
#include <string.h>

#define max 100
#define EXIT_CODE 0

typedef struct credential{
    char username[20];
    char password[20];
    char f_name[20], l_name[20];
} credential;

bool login(const char* username,const char* password, char* info){
    FILE* __db__ = fopen("db.csv", "r");
    char row[max];
    fgets(row, max, __db__);
    char* token;
    while(fgets(row, max, __db__)){
        token = strtok(row, ",");
        if(strcmp(token,username) == 0){
            token = strtok(NULL, ", ");
            if(strcmp(token, password) == 0){
                sprintf(info, "%s %s", strtok(NULL, ", "), strtok(NULL, ", "));
                return true;
            }
        }
    }
    fclose(__db__);
    return false;
}