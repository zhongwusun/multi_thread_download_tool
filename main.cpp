#include<iostream>

#include "downLoader.h"
#include "httpDownLoader.h"

using namespace std;
int main(int argc, char **args) {
    // 使用HTTP协议下载
    Downloader* httpDownloader = DownloaderFactory<HTTPDownloader>::create();
    if(argc != 4) {
        cout<<"下载链接需要提供, 使用方式: ./downloader url(链接地址) fileName(下载到本地文件名) threadNum(使用线程数量)"<<endl;
        return 0;
    }
    string inputUrl = args[1];
    string fileName = args[2];
    int threadNum = stoi(args[3]);
    
    httpDownloader->download(inputUrl, fileName, threadNum);

    // 使用FTP协议下载
    // Downloader* ftpDownloader = DownloaderFactory<FTPDownloader>::create();
    // ftpDownloader->download("ftp://example.com/file.txt", "file.txt");

    delete httpDownloader;
    // delete ftpDownloader;

    return 0;
}
