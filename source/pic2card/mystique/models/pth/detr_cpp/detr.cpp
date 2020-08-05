#include <vector>
#include <torch/extension.h>
#include <torch/script.h>
#include <torch/python.h>
#include <torch/torch.h>
#include <torch/csrc/utils/tensor_numpy.h>
#include <torch/csrc/python_headers.h>

#include "detr.hpp"

cv::Mat addmat(cv::Mat &lhs, cv::Mat &rhs)
{
    return lhs + rhs;
}

struct Detr
{

    std::string model_path;
    torch::jit::script::Module model;

    Detr(const std::string &model_path) : model_path(model_path) {}

    const std::string &getModelPath()
    {
        return model_path;
    }

    void loadModel()
    {
        model = torch::jit::load(model_path);
    }

    //c10::IValue predict(cv::Mat &image)
    const std::vector<cv::Mat> predict(cv::Mat &image)
    {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        image.convertTo(image, CV_32FC3, 1.0f / 255.0f);
        cv::Size imsize = image.size();
        std::cout << "Width: " << imsize.width << std::endl;
        torch::Tensor imTensor = torch::from_blob(image.data, { 1, imsize.width, imsize.height, 3 });
        imTensor = imTensor.permute({ 0, 3, 1, 2 });
        imTensor[0][0] = imTensor[0][0].sub_(0.485).div_(0.229);
        imTensor[0][1] = imTensor[0][1].sub_(0.456).div_(0.224);
        imTensor[0][2] = imTensor[0][2].sub_(0.406).div_(0.225);

        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(imTensor);
        auto outDict = model.forward(inputs).toGenericDict();

        torch::Tensor predLogits = outDict.at("pred_logits").toTensor();
        torch::Tensor predBoxes = outDict.at("pred_boxes").toTensor();
        //return predLogits;
        std::cout << "PredLogits Size: " << predLogits.size(1) << " " << predLogits.size(2) << std::endl;
        std::cout << "predBoxes Size: " << predBoxes.size(1) << " " << predBoxes.size(2) << std::endl;

        // return torch::utils::tensor_to_numpy(predLogits.detach().cpu());
        // return predLogits.detach().cpu();
        //std::cout << predLogits.size(0) << std::endl;
        predLogits = predLogits.to(torch::kCPU);
        cv::Mat cvMatLogits(predLogits.size(1), predLogits.size(2), CV_32F);
        std::memcpy((void*)cvMatLogits.data, predLogits.data_ptr(), sizeof(torch::kF32)*predLogits.numel());

        predBoxes = predBoxes.to(torch::kCPU);
        cv::Mat cvMatBoxes(predBoxes.size(1), predBoxes.size(2), CV_32F);
        std::memcpy((void*)cvMatBoxes.data, predBoxes.data_ptr(), sizeof(torch::kF32)*predBoxes.numel());

        return { cvMatLogits, cvMatBoxes };
    }
};

struct MatrixMultiplier
{
    MatrixMultiplier(int A, int B)
    {
        tensor_ =
            torch::ones({ A, B }, torch::dtype(torch::kFloat64).requires_grad(true));
    }
    torch::Tensor forward(torch::Tensor weights)
    {
        return tensor_.mm(weights);
    }
    torch::Tensor get() const
    {
        return tensor_;
    }

private:
    torch::Tensor tensor_;
};

bool function_taking_optional(c10::optional<torch::Tensor> tensor)
{
    return tensor.has_value();
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m)
{
    m.def("addmat", &addmat, "add two matrix");

    py::class_<Detr>(m, "Detr")
        .def(py::init<const std::string &>())
        .def("get_model_path", &Detr::getModelPath)
        .def_readonly("model_path", &Detr::model_path)
        .def("load", &Detr::loadModel)
        .def("predict", &Detr::predict)
        .def_readonly("model", &Detr::model);

    m.def(
        "function_taking_optional",
        &function_taking_optional,
        "function_taking_optional");

    py::class_<MatrixMultiplier>(m, "MatrixMultiplier")
        .def(py::init<int, int>())
        .def("forward", &MatrixMultiplier::forward)
        .def("get", &MatrixMultiplier::get);
}
