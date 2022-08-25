//-----------------------------------------
// NAME: Eriq Hampton 
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Robert Guderian
// LAB 1: Lab #1, QUESTION: question 3
// 
// REMARKS: Download a file using a curl and threads to show the program is still running.
//
//-----------------------------------------
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <assert.h>




static FILE *output; // make sure to `fopen` and `fclose` this in `main`!
size_t write_data(char *, size_t, size_t, void *);
void* curly(void *);
void* progress(void *);



int main(void) {

    // create 2 threads
    pthread_t my_thread, my_thread2;

    // integer used as a boolean. Asserts used to catch undefined behaviour.
    int run = 1;
    
    printf("\nThis program is going to download a picture file!\n");
    printf("Download Started!\n");
    output = fopen("your_internet_friend.jpg", "w");
    pthread_create( &my_thread, NULL, curly, &run);
    pthread_create(&my_thread2, NULL, progress, &run);

    
    pthread_join(my_thread,NULL);
    pthread_join(my_thread2, NULL);

    fclose(output);

    
    assert(run == 0 || run == 1);

    printf("Program Complete.\n");
    return 0;
}

size_t write_data(char *data, size_t size, size_t nmemb, void *extra) {
    (void) extra; // we're not using this argument at all, cast it

    return fwrite(data, size, nmemb, output);
}


void* curly(void* run){
    int* ptr = (int*) run;
    assert(*ptr != 0);
    CURL *curl = curl_easy_init();
    if (curl) {
    CURLcode res;
    
    curl_easy_setopt(curl, CURLOPT_URL, "https://news.umanitoba.ca/wp-content/uploads/2021/06/teachinglife-robert-guderian-headshot-250x350.jpg");
    // use our write function (to write to a file instead of stdout)
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    // artificially limit download speeds to 2kb/s
    curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, (curl_off_t) 2048);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    }
    
    (*ptr)--;
    assert(*ptr == 0);
    
    pthread_exit(0);
}

void* progress(void* run) {
    int* ptr = (int*) run;
    char progress[] = { '|', '/', '-', '\\' };
    int length = sizeof(progress)/sizeof(progress[0]);

    while(*ptr != 0) { 
        for(int i = 0; i < length; i++){
        
            printf("\rDownloading... [%c]", progress[i]);
        
            fflush(stdout);
            usleep(90000);
        }
    }
    printf("\nDownload Complete!\n");

    assert(*ptr == 0);
    pthread_exit(0);
}
