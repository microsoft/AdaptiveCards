// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include <sal.h>

#define RETURN_IF_FAILED(statement) \
    do \
    { \
        HRESULT __hr = statement; \
        if (FAILED(__hr)) \
        { \
            return __hr; \
        } \
    } while (0, 0)
#define THROW_IF_FAILED(__hr) \
    do \
    { \
        if (FAILED(__hr)) \
        { \
            throw new std::exception(); \
        } \
    } while (0, 0)
#define CATCH_RETURN \
    catch (...) { return E_FAIL; }
