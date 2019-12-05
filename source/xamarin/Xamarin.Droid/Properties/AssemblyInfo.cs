// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Reflection;
using System.Runtime.CompilerServices;
using Android.App;

#if DELAY_SIGN
[assembly: AssemblyKeyFileAttribute(@"\source\xamarin\Build\35MSSharedLib1024.snk")]
[assembly: AssemblyDelaySignAttribute(true)]
#endif