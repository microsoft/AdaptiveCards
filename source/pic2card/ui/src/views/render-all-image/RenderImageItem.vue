<template>
  <div
    class=" position-relative d-flex justify-content-center mb-2"
    style="min-height:200px"
  >
    <b-modal
      :id="modalId"
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
    <loading :isLoading="isLoading" v-bind:color="'primary'" />
    <!-- <div v-if="isError" class="d-flex justify-content-center mt-2 p-2">
            <b-alert
                show
                variant="warning"
                dismissible
                @dismissed=";(isError = false), pic2Card(url)"
            >
                {{ error }} please try again.!
            </b-alert>
        </div> -->
    <div class="d-flex bg-white  main-container " style="min-height:200px">
      <div class=" left-container bg-light shadow-sm">
        <b-img-lazy
          v-if="imageBoundary"
          v-bind="{
            blank: true,
            blankColor: '#bbb',
          }"
          :src="imageBoundary | image_data_url"
          class="fit-image"
          rounded
        ></b-img-lazy>
      </div>
      <div class="right-container   bg-light p-2 shadow-sm">
        <div :id="cardId" :ref="cardId" class="cards"></div>
        <div class="d-flex justify-content-center m-1 -1">
          <div
            v-if="cardJson && !isLoading"
            class="btn btn-sm btn-primary"
            v-b-modal="modalId"
          >
            View Json
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
export default {
  name: "RenderImageItem",
  props: {
    url: String,
    id: String,
    hostConfig: String
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
      cardId: "card" + this.id,
      modalId: "modal" + this.id,
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
  watch: {
    hostConfig: function(newVal, oldVal) {
      this.renderCard(this.imageString, this.cardJson, this.hostConfig);
    }
  },
  filters: {
    image_data_url(value) {
      return "data:image/png;base64," + value;
    }
  },
  methods: {
    renderCard(base64_image, card_json, hostConfig) {
      this.$refs[this.cardId.toString()].innerHTML = "";
      this.isLoading = true;
      AdaptiveCards.AdaptiveCard.onProcessMarkdown = function(text, result) {
        let md = new MarkdownIt();
        result.outputHtml = md.render(text);
        result.didProcess = true;
      };
      let adaptiveCard = new AdaptiveCards.AdaptiveCard();
      const host = Config[hostConfig];
      adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(host);
      adaptiveCard.parse(this.cardJson);
      this.cardHtml = adaptiveCard.render();
      setTimeout(() => {
        this.$refs[this.cardId.toString()].appendChild(this.cardHtml);
        this.isLoading = false;
      }, 500);
    },
    pic2Card(base64_image) {
      this.isLoading = true;
      AdaptiveCardApi.getAdaptiveCard(base64_image)
        .then(response => {
          let card_json = response.data["card_json"];
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
          const host = Config.adaptiveHostConfig;
          adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(host);
          adaptiveCard.parse(card_json);
          this.cardHtml = adaptiveCard.render();
          this.$refs[this.cardId.toString()].appendChild(this.cardHtml);
          // Also update the image that has bounding box.
          this.imageString = response.data["image"];
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
  mounted() {
    this.pic2Card(this.imageString);
  },
  destroyed() {
    // console.log('renderimageitem-destroyed')
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
  width: 50%;
  max-height: 400px;
  min-height: 400px;
  margin-right: 1rem;
}
.right-container {
  display: flex;
  flex-direction: column;
  height: 400px;
  width: 50%;
  max-height: 400px;
  min-height: 400px;
  margin-left: 1rem;
  position: relative;
  justify-content: space-between;
  align-items: center;
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
.fit-image {
    max-width: 100%;
    max-height: 100%;
}
</style>
