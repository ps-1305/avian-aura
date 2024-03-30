#include <stdio.h>
#include <curl/curl.h>
#include <jansson.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max 1024
#define english "en-IN"
#define rupees "INR"
#define India "IND"
#define economy "CABIN_CLASS_ECONOMY"

typedef struct __info__{
    int day;
    int month;
    int year;
    int adults;
    int child;
} __info__;

void extractData(__info__ user){

    // 1. Reading data from CSV

    char row[max]; // defining the row 
    char* token; // tokenizing the CSV

    char filename[20];

    // opening the file
    FILE* fp = fopen("flights.csv", "r");
    
    // this runs through the csv
    // this is for rows
    // ! We need to hardcode the number of combinations we are going to try 
    for(int i=0; i<=4; i++){

        // 2. Setting up the JSON file

        // we ignore the headers
        if(i == 0){
            fgets(row, max, fp);
            continue;
        }

        // defining our different ptrs for .json file
        json_t* root = json_object();
        json_t* query = json_object();

        /*
        query:{
            market : ...
            locale : ...
            currency : ...
            queryLegs : ...
        }
        */
        json_object_set_new(query, "market", json_string(India));
        json_object_set_new(query, "locale", json_string(english));
        json_object_set_new(query, "currency", json_string(rupees));
        
        // time for queryLegs
        json_t* queryLegs = json_array();
        json_t* Leg = json_object();

        /*
        queryLegs : [
            {
                originPlaceId : {
                    iata : ...
                }
                destinationPlaceId : {
                    iata : ...
                }
                date : {
                    year : ...
                    month : ...
                    day : ...
                }
            }
        ]
        
        */

        // creating the two objects
        json_t* originPlaceId = json_object();
        json_t* destinationPlaceId = json_object();

        // we read a row
        fgets(row, max, fp);

        // we replace the ending character with a null value
        row[strcspn(row,"\n")] = '\0';

        // tokeninzing the CSV file with a ", " delimiter
        token = strtok(row, ", ");

        // we use for loop since the format of the CSV is known by us
        // this for loop is for columns
        for(int j=0; j<=2; j++){
            // we use switch case
            switch(j){
                case 1: json_object_set_new(originPlaceId, "iata", json_string(token)); break;
                case 2: json_object_set_new(destinationPlaceId, "iata", json_string(token)); break;
            }
            token = strtok(NULL, ", ");
        }

        // creating a date object
        json_t* date = json_object();

        // setting up the date
        json_object_set_new(date,"year",json_integer(user.year));
        json_object_set_new(date,"month",json_integer(user.month));
        json_object_set_new(date,"day",json_integer(user.day));

        // now we add objects to the leg
        json_object_set_new(Leg, "originPlaceId", originPlaceId);
        json_object_set_new(Leg, "destinationPlaceId", destinationPlaceId);
        json_object_set_new(Leg, "date", date);

        // and to the queryLegs 
        json_array_append(queryLegs, Leg);


        // ... and to the query as well
        json_object_set_new(query, "queryLegs", queryLegs);

        /*
        {
            .
            .
            .
            queryLegs : ...
            adults : ...
            children : ...
            cabinClass : ...
        }
        */

        // creating the last remaining fields
        json_object_set_new(query, "adults", json_integer(user.adults));
        json_object_set_new(query, "childrenAges", json_integer(user.child));
        json_object_set_new(query, "cabinClass", json_string(economy));

        // adding the root element to the JSON file
        json_object_set_new(root, "query:", query);

        // 3. Writing to the JSON file

        sprintf(filename, "node%d.json", i);

        // opening the file 
        FILE* json = fopen(filename, "w");
        if(json == NULL){
            return;
        }

        // now we write to the json file;
        char* dump = json_dumps(root, JSON_INDENT(4));
        fprintf(json, "%s\n", dump);

        // free the memory allocated to json file
        json_decref(root);
        
        // close the json file
        fclose(json);

        // 4. running the JSON file through the cURL library
        // todo
    }

    // closing the CSV file
    fclose(fp);

}

// ! TESTING CODE =>
// int main(void){
//     // ! FOR TESTING PURPOSES ONLY. NOT MEANT FOR ACTUAL PROJECT
    
//     // $ some scanf operations
//     __info__ passenger;
//     scanf("%d %d %d %d %d", &passenger.day, &passenger.month, &passenger.year, &passenger.adults, &passenger.child);
//     extractData(passenger);
// }

// Test results : 
