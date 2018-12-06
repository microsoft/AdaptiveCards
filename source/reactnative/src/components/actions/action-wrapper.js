/**
 * Wrapper to render the actions from given payload.
 */

import React from 'react';
import { StyleSheet, View, ScrollView ,Text, Dimensions } from 'react-native';
import { Registry } from '../registration/registry';
import * as Constants from '../../utils/constants';
import { InputContextConsumer } from '../../utils/context'
import AdaptiveCards from '../../adaptive-cards'

const padding = 10;

export class ActionWrapper extends React.Component {
  constructor(props) {
    super(props);
  }

  hasShowCard = false;

  state = {
    isShowCard:false,
    cardJson:null,
  }

  showCardJson = null;

  onShowAdaptiveCard = (adaptiveCard) => {
    this.setState(prevState => ({
      isShowCard: !prevState.isShowCard,
      cardJson: adaptiveCard
    }));


  }


/**
  * @description Parses the actions from the given json
  */
  parseActions = () => {
    const renderedElement = [];
    const { actions } = this.props;

    if (!actions)
      return renderedElement;

      actions.map((element, index) => {
        const Element = Registry.getManager().getComponentOfType(element.type);
         if (Element) {
          if (element.type==='Action.ShowCard'){
            this.hasShowCard = true;
            renderedElement.push(<Element json={element} onShowCardTapped={this.onShowAdaptiveCard} key={`${element.type}-${index}`} />);
          }
          else{
            renderedElement.push(<Element json={element} key={`${element.type}-${index}`} />);
          }
          
        } else {
         return null;
        }
      });
    return renderedElement;
  }

  render() {
    return (
      <View>
        <View style={[styles.actionButtonContainer]}>
                    {this.parseActions()}
        </View>
        { this.hasShowCard ? ((this.state.isShowCard) ? 
          (<InputContextConsumer>
            {({ onExecuteAction }) => 
<AdaptiveCards payload={this.state.cardJson} onExecuteAction={onExecuteAction}/>}</InputContextConsumer>):null) : null}
          </View>
    );
  }
}

const styles = StyleSheet.create({
  actionButtonContainer: {
  flex: 1,
  paddingTop: padding,
  flexWrap: 'wrap',
  flexDirection: 'row',
  justifyContent:'center'
  },
  actionContainer: {
    marginVertical: padding
  }
});

