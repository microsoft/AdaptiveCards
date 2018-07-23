// ConsoleApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace AdaptiveSharedNamespace;

int main(int argc, char *argv[])
{
	auto path = argv[1];
	printf(argv[1]);
	printf(+"\n");

	auto parseResult = AdaptiveCard::DeserializeFromFile(argv[1], 1.0);

	std::string result;
	RenderToConsole(parseResult->GetAdaptiveCard(), result);
	printf(result.c_str());

    return 0;
}

