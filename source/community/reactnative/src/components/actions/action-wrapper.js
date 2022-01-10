/**
 * Wrapper to render the actions from given payload.
 */

import React from 'react';
import {
	StyleSheet,
	View
} from 'react-native';

import { Registry } from '../registration/registry';
import * as Constants from '../../utils/constants';
import { InputContextConsumer } from '../../utils/context';
import AdaptiveCard from '../../adaptive-card';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';

const padding = 10;

export class ActionWrapper extends React.Component {

	constructor(props) {
		super(props);
		this.hostConfig = props.configManager.hostConfig;
		this.state = {
			isShowCard: false,
			cardJson: null,
		}
	}

	componentDidUpdate(prevProps) {
		if (prevProps.actions !== this.props.actions) {
			this.hasShowCard = false;
			this.setState({
				isShowCard: false,
			});
		}
	}

	hasShowCard = false;

	onShowAdaptiveCard = (adaptiveCard) => {
		let isDifferentcard = (Utils.isNullOrEmpty(this.state.cardJson) ? false :
			(adaptiveCard === this.state.cardJson ? false : true));
		this.setState(prevState => ({
			isShowCard: !prevState.isShowCard,
			cardJson: adaptiveCard
		}));
		if (isDifferentcard) {
			setTimeout(() => {
				this.setState({ isShowCard: true });
			}, 50)
		}
	}

	/**
	 * @description Parses the actions from the given json
	 */
	parseActionsArray = (onParseError) => {
		const renderedElement = [];
		const { actions } = this.props

		if (!actions)
			return renderedElement;

		actions.map((element, index) => {
			const Element = Registry.getManager().getComponentOfType(element.type);
			if (Element) {

				let isValid = true;
				for (var key in Registry.getManager().validateSchemaForType(element.type)) {
					if (!element.hasOwnProperty(key)) {
						let error = { "error": Enums.ValidationError.PropertyCantBeNull, "message": `Required property ${key} for ${element.type} is missing` };
						onParseError(error);
						isValid = false;
					}
				}
				if (isValid) {
					const isFirstElement = index == 0
					const isLastElement = index == (actions.length - 1)
					if (element.type === 'Action.ShowCard') {
						this.hasShowCard = true;
						renderedElement.push(
							<Element
								json={element}
								isFirst={isFirstElement}
								isLast={isLastElement}
								maxWidth={100 / actions.length + "%"}
								configManager={this.props.configManager}
								onShowCardTapped={this.onShowAdaptiveCard}
								key={`${element.type}-${index}`}
							/>);
					}
					else {
						renderedElement.push(<Element json={element} configManager={this.props.configManager} isFirst={isFirstElement} isLast={isLastElement} maxWidth={100 / actions.length + "%"} key={`${element.type}-${index}`} />);
					}
				}
			} else {
				let error = { "error": Enums.ValidationError.UnknownActionType, "message": `Unknown Type ${element.type} encountered` };
				onParseError(error);
				return null;
			}
		});
		return renderedElement;
	}

	getActionOrientation() {
		if (this.hostConfig.actions.actionsOrientation === Enums.Orientation.Horizontal)
			return styles.actionAlignmentHorizontal
		else return styles.actionAlignmentVertical
	}

	getActionAlignment() {
		switch (this.hostConfig.actions.actionAlignment) {
			case Enums.ActionAlignment.Center:
				return styles.centerAlignment
			case Enums.ActionAlignment.Right:
				return styles.rightAlignment
			default:
				return styles.leftAlignment
		}
	}

	render() {
		return (
            <InputContextConsumer>
                {({onExecuteAction, onParseError}) => (
                    <View>
                        <View
                            style={[
                                styles.actionButtonContainer,
                                this.getActionOrientation(),
                                this.getActionAlignment(),
                                this.props.style,
                            ]}>
                            {this.parseActionsArray(onParseError)}
                        </View>
                        {this.hasShowCard ? (
                            this.state.isShowCard ? (
                                <AdaptiveCard
                                    payload={this.state.cardJson}
                                    configManager={this.props.configManager}
                                    onExecuteAction={onExecuteAction}
                                    isActionShowCard={true}
									containerStyle={{paddingVertical: 0}}
                                />
                            ) : null
                        ) : null}
                    </View>
                )}
            </InputContextConsumer>
        );
	}
}

const styles = StyleSheet.create({
	actionButtonContainer: {
		paddingTop: padding,
		flexWrap: Constants.FlexWrap
	},
	actionAlignmentHorizontal: {
		flexDirection: Constants.FlexRow,
	},
	actionAlignmentVertical: {
		flexDirection: Constants.FlexColumn,
        flexWrap: Constants.NoWrap
	},
	leftAlignment: {
		justifyContent: Constants.FlexStart,
	},
	centerAlignment: {
		justifyContent: Constants.CenterString,
	},
	rightAlignment: {
		justifyContent: Constants.FlexEnd,
	}
});

