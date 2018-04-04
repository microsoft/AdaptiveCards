#pragma once

#ifdef ADAPTIVE_CARDS_WINDOWS
#include "winPch.h"
#endif

#ifndef AdaptiveSharedNamespaceStart
#define AdaptiveSharedNamespaceStart namespace AdaptiveCards { 
#define AdaptiveSharedNamespace AdaptiveCards
#define AdaptiveSharedNamespaceEnd }
#endif

#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <functional>
#include <unordered_map>
#include <numeric>
#include <cctype>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <locale>