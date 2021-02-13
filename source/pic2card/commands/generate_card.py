"""
Command to predict the adaptive card json

Usage :
python -m command.generate_card --image_path=/path/to/input/image
"""
import argparse
import json
from PIL import Image

from mystique.predict_card import PredictCard
from mystique.utils import load_od_instance


def main(image_path=None, card_format=None):
    """
    Command runs the predict card function

    @param image_path: input image path
    """
    image = Image.open(image_path)
    object_detection = load_od_instance()
    card_json = PredictCard(object_detection).main(image=image,
                                                   card_format=card_format)
    print(json.dumps(card_json.get("card_json"), indent=2))
    print(card_json.keys(), card_json["card_json"].keys())


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Predict the Card Json")
    parser.add_argument("--image_path", required=True,
                        help="Enter Image path")
    parser.add_argument("--card_format",
                        help="Enter Format as 'template' if template data \
                              payload is required",
                        default=None)
    args = parser.parse_args()
    main(image_path=args.image_path, card_format=args.card_format)
