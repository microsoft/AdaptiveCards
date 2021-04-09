#include "ImageDownloader.h"

using namespace RendererQml;

size_t ImageDownloader::callbackfunction(void* ptr, size_t size, size_t nmemb, void* userdata)
{
	FILE* stream = (FILE*)userdata;
	if (!stream)
	{
		printf("!!! No stream\n");
		return 0;
	}

	size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
	return written;
}

char* ImageDownloader::Convert(const std::string& s) //Convert url from std::string to raw char pointer
{
	char* pc{ new char[s.size() + 1] };
	std::strcpy(pc, s.c_str());
	return pc;
}

bool ImageDownloader::download_jpeg(const std::string& imgName, char* url)
{
	const std::string imgSource = SolutionDir + imageFolder + imgName;
	FILE* fp = fopen(Convert(imgSource), "wb");
	if (!fp)
	{
		printf("!!! Failed to create file on the disk\n");
		return false;
	}

	CURL* curlCtx = curl_easy_init();
	curl_easy_setopt(curlCtx, CURLOPT_URL, url);
	curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, callbackfunction);
	curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

	CURLcode rc = curl_easy_perform(curlCtx);
	if (rc)
	{
		printf("!!! Failed to download: %s\n", url);
		return false;
	}

	long res_code = 0;
	curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
	if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
	{
		printf("!!! Response code: %d\n", res_code);
		return false;
	}

	curl_easy_cleanup(curlCtx);

	fclose(fp);

	return true;
}

timeval ImageDownloader::get_timeout(CURLM* multi_handle)
{
	long curl_timeout = -1;
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	//Stores suggested timeout by libcurl in curl_timeout variable
	curl_multi_timeout(multi_handle, &curl_timeout);

	if (curl_timeout >= 0) {
		timeout.tv_sec = curl_timeout / 1000;
		if (timeout.tv_sec > 1)
			timeout.tv_sec = 1;
		else
			timeout.tv_usec = (curl_timeout % 1000) * 1000;
	}
	return timeout;
}

int ImageDownloader::wait_if_needed(CURLM* multi_handle, timeval& timeout)
{
	fd_set fdread;
	fd_set fdwrite;
	fd_set fdexcep;
	FD_ZERO(&fdread);
	FD_ZERO(&fdwrite);
	FD_ZERO(&fdexcep);
	int maxfd = -1;
	// get file descriptors representing the sockets from the transfers 
	auto check = curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

	if (check != CURLM_OK)
	{
		std::cerr << "curl_multi_fdset() failed, code " << check << "." << std::endl;
	}
	/* On success the value of maxfd is guaranteed to be >= -1. We call
	sleep for 100ms, which is the minimum suggested value in the
	curl_multi_fdset() doc. */
	if (maxfd == -1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	int NumAvailableSockets = maxfd != -1 ? select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout) : 0;
	return NumAvailableSockets;
}

const std::map<std::string, std::string> ImageDownloader::download_multiple_jpeg(const std::map<std::string, std::string> &urls)
{
	std::map<std::string, std::string> file_paths;
	CURLM* multi_handle;
	int still_running = 0;
	multi_handle = curl_multi_init();

	std::map<FILE*, CURL*> easy_handles;
	FILE* fp;
	CURL* easy_handle;
	std::string imgSource;
	std::string imageFormat;

	for(auto &url:urls)
	{
		imageFormat = Utils::splitString(url.second, '.').back();
		imgSource = SolutionDir + imageFolder + url.first + "." + imageFormat;
		fp = fopen(Convert(imgSource), "wb");
		if (!fp)
		{
			printf("!!! Failed to create file on the disk\n");
			continue;
		}

		file_paths.insert(std::pair<std::string, std::string>(url.first, imgSource));

		easy_handle = curl_easy_init();
		//Note:The url passed should be of type char*
		curl_easy_setopt(easy_handle, CURLOPT_URL, url.second.c_str());
		curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, callbackfunction);
		curl_easy_setopt(easy_handle, CURLOPT_FOLLOWLOCATION, 1);

		easy_handles.insert(std::pair<FILE*, CURL*>(fp, easy_handle));
		curl_multi_add_handle(multi_handle, easy_handle);
	}

	curl_multi_perform(multi_handle, &still_running);
	
	while (still_running)
	{
		struct timeval timeout = get_timeout(multi_handle);

		auto NumAvailableSockets = wait_if_needed(multi_handle, timeout);
		if (NumAvailableSockets >= 0)
		{
			curl_multi_perform(multi_handle, &still_running);
		} 
	}

	curl_multi_cleanup(multi_handle);

	for (auto& handle : easy_handles)
	{
		curl_easy_cleanup(handle.second);
		fclose(handle.first);
	}

    return file_paths;
}

void ImageDownloader::clearImageFolder()
{
    const auto dir_path = SolutionDir + imageFolder;
    for (auto& path : fs::directory_iterator(dir_path)) {
        fs::remove_all(path);
    }
}
