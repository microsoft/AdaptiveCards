import detr
import numpy as np

arr1 = np.array([[1, 2, 3], [2, 3, 4], [3, 4, 5]], dtype=np.uint8)

print(detr.addmat(arr1, arr1))
