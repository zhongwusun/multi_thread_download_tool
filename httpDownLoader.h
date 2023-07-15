#ifndef _HTTP_DOWNLOADER_H_
#define _HTTP_DOWNLOADER_H_

#include<string>
#include "downLoader.h"
#include<iostream>

using namespace std;

class HTTPDownloader : public Downloader {
public:
    void download(const std::string& url, string fileName, int threadNum) override ;

    static size_t writeData(void* buffer, size_t size, size_t nmemb, void* userp);
    static void downloadThread(const string& url, const string& outputFile, long startPos, long endPos);
};

#endif