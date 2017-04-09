@rep -find:"//[assembly: AssemblyKeyFileAttribute(\@\"\\\\cp1pd2cdscvlt01\\Public\\StrongNamePublicKeys\\35MSSharedLib1024.snk\")]" -replace:"[assembly: AssemblyKeyFileAttribute(\@\"\\\\cp1pd2cdscvlt01\\Public\\StrongNamePublicKeys\\35MSSharedLib1024.snk\")]" -r AssemblyInfo.cs

@rep -find:"//[assembly: AssemblyDelaySignAttribute(true)]" -replace:"[assembly: AssemblyDelaySignAttribute(true)]" -r AssemblyInfo.cs

@rep -find:"[assembly: InternalsVisibleTo(" -replace:"//[assembly: InternalsVisibleTo(" -r AssemblyInfo.cs