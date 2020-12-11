import axios from "axios";
const baseURL = process.env.VUE_APP_BASE_URL;
const apiClient = axios.create({
    baseURL: baseURL,
    withCredentials: false,
    headers: {
        Accept: "application/json",
        "Content-Type": "application/json"
    },
    timeout: 2000000
});

export default {
    baseURL() {
        return apiClient.baseURL;
    },
    getTemplateImages() {
        return apiClient.get("/get_card_templates");
    },
    getAdaptiveCard(base64_image) {
        let data = {
            image: base64_image
        };
        // Creating fresh client instance to handle the request, as
        // latency of this endpoint is higher.sample_predict_json_debug
        return axios({
            method: "post",
            url: baseURL + "/predict_json_debug",
            timeout: 2000000,
            data: data,
            headers: {
                "Content-Type": "application/json"
            }
        });
    }
};
