"""
Command to predict the adaptive card json using python client

Usage :
python generate_card_using_python_client.py --image_path=/image_path \
    --api_url=url_of_the_service
"""
import argparse
import base64
from mystique.utils import send_json_payload


def main(image_path=None, api_server=None, card_format=None):
    """
    Predict the card using python client

    @param image_path: input image path
    @param api_url: url of the prediction service
    """
    base64_string = ""
    api_path = "/predict_json"
    with open(image_path, "rb") as image_file:
        base64_string = base64.b64encode(image_file.read()).decode()
    if card_format:
        response = send_json_payload(api_path,
                                     body={"image": base64_string},
                                     host_port=api_server,
                                     url_params={"format": card_format})
    else:
        response = send_json_payload(api_path,
                                     body={"image": base64_string},
                                     host_port=api_server)

    print(response.get("card_json", ""))
    if card_format:
        print(response.get("template_data_payload", ""))


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Predict the Card Json")
    parser.add_argument("--image_path", required=True,
                        help="Enter Image path")
    parser.add_argument("--api_server", required=True,
                        help="Enter the api server host and port")
    parser.add_argument("--card_format",
                        help="Enter 'template' if card template data \
                              payload is needed",
                        default=None)
    args = parser.parse_args()
    main(image_path=args.image_path,
         api_server=args.api_server,
         card_format=args.card_format)
