<template>
  <div>
    <div class="demo">
      <div class="container">
        <h1>
          Adaptive Cards in Vue.js
          <a
            style="color: #000;text-transform: uppercase;font-size: 14px;font-weight: 400;"
            href="https://github.com/deejaytc/adaptivecards-vue"
          >
            Github
          </a>
        </h1>
        <p>Adaptive Cards in Vue.js</p>
        <hr style="margin: 50px 0px;border: 1px solid #e3e3e3;">
      </div>
      <adaptive-card 
        :card="card" 
        :data="data"
        :cardUrl="cardUrl"
        :useTemplating="true"
        v-on:onActionClicked="onItemClick"
      />
    </div>
  </div>
</template>

<script>
import SampleCard from '../src/assets/exampleCard.json';
import SampleData from '../src/assets/exampleData.json';
export default {
  name: 'App',
  components:[
    SampleCard,
    SampleData
  ],
  data () {
    return {
      data: SampleData,
      card: SampleCard,
      cardUrl: 'https://templates.adaptivecards.io/teamwork.com/projects/task.json'
    }
  },
  methods: {
    onItemClick (event, item) {
      alert(event);
      alert(item);
    }
  }
}
</script>

<style lang="scss">
@import url('https://fonts.googleapis.com/css?family=Source+Sans+Pro:400,600');

body,
html {
  margin: 0;
  padding: 0;
}

body {
  font-family: 'Source Sans Pro', sans-serif;
  font-size: 18px;
  background-color: #f2f4f7;
  color: #262626;
}

#demo {
  padding-left: 350px;
}
#demo.collapsed {
  padding-left: 50px;
}

.demo {
  padding: 50px;
}

.container {
  max-width: 900px;
}

pre {
  font-family: Consolas, monospace;
  color: #000;
  background: #fff;
  border-radius: 2px;
  padding: 15px;
  line-height: 1.5;
  overflow: auto;
}
</style>
