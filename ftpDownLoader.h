#ifndef _FTP_DOWNLOADER_H_
#define _FTP_DOWNLOADER_H_

#include<string>
#include "downLoader.h"

class FTPDownloader : public Downloader {
public:
    void download(const std::string& url, string fileName, int threadNum) override {
        // 实现FTP下载逻辑
        // ...
    }
};

#endif