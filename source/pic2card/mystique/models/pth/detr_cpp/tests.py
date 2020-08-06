import detr
import numpy as np
from PIL import Image
import unittest


class TestDetrLib(unittest.TestCase):
    def setUp(self):
        self.model_path = "/mnt1/haridas/projects/pic2card-models/pytorch/detr_trace.pt"
        self.image_path = "/home/haridas/projects/mystique/data/templates_test_data/1.png"
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

    def test_model_loading(self):
        model = detr.Detr(self.model_path)
        model.load()
        pred_logits, pred_boxes = model.predict(self.img_np)

        print(pred_logits.shape)
        self.assertEqual(pred_logits.shape, (60, 7))
        self.assertEqual(pred_boxes.shape, (60, 4))