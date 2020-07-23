const state = {
    base64_images: [],
    error: null
};

const getters = {
    getTemplateImages(state) {
        return state.base64_images;
    }
};

const actions = {
    saveTemplateImages(context, base64_images) {
        context.commit("UpdateTemplateImages", base64_images);
    }
};

const mutations = {
    UpdateTemplateImages(state, base64_images) {
        state.base64_images = base64_images;
    },
    updateError(state, error) {
        state.error = error;
    }
};

export default {
    state,
    actions,
    mutations,
    getters
};
