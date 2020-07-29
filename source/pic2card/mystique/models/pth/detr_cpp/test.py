import detr_infer
import torch
import numpy as np

t = torch.Tensor([1, 2, 3])
print(detr_infer.sigmoid(t))
print(detr_infer.get_tensor())


tw = detr_infer.TensorWrapper()
print(tw.tensor)


#arr = np.array([1, 2, 3, 4], dtype=np.uint8)
arr = np.random.normal(loc=255, size=(10, 10, 3))

print(detr_infer.np_to_mat(arr))

#print(detr_infer.cvMatrix())
