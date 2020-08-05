import os
from setuptools import setup, Extension
from torch.utils import cpp_extension

os.environ["CXX"] = "g++-8"
os.environ["CC"] = "g++-8"

# Required libopencv-3.2-dev and libopencv-3.2
setup(name="detr",
    ext_modules=[cpp_extension.CppExtension(
        name='detr',
        sources=['detr.cpp'],
        libraries=["opencv_core", "opencv_imgproc"],
        extra_compile_args=["-fno-inline"]
        )
    ],
    cmdclass={'build_ext': cpp_extension.BuildExtension}
)