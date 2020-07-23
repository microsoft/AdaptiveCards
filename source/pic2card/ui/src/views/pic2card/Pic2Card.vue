<template>
  <div>
    <div class=" d-flex justify-content-end p-1 sticky-top">
      <div class="d-flex w-50 justify-content-end">
        <!-- Upload image and render card feature added to landing page -->
        <!-- <b-form-file
                    v-model="file"
                    placeholder=""
                    class="w-50 mr-1"
                    accept="image/*"
                    size="sm"
                    ref="fileSelect"
                >
                </b-form-file> -->
        <b-button
          :disabled="isLoading"
          size="sm"
          variant="primary"
          @click="openRenderAll()"
          >Render All</b-button
        >
      </div>
    </div>
    <div class=" d-flex w-100 ">
      <loading :isLoading="isLoading" :color="'primary'" />
      <div class="flex-wrap  d-flex w-100 justify-content-center  bg-white ">
        <div v-if="isError" class="justify-content-center mt-2 p-1">
          <b-alert
            show
            variant="warning"
            dismissible
            @dismissed="(isError = false), getTemplateImages()"
          >
            {{ error }} please try again.!
          </b-alert>
        </div>
        <div
          v-else
          v-for="(item, index) in templates"
          :key="index"
          class="col-lg-3 col-md-4 col-12   border border-light image-item "
          @click="openDetailView(item)"
        >
          <div class="d-block h-100 ">
            <b-img-lazy
              v-bind="{
                blank: true,
                blankColor: '#bbb',
                width: 300,
                height: 300
              }"
              :src="item | image_data_url"
              class="p2c-thumbnail"
            ></b-img-lazy>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import Loader from "../../components/loader/Loader.vue";
import CardDetailView from "./CardDetailView";
import imageapi from "@/services/ImageApi.js";
import { mapState } from "vuex";
export default {
  name: "Pic2card",
  components: {
    loading: Loader
    // CardDetailView: CardDetailView
  },
  data() {
    return {
      isLoading: false,
      isError: false,
      error: "",
      file: null
    };
  },

  watch: {
    file: function(newVal, oldVal) {
      var filethis = this;
      var reader = new FileReader();
      reader.readAsDataURL(newVal);
      reader.onload = function() {
        filethis.$router.push({
          name: "cardDetailView",
          params: {
            url: reader.result.split(",")[1],
            isFromPic2card: true
          }
        });
      };
      reader.onerror = function(error) {
        // console.log('Error: ', error)
      };
    }
  },
  computed: mapState({
    templates: state => state.pic2card.base64_images
  }),
  methods: {
    openDetailView: function(value) {
      this.$router.push({
        name: "cardDetailView",
        params: {
          url: value,
          isFromPic2card: true
        }
      });
    },
    openRenderAll: function(value) {
      this.$router.push({
        name: "renderAllImage"
      });
    },
    getTemplateImages: function() {
      // console.log('calling get template image api')
      this.isLoading = true;
      imageapi
        .getTemplateImages()
        .then(response => {
          let cards = response.data["templates"];
          this.$store.dispatch("saveTemplateImages", cards);
          this.isLoading = false;
        })
        .catch(err => {
          // console.log(err)
          this.isLoading = false;
          this.error = "Something Went Wrong";
          this.isError = true;
        });
    }
  },

  filters: {
    image_data_url(value) {
      return "data:image/png;base64," + value;
    }
  },
  created() {
    if (this.templates.length == 0) {
      this.getTemplateImages();
    }
  },
  beforeDestroy() {
    // this.$refs.fileSelect.reset()
  }
};
</script>
<style lang="scss" scoped>
.p2c-thumbnail {
  cursor: pointer;
}
.image-item {
  padding: 5px;
  // margin: 5px;
}
</style>
