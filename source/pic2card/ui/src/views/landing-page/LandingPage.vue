<template>
  <div class="bg-light">
    <div
      class="d-flex flex-row justify-content-center  align-items-center bg-white w-100 h-100"
      align-content="center"
    >
      <b-col class="w-50 d-flex justify-content-end  mr-1 ">
        <div class="pc-card  p-2 shadow-sm  bg-light">
          <div class="card-text m-1">
            Select Templates
          </div>
          <div class="d-flex justify-content-center p-1">
            <div class="icon-placeholder">
              <b-img src="icons/template.svg" class="pc-icons" />
            </div>
          </div>
          <div class="d-flex justify-content-center ">
            <div class="btn btn-success m-1 btn-sm w-75" @click="openPic2card">
              Choose
            </div>
          </div>
        </div>
      </b-col>

      <b-col class="w-50 d-flex justify-content-start ml-1 ">
        <div class="pc-card  p-2 shadow-sm  bg-light">
          <div class="card-text m-1">
            Upload Image
          </div>
          <div class="d-flex justify-content-center p-1">
            <div class="icon-placeholder">
              <b-img src="icons/upload.svg" class="pc-icons" />
            </div>
          </div>
          <div class="d-flex justify-content-center ">
            <div
              class="btn btn-success m-1 btn-sm w-75"
              @click="imageSelectClick"
            >
              Choose
            </div>
            <input
              v-show="isHidden"
              type="file"
              accept="image/*"
              ref="fileSelect"
              @change="previewFiles"
            />
          </div>
        </div>
      </b-col>
    </div>
  </div>
</template>

<script>
export default {
  name: "LandingPage",
  data() {
    return {
      file: null,
      isHidden: false
    };
  },
  methods: {
    openPic2card: function(value) {
      this.$router.push({
        name: "Pic2Card"
      });
    },
    imageSelectClick: function() {
      this.$refs["fileSelect"].click();
    },
    previewFiles(event) {
      const newVal = event.target.files[0];
      var filethis = this;
      var reader = new FileReader();
      reader.readAsDataURL(newVal);
      reader.onload = function() {
        filethis.$router.push({
          name: "cardDetailView",
          params: {
            url: reader.result.split(",")[1],
            isFromPic2card: false
          }
        });
      };
      reader.onerror = function(error) {
        // console.log('Error: ', error)
      };
    }
  }
};
</script>
<style lang="scss" scoped>
.pc-card {
  display: flex;
  flex-direction: column;
  justify-content: center;
  height: 220px;
  width: 250px;
  padding: 10px;
}
.pc-icons {
  height: 120px;
  width: 120px;
  padding: 1.5rem;
}
.card-text {
  display: flex;
  justify-content: center;
  font-size: 18px;
  font-weight: 500;
  margin-top: 10px;
  color: #646464;
}
.icon-placeholder {
  border-radius: 50%;
  border: 5px solid white;
  background: #bcbcbc;
  user-select: none;
}
</style>
