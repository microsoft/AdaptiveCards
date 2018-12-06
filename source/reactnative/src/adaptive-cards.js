/**
 * Render the adaptive card for the given payload.
 */

import React from 'react';
import { StyleSheet, View, ScrollView ,Text} from 'react-native';
import { Registry } from './components/registration/registry'
import { InputContextProvider } from './utils/context'
import { HostConfigManager } from './utils/host-config'
import * as Utils from './utils/util';



export default class AdaptiveCards extends React.Component {
  constructor(props) {
    super(props);
    this.payload = props.payload;
    if (props.hostConfig) {
      HostConfigManager.setHostConfig(this.props.hostConfig);
    }
  }

  inputArray = {};

  addInputItem = (key, value) => {
    this.inputArray[key] = value;
  }

  /**
 * @description Parse the given payload and render the card accordingly
 */
  parsePayload = () => {
    const renderedElement = [];
    const { body, actions } = this.payload;

    if (!body)
      return renderedElement;
    const register = new Registry();

    // parse elements
    body.map((element, index) => {
      const Element = register.getComponentOfType(element.type);

      if (Element) {
        renderedElement.push(<Element json={element} key={`ELEMENT-${index}`} />);
      } else {
        let error = {"type":"ParseError", "error": "Unknown Type encountered"};        
        this.props.onParseError(error);
       return null;
      }
    });
      
    // parse actions
    if (actions) {
      renderedElement.push(<View key="AC-CONTAINER" style={styles.actionContainer}/>);
      actions.map((action, index) => {
        const ActionButton = register.getActionOfType(action.type);
        if (ActionButton) {
          renderedElement.push(<ActionButton key={`ACTION-${index}`} json={action} actionHandler={null} />);
        }
      });
    }
    return renderedElement;
  }
  getAdaptiveCardConent() {
    var adaptiveCardContent =
      (
        <View style={styles.container}>
          <ScrollView>
            {this.parsePayload()}
          </ScrollView>
        </View>
      );

    if (!Utils.isNullOrEmpty(this.payload.backgroundImage)) {
      return (
        <ImageBackground source={{ uri: this.payload.backgroundImage }} style={styles.backgroundImage}>
          {adaptiveCardContent}
        </ImageBackground>
      );
    }
    else {
      return adaptiveCardContent;
    }
  }
  render() {
    const { addInputItem } = this;
    const inputArray = this.inputArray;
    const onExecuteAction = this.props.onExecuteAction;
    const isTransparent = this.payload.backgroundImage ? true : false;
    const onParseError = this.props.onParseError;

    return (

      <InputContextProvider value={{ addInputItem, inputArray, onExecuteAction, isTransparent, onParseError }}>
        {
          this.getAdaptiveCardConent()
        }
      </InputContextProvider>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: 'transparent',
  },
  highlight: {
    backgroundColor: 'yellow',
    marginVertical: 5,
    paddingVertical: 5,
    fontSize: 15
  },
  actionContainer: {
    marginVertical: 10
  },
  backgroundImage: {
    width: "100%",
    flex: 1
  }
});

