"""
Command to predict the adaptive card json

Usage :
python -m command.generate_card --image_path=/path/to/input/image
"""
import argparse
import json
from PIL import Image

from mystique.detect_objects import ObjectDetection
from mystique.predict_card import PredictCard
from mystique.initial_setups import set_graph_and_tensors


def main(image_path=None, card_format=None):
    """
    Command runs the predict card function

    @param image_path: input image path
    """
    image = Image.open(image_path)
    object_detection = ObjectDetection(*set_graph_and_tensors())
    card_json = PredictCard(object_detection).main(image=image,
                                                   card_format=card_format)
    print(json.dumps(card_json.get("card_json"), indent=2))
    if card_format:
        print(json.dumps(card_json.get('template_data_payload', ''),
                         indent=2))


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
