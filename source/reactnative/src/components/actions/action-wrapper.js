/**
 * Wrapper to render the actions from given payload.
 */

import React from 'react';
import { StyleSheet, View, ScrollView ,Text, Dimensions } from 'react-native';
import { HostConfigManager } from '../../utils/host-config'
import { Registry } from '../registration/registry';
import * as Constants from '../../utils/constants';

const padding = 10;

export class ActionWrapper extends React.Component {
  constructor(props) {
    super(props);
    if (props.hostConfig) {
		HostConfigManager.setHostConfig(this.props.hostConfig);
	}
  }

  state = {
    screenWidth: 0
  };  
 
/**
  * @description Invoked on change in the content size of scrollview
  */
  onContentSizeChange = (contentWidth, contentHeight) => {
    this.setState({ screenWidth: contentWidth });
  }

/**
  * @description Parses the actions from the given json
  */
  parseActions = () => {
    const renderedElement = [];
    const { actions } = this.props;

    if (!actions)
      return renderedElement;

	renderedElement.push(Registry.getManager().parseRegistryComponents(actions));

    return renderedElement;
  }

  render() {
    const width  = Dimensions.get("window").width;
    const scrollEnabled = (this.state.screenWidth - 2*padding) > width
    const { actions } = this.props;
	const isScrollRequired = actions.length > 2
	const flexStyle =  { flexDirection: actions.length > 1 ? Constants.FlexRow : Constants.FlexColumn }

    return (
        <View style={[styles.actionButtonContainer, flexStyle]}>
            { isScrollRequired ? 
				<ScrollView 
					horizontal={true}
					scrollEnabled={scrollEnabled}
					onContentSizeChange={this.onContentSizeChange}>
                		{this.parseActions()}
				</ ScrollView> :
				this.parseActions() 
			}
        </View>
    );
  }
}

const styles = StyleSheet.create({
  actionButtonContainer: {
    flex: 1,
	paddingTop: padding,
  },
  actionContainer: {
    marginVertical: padding
  }
});

