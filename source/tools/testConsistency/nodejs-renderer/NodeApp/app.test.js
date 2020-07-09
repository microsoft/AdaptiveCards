// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License. 
const path = require('path');
const fs = require('fs');
const spawn = require('child_process').spawn;

it.each(GetVersionZeroFiles())('%s should act correctly', function(card, done) {
  testOneCard(card, done);
});

it.each(GetVersionOneFiles())('%s should act correctly', function(card, done) {
    testOneCard(card, done);
});

it.each(GetVersionTwoFiles())('%s should act correctly', function(card, done) {
  testOneCard(card, done);
});

function testOneCard(card, done) {
  const child = spawn('node', ['app.js']);
  const fs = require('fs');
  const data = fs.readFileSync(card);
  const cardPayLoad = `{"data" : "", "template": ${data}}`
  const buffer = Buffer.from(cardPayLoad, 'utf-8')
  child.stdin.write(buffer);
  var resultBuffer = "";
  child.stdout.on('data', function(data) {
    resultBuffer = resultBuffer + data;
  });

  child.on('close', function(exitCode) {
    resultJsonString = resultBuffer.toString('utf8');
    expect(exitCode).toBe(0);
    expect(resultJsonString.length).toBeGreaterThan(0);
    var resultJsonObj  = JSON.parse(resultJsonString);
    if (successfullyRendered(resultJsonObj)) {
      expect(isValidBase64(resultJsonObj)).toBeTruthy();
      done();
    } else {
      expect(nonEmptyWarningsAndErrors(resultJsonObj)).toBeTruthy();
      done();
    }
  });
}


function GetData(payLoadPath) {
  const fileNames = fs.readdirSync(payLoadPath);
  var data = []
  fileNames.forEach(function(file) {
    data.push(payLoadPath + "/" + file);
  });
  return data;
}


function GetVersionZeroFiles() {
  const tests = GetData("../../../../../samples/v1.0/Tests");
  const scenarios = GetData("../../../../../samples/v1.0/Scenarios");
  const elements = GetData("../../../../../samples/v1.0/Elements");
  const cards = [].concat(tests, scenarios, elements);
  return cards;
}


function GetVersionOneFiles() {
  const tests = GetData("../../../../../samples/v1.1/Tests");
  const scenarios = GetData("../../../../../samples/v1.1/Scenarios");
  const elements = GetData("../../../../../samples/v1.1/Elements");
  const cards = [].concat(tests, scenarios, elements);
  return cards;
}

function GetVersionTwoFiles() {
  const tests = GetData("../../../../../samples/v1.2/Tests");
  const scenarios = GetData("../../../../../samples/v1.2/Scenarios");
  const elements = GetData("../../../../../samples/v1.2/Elements");
  const cards = [].concat(tests, scenarios, elements);
  return cards;
}


function nonEmptyWarningsAndErrors(resJsonObj) {
  const errorList = resJsonObj.errors;
  const warningList = resJsonObj.warnings;
  return (errorList.length != 0 || warningList.length!= 0);
}


function successfullyRendered(resJsonObj) {
  const img = resJsonObj.imageData; 
  const errorList = resJsonObj.errors; 
  const warningList = resJsonObj.warnings;
  return (img!= null && img.length != 0 && errorList.length == 0 && warningList.length == 0);
}

function isValidBase64(resJsonObj) {
  try {
    imgStr = resJsonObj.imageData;
    return btoa(atob(imgStr)) == imgStr;
  } 
  catch (err) {
    return false;
  }
}
