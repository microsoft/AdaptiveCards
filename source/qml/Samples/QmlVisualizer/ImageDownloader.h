#pragma once
#define CURL_STATICLIB
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <functional>
#include <curl.h>
#include <filesystem>
#include <thread>
#include <map>

#include <Utils.h>

namespace fs = std::filesystem;

const std::string SolutionDir = SOLUTION_DIR;
const std::string imageFolder = "Samples\\QmlVisualizer\\Images\\";

class ImageDownloader
{
	public:
		static char* Convert(const std::string& s);
		static bool download_jpeg(const std::string& imgName, char* url);
		static const std::map<std::string, std::string> download_multiple_jpeg(const std::map<std::string,std::string> &urls);

		static void clearImageFolder();
	private:
		static size_t callbackfunction(void* ptr, size_t size, size_t nmemb, void* userdata);
		static timeval get_timeout(CURLM* multi_handle);
		static int wait_if_needed(CURLM* multi_handle, timeval& timeout);
	
};

