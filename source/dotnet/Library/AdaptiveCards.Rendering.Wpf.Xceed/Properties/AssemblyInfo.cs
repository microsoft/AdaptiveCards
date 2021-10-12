using System;
using System.Reflection;

#if DELAY_SIGN
[assembly: AssemblyKeyFileAttribute(@"../../../../25StrongName.snk")]
[assembly: AssemblyDelaySignAttribute(true)]
#endif
