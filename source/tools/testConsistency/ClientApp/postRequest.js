// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License. 
const http = require('http');

/** 
 * This function takes an options argument, the platform name and the form data
 * and returns a promise. The promise contains a function that sends the form data
 * via HTTP POST request to the address mentioned in options. It sends back the response
 * data on a successful HTTP POST request. Otherwise it sends back the error.  
 */
function getPostRequestPromise(options, platformName, formData) {
    const postReqPromise = new Promise(function(resolve, reject) {
      const postRequest = http.request(options, function(postResponse) {
        console.log(`STATUS FOR ${platformName}: ${postResponse.statusCode}`);
        console.log(`HEADERS: ${JSON.stringify(postResponse.headers)}`);
        postResponse.setEncoding('utf8');
        var responseData = ""
        postResponse.on('data', function(data) {
          responseData = responseData + data;
        });
        postResponse.on('end', function() {
          resolve(responseData);
          console.log('No more data in response.');
        });
      });
      
      postRequest.on('error', function(e) {
        console.error(`problem with request: ${e.message}`);
        reject(e.message);
      });
      
      // Write data to request body
      postRequest.write(formData);
      postRequest.end();
    });
    return postReqPromise;
}
 
module.exports = { getPostRequestPromise };
