// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License. 
const app = require("./app");
const options = require('optimist').argv;

const listeningPort = options.p || 8000;

app.listen(listeningPort, function(){
    console.log(`Web Interface listening on port ${listeningPort}!`);
});
