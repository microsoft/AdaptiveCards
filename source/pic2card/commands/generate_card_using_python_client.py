"""
Command to predict the adaptive card json using python client

Usage :
python generate_card_using_python_client.py --image_path=/image_path \
    --api_url=url_of_the_service
"""
import argparse
import json
import base64
import requests


def main(image_path=None, api_url=None, card_format=None):
    """
    Predict the card using python client

    @param image_path: input image path
    @param api_url: url of the prediction service
    """
    base64_string = ""
    with open(image_path, "rb") as image_file:
        base64_string = base64.b64encode(image_file.read()).decode()
    if card_format:
        response = requests.post(api_url,
                                 data=json.dumps({"image": base64_string}),
                                 headers={"Content-Type": "application/json"},
                                 params={"format": card_format})
    else:
        response = requests.post(api_url,
                                 data=json.dumps({"image": base64_string}),
                                 headers={"Content-Type": "application/json"})

    print(json.dumps(response.json().get("card_json", ""), indent=2))
    if card_format:
        print(json.dumps(response.json().get("template_data_payload", ""),
                         indent=2))


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Predict the Card Json")
    parser.add_argument("--image_path", required=True,
                        help="Enter Image path")
    parser.add_argument("--api_url", required=True,
                        help="Enter Service URL")
    parser.add_argument("--card_format",
                        help="Enter 'template' if card template data \
                              payload is needed",
                        default=None)
    args = parser.parse_args()
    main(image_path=args.image_path,
         api_url=args.api_url,
         card_format=args.card_format)
