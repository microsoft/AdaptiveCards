import Vue from 'vue';
import vueCustomElement from 'vue-custom-element';
import Modal from './components/Modal.vue';

Vue.component('modal', Modal);

Vue.use(vueCustomElement);

const customElementOptions = {
  shadow: true,
  shadowCss: `.dark .ac-media-poster {}

  .dark .ac-media-poster.empty {
    height: 200px;
    background-color: #F2F2F2;
  }
  
  .dark .ac-media-playButton {
    width: 56px;
    height: 56px;
    border: 1px solid #EEEEEE;
    border-radius: 28px;
    box-shadow: 0px 0px 10px #EEEEEE;
    background-color: rgba(255, 255, 255, 0.9);
    color: black;
    cursor: pointer;
  }
  
  .dark .ac-media-playButton-arrow {
    color: black;
  }
  
  .dark .ac-media-playButton:hover {
    background-color: white;
  }
  
  .dark .ac-image.ac-selectable {
    cursor: pointer;
  }
  
  .dark .ac-image.ac-selectable:hover {
    background-color: rgba(0, 0, 0, 0.1);
  }
  
  .dark .ac-image.dark .ac-selectable:active {
    background-color: rgba(0, 0, 0, 0.15);
  }
  
  a.ac-anchor {
    text-decoration: none;
  }
  
  a.ac-anchor:link {
    color: #6264A7;
  }
  
  a.ac-anchor:visited {
    color: #6264A7;
  }
  
  a.ac-anchor:link:active {
    color: #6264A7;
  }
  
  a.ac-anchor:visited:active {
    color: #6264A7;
  }
  
  .dark .ac-container.ac-selectable, .dark .ac-columnSet.ac-selectable {
    padding: 0px;
  }
  
  .dark .ac-container.ac-selectable:hover, .dark .ac-columnSet.ac-selectable:hover {
    background-color: rgba(0, 0, 0, 0.1) !important;
  }
  
  .dark .ac-container.ac-selectable:active, .dark .ac-columnSet.ac-selectable:active {
    background-color: rgba(0, 0, 0, 0.15) !important;
  }
  
  .dark .ac-pushButton {
    overflow: hidden;
    text-overflow: ellipsis;
    text-align: center;
    vertical-align: middle;
    cursor: default;
    font-family: "Segoe UI", sans-serif;
    font-size: 14px;
    padding: 4px 10px 5px 10px;
    -webkit-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    height: 34px;
    background-color: transparent;
    color: white;
    border: 2px solid #6165A4;
    border-radius: 4px;
  }
  
  .dark .ac-pushButton:hover {
    background-color: #6165A4;
    border: 2px solid #A7A8DA;
    color: black;
  }
  
  .dark .ac-pushButton:active {
    background-color: #6165A4;
    border: 2px solid #A7A8DA;
    color: black;
  }
  
  .dark .ac-pushButton.expanded {
    background-color: #6165A4;
    border: 2px solid #A7A8DA;
    color: black;
  }
  
  .dark .ac-pushButton.style-emphasis {
    background-color: #6264A7;
    border: 2px solid #6264A7;
    color: white;
  }
  
  .dark .ac-input {
    font-family: "Segoe UI", sans-serif;
    font-size: 14px;
    color: #EEEEEE;
  }
  
  .dark .ac-input.ac-input-required {
    background-image: linear-gradient(45deg, transparent, transparent 50%, red 50%, red 100%);
    background-position: top right;
    background-size: .5em .5em;
    background-repeat: no-repeat;
  }
  
  .dark .ac-input.ac-input-validation-failed {
    border: 1px solid red !important;
  }
  
  .dark .ac-input.ac-textInput {
    resize: none;
  }
  
  .dark .ac-input.ac-textInput.ac-multiline {
    height: 72px;
  }
  
  .dark .ac-input.ac-textInput, .dark .ac-input.ac-numberInput, .dark .ac-input.ac-dateInput, .dark .ac-input.ac-timeInput {
    height: 31px;
  }
  
  .dark .ac-input.ac-textInput, .dark .ac-input.ac-numberInput, .dark .ac-input.ac-dateInput, .dark .ac-input.ac-timeInput, .dark .ac-input.ac-multichoiceInput {
    background-color: #201E1F;
    border: 1px solid #201E1F;
    border-radius: 4px;
    padding: 4px 8px 4px 8px;
  }
  
  /* ac-inlineActionButton should set height to the same as ac-input.dark .ac-textInput */
  
  .ac-inlineActionButton {
    overflow: hidden;
    text-overflow: ellipsis;
    text-align: center;
    vertical-align: middle;
    cursor: pointer;
    font-family: "Segoe UI", sans-serif;
    font-size: 14px;
    -webkit-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    border: none;
    background-color: transparent;
    height: 31px;
  }
  
  .dark .ac-inlineActionButton.textOnly {
    padding: 0 8px;
  }
  
  .dark .ac-inlineActionButton.iconOnly {
    padding: 0;
  }
  
  .dark .ac-inlineActionButton:hover {
    background-color: #EEEEEE;
  }
  
  .dark .ac-inlineActionButton:active {
    background-color: #CCCCCC;
  }
  
  .ac-media-poster {}
  
   .light .ac-media-poster.empty {
      height: 200px;
      background-color: #F2F2F2;
  }
  
  .th, td  {
      border:none !important;
  }
  
   .light .ac-fact-title,
   .light .ac-fact-value{
      border: none !important;
  }
  
   .light .ac-media-playButton {
      width: 56px;
      height: 56px;
      border: 1px solid #EEEEEE;
      border-radius: 28px;
      box-shadow: 0px 0px 10px #EEEEEE;
      background-color: rgba(255, 255, 255, 0.9);
      color: black;
      cursor: pointer;
  }
  
   .light .ac-media-playButton-arrow {
      color: black;
  }
  
   .light .ac-media-playButton:hover {
      background-color: white;
  }
  
   .light .ac-image.ac-selectable {
      cursor: pointer;
  }
  
   .light .ac-image.ac-selectable:hover {
      background-color: rgba(0, 0, 0, 0.1);
  }
  
   .light .ac-image.ac-selectable:active {
      background-color: rgba(0, 0, 0, 0.15);
  }
  
  a.ac-anchor {
      text-decoration: none;
  }
  
  a.ac-anchor:link {
      color: #6264A7;
  }
  
  a.ac-anchor:visited {
      color: #6264A7;
  }
  
  a.ac-anchor:link:active {
      color: #6264A7;
  }
  
  a.ac-anchor:visited:active {
      color: #6264A7;
  }
  
   .light .ac-container.ac-selectable,  .light .ac-columnSet.ac-selectable {
      padding: 0px;
  }
  
   .light .ac-container th{
      border:none !important;
  }
  
   .light .ac-container th,td{
      border:none !important;
  }
  
   .light .ac-container tr{
      border:none !important;
  }
  
   .light .ac-container.ac-selectable:hover, .ac-columnSet.ac-selectable:hover {
      background-color: rgba(0, 0, 0, 0.1) !important;
  }
  
   .light .ac-container.ac-selectable:active,  .light .ac-columnSet.ac-selectable:active {
      background-color: rgba(0, 0, 0, 0.15) !important;
  }
  
   .light .ac-pushButton {
      overflow: hidden;
      text-overflow: ellipsis;
      text-align: center;
      vertical-align: middle;
      cursor: default;
      font-family: "Segoe UI", sans-serif;
      font-size: 14px;
      padding: 4px 10px 5px 10px;
      -webkit-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
      user-select: none;
      height: 32px;
      background-color: white;
      color: #6264A7;
      border: 2px solid #BFC0DA;
      border-radius: 4px;
  }
  
   .light .ac-pushButton:hover {
      background-color: #6264A7;
      border: 2px solid #6264A7;
      color: white;
  }
  
   .light .ac-pushButton:active {
      background-color: #6264A7;
      border: 2px solid #6264A7;
      color: white;
  }
  
   .light .ac-pushButton.expanded {
      background-color: #6264A7;
      border: 2px solid #6264A7;
      color: white;
  }
  
   .light .ac-pushButton.style-emphasis {
      background-color: #6264A7;
      border: 2px solid #6264A7;
      color: white;
  }
  
   .light .ac-input {
      font-family: "Segoe UI", sans-serif;
      font-size: 14px;
      color: black;
  }
  
   .light .ac-input.ac-input-required {
      background-image: linear-gradient(45deg, transparent, transparent 50%, red 50%, red 100%);
      background-position: top right;
      background-size: .5em .5em;
      background-repeat: no-repeat;
  }
  
   .light .ac-input.ac-input-validation-failed {
      border: 1px solid red !important;
  }
  
   .light .ac-input.ac-textInput {
      resize: none;
  }
  
   .light .ac-input.ac-textInput.ac-multiline {
      height: 72px;
  }
  
   .light .ac-input.ac-textInput,  .light .ac-input.ac-numberInput,  .light .ac-input.ac-dateInput,  .light .ac-input.ac-timeInput {
      height: 31px;
  }
  
   .light .ac-input.ac-textInput,  .light .ac-input.ac-numberInput,  .light .ac-input.ac-dateInput,  .light .ac-input.ac-timeInput,  .light .ac-input.ac-multichoiceInput {
      background-color: #F3F2F1;
      border: 1px solid #F3F2F1;
      border-radius: 4px;
      padding: 4px 8px 4px 8px;
  }
  
  /* ac-inlineActionButton should set height to the same as ac-input .light .ac-textInput */
  
  .ac-inlineActionButton {
      overflow: hidden;
      text-overflow: ellipsis;
      text-align: center;
      vertical-align: middle;
      cursor: pointer;
      font-family: "Segoe UI", sans-serif;
      font-size: 14px;
      -webkit-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
      user-select: none;
      border: none;
      background-color: transparent;
      height: 31px;
  }
  
   .light .ac-inlineActionButton.textOnly {
      padding: 0 8px;
  }
  
   .light .ac-inlineActionButton.iconOnly {
      padding: 0;
  }
  
   .light .ac-inlineActionButton:hover {
      background-color: #EEEEEE;
  }
  
   .light .ac-inlineActionButton:active {
      background-color: #CCCCCC;
  }
  
    `
};
const load = (loader) => async () => (await loader()).default;
Vue.config.ignoredElements = ['adaptive-card'];
Vue.customElement('adaptive-card', load(() => import('./components/AdaptiveCards.vue')), customElementOptions);
