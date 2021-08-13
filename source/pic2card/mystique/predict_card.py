"""Module to  get the predicted adaptive card json"""

import base64
import io
import uuid
from typing import Dict, List

import cv2
import numpy as np
from PIL import Image
from mystique import config
from mystique.ac_export.card_template_data import DataBinding
from mystique.extract_properties import CollectProperties
from mystique.font_properties import classify_font_weights
from mystique.utils import get_property_method, send_json_payload
from mystique.card_layout import row_column_group
from mystique.card_layout import bbox_utils
from mystique.ac_export import adaptive_card_export


class PredictCard:
    """
    Collects the faster rcnn detected objects and handles the
    functionality of calling diffrent modules in card prediction
    and returning the predicted json objects.
    """

    def __init__(self, od_model=None):
        """
        Find the card components using Object detection model
        """
        self.od_model = od_model

    def collect_objects(
        self, output_dict=None, pil_image=None
    ):  # pylint: disable=too-many-locals, unused-argument, no-self-use
        """
        Returns the design elements from the faster rcnn model with its
        properties mapped
        @param output_dict: output dict from the object detection
        @param pil_image: input PIL image
        @return: Collected json of the design objects
                 and list of detected object's coordinates
        """
        boxes = output_dict["detection_boxes"]
        scores = output_dict["detection_scores"]
        classes = output_dict["detection_classes"]
        r_a, _ = boxes.shape
        detected_coords = []
        json_object = {}.fromkeys(["objects"], [])
        for i in range(r_a):
            if scores[i] * 100 >= config.MODEL_CONFIDENCE:
                object_json = dict().fromkeys(
                    ["object", "xmin", "ymin", "xmax", "ymax"], ""
                )
                object_json["object"] = config.ID_TO_LABEL[classes[i]]
                if object_json["object"]:
                    xmin, ymin, xmax, ymax = boxes[i]
                    object_json["xmin"] = xmin
                    object_json["ymin"] = ymin
                    object_json["xmax"] = xmax
                    object_json["ymax"] = ymax
                    object_json["coordinates"] = (xmin, ymin, xmax, ymax)
                    object_json["score"] = scores[i]
                    object_json["uuid"] = str(uuid.uuid4())
                    object_json["class"] = classes[i]

                    if object_json["object"] == "textbox":
                        detected_coords.append(
                            (
                                xmin - config.TEXTBOX_PADDING,
                                ymin,
                                xmax + config.TEXTBOX_PADDING,
                                ymax,
                            )
                        )
                    else:
                        detected_coords.append((xmin, ymin, xmax, ymax))

                    json_object["objects"].append(object_json)

        return json_object, detected_coords

    # pylint: disable=no-self-use
    def get_object_properties(
        self, design_objects: List[Dict], pil_image: Image, queue=None
    ) -> None:
        """
        Extract each design object's properties.
        @param design_objects: List of design objects collected from the model.
        @param pil_image: Input PIL image
        @param queue: Queue object of the calling process
        """
        # Creating an Extract Property class instance
        collect_prop = CollectProperties()
        for design_object in design_objects:
            collect_prop.uuid = design_object.get("uuid")
            # Invoking the methods from dict according to the design object
            property_object = get_property_method(
                collect_prop, design_object.get("object")
            )
            property_element = property_object(
                pil_image, design_object.get("coordinates")
            )
            design_object.update(property_element)
        design_objects = classify_font_weights(design_objects)
        # If any Queue object is passed , put the return value inside the
        # queue in-order to retrieve the value after the process finishes.
        if queue:
            queue.put(design_objects)
        return design_objects

    def main(self, image=None, card_format=None):
        """
        Handles the different components calling and returns the
        predicted card json to the API
        @param labels_path: faster rcnn model's label path
        @param forzen_graph_path: faster rcnn model path
        @param image: input image path
        @return: predicted card json
        """
        image = image.convert("RGB")
        image_np = np.asarray(image)
        image_np = cv2.cvtColor(image_np, cv2.COLOR_RGB2BGR)
        # Extract the design objects from faster rcnn model
        output_dict = self.od_model.get_objects(image_np=image_np, image=image)
        return self.generate_card(output_dict, image, image_np, card_format)

    # pylint: disable=unused-argument
    def tf_serving_main(
        self,
        bs64_img: str,
        tf_server: str,
        model_name: str,
        card_format: str = None,
    ) -> Dict:
        """
        Do model inference using TF-Serve service.
        """

        api_path = "v1/models/{model_name}:predict"
        payloads = {
            "signature_name": "serving_default",
            "instances": [{"b64": bs64_img}],
        }
        # Hit the tf-serving and get the prediction
        response = send_json_payload(
            api_path, body=payloads, host_port=tf_server
        )

        pred_res = response["predictions"][0]

        filtered_res = {}
        for key_col in [
            "detection_boxes",
            "detection_scores",
            "detection_classes",
        ]:
            filtered_res[key_col] = np.array(pred_res[key_col])

        # Prepare the card from object detection.
        imgdata = base64.b64decode(bs64_img)
        image = Image.open(io.BytesIO(imgdata))
        image = image.convert("RGB")
        image_np = np.asarray(image)
        image_np = cv2.cvtColor(image_np, cv2.COLOR_RGB2BGR)
        card = self.generate_card(filtered_res, image, image_np, card_format)
        return card

    # pylint: disable=unused-argument
    def generate_card(
        self,
        prediction: Dict,
        image: Image,
        image_np: np.array,
        card_format: str,
    ):
        """
        From the object detection result and image, generate adaptive
        card object.
        @param prediction: Prediction result from rcnn model
        @param image: PIL Image object to crop the regions.
        @param image_np: Array representation of the image.
        @param card_format: format specification for template data binding
        """
        # TODO: Remove the reduendant usage of image and image_np

        # Collect the objects along with its design properites

        predicted_objects, detected_coords = self.collect_objects(
            output_dict=prediction, pil_image=image
        )
        # Remove overlapping rcnn objects
        bbox_utils.remove_noise_objects(predicted_objects)

        # Arrange the design elements
        return_dict = {}.fromkeys(["card_json"], "")
        card_json = {
            "type": "AdaptiveCard",
            "version": "1.0",
            "body": [],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
        }

        if config.MULTI_PROC:
            card_layout = row_column_group.generate_card_layout_multi(
                predicted_objects, image, self
            )
        else:
            card_layout = row_column_group.generate_card_layout_seq(
                predicted_objects, image, self
            )
        body = adaptive_card_export.export_to_card(card_layout, image)

        # if format==template - generate template data json
        return_dict["card_json"] = {}.fromkeys(["data", "card"], {})
        if card_format == "template":
            databinding = DataBinding()
            data_payload, body = databinding.build_data_binding_payload(body)
            return_dict["card_json"]["data"] = data_payload
        # Prepare the response with error code
        error = None
        if not body or not detected_coords:
            error = {"msg": "Failed to generate card components", "code": 1000}
        else:
            card_json["body"] = body

        if card_format != "template":
            return_dict["card_json"]["card"] = card_json
        else:
            return_dict["card_json"]["card"] = card_json
        return_dict["error"] = error

        return return_dict
