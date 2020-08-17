<template>
  <div id="app-container">
    <app-header />
    <router-view class="content-height w-100" />
    <app-footer />
  </div>
</template>

<script>
import Header from "./views/header/Header.vue";
import Footer from "./views/footer/Footer";
export default {
  name: "App",
  components: {
    "app-header": Header,
    "app-footer": Footer
  }
};
</script>

<style lang="scss">
@import "node_modules/bootstrap/scss/bootstrap";
@import "node_modules/bootstrap-vue/src/index.scss";
@import "./scss/jsoneditor.scss";
#app-container {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  height: 100%;
}
body,
html {
  height: 100%;
  width: 100%;
}
.content-height {
  height: calc(100vh - 8rem);
  width: 100%;
  position: relative;
  overflow-x: hidden;
  overflow-y: auto;
}
</style>
