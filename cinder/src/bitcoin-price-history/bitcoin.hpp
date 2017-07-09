#pragma once

#include <curl/curl.h>
#include <curl/curlbuild.h>
#include <curl/easy.h>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace std;

class HTTPDownloader {
public:
    HTTPDownloader();
    ~HTTPDownloader();
    std::string download(const std::string& url);
private:
    void* curl;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    string data((const char*) ptr, (size_t) size * nmemb);
    *((stringstream*) stream) << data;
    return size * nmemb;
}
HTTPDownloader::HTTPDownloader() {
    curl = curl_easy_init();
}
HTTPDownloader::~HTTPDownloader() {
    curl_easy_cleanup(curl);
}
string HTTPDownloader::download(const std::string& url) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
    std::stringstream out;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    return out.str();
}
