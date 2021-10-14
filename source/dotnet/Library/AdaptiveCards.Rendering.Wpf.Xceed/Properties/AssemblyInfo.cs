using System;
using System.Reflection;

#if DELAY_SIGN
[assembly: AssemblyKeyFileAttribute(@"../../../../35MSSharedLib1024.snk")]
[assembly: AssemblyDelaySignAttribute(true)]
#endif
