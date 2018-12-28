/**
 * Toggle Component based on the given payload.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputtoggle
 */

import React from 'react';
import {
	Switch,
	StyleSheet
} from 'react-native';

import { StyleManager } from '../../styles/style-config';
import { HostConfigManager } from '../../utils/host-config';
import { InputContextConsumer } from '../../utils/context';
import { Label } from '../elements';
import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';

export class ToggleInput extends React.Component {

	styleConfig = StyleManager.getManager().styles;

	constructor(props) {
		super(props);

		this.title = props.json.title;
		this.valueOn = props.json.valueOn || TrueString;
		this.valueOff = props.json.valueOff || FalseString;
		this.value = props.json.value || this.valueOff;
		this.id = props.json.id || ToggleValueOn

		// state
		this.state = {
			toggleValue: (this.value === this.valueOn)
		}
	}

	/**
	 * @description Invoked on every change in Toggle
	 * @param {Boolean} toggleValue
	 * @param {InputContextConsumer} addInputItem
	 */
	toggleValueChanged = (toggleValue, addInputItem) => {
		this.setState({ toggleValue });
		addInputItem(this.id, toggleValue);
	}

	render() {
		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}
		const { toggleValue } = this.state;

		return (
			<ElementWrapper json={this.props.json} style={styles.toggleContainer}>
				<Label
					text={this.title}
					wrap={true}
					style={styles.title} />
				<InputContextConsumer>
					{({ addInputItem }) => (
						<Switch
							style={styles.switch}
							value={toggleValue}
							onValueChange={toggleValue => {
								this.toggleValueChanged(toggleValue, addInputItem)
							}}>
						</Switch>
					)}
				</InputContextConsumer>
			</ElementWrapper>
		)
	}
}

const styles = StyleSheet.create({
	toggleContainer: {
		flexDirection: Constants.FlexRow,
		justifyContent: Constants.SpaceBetween,
		alignItems: Constants.CenterString,
		paddingTop: 5,
		paddingBottom: 5
	},
	title: {
		flexShrink: 1,
		marginRight: 10
	}
});