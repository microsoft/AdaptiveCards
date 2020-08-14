import Vue from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store";
import Loader from "./components/loader/Loader.vue";
import { BootstrapVue, IconsPlugin } from "bootstrap-vue";
import VJsoneditor from "v-jsoneditor/src/index";

Vue.config.productionTip = false;

import VueKonva from "vue-konva";
Vue.use(VueKonva);
Vue.use(VJsoneditor);
Vue.component("app-loading", Loader);
Vue.component("json-viewer", VJsoneditor);
// Install BootstrapVue
Vue.use(BootstrapVue);
new Vue({
    router,
    store,
    render: h => h(App)
}).$mount("#app");
