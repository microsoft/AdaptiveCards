#include "ImageDownloader.h"

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

void ImageDownloader::clearImageFolder()
{
    const auto dir_path = SolutionDir + imageFolder;
    for (auto& path : fs::directory_iterator(dir_path)) {
        fs::remove_all(path);
    }
}
