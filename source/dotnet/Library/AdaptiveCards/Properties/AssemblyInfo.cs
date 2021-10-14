// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Reflection;

#if DELAY_SIGN
[assembly: AssemblyKeyFileAttribute(@"../../../../35MSSharedLib1024.snk")]
[assembly: AssemblyDelaySignAttribute(true)]
#endif
