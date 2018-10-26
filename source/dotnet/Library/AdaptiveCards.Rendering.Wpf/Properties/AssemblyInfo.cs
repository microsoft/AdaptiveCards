using System;
using System.Reflection;
using System.Windows;

#if DELAY_SIGN
[assembly: AssemblyKeyFileAttribute(@"\\cp1pd2cdscvlt01\Public\StrongNamePublicKeys\35MSSharedLib1024.snk")]
[assembly: AssemblyDelaySignAttribute(true)]
#endif
[assembly: ThemeInfo(ResourceDictionaryLocation.None, ResourceDictionaryLocation.SourceAssembly)]
