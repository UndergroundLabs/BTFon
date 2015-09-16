#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct HTTPBody {
    char *str;
    size_t size;
} HTTPBody;

/*
 * This method is a callback method for cURL's CURLOPT_WRITEDATA
 */
size_t write_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    size_t realsize = size * nitems;
    
    HTTPBody *body = (HTTPBody *)userdata;

    body->str = realloc(body->str, body->size + realsize +1);
    memcpy(&(body->str[body->size]), buffer, realsize);
    body->size += realsize;
    body->str[body->size] = 0;

    return realsize;
}

/*
 * Log into BTFon. If successful return 1, else return 0
 */
int btfon_login(char *username, char *password)
{
    CURL *curl;
    CURLcode res;
    HTTPBody body;
    int result = 0;
    char post_data[500];
    
    body.str = malloc(1);
    body.size = 0;

    if(!(curl = curl_easy_init()))
    {
        printf("cURL Error: %s\n", curl_easy_strerror(res));
        exit(EXIT_FAILURE);
    }
    
    // Create the body 
    snprintf(post_data, 500, "username=%s&password=%s&xhtmlLogon=https://www.btopenzone.com:8443/tbbLogon", username, password);
     
    curl_easy_setopt(curl, CURLOPT_URL, "https://btopenzone.com/tbbLogon");
    curl_easy_setopt(curl, CURLOPT_PORT, 8443);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);    
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

    if((res = curl_easy_perform(curl)) != CURLE_OK)
    {
        printf("cURL Error: %s\n", curl_easy_strerror(res));
        exit(EXIT_FAILURE);
    }
    
    // Finished with the cURL request. Clean up :)
    curl_easy_cleanup(curl);
    
    /* Check to see if page contains string "now logged on to".
     * This indicates a successful login.
     */
    if(strstr(body.str, "now logged on to") != NULL)
        result = 1;
    
    free(body.str);
    return result;
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Usage: %s username password\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Attempt to login   
    if(!btfon_login(argv[1], argv[2])) {
        printf("Login Failed :(\n");
        return 1;
    }

    printf("Logged In :)\n");

    return 0;
}
