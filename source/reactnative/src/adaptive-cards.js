/**
 * Render the adaptive card for the given payload.
 */

import React from 'react';
import { StyleSheet, View, ScrollView ,Text} from 'react-native';
import { Registry } from './components/registration/registry'
import { InputContextProvider } from './utils/context'
import { HostConfigManager } from './utils/host-config'
import { ActionWrapper } from './components/actions/action-wrapper'
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
    const { body } = this.payload;

    if (!body)
      return renderedElement;
    const register = new Registry();

    // parse elements
    body.map((element, index) => {
      const Element = register.getComponentOfType(element.type);

      if (Element) {
        renderedElement.push(<Element json={element} key={`ELEMENT-${index}`} />);
      } else {
        // This fallback is for dev/t esting purpose. 
        TODO: // Must be removed on release version.
        renderedElement.push(<Text style={styles.highlight} key={`ELEMENT-${index}`}>I'm a <Text style={{ fontWeight: 'bold' }}>{element.type}</Text> element</Text>);
      }
    });
    return renderedElement;
  }

  getAdaptiveCardConent() {
    var adaptiveCardContent =
      (
		<View style={styles.container}>
			<ScrollView>
			{ this.parsePayload() }
			{ !Utils.isNullOrEmpty(this.payload.actions) && 
				<ActionWrapper actions={this.payload.actions}/> }
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

    return (

      <InputContextProvider value={{ addInputItem, inputArray, onExecuteAction, isTransparent }}>
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

