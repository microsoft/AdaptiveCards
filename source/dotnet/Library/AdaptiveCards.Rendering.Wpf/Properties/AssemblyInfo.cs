// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Reflection;
using System.Windows;

#if DELAY_SIGN
[assembly: AssemblyKeyFileAttribute(@"../../../../36MSApp1024.snk")]
[assembly: AssemblyDelaySignAttribute(true)]
#endif
[assembly: ThemeInfo(ResourceDictionaryLocation.None, ResourceDictionaryLocation.SourceAssembly)]
