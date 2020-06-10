import fs from 'fs';
import express from 'express';
import path from 'path';

const stdinBuffer = fs.readFileSync(0); 
const jsonData = JSON.parse(stdinBuffer);
const cardData = jsonData.data;
const cardTemplate = jsonData.template;

const __dirname = path.resolve();
const app = express();
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

app.get('/', function(req, res){
  res.render('home.ejs', {
    cardTemplate: JSON.stringify(cardTemplate),
    cardData: JSON.stringify(cardData),
  });
});

app.listen(3000);
console.log('App is running at:');
console.log('http://localhost:3000/');
