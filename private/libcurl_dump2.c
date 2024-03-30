// * green code::blocks for cURL

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
#define __SKYSCANNER__ "https://partners.api.skyscanner.net/apiservices/v3/flights/live/search/create"
#define __KEY__ "x-api-key: sh428739766321522266746152871799"

typedef struct __info__{
    int day;
    int month;
    int year;
    int adults;
    int child;
} __info__;

size_t writeData(void* ptr, size_t size, size_t nmemb, FILE* stream){
    size_t written = fwrite(ptr, size, nmemb, stream);
    // fwrite(ptr, size, nmemb, stream);
    return written;
}

void extractData(__info__ user){
    // * Setting up cURL

    CURL* curl;
    CURLcode result;
    struct curl_slist *headers = NULL;

    curl = curl_easy_init();
    if(!curl){
        fprintf(stderr, "Err::C-101");
    }

    /*
    curl --location --request POST 'https://partners.api.skyscanner.net/apiservices/v3/flights/live/search/create' \
    --header 'x-api-key: ADD-YOUR-API-KEY-HERE' \
    --data-raw '...'
    */

    // setting up the URL
    curl_easy_setopt(curl, CURLOPT_URL, "https://partners.api.skyscanner.net/apiservices/v3/flights/live/search/create");

    // setting the request method to post
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    // entering the skyscanner public API key
    headers = curl_slist_append(headers, "x-api-key: sh428739766321522266746152871799");
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER, headers);

    // output file
    char output[20];

    // * we'll talk json from here in cURL

    // 1. Reading data from CSV

    char row[max]; // defining the row 
    char* token; // tokenizing the CSV

    char filename[20];
    char _filename[25];

    // opening the file
    FILE* fp = fopen("flights.csv", "r");
    if(fp == NULL){
        fprintf(stderr, "Err::F-102");
    }
    
    // this runs through the csv
    // this is for rows
    // ! We need to hardcode the number of combinations we are going to try 
    for(int i=0; i<=1; i++){

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
        
        // * cURL part starts here again

        // making our output file
        sprintf(output, "curl%d.json", i);
        sprintf(_filename, "@%s", filename);

        // opening the output file
        FILE* out = fopen(output, "wb");
        if(out == NULL){
            fprintf(stderr, "Err::F-101");
        }

        // time to talk JSON
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, _filename);

        // now we need to process some data using cool functions
        // we also need to overwrite cURL's habit of dumping everything @ stdout
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);

        // now we tell cURL to not include <body> tag (uncool)
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // result time
        result = curl_easy_perform(curl);
        if(result != CURLE_OK){
            fprintf(stderr, "Err::C-102 | %s", curl_easy_strerror(result));
        }

        // clean it up!
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        // closing the output file
        fclose(out);
    }

    // closing the CSV file
    fclose(fp);

}

int main(void){
    // ! FOR TESTING PURPOSES ONLY. NOT MEANT FOR ACTUAL PROJECT
    
    // $ some scanf operations
    __info__ passenger;
    scanf("%d %d %d %d %d", &passenger.day, &passenger.month, &passenger.year, &passenger.adults, &passenger.child);
    extractData(passenger);
}
