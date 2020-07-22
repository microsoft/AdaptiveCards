## Torchscript based Inference

Here we are trying to evaluate the benefits of using libtorch to handle the
model core functionality.



## Dependencies

1. Opencv 4.3.0
2. libtorch nightly build.
2. DETR github implementation.



You need to download the C++-11 ABI compatible libtorch, and latest opencv to
link all the libraries correctly.

Opencv you can download from source and install it in local path, so that we can
link our library. As mentioned libtorch is already build one, only thing need to
be take care is the ABI compatibility.


## Build and test the libtorch

```bash
# Build opencv first
cd opencv-4.3.0
mkdir build
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../release ..
make install


# Build the detr_inference
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH="<path-to>/libtorch;<path-to>/opencv-4.3.0/release"
cmake --build . --config Release --verbose

# The model path and image path are supplied via variables now.
./deter_infer
..
```


## Integration with pic2card

Model inference is the first stage of the pic2card pipeline and all the pic2card
implementation are in python based, we have to expose the c++ inference model to
python ecosystem back, in this case we are skipping all other requirements of
the python torch library.

This can be done multiple ways, looking into ways to expose the model interface
as a python module.
