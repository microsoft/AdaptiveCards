// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License. 
// To run these tests, first ensure that the flask app for nodeJs is running at 127.0.0.1 port 5000
// and the flask app for .NET WPF is running at 127.0.0.1 port 4000. 
const request = require("supertest");
const app = require("./app");
const fs = require("fs");

test("The index/main page is accessible", function(done) {
     request(app)
      .get("/")
      .then(function(response) {
        expect(response.statusCode).toBe(200);
        done();
      });
});

test("Non-Templated cards are supported: Static cards without any template parameter specified should be accepted by the API", function(done) {
    const templateBuffer = fs.readFileSync("../../../../samples/v1.0/Scenarios/ActivityUpdate.json");
    const template = templateBuffer.toString('utf8')
    request(app)
      .post("/")
      .send(cardTemplate=template, cardData="")
      .then(function(response){
          expect(response.statusCode).toBe(200);
          done();
      });
});

test("Sending only data of template card is permitted: The data of the templated card should be accepted by the API and relevant errors will be generated", function(done) {
    const data = {
                    "name": "Helen Byrde"
                 }
    request(app)
      .post("/")
      .send(cardTemplate="", cardData=data)
      .then(function(response){
          expect(response.statusCode).toBe(200);
          done();
      });
});

test("Empty card payload is permitted: The API should accept and handle the case where no input is provided", function(done) {
    const data = {
                    "name": "Helen Byrde"
                 }
    request(app)
      .post("/")
      .send(cardTemplate="", cardData="")
      .then(function(response){
          expect(response.statusCode).toBe(200);
          done();
      });
});

test("Invalid JSON is permitted: Sending invalid JSON data is possible so that errors are caught at the renderer level", function(done) {
    const data = '{"title" : "invalid card data" ';
    const template = '{"title" : "invalid card template" ';
    request(app)
      .post("/")
      .send(cardTemplate=template, cardData=data)
      .then(function(response){
          expect(response.statusCode).toBe(200);
          done();
      });
});

test("Templated Cards are supported: A valid card template and along with valid data should be accepted by the API", function(done) {
   const template = {
                       "type": "AdaptiveCard",
                        "version": "1.0",
                        "body": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Hello ${name}!"
                                    }
                                ]
                }

    const data = {
                   "name": "Helen Byrde"
                 }
    request(app)
      .post("/")
      .send(cardTemplate=template, cardData=data)
      .then(function(response){
          expect(response.statusCode).toBe(200);
          done();
      });
}); 

test("Receiving Partial Result is permitted", function(done) {
    const template = {
                        "type": "AdaptiveCard",
                         "version": "1.0",
                         "body": [
                                     {
                                         "type": "TextBlock",
                                         "text": "Hello ${name}!"
                                     }
                                 ]
                 }
 
     const data = {
                    "name": "Helen Byrde"
                  }
     request(app)
       .post("/testIncompleteResult")
       .send(cardTemplate=template, cardData=data)
       .then(function(response){
           expect(response.statusCode).toBe(200);
           done();
       });
}); 
 