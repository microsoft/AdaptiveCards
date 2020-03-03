import AdaptiveCard from './components/AdaptiveCard.vue'

export default {
  install (Vue) {
    Vue.component('adaptive-card', AdaptiveCard)
  }
}

export { AdaptiveCard }
