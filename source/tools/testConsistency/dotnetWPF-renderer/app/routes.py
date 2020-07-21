# Copyright (c) Microsoft Corporation. All rights reserved. 
# Licensed under the MIT License. 
import os 
import json 
from flask import request 
import subprocess 
from app import app 

@app.route('/', methods=['POST'])
def index():
        """This POST request accepts JSON and returns the card screenshot on .NET WPF

            It accepts JSON data via HTTP POST, creates a new JSON string with the new 
            fields and sends it to the nodejs app. It then receives back the screenshot 
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

        card_byte_buffer = bytes(card, 'utf-8')  # The subprocess module requires the input to be a byte stream


        res_json = subprocess.run(['WPFDriver/WPFDriver/bin/Debug/WPFDriver.exe'],
                                    input=card_byte_buffer,
                                    capture_output=True 
                                    )
        img_json_str = (res_json.stdout).decode('utf-8')
        return img_json_str

@app.route('/test', methods=['POST'])
def test():
        """This POST request is primarily for testing purposes. 

            It accepts JSON data via HTTP POST, creates a new JSON string with the new 
            fields and sends it a mock WPF app. It receives an incomplete JSON string that contains only 
            part of a base64encoded string. It serves to demonstrate the scenario where the driver program 
            crashes midway or is not able to send back all the data.

            Returns:
                A string that contains only part of the base64 encodeded image.
        """
        template = request.form['template']
        data = request.form['data']
        card = ''
        if len(data) != 0:
            card = '{"data": ' + data + ', "template" : ' + template + '}'
        else: 
            card = '{"data": "" ' + ', "template" : ' + template + '}'
        card_byte_buffer = bytes(card, 'utf-8')

        res_json = subprocess.run(['WPFDriver/sendPartialResult/bin/Debug/netcoreapp3.1/sendPartialResult.exe'],
                                    input=card_byte_buffer,
                                    capture_output=True 
                                    )
        img_json_str = (res_json.stdout).decode('utf-8')
        return img_json_str
