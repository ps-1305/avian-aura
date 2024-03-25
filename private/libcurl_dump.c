#include "dependencies.h"

static size_t process_data(void *ptr, size_t size, size_t nmemb, void* userp){
    // we will write what to extract here hehe
    // use jansson.h
    return size*nmemb;
}

int main(void){
    CURL* curl;
    CURLcode result;
    struct curl_slist *headers = NULL;

    curl = curl_easy_init();
    if(!curl){
        fprintf(stderr, "Hehe");
    }
    /*
    $ this code represents the following terminal command (as given in the API)
    curl --location --request POST 'https://partners.api.skyscanner.net/apiservices/v3/flights/live/search/create' \
    --header 'x-api-key: ADD-YOUR-API-KEY-HERE' \
    --data-raw '...'
    */
   
    // setting the URL
    curl_easy_setopt(curl, CURLOPT_URL, "https://partners.api.skyscanner.net/apiservices/v3/flights/live/search/create");

    // setting the request method to post 
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    // entering the skyscanner public API key
    headers = curl_slist_append(headers, "x-api-key: sh428739766321522266746152871799");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // now we talk json
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "@nodes.json");

    // now we need to process some data using cool functions and coding
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, process_data);

    // now we tell cURL not to include <body> tag (uncool)
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // result time
    result = curl_easy_perform(curl);
    if(result != CURLE_OK){
        fprintf(stderr, "Error lololol", curl_easy_strerror(result));
    }

    // clean it up!
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    // hehe
    return 0;
}
