from setuptools import setup, Extension
from torch.utils import cpp_extension

#opencv_inc_dir = "/home/haridas/projects/opensource/detr/libs/opencv-4.3.0/build/release/include/opencv4/"
#opencv_lib_dir = "/home/haridas/projects/opensource/detr/libs/opencv-4.3.0/build/release/lib"


setup(name="detr",
    ext_modules=[cpp_extension.CppExtension(
        name='detr',
        sources=['detr.cpp'],
        libraries=["opencv_core"],
        #include_dirs=[opencv_inc_dir],
        #library_dirs=[opencv_lib_dir],
        extra_compile_args=["-fno-inline"]
        )
    ],
    cmdclass={'build_ext': cpp_extension.BuildExtension}
)