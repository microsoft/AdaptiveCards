<template>
  <div class="bg-white w-100 position-relative p-2 ">
    <div class=" d-flex justify-content-end p-1  sticky-top">
      <b-form-select
        v-model="selected"
        class="form-control w-25 mr-1"
        @change="onChange"
        size="sm"
        :options="options"
      >
      </b-form-select>
      <b-button size="sm" variant="warning" @click="goBack()">Go back</b-button>
    </div>
    <div
      class="position-relative d-flex justify-content-center"
      style="width:100%;height:90%"
    >
      <loading :isLoading="isLoading" v-bind:color="'primary'" />
      <div v-if="isError" class="d-flex justify-content-center mt-2 p-2">
        <b-alert
          show
          variant="warning"
          dismissible
          @dismissed="(isError = false), pic2Card(url)"
        >
          {{ error }} please try again.!
        </b-alert>
      </div>
      <div v-else v-show="!isLoading" class="main-container">
        <div class=" left-container mr-1 bg-light shadow-sm mr-5">
          <div v-if="!isLoading" class="title text-center">
            Picture Boundary
          </div>
          <b-img-lazy
            v-if="imageBoundary"
            v-bind="{
              blank: true,
              blankColor: '#bbb',
              width: 350,
              height: 350
            }"
            :src="imageBoundary | image_data_url"
            class="p-2"
            rounded
          ></b-img-lazy>
        </div>
        <div class="right-container ml-1  bg-light shadow-sm p-2 ml-5">
          <div v-if="!isLoading" class="title text-center">
            Adaptive Card
          </div>
          <div ref="cards" class=" cards  "></div>
          <div class="d-flex justify-content-center mt-1">
            <div
              v-if="cardJson && !isLoading"
              class="btn btn-sm btn-primary"
              v-b-modal.my-modal
            >
              View Json
            </div>
            <b-modal
              id="my-modal"
              content-class=""
              title="Adaptive Card Json"
              button-size="sm"
              size="lg"
            >
              <div class="modalBody">
                <json-viewer
                  v-model="cardJson"
                  :options="jsonViewerOption"
                  :plus="false"
                  :height="'400px'"
                />
              </div>
            </b-modal>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import Loader from "../../components/loader/Loader.vue";
import imageapi from "@/services/ImageApi.js";
import * as AdaptiveCards from "adaptivecards";
import AdaptiveCardApi from "../../services/ImageApi";
import Config from "../../utils/config";
import MarkdownIt from "markdown-it";
import config from "../../utils/config";
export default {
  name: "CardDetailView",
  props: {
    url: String,
    isFromPic2card: Boolean
  },
  components: {
    loading: Loader
  },
  data() {
    return {
      isLoading: false,
      imageString: this.url,
      cardHtml: null,
      imageBoundary: null,
      cardJson: null,
      isError: false,
      error: "",
      selected: "adaptiveHostConfig",
      options: Object.keys(config),
      jsonViewerOption: {
        mode: "code",
        mainMenuBar: false,
        navigationBar: false,
        statusBar: false,
        onEditable: function(node) {
          if (!node.path) {
            // returning false makes the text area read-only
            return false;
          }
        },
        onError: function(err) {
          // console.log(err)
        }
      }
    };
  },
  computed: {
    image_data_url() {
      return "data:image/png;base64," + this.imageString;
    }
  },
  filters: {
    image_data_url(value) {
      return "data:image/png;base64," + value;
    }
  },
  methods: {
    onChange(event) {
      this.$refs.cards.innerHTML = "";
      AdaptiveCards.AdaptiveCard.onProcessMarkdown = function(text, result) {
        let md = new MarkdownIt();
        result.outputHtml = md.render(text);
        result.didProcess = true;
      };

      let adaptiveCard = new AdaptiveCards.AdaptiveCard();
      const host = Config[this.selected];
      adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(host);
      adaptiveCard.parse(this.cardJson);
      this.cardHtml = adaptiveCard.render();
      setTimeout(() => {
        this.$refs.cards.appendChild(this.cardHtml);
        // Also update the image that has bounding box.
        this.isLoading = false;
      }, 200);
    },
    goBack: function(value) {
      this.$router.push({
        name: this.isFromPic2card ? "Pic2Card" : "LandingPage"
      });
    },
    pic2Card(base64_image) {
      this.isLoading = true;
      AdaptiveCardApi.getAdaptiveCard(base64_image)
        .then(response => {
          // console.log(response.data)
          let card_json = response.data["card_json"];
          // this.cardJson = JSON.stringify(card_json, null, 2)
          this.cardJson = card_json;
          this.imageBoundary = response.data.image || null;
          // Add markdown rendering.
          AdaptiveCards.AdaptiveCard.onProcessMarkdown = function(
            text,
            result
          ) {
            let md = new MarkdownIt();
            result.outputHtml = md.render(text);
            result.didProcess = true;
          };

          let adaptiveCard = new AdaptiveCards.AdaptiveCard();
          const host = Config[this.selected];
          adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(host);
          adaptiveCard.parse(card_json);
          this.cardHtml = adaptiveCard.render();
          setTimeout(() => {
            this.$refs.cards.appendChild(this.cardHtml);
            // Also update the image that has bounding box.
            this.imageString = response.data["image"];
            this.isLoading = false;
          }, 200);
        })
        .catch(err => {
          // console.log(err)
          this.isLoading = false;
          this.error = "Something Went Wrong";
          this.isError = true;
        });
    }
  },
  beforeMount() {
    this.pic2Card(this.imageString);
    // this.isLoading = true
  },
  mounted() {
    this.$refs.cards.innerHTML = "";
    if (this.cardHtml) {
      this.$refs.cards.appendChild(this.cardHtml);
    }
  }
};
</script>

<style lang="scss" scoped>
.main-container {
  display: flex;
  width: 85%;
  height: 100%;
  padding: 1rem;
  margin: 0.5rem;
  position: relative;
}
.left-container {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  height: 400px;
  max-height: 400px;
  min-height: 400px;
  width: 50%;
}
.right-container {
  display: flex;
  position: relative;
  justify-content: space-between;
  flex-direction: column;
  align-items: center;
  height: 400px;
  width: 50%;
  max-height: 400px;
  min-height: 400px;
}
.cards {
  overflow: overlay;
  position: relative;
  width: 100%;
  height: 100%;
  justify-content: center;
}
.cards::-webkit-scrollbar {
  background: transparent;
  height: 15px;
  width: 15px;
}
.cards::-webkit-scrollbar-thumb {
  background-color: rgba(0, 0, 0, 0.2);
  border: solid whiteSmoke 6px;
  -webkit-border-radius: 5px;
  border-radius: 5px;
}
.cards::-webkit-scrollbar-thumb:hover {
  background-color: rgba(0, 0, 0, 0.3);
}
.cards::-webkit-scrollbar-track {
  -webkit-border-radius: 5px;
  border-radius: 5px;
}
.title {
  font-size: 1.2rem;
  font-variant-caps: petite-caps;
  font-weight: bold;
  color: #505050;
  padding: 0.5rem;
}
.modalBody {
  overflow: auto;
}
</style>
