<template>
  <div />
</template>
<style scoped lang="scss">
@import '../scss/adaptive-card';
</style>

<script>
import * as AdaptiveCards from 'adaptivecards/dist/adaptivecards';
import { Template, EvaluationContext } from 'adaptivecards-templating/dist/adaptivecards-templating';
import HostConfig from '../assets/exampleHostConfig.json';
import axios from 'axios';

export default {
  name: 'AdaptiveCard',
  components: {
    AdaptiveCards,
    Template,
    EvaluationContext,
  },
  props: {
    card: {
        type: Object | String,
        required: true,
        default: null
    },
    data: {
        type: Object | String,
        required: false,
        default: null
    },
    hostConfig: {
        type: Object | String,
        required: false,
        default: ''
    },
    useTemplating: {
        type: Boolean,
        required: true,
        default: true
    },
    cardUrl: {
        type: String,
        required: false,
        default: null
    }
  },
  data() {
      return {
          cardHolder: null,
          cardParsed: this.card.type == Object ? JSON.stringify(this.card) : this.card,
          dataParsed: this.data.type == Object ? JSON.stringify(this.data) : this.data
      }
  },
  mounted() {


    const instance = axios.create({
    paramsSerializer(params) {
        return stringify(params, { arrayFormat: 'brackets' });
    },
    });

    // Load the card from url if passed
    if(this.cardUrl != null){
        const json = axios.get(this.cardUrl).then( data => {
           if(data.status == 200){
             this.cardParsed = JSON.stringify(data.data)
           }
        });
    }
    this.cardHolder = new AdaptiveCards.AdaptiveCard();
    // Use Default Host Config if not passed
    this.cardHolder.HostConfig = this.hostConfig == '' ? JSON.stringify(HostConfig) : this.hostConfig;

    if(this.useTemplating && this.data == null){
        this.$el.remove();
        throw new Error("When using templating data is required");
    }

    if (this.useTemplating && this.data != null) {
      let template = new Template(this.cardParsed);
      let context = new EvaluationContext();
      context.$root = this.dataParsed;
      this.cardParsed = template.expand(context);

      this.cardHolder.parse(this.cardParsed);
    } else {
      this.cardHolder.parse(this.cardParsed);
    }

    this.cardHolder.onExecuteAction = (action) => {
      this.$emit('onActionClicked', action, action.data);
    };

    this.cardElement = this.cardHolder.render();
    this.$el.appendChild(this.cardElement);
  },
};

</script>