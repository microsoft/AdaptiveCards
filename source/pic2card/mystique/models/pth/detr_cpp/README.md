## Torchscript based Inference

Here we are trying to evaluate the benefits of using libtorch to handle the
model inference part.


## Dependencies

1. Opencv 3.2+
2. torch 1.6+
3. Detr Model trace file.
4. g++7 and above.


You need to download the C++-11 ABI compatible libtorch, and latest opencv to
link all the libraries correctly.

Opencv you can download from source and install it in local path, so that we can
link our library. As mentioned libtorch is already build one, only thing need to
be take care is the ABI compatibility.




## Integration with pic2card

Model inference is the first stage of the pic2card pipeline and all the pic2card
implementation are in python, we have to expose the c++ inference model to
python ecosystem back, in this case we are skipping all other requirements of
the python torch library.

This can be done multiple ways, looking into ways to expose the model interface
as a python module.


## Build the detr cpp inference python binding

To build this cpp extension you requires the torch python package, after
building you can remove that dependency except for those dynamic linked
libraries comes with the torch package. Initially we will keep both, eventually
for the production pipeline we can remove the dependency on the pytorch
dependency instead using the libtorch.


```bash
    pip install torch torchvision
    apt-get install libopencv-core-dev libopencv-imgproc-dev

    # Install the detr package into your python environment.
    python setup.py install
```

## To run the Pic2card with this new inference pipeline

```bash
# From the root dir of pic2card
ACTIVE_MODEL_NAME=pth_detr_cpp python -m app.main
```

## Debug Build and testing

Building a executable able testing without attaching to the python would be
required to debug problems at the c++ world in much easier fashion, for that use
this camke based build and corresponding executable.

```bash
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH="<path-to>/libtorch"
cmake --build . --config Release --verbose

# The model path and image path are supplied via variables now.
./deter
..
```
