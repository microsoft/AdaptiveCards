// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Reflection;
using System.Windows;

#if DELAY_SIGN
[assembly: AssemblyKeyFileAttribute(@"\\cp1pd1cdscvlt04\public\StrongNamePublicKeys\35MSSharedLib1024.snk")]
[assembly: AssemblyDelaySignAttribute(true)]
#endif
[assembly: ThemeInfo(ResourceDictionaryLocation.None, ResourceDictionaryLocation.SourceAssembly)]
