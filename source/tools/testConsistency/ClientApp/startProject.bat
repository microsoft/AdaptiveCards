@echo off
cd ../nodejs-renderer
START flask run 
cd ../dotnetWPF-renderer
START flask run -p 4000
cd ../ClientApp
START node server.js