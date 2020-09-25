import os
from typing import Dict, List

from PIL import Image
import unittest
import numpy as np
import cv2

from mystique.utils import load_od_instance
from mystique.predict_card import PredictCard
from mystique.arrange_card import CardArrange
from mystique.extract_properties import CollectProperties

curr_dir = os.path.dirname(__file__)


class TestUtil:

    def collect_json_objects(self, image: Image,
                             model_instance: PredictCard) -> Dict:
        """
        Returns the dict of design objects collected from the prediction
        @param image: input PIL image
        @param model_instance: model instance object
        @return: dict of design objects
        """
        image = image.convert("RGB")
        image_np = np.asarray(image)
        image_np = cv2.cvtColor(image_np, cv2.COLOR_RGB2BGR)
        output_dict = model_instance.od_model.get_objects(
                image_np=image_np, image=image
        )
        return model_instance.collect_objects(output_dict=output_dict,
                                              pil_image=image)

    def collect_image_sizes(self, json_objects: Dict, image: Image) -> List:
        """
        Returns the list of extracted image object sizes of the input image
        @param json_objects: dict of design objects
        @param image: input PIL image
        @return: list of image object sizes
        """
        collect_properties = CollectProperties(image)
        image_objects = [image_object for image_object in
                         json_objects["objects"]
                         if image_object["object"] == "image"]
        for design_object in image_objects:
            property_object = getattr(collect_properties,
                                      design_object.get("object"))
            design_object.update(property_object(design_object.get("coords")))
        return [design_object.get("size", "") for design_object in
                image_objects]


class TestIOU(unittest.TestCase):
    card_arrange = CardArrange()

    def setUp(self):
        self.image_path = os.path.join(
                curr_dir, "../tests/test_images/test01.png")
        self.test_util = TestUtil()
        self.model_instance = load_od_instance()
        self.model_instance = PredictCard(self.model_instance)

        self.image = Image.open(self.image_path)
        self.json_objects, _ = self.test_util.collect_json_objects(
                self.image, self.model_instance)

    def test_object_collection(self):
        """Tests the collected object's count"""
        self.assertEqual(len(self.json_objects["objects"]), 23)

    def test_iou(self):
        """Tests the iou based noise removal count"""
        self.card_arrange.remove_noise_objects(self.json_objects)
        self.assertEqual(len(self.json_objects["objects"]), 19)

    def test_image_size(self):
        """Tests the image object sizes"""
        extracted_sizes = self.test_util.collect_image_sizes(self.json_objects,
                                                             self.image)
        self.assertEqual(extracted_sizes, ["Small", "Small"])


if __name__ == '__main__':
    unittest.main()
