#ifndef _DOWNLOADER_H_
#define _DOWNLOADER_H_

#include<string>
using namespace std;
class Downloader {
public:
    virtual void download(const std::string& url, string fileName, int threadNum) = 0;
};


template<typename Protocol>
class DownloaderFactory {
public:
    static Downloader* create() {
        return new Protocol();
    }
};
#endif