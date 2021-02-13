<template>
  <nav class="navbar navbar-expand-lg sticky-top navbar-light bg-light">
    <router-link to="/" exact>
      <div class="navbar-brand h4 text-primary">{{ title }}</div>
    </router-link>
    <!-- <button
            class="navbar-toggler"
            type="button"
            data-toggle="collapse"
            data-target="#navbarNav"
            aria-controls="navbarNav"
            aria-expanded="false"
            aria-label="Toggle navigation"
        >
            <span class="navbar-toggler-icon"></span>
        </button> -->
    <!-- <div class="collapse navbar-collapse" id="navbarNav">
            <ul class="navbar-nav w-100  justify-content-end">
                <li class="nav-item ">
                    <router-link
                        to="/renderAll"
                        class="btn  btn-sm btn-primary"
                        active-class="btn  btn-sm btn-warning "
                    >
                        Render All
                    </router-link>
                </li>
            </ul>
        </div> -->
  </nav>
</template>

<script>
export default {
  name: "Header",
  data: () => {
    return {
      title: "Pic2Card"
    };
  }
};
</script>

<style lang="scss" scoped>
.navbar {
  height: 3.5rem;
  align-items: center;
}
.navbar-brand {
  font-variant-caps: petite-caps;
}
</style>
