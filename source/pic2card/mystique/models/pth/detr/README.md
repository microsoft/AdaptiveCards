# DETR Model From Facebook

DETR is a new type of architecture used to train the object detection models
using the Transformers, and provides end-to-end design specification.


This model supports the COCO data format, so we have build our custom data in
coco standards and trained our model.


## Training Process

Before proceeding to training We need two things
1. Clone the detr project from github
2. Prepare the coco datasets for our custom data.


```bash
git clone https://github.com/facebookresearch/detr

# For dataset, Use Labelmg to label the images and use the voc2coco command
# to conver the data to coco format.

python -m commands.voc2coco ./labelmg_img_foler <coco-jsonpath>.json
```

### Training command 

Play with the different hyper parameters to find the best model possible from
our data.

We have mainly played with the learning rate and epoch to get better model out
of it. The model pipeline has inbuilt data transformations to prevent
over fitting the training data.


```bash
python main.py --dataset_file pic2card \
    --coco_path ./train_and_test-2020-Jun-05-coco \
    --epochs 150 \
    --lr=1e-4 \
    --batch_size=2 \
    --num_queries=100 \
    --output-dir=outputs-`date +%F-%s` \
    --lr_drop 20  \
    --resume=detr-r50_no-class-head.pth
```

## Inference Options

We are using torchscript to do the inference. Which provides the best way to
serialize and share the trained model without any dependencies to the training
pipeline. This means we can train the model using the `detr` repo and use the
exported model for inference by simply load it under torch.

We can load this torchscript version of the model via libtorch, that means
without any python dependency we can do the optimal inference.


NOTE: We are keeping the exported models in google drive, please download it to serve
the detr based pic2card geeneration


## Notebooks

Please check the `<root>/notebooks/DETR.ipynb` to do the model inference
and evaluation pipelines.
