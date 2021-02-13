<template>
  <div v-if="isLoading" class="overlay">
    <b-spinner :variant="color" label="Loading..."></b-spinner>
  </div>
</template>

<script>
export default {
  name: "Loader",
  props: ["isLoading", "color"],
  data() {
    return {};
  }
};
</script>

<style lang="scss" scoped>
.overlay {
  justify-content: center;
  align-items: center;
  display: flex;
  width: 100%;
  height: 100%;
  position: absolute;
  background: rgba(0, 0, 0, 0.1);
  /* color: black; */
  z-index: 99;
}
</style>
