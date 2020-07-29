import detr_infer
import torch
t = torch.Tensor([1, 2, 3])
print(detr_infer.sigmoid(t))
print(detr_infer.get_tensor())


tw = detr_infer.TensorWrapper()
print(tw.tensor)
