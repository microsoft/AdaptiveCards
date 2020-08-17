import Vue from "vue";
import Vuex from "vuex";
import pic2card from "./pic2card.module";
Vue.use(Vuex);

export default new Vuex.Store({
    modules: {
        pic2card
    }
});
