npm run build-all
hexo clean
hexo generate
remove-item -recurse -force ..\..\website\wwwroot\*
copy-item -path .\public\* -recurse -destination ../../website/wwwroot

