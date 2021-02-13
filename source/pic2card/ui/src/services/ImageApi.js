import axios from 'axios'

const baseURL = 'http://172.17.0.5:5050'

const apiClient = axios.create({
    baseURL: baseURL,
    withCredentials: false,
    headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json'
    },
    timeout: 10000
})

export default {
    baseURL() {
        return apiClient.baseURL
    },
    getTemplateImages() {
        return apiClient.get('/get_card_templates')
    },

    /**
     * @param {any} base64_image
     */
    getAdaptiveCard(base64_image) {
        let data = {
            image: base64_image
        }
        let config = {
            header: {
                'Content-Type': 'application/json'
            }
        }

        // Creating fresh client instance to handle the request, as
        // latency of this endpoint is higher.
        return axios({
            method: 'post',
            url: baseURL + '/predict_json_debug',
            timeout: 200000,
            data: { image: base64_image },
            headers: {
                'Content-Type': 'application/json'
            }
        })
    }
}
