#
# Mystique App docker.
#
# Mystique make use of the rcnn based model to do the object detection, here
# we are employing two optional methods of accessing the models for prediction.
# 1. Model is embedded inside the docker itself, or as frozen model.
# 2. The model will be deployed in tf_serving service outside this service,
#    we access that api from here.
#
# Both has it's pros and cons, so we will use based on which fits at particular
# usecase at hand.
#
# To build docker image with TFS support
#   $docker build -t imaginea.azurecr.io/imaginea/api_tfs_mystique:v0.6 .
#
# To build pic2card with backend TFS service.
#   $docker build --build-args tfs_enable=tfs --build-arg TARGET_API=tfs \
#      -t imaginea.azurecr.io/imaginea/api_frozen_mystique:v0.6 .
#
ARG TARGET_API=frozen_graph
FROM python:3.7.9-slim-buster as tfs
ADD requirements/requirements.txt /app/requirements.txt


FROM python:3.7.9-slim-buster as frozen_graph
# Fill in both, as in this case we need both dependencies.
ADD requirements/requirements-frozen_graph.txt /app/
ADD requirements/requirements.txt /app/
RUN cat /app/requirements-frozen_graph.txt >> /app/requirements.txt
COPY model/frozen_inference_graph.pb /app/model/


FROM $TARGET_API AS build
COPY app /app/app
COPY mystique /app/mystique


FROM python:3.7.9-slim-buster

# build args scoped inside current from block
# When building for frozen model disable it.
ARG tfs_enable=

ENV ENABLE_TF_SERVING=$tfs_enable
ENV TF_SERVING_URL=http://172.17.0.5:8501 \
    TF_SERVING_MODEL_NAME=mystique \
    PIP_DEFAULT_TIMEOUT=1000 \
    PORT=5050
COPY --from=build /app /app
WORKDIR /app

RUN pip install --upgrade pip && \
    apt-get update && \
    apt-get install -y --no-install-recommends libsm6 tesseract-ocr gcc && \
    apt-get clean &&\
    rm -rf /var/lib/apt/lists/*

RUN pip install -r requirements.txt && \
    rm -rf /root/.cache/pip && \
    echo '#!/bin/bash \n\n\
          gunicorn -w 2 -b 0.0.0.0:$PORT app.api:app \
          "$@"' >> /usr/local/bin/entrypoint.sh &&\
    chmod +x /usr/local/bin/entrypoint.sh

EXPOSE $PORT
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
