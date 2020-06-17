import os
import json
from flask import request 
import subprocess 
from app import app 


@app.route('/node', methods=['POST'])
def index():
    """This POST request accepts JSON and returns the card screenshot on nodeJS.

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

    template_json = json.loads(template)
    data_json = json.loads(data)

    #We create the new JSON string to send to the node renderer
    card = '{"data": "", "template": ""}'
    card_json = json.loads(card)
    card_json["data"] = data_json
    card_json["template"] = template_json

    card_byte_buffer = bytes(json.dumps(card_json), 'utf-8')  # The subprocess module requires the input to be a byte stream

    #output saves saves all the data node sends to stdout
    output = subprocess.check_output(
              ['node', 'NodeApp/app.js'],
              input=card_byte_buffer,
             )

    img_json_str = output.decode('utf-8')
    img_json = json.loads(img_json_str)
    return json.dumps(img_json)
  