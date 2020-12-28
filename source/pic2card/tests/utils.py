import os
import base64
import string
from random import choice

os.environ["test_img_path"] = "./tests/test_images/test01.png"
headers = {"Content-Type": "application/json"}
payload_empty_dict_data = "{'image': null}"
payload_data_some_string = "{'image': 'some string'}"
api_dict = {
            "GetCardTemplatesTestAPI": "/get_card_templates",
            "PredictJsonTestAPI": "/predict_json",
            "TestSampleImages": "/predict_json",
            "PredictJsonDebugTestAPI": "/predict_json_debug"
            }


def img_to_base64(img_path):
    """ Returns base64 string in payload format for a given image path """
    with open(img_path, "rb") as img_file:
        imgb64_string = base64.b64encode(img_file.read()).decode("utf-8")
        payload_data = f'{{"image": "{imgb64_string}"}}'
    return payload_data


def generate_base64():
    """ Returns a random generated base64 string of size 3MB """
    upper = string.ascii_uppercase
    lower = string.ascii_lowercase
    digits = string.digits
    rand_b64 = "".join(choice(upper + lower + digits) for _ in range(2000001))
    payload_data = f'{{"image": "{rand_b64}"}}'
    return payload_data


def get_response(client, api, headers, data):
    """ Returns the response of a post request """
    response = client.post(api, headers=headers, data=data)
    return response
