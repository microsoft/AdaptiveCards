const fs = require('fs');
const express = require('express');
const path = require('path');
const puppeteer = require("puppeteer");
const ACData = require("adaptivecards-templating");
const AdaptiveCards = require("adaptivecards");

const app = express();
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));
app.use(express.static(__dirname + '/public'));

var cardPayLoad = "";

//This jsonString captures the required fields
const resultJsonString = '{ "imageData": "", "errors": "", "warnings" : ""}';
var resultJson = JSON.parse(resultJsonString);
var errorList = [];
resultJson.errors = errorList;

app.get('/', function(req, res) {
  res.render('home.ejs', {
    cardPayLoad: JSON.stringify(cardPayLoad)
  });
});

app.listen(3000);

async function takeScreenShot(pageURL, elementSelector) {
  try {
    const browser = await puppeteer.launch();
    const page = await browser.newPage(); 
    
    await page.setViewport({
      width:1280,
      height:800,
    });

    await page.goto(pageURL);

    const card = await page.$(elementSelector);
    const imgScreenshot = await card.screenshot();
    browser.close();
    return imgScreenshot.toString('base64');
  }
  catch(error) {
    throw error;
  }
}

function readInputFromStdin() {
  try {
    const stdinBuffer = fs.readFileSync(0);
    return stdinBuffer;
  }
  catch(error) {
    throw error;
  }
}

function createCardPayLoad(jsonPayLoad) {
  try {
    const template = new ACData.Template(jsonPayLoad.template);
    const payLoad = template.expand({$root: jsonPayLoad.data });
    return payLoad;
  }
  catch(error) {
    throw error;
  }
}

function getRenderingFailures(payLoad) {
  try {
    const testCard = new AdaptiveCards.AdaptiveCard();
    testCard.parse(payLoad);
    const validationProperties = testCard.validateProperties();
    return validationProperties.failures;
  }
  catch(error) {
    throw error;
  }
}


async function main() {
  try {
    const input = readInputFromStdin();
    const jsonData = JSON.parse(input);
    const payLoad = createCardPayLoad(jsonData);
    cardPayLoad = payLoad;
    resultJson.warnings = getRenderingFailures(payLoad);
    resultJson.imageData = await takeScreenShot('http://localhost:3000/', '#AdaptiveCard');
  }
  catch(error) {
    errorList.push(error.name +": " + error.message);
  }
  finally {
    console.log(JSON.stringify(resultJson));
    process.exit(0);
  }
}
main();
