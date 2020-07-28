::===============================================================
:: This bat file starts the two REST API(Flask Apps) and the Web
:: Interface
::===============================================================
@echo off
:: navigate to the directory of the flask app for JavaScript
cd ../nodejs-renderer
:: start the flask app(runs on http://127.0.0.1:5000/). 
:: the port can be changed by adding -p PORT to the command
START flask run 
:: navigate to the directory of the flask app for .NET WPF
cd ../dotnetWPF-renderer
:: start the flask app on port 4000.
:: The port number can be changed by changing 4000 to desired port.
START flask run -p 4000
:: navigate to the directory of the flask app for android
cd ../android-renderer
:: start the flask app on port 7000.
:: The port number can be changed by changing 7000 to desired port
START flask run -p 7000
:: navigate to the directory of the flask app for android
cd ../uwp-renderer 
:: start the flask app on port 7700.
:: The port number can be changed by changing 7000 to desired port
START flask run -p 7700
:: navigate to the directory of the web interface
cd ../ClientApp
:: start the node serve(runs on localhost:8000 by default)
:: The port number can be changed by add -p PORT to the command
:: e.g(node server.js -p 8000)
START node server.js
