# Copyright (c) Microsoft Corporation. All rights reserved. 
# Licensed under the MIT License. 
import os
import requests 
import json 
from flask import request 
import subprocess 
from app import app 
 
android_post_url = 'http://127.0.0.1:8080/'

@app.route('/', methods=['POST'])
def index():
        """This POST request accepts JSON and returns the card screenshot on android 
           Pixel 3

            It accepts JSON data via HTTP POST, creates a new JSON string with the new 
            fields and sends it to the nodejs app. It then receives back the screenshot 
            of the card to the client.

            Returns:
                A JSON string that has fields for "imageData" and "errors". The
                imageData field contains a base 64 encoded string representing the
                screenshot of the card.
        """
        print("requested on android")
        cardPayload = request.form["template"]
        params = {'cardPayload' : cardPayload}
        session = requests.Session()
        response = session.post(android_post_url, data=params)
        resJson = str(response.text) 

        # Java adds extra escape characters which we need to manually remove
        resJson = resJson.replace('\\', '')
        return resJson 
