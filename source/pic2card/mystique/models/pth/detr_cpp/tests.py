import os
import detr
import numpy as np
from PIL import Image
import unittest

curr_dir = os.path.dirname(__file__)


class TestDetrLib(unittest.TestCase):
    def setUp(self):
        self.model_path = os.path.join(
            curr_dir, "../../../../model/pth_models/detr_trace.pt")
        self.image_path = os.path.join(
            curr_dir, "../../../../tests/test_images/test01.png")
        img = Image.open(self.image_path)
        self.img_np = np.asarray(img)

    def test_add_np_array(self):
        "Check numpy Type conversion works"
        arr1 = np.array([[1, 2, 3], [2, 3, 4], [3, 4, 5]], dtype=np.uint8)
        res = detr.addmat(arr1, arr1)
        exp_res = np.array([[2, 4, 6], [4, 6, 8], [6, 8, 10]], dtype=np.uint8)
        self.assertTrue(np.all(res == exp_res))

    def test_detr_constructor(self):
        detr1 = detr.Detr(self.model_path)
        self.assertEqual(self.model_path, detr1.model_path)
        self.assertEqual(self.model_path, detr1.get_model_path())

    def test_model_inference(self):
        model = detr.Detr(self.model_path)
        pred_logits, pred_boxes = model.predict(self.img_np)

        self.assertEqual(pred_logits.shape, (60, 7))
        self.assertEqual(pred_boxes.shape, (60, 4))

    def test_image_resizing(self):
        model = detr.Detr(self.model_path)
        self.assertEqual(
            model.get_new_size(400, 300, 800, 1333),
            [800, 600])

        self.assertEqual(
            model.get_new_size(800, 300, 800, 1333),
            [500, 187])

        self.assertEqual(
            model.get_new_size(300, 500, 800, 1333),
            [480, 800])

        self.assertEqual(
            model.get_new_size(1500, 1500, 800, 1333),
            [800, 800])
