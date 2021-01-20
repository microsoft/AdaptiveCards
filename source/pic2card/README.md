# Pic2Card
![pic2card-build](https://github.com/Imaginea/pic2card/workflows/pic2card-build/badge.svg?branch=master)
## Description
Pic2Card is a solution for converting adaptive cards GUI design image into adaptive card payload Json.



![Pic2Card](./images/pic2card.png)


## Architecture
![Prediction Architecture](./images/architecture.png)

## Integrated with Adaptivecard designer
![Working Screenshot](./images/working1.jpg)

## Setup and Install pic2card 


### Setup Locally

**Install the requirements**

```shell
    # Setup dependency under a virtualenv
    $ virtualenv ~/env
    $ . ~/env/bin/activate
    (env)$ pip install -r requirements/requirements.txt
    (env)$ pip install -r requirements/requirements-frozen_graph.txt # tf specific only
```

**Run the pic2card Servie**

```shell
    # Start the service.
    (env)$ python -m app.main

    # Hit the API using curl
    $ (env) curl --header "Content-Type: application/json" \
            --request POST \
            --data '{"image":"base64 of the image"}' \
            http://localhost:5050/predict_json
```

**For Batch process**


```shell
   python -m commands.generate_card  --image_path="path/to/image"
```

### Select different Object Detection Model

The default object-detection model used with the pic2card pipeline is
`Faster-RCNN` based. If you want to try `DETR` based model shipped with
pic2card, you can easily switch the model and try the entire pic2card pipeline.
Or if you wish to train a custom object detection model for the pic2card
pipeline, you can do the same.

Currently the available models are:

- Faster-RCNN (default)
- DETR

```python
# To switch the model pipeline to `detr` based one.
$ ACTIVE_MODEL_NAME=detr python -m app.main
```

Select the model based on the below configuration.

```python
MODEL_REGISTRY = {
    # 1. Default model
    "tf_faster_rcnn": "mystique.detect_objects.ObjectDetection",
    # 2. Use it if you are deploying model in TFS
    "tfs_faster_rcnn": "mystique.detect_objects.TfsObjectDetection",
    # 3. DETR 
    "pth_detr": "mystique.obj_detect.DetrOD",
    # 4. DETR with CPP inference
    "pth_detr_cpp": "mystique.obj_detect.DetrCppOD"
}
```



### Run the pic2card service in docker container

You can build a docker image from the source code and play with it.

By default we only need single container, which embed the model model as well as
the pic2card application.

```bash

# Build the image with frozen model.
$ docker build -f docker/Dockerfile -t <username>/<container-name:tag> .

# Run the pic2card service with frozen graph model.
$ docker run -it --name pic2card -p 5050:5050 <image:name:tag>
```

### Use Tensorflow Serving to deploy pic2card

NOTE: This is an experimental feature only.

If you want to use the tensorflow serving to serve the model, then first build
the tensorflow serving with our model loaded with it in an another separate
docker. tf_serving provide RESTful APIs to interact with tensorflow models, in
standard way.

```bash
# You can export the model for inferencing from model checkpoint.
#
$ cp <tf saved_model>/* model/*
$ docker build . -t <image:tag> docker/Dockerfile-tf_serving
$ docker run -it -p 8501:8501 <image:tag>

# Build the pic2card pipeline without trained model. Now the inference is
# provided by the tensorflow serving.

$ docker build -t <image:tag> -f docker/Dockerfile .
```
