#include <torch/extension.h>
#include <torch/script.h>

#include "detr.hpp"

cv::Mat addmat(cv::Mat &lhs, cv::Mat &rhs)
{
    return lhs + rhs;
}

struct Detr
{

    std::string model_path;
    torch::jit::script::Module model;

    Detr(const std::string &model_path) : model_path(model_path)
    {
        loadModel();
    }

    const std::string &getModelPath()
    {
        return model_path;
    }

    void loadModel()
    {
        model = torch::jit::load(model_path);
    }

    /**
     * Resize the image without lossing the aspect ratio, and ensure the dimentions
     * won't over shoot due to higher or lower aspect ratio.
     * 
     * max_size should be greater than the size.
     * 
     *  width / height == newW / newH
     **/
    std::vector<uint> getNewSize(uint width, uint height, uint size, uint max_size)
    {

        uint newW = width;
        uint newH = height;
        float aspect_ratio;

        if (max_size < size)
        {
            max_size = size;
        }
        aspect_ratio = (float)width / (float)height;

        // Ensure size not crossing the max_size.
        if (aspect_ratio * size > max_size)
        {
            size = (uint)round(max_size * (1 / aspect_ratio));
        }

        if (width < height)
        {
            newH = size;
            // aspect_ratio < 1
            newW = (uint)(size * aspect_ratio);
        }
        else if (width > height)
        {
            newW = size;
            newH = (uint)(size / aspect_ratio);
        }
        else
        {
            newW = size;
            newH = size;
        }

        return {newW, newH};
    }

    const std::vector<cv::Mat> predict(cv::Mat &image)
    {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        image.convertTo(image, CV_32FC3, 1.0f / 255.0f);

        // (width, height)
        std::vector<uint> imsize = getNewSize(image.cols, image.rows, 800, 1333);

        // Resize the image.
        cv::Size scale(imsize[0], imsize[1]);
        cv::resize(image, image, scale);

        torch::Tensor imTensor = torch::from_blob(
            image.data,
            {1,
             imsize[1], // height
             imsize[0], // width
             3});

        // BGR -> RGB
        imTensor = imTensor.permute({0, 3, 1, 2});

        // Imagenet normalisation
        imTensor[0][0] = imTensor[0][0].sub_(0.485).div_(0.229);
        imTensor[0][1] = imTensor[0][1].sub_(0.456).div_(0.224);
        imTensor[0][2] = imTensor[0][2].sub_(0.406).div_(0.225);

        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(imTensor);
        auto outDict = model.forward(inputs).toGenericDict();

        torch::Tensor predLogits = outDict.at("pred_logits")
                                       .toTensor()
                                       .squeeze()
                                       .softmax(-1);

        // predLogits = predLogits.narrow(1, 0, predLogits.size(1) - 1);
        torch::Tensor predBoxes = outDict.at("pred_boxes").toTensor().squeeze();

        // // Map the torch::Tensor to cv::Mat, helps to avoid torch package dependency at python side.
        predLogits = predLogits.to(torch::kCPU).to(torch::kF32);
        cv::Mat cvMatLogits(predLogits.size(0), predLogits.size(1), CV_32F);
        std::memcpy((void *)cvMatLogits.data, predLogits.data_ptr(), sizeof(float) * predLogits.numel());

        predBoxes = predBoxes.to(torch::kCPU).to(torch::kF32);
        cv::Mat cvMatBoxes(predBoxes.size(0), predBoxes.size(1), CV_32F);
        std::memcpy((void *)cvMatBoxes.data, predBoxes.data_ptr(), sizeof(float) * predBoxes.numel());

        return {cvMatLogits, cvMatBoxes};
    }
};

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m)
{
    m.def("addmat", &addmat, "add two matrix");

    py::class_<Detr>(m, "Detr")
        .def(py::init<const std::string &>())
        .def("get_model_path", &Detr::getModelPath)
        .def_readonly("model_path", &Detr::model_path)
        // .def("load", &Detr::loadModel)
        .def("get_new_size", &Detr::getNewSize)
        .def("predict", &Detr::predict)
        .def_readonly("model", &Detr::model);
}
