@rep -find:"//[assembly: AssemblyKeyFileAttribute" -replace:"[assembly: AssemblyKeyFileAttribute" -r AssemblyInfo.cs

@rep -find:"//[assembly: AssemblyDelaySignAttribute(true)]" -replace:"[assembly: AssemblyDelaySignAttribute(true)]" -r AssemblyInfo.cs

@rep -find:"[assembly: InternalsVisibleTo(" -replace:"//[assembly: InternalsVisibleTo(" -r AssemblyInfo.cs