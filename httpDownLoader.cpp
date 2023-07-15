#include "httpDownLoader.h"
#include <fstream>
#include <curl/curl.h>
#include <thread>
#include <vector>
using namespace std;

// 回调函数，用于将下载的数据写入本地文件
size_t HTTPDownloader::writeData(void* buffer, size_t size, size_t nmemb, void* userp) {
    std::ofstream& file = *static_cast<std::ofstream*>(userp);
    file.write(static_cast<char*>(buffer), size * nmemb);
    return size * nmemb;
}

// 每个线程的下载任务
void HTTPDownloader::downloadThread(const string& url, const string& outputFile, long startPos, long endPos) {
    std::ofstream file(outputFile, std::ios::binary);
    if (!file) {
        std::cout << "Failed to open file: " << outputFile << std::endl;
        return;
    }
    file.seekp(startPos);

    CURL* curl = curl_easy_init();
    if (curl) {
        std::string range = std::to_string(startPos) + "-" + to_string(endPos);

        // 设置URL和回调函数
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPDownloader::writeData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

        // 设置下载范围
        curl_easy_setopt(curl, CURLOPT_RANGE, range.c_str());

        // 执行下载
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cout << "Failed to download file: " << curl_easy_strerror(res) << std::endl;
        }

        // 清理CURL句柄
        curl_easy_cleanup(curl);
    }

    file.close();
    std::cout << "Download complete: " << outputFile << std::endl;
}


void HTTPDownloader::download(const std::string& url, string outputFile, int numThreads) {
        // 实现HTTP下载逻辑
    cout<<"开始执行下载逻辑, 下载链接为:"<<url<<"， 下载到本地文件名为:"<<outputFile<<"，并发线程数量为:"<<numThreads<<endl;
    // 获取文件大小
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

        CURLcode res = curl_easy_perform(curl);
        long long fileSize;
        if (res == CURLE_OK) {
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &fileSize);
            if (res != CURLE_OK) {
                cerr << "Failed to get file size: " << curl_easy_strerror(res) << endl;
                return;
            }
        }
        else {
            cerr << "Failed to retrieve file information: " << curl_easy_strerror(res) << endl;
            return;
        }

        curl_easy_cleanup(curl);
        vector<thread> threads;
        cout << "File size: " << fileSize << " bytes" << endl;

        if(fileSize == 0) {
            cout<<"fileSize== 0, return!"<<endl;
            return;
        }

        // 计算每个线程下载的文件范围
        long long chunkSize = fileSize / numThreads;
        long long lastChunkSize = fileSize % numThreads;

        for (int i = 0; i < numThreads; i++) {
            long long startPos = i * chunkSize;
            long long endPos = startPos + chunkSize - 1;
            if(i == numThreads - 1) {
                endPos += lastChunkSize;
            }
            threads.emplace_back(HTTPDownloader::downloadThread, url, outputFile, startPos, endPos);
        }
        // 等待所有线程完成下载
        for (auto& thread : threads) {
            thread.join();
        }

        cout << "Download complete" << endl;
    }
    else {
        cerr << "Failed to initialize libcurl" << endl;
        return;
    }

}
