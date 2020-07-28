# Copyright (c) Microsoft Corporation. All rights reserved. 
# Licensed under the MIT License. 
import os
import json
from flask import request 
import subprocess 
from app import app 
import requests


@app.route('/', methods=['POST'])
def index():
    """This POST request accepts JSON and returns the card screenshot on UWP.

    It accepts JSON data via HTTP POST, creates a new JSON string with the new 
    fields and sends it to the UWP app. It then receives back the screenshot 
    of the card to the client.

    Returns:
        A JSON string that has fields for "imageData" and "errors". The
        imageData field contains a base 64 encoded string representing the
        screenshot of the card.
   """
    template = request.form['template']
    data = request.form['data']
    card = ''
    
    if len(data) != 0:
        card = '{"data": ' + data + ', "template" : ' + template + '}'
    else: 
        card = '{"data": "" ' + ', "template" : ' + template + '}'

    # POST URL
    url = "http://10.64.36.176:8800/"

    headers = {
    'Content-Type': 'application/json'
    }

    response = requests.request("POST", url, headers=headers, data = card.encode('utf8'))

    img_json_str = response.text.encode('utf8')
    return img_json_str
  
