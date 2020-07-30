import detr
import numpy as np
import unittest


class TestDetrLib(unittest.TestCase):
    def setUp(self):
        pass
    def test_add_np_array(self):
        arr1 = np.array([[1, 2, 3], [2, 3, 4], [3, 4, 5]], dtype=np.uint8)
        res = detr.addmat(arr1, arr1)
        exp_res = np.array([[2, 4, 6], [4, 6, 8], [6, 8, 10]], dtype=np.uint8)
        self.assertTrue(np.all(res == exp_res))

    



