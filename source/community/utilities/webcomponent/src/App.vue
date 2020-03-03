<template>
  <div id="app">
    <img alt="Vue logo" src="./assets/logo.png">
    <AdaptiveCards />
  </div>
</template>

<script>
import AdaptiveCards from './components/AdaptiveCards.vue'
export default {
  name: 'app',
  components: {
    AdaptiveCards
  }
}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>