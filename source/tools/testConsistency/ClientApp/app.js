 // Copyright (c) Microsoft Corporation. All rights reserved. 
 // Licensed under the MIT License. 
const express = require("express");
const path = require('path');
const bodyParser = require('body-parser');
const querystring = require('querystring');
const optionsArray = require("./options");
const postRequest = require("./postRequest");

const getPostRequestPromise = postRequest.getPostRequestPromise;

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

  var postRequestPromises = []
  var platformNames = []

  optionsArray.forEach(function(element) {
    const platformJson = JSON.parse(element);
    platformNames.push(platformJson["platformName"]);
    const options = platformJson["options"];
    options["headers"]["Content-Length"] = Buffer.byteLength(formData);
    postRequestPromises.push(getPostRequestPromise(options, platformJson["platformName"], formData));
  });

  Promise.all(postRequestPromises).then(function(results) {
    var imageList = []
    var warningList = []
    var errorList = []

    parseResults(results, imageList, warningList, errorList);

    res.render("results.ejs", { 
      platformNames: JSON.stringify(platformNames),
      imageList: JSON.stringify(imageList),
      errorList: JSON.stringify(errorList),
      warningList: JSON.stringify(warningList)
    })
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

  var postRequestPromises = []
  var platformNames = []
  optionsArray.forEach(function(element) {
    const platformJson = JSON.parse(element);
    platformNames.push(platformJson["platformName"]);
    const options = platformJson["options"];
    options["headers"]["Content-Length"] = Buffer.byteLength(formData);
    options["path"] = "/test"
    postRequestPromises.push(getPostRequestPromise(options,
                                                  platformJson["platformName"], 
                                                  formData));
  });

  Promise.all(postRequestPromises).then(function(results) {
    var imageList = []
    var warningList = []
    var errorList = []

    parseResults(results, imageList, warningList, errorList);

    res.render("results.ejs", { 
      platformNames: JSON.stringify(platformNames),
      imageList: JSON.stringify(imageList),
      errorList: JSON.stringify(errorList),
      warningList: JSON.stringify(warningList)
    })
  });
  
});

function parseResults(results, imageList, warningList, errorList){
  for(var i = 0; i < results.length; i++){
    var image = "";
    var warnings = "";
    var errors = "";
    try{
      var platformResult = JSON.parse(results[i]);
      image = platformResult["imageData"];
      warnings = platformResult["warnings"];
      errors = platformResult["errors"];
    }
    catch(err){
      errors = "There was an error rendering the card. Please try again";
    }
    finally{
      imageList.push(image);
      warningList.push(warnings);
      errorList.push(errors);
    }
  }
}

module.exports = app;
