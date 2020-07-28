// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License. 
const optionsTemplate = {
    platformName: "",
    options: {
        protocol: 'http:',
        hostname: '127.0.0.1',
        port: 5000,
        path: '/',
        method: 'POST',
        headers: {
            'Content-Type' : 'application/x-www-form-urlencoded',
            'Content-Length': 0
        }
    }
};

const optionsForNodeJs = JSON.parse(JSON.stringify(optionsTemplate));
optionsForNodeJs["platformName"] = "Node JS";

const optionsForWPF = JSON.parse(JSON.stringify(optionsTemplate));
optionsForWPF["platformName"] = "WPF";
optionsForWPF["options"]["port"] = 4000;

const optionsForAndroid = JSON.parse(JSON.stringify(optionsTemplate));
optionsForAndroid["platformName"] = "Android";
optionsForAndroid["options"]["port"] = 7000


const optionsForUWP = JSON.parse(JSON.stringify(optionsTemplate));
optionsForUWP["platformName"] = "UWP";
optionsForUWP["options"]["port"] = 7700;


optionsArray = [JSON.stringify(optionsForNodeJs), JSON.stringify(optionsForWPF), JSON.stringify(optionsForAndroid), JSON.stringify(optionsForUWP)];

module.exports = optionsArray;
