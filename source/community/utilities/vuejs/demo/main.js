import Vue from 'vue'
import App from './App.vue'
import VueRouter from 'vue-router'
import AdaptiveCard from '../src/index'


Vue.use(VueRouter)
Vue.use(AdaptiveCard)
const router = new VueRouter({
  routes: [
    {
      path: '/',
      name: 'Installation',
      component: App
    }
  ]
})

new Vue({ // eslint-disable-line no-new
  el: '#app',
  router,
  render: h => h(App)
})
