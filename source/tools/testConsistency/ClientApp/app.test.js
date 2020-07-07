// To run these tests, first ensure that the flask app for nodeJs is running at 127.0.0.1 port 5000
// and the flask app for .NET WPF is running at 127.0.0.1 port 4000. 
const request = require("supertest");
const app = require("./app");
const fs = require("fs");

test("The GET request to the index page should return a response code 200", function(done) {
     request(app)
      .get("/")
      .then(function(response) {
        expect(response.statusCode).toBe(200);
        done();
      });
});

test("Sending no card data should still return a response code 200", function(done) {
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

test("Sending no card template should still return a response code 200", function(done) {
    const data = {
                    "name": "Matt Hidinger"
                 }
    request(app)
      .post("/")
      .send(cardTemplate="", cardData=data)
      .then(function(response){
          expect(response.statusCode).toBe(200);
          done();
      });
});

test("Sending an empty form should still return a response code 200", function(done) {
    const data = {
                    "name": "Matt Hidinger"
                 }
    request(app)
      .post("/")
      .send(cardTemplate="", cardData="")
      .then(function(response){
          expect(response.statusCode).toBe(200);
          done();
      });
});

test("Sending invalid JSON data should still return a response code 200", function(done) {
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

test("Sending a valid card PayLoad should return a response code 200", function(done) {
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
                   "name": "Matt Hidinger"
                 }
    request(app)
      .post("/")
      .send(cardTemplate=template, cardData=data)
      .then(function(response){
          expect(response.statusCode).toBe(200);
          done();
      });
}); 

test("Receiving partial JSON data should return a response code 200", function(done) {
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
                    "name": "Matt Hidinger"
                  }
     request(app)
       .post("/testIncompleteResult")
       .send(cardTemplate=template, cardData=data)
       .then(function(response){
           expect(response.statusCode).toBe(200);
           done();
       });
}); 
 