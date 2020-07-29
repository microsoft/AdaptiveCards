// #include <iostream>
// #include <memory>
#include <stdio.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>
#include <torch/extension.h>

using namespace cv;
// using namespace std;
namespace py = pybind11;

// // Scale sizes
// int
// main(int argc, const char *argv[])
// {
//   string model_path = "/mnt1/haridas/projects/pic2card-models/pytorch/detr_trace.pt";
//   string image_path = "/mnt1/haridas/projects/mystique/data/templates_test_data/1.png";

//   // if (argc != 3)
//   // {
//   //   std::cerr << "usage: detr-app <path-to-exported-script-module> <image-path> \n";
//   //   return -1;
//   // }

//   try
//   {
//     // Deserialize image_pathiptModule from a file using torch::jit::load().
//     Mat image = cv::imread(image_path, 1);
//     cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
//     cv::Size scale(500, 600);
//     cv::resize(image, image, scale);
//     image.convertTo(image, CV_32FC3, 1.0f / 255.0f);
//     std::cout << "Image: " << image.size();

//     auto input_tensor = torch::from_blob(image.data, {1, 500, 600, 3});
//     input_tensor = input_tensor.permute({0, 3, 1, 2});
//     std::cout << "Tensor: " << input_tensor[0][0].sizes();
//     // Apply normalization based on imagenet data.
//     input_tensor[0][0] = input_tensor[0][0].sub_(0.485).div_(0.229);
//     input_tensor[0][1] = input_tensor[0][1].sub_(0.456).div_(0.224);
//     input_tensor[0][2] = input_tensor[0][2].sub_(0.406).div_(0.225);

//     torch::jit::script::Module module;
//     module = torch::jit::load(model_path);
//     // Create a vector of inputs.
//     std::vector<torch::jit::IValue> inputs;
//     //inputs.push_back(torch::ones({1, 3, 500, 600}));
//     inputs.push_back(input_tensor);

//     // Execute the model and turn its output into a tensor.
//     c10::IValue output = module.forward(inputs);
//     std::cout << output;
//   }
//   catch (const c10::Error &e)
//   {
//     std::cerr << "error loading the model\n";
//     std::cout << e.what() << "\n";
//     return -1;
//   }

//   std::cout << "ok\n";
// }

struct TensorWrapper
{
  TensorWrapper()
  {
    tensor = torch::ones({3, 3}, torch::kInt32);
    cvmat = cv::Mat::zeros(10, 10, CV_32F);
  }

  int size;
  torch::Tensor tensor;
  cv::Mat cvmat;

  int myfunc()
  {
    return 0;
  }
};

cv::Mat cvMatrix(cv::Mat const &img)
{
  cv::Mat cvmat = cv::Mat::zeros(10, 10, CV_32F);
  return cvmat;
}

torch::Tensor testTensor()
{
  torch::Tensor tensor = torch::ones({3, 3}, torch::kInt32);
  return tensor;
}

torch::Tensor d_sigmoid(torch::Tensor z)
{
  std::cout << CV_8UC3;
  auto s = torch::sigmoid(z);
  return (1 - s) * s;
}

torch::Tensor numpy_uint8_3c_to_cv_mat(py::array_t<unsigned char> &input)
{
  cv::Mat cvmat = cv::Mat::zeros(10, 10, CV_32F);
  if (input.ndim() != 3)
    throw std::runtime_error("3-channel image must be 3 dims ");

  torch::Tensor tmat = torch::from_blob(cvmat.data, {10, 10});
  return tmat;
}

// cv::Mat numpy_uint8_3c_to_cv_mat(py::array_t<unsigned char> &input)
// {

//   if (input.ndim() != 3)
//     throw std::runtime_error("3-channel image must be 3 dims ");

//   py::buffer_info buf = input.request();

//   cv::Mat mat(buf.shape[0], buf.shape[1], CV_8UC3, (unsigned char *)buf.ptr);

//   return mat;
// }

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m)
{
  m.def("get_tensor", &testTensor, "Get a sample tensor.");
  m.def("sigmoid", &d_sigmoid, "Sigmoid activation");
  m.def("cvMatrix", &cvMatrix, "Sigmoid activation");
  m.def("np_to_mat", &numpy_uint8_3c_to_cv_mat, "numpy_unit8 to 3 channel cv::Mat");
  py::class_<TensorWrapper>(m, "TensorWrapper")
      .def(py::init<>())
      .def_readwrite("tensor", &TensorWrapper::tensor)
      .def_readwrite("size", &TensorWrapper::size)
      .def_readwrite("cvmat", &TensorWrapper::cvmat);
}