// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Reflection;
using System.Windows;

#if DELAY_SIGN
[assembly: AssemblyKeyFileAttribute(@"\\25StrongName.snk")]
[assembly: AssemblyDelaySignAttribute(true)]
#endif
[assembly: ThemeInfo(ResourceDictionaryLocation.None, ResourceDictionaryLocation.SourceAssembly)]
