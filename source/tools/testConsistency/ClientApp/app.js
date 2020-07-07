const express = require("express");
const path = require('path');
const bodyParser = require('body-parser');
const http = require('http');
const restler = require('restler');
const querystring = require('querystring');

const app = express();
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));
app.use(bodyParser.urlencoded({extended: false}));

app.get('/', function(req, res) {
  res.render('index.ejs');
});

app.post('/', function(req, res) {
  var cardData = req.body.cardData;
  var cardTemplate = req.body.cardTemplate;

  const formData = querystring.stringify({
    "data" : cardData,
    "template" : cardTemplate
  });

  const optionsForNodeJs = {
    protocol: 'http:',
    hostname: '127.0.0.1',
    port: 5000,
    path: '/',
    method: 'POST',
    headers: {
      'Content-Type' : 'application/x-www-form-urlencoded',
      'Content-Length': Buffer.byteLength(formData)
    }
  };

  const optionsForWPF = Object.assign({}, optionsForNodeJs);
  optionsForWPF["port"] = 4000;


  function getPostRequestPromise(options, platformName) {
    const postReqPromise = new Promise(function(resolve, reject) {
      const postRequest = http.request(options, function(postResponse) {
        console.log(`STATUS FOR ${platformName}: ${res.statusCode}`);
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

  const nodePostReq = getPostRequestPromise(optionsForNodeJs, "Node JS");
  const WPFPostReq = getPostRequestPromise(optionsForWPF, "WPF");

  Promise.all([nodePostReq, WPFPostReq]).then(function(results) {
    var WPFImg = ""
    var WPFWarnings = "";
    var WPFErrors = "";
    var nodeImg = "";
    var nodeWarnings = "";
    var nodeErrors = "";
    try {
      nodeData = JSON.parse(results[0]);
      WPFData = JSON.parse(results[1]);
      WPFImg = WPFData.imageData;
      WPFWarnings = WPFData.warnings;
      WPFErrors = WPFData.errors; 
      nodeImg = nodeData.imageData;
      nodeWarnings = nodeData.warnings;
      nodeErrors = nodeData.errors;
    }
    catch(err) {
      WPFErrors = "There was an error rendering the card. Please try again";
      nodeErrors = "There was an error rendering the card. Please try again";
    }
    res.render('results.ejs', {
      WPFImg: WPFImg, 
      WPFWarnings: WPFWarnings,
      WPFErrors: WPFErrors, 
      nodeImg: nodeImg,
      nodeWarnings: nodeWarnings,
      nodeErrors: nodeErrors,
    });
  });
  
});
  
//This test route is is simply to illustrate that we can handle the situation where we get incomplete JSON from the POST request
app.post('/testIncompleteResult', function(req, res) {
  var cardData = req.body.cardData;
  var cardTemplate = req.body.cardTemplate;

  const formData = querystring.stringify({
    "data" : cardData,
    "template" : cardTemplate
  });

  const optionsForNodeJs = {
    protocol: 'http:',
    hostname: '127.0.0.1',
    port: 5000,
    path: '/test',
    method: 'POST',
    headers: {
      'Content-Type' : 'application/x-www-form-urlencoded',
      'Content-Length': Buffer.byteLength(formData)
    }
  };

  const optionsForWPF = Object.assign({}, optionsForNodeJs);
  optionsForWPF["port"] = 4000;


  function getPostRequestPromise(options, platformName) {
    const postReqPromise = new Promise(function(resolve, reject) {
      const postRequest = http.request(options, function(postResponse) {
        console.log(`STATUS FOR ${platformName}: ${res.statusCode}`);
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

  const nodePostReq = getPostRequestPromise(optionsForNodeJs, "Node JS");
  const WPFPostReq = getPostRequestPromise(optionsForWPF, "WPF");

  Promise.all([nodePostReq, WPFPostReq]).then(function(results) {
    var WPFImg = ""
    var WPFWarnings = "";
    var WPFErrors = "";
    var nodeImg = "";
    var nodeWarnings = "";
    var nodeErrors = "";
    try{
      nodeData = JSON.parse(results[0]);
      WPFData = JSON.parse(results[1]);
      WPFImg = WPFData.imageData;
      WPFWarnings = WPFData.warnings;
      WPFErrors = WPFData.errors; 
      nodeImg = nodeData.imageData;
      nodeWarnings = nodeData.warnings;
      nodeErrors = nodeData.errors;
    }
    catch(err){
      WPFErrors = "There was an error rendering the card. Please try again";
      nodeErrors = "There was an error rendering the card. Please try again";
    }
    res.render('results.ejs', {
      WPFImg: WPFImg, 
      WPFWarnings: WPFWarnings,
      WPFErrors: WPFErrors, 
      nodeImg: nodeImg,
      nodeWarnings: nodeWarnings,
      nodeErrors: nodeErrors,
    });
  });
  
});
 
module.exports = app;