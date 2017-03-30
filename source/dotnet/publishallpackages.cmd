cd bin
for %%s in (*.nupkg) do NuGet.exe push -Source packages -ApiKey VSTS %%s 
cd ..
