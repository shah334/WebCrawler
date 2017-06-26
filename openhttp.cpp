#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

//
// Using curl to get a URL and put in in a string 
// https://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string
//

struct pstring {
  char *ptr;
  size_t len;
};

void init_pstring(struct pstring *s) {
  s->len = 0;
  s->ptr = (char*) malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct pstring *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = (char*) realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

static int initialize_curl = 0;

char * fetchHTML( const char * url, int * n) {
    CURLcode res;
    CURL * curl = curl_easy_init();

    if(!curl) {
      return NULL;
    }

    struct pstring s;
    init_pstring(&s);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);

    *n = s.len;
  
    return s.ptr;
}


