#include <iostream>
#include <memory>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <torch/script.h> // One-stop header.
#include <pybind11/pybind11.h>

using namespace cv;
using namespace std;

namespace py = pybind11;

// // Scale sizes
// int main(int argc, const char *argv[])
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

//int add(int i, int j)
//{
//  return i + j;
//}
//
//PYBIND11_MODULE(example, m)
//{
//  m.doc() = "pybind11 example plugin"; // optional module docstring
//  m.def("add", &add, "A function which adds two numbers");
//}

struct TensorWrapper
{
  TensorWrapper()
  {
    tensor = torch::ones({3, 3}, torch::kInt32);
  }

  int size;
  torch::Tensor tensor;
};

PYBIND11_MODULE(detr, m)
{
  py::class_<TensorWrapper>(m, "TensorWrapper")
      .def(py::init<>())
      .def_readwrite("tensor", &TensorWrapper::tensor)
      .def_readwrite("size", &TensorWrapper::size);
}
