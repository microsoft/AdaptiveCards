const fs = require('fs');
const express = require('express');
const path = require('path');
const puppeteer = require("puppeteer");

const stdinBuffer = fs.readFileSync(0); 
const jsonData = JSON.parse(stdinBuffer);
const cardData = jsonData.data;
const cardTemplate = jsonData.template;

const app = express();
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));


//This jsonString captures the required fields
const resultJsonString = '{ "imageData": "", "errors": ""}';

//This is declared as a variable because its fields will be updated
var imgJson = JSON.parse(resultJsonString);

app.get('/', function(req, res){
  res.render('home.ejs', {
    cardTemplate: JSON.stringify(cardTemplate),
    cardData: JSON.stringify(cardData),
  });
});

async function takeScreenShot() {
  const browser = await puppeteer.launch();
  const page = await browser.newPage(); 
  const imgName = 'nodeRender.png';
  
  await page.setViewport({
    width:1280,
    height:800,
  });

  await page.goto('http://localhost:3000/');

  const card = await page.$('#AdaptiveCard');
  await card.screenshot({
    path: imgName,
  });

  await browser.close();
};

function base64_encode(img){
  const bitmap = fs.readFileSync(img);
  return new Buffer(bitmap).toString('base64');
}

async function sendEncodedImage() {
  await takeScreenShot();
  const img = base64_encode('nodeRender.png');
  imgJson.imageData = img;

  //Delete the image file from the system after reading it 
  fs.unlinkSync('nodeRender.png');
  console.log(JSON.stringify(imgJson));
  process.exit(0);
}

app.listen(3000);
sendEncodedImage();
