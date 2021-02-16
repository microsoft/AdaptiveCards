/**
 * FactSet Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-factset
 */

import React from 'react';
import {
	View,
	StyleSheet,
} from 'react-native';

import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';
import { StyleManager } from '../../styles/style-config';
import { HostConfigManager } from "../../utils/host-config";
import * as Utils from '../../utils/util';
import { Label } from '../elements';

export class FactSet extends React.Component {

	styleConfig = StyleManager.getManager().styles;
	hostConfig = HostConfigManager.getHostConfig();

	constructor(props) {
		super(props);

		this.payload = props.json;
		// state
		this.state = {
			isMaximumWidthValueFound: false,
			keyWidth: '50%',
			valueWidth: '50%'
		}
		this.viewSize = 0;
		this.maxWidth = 0;
		this.widthArray = [];
		this.currentWidth = 0;
	}

    /**
     * @description Measures the view size for Factset
     */
	measureView(event) {
		if (this.currentWidth === 0 || this.currentWidth !== event.nativeEvent.layout.width) {
			this.currentWidth = event.nativeEvent.layout.width;
			this.viewSize = event.nativeEvent.layout.width;
			this.getFactSetWidthFromHostConfig();
		}
	}

	/**
     * @description Finds the width for Fact key and column value 
     */
	getFactSetWidthFromHostConfig() {
		let titleConfig = this.hostConfig.factSet.title;
		let valueConfig = this.hostConfig.factSet.value;
		if (!Utils.isNullOrEmpty(titleConfig.maxWidth) && (titleConfig.maxWidth !== 0) && Utils.isaNumber(titleConfig.maxWidth)) {
			if (titleConfig.maxWidth < (0.8 * this.viewSize)) {
				let currentValueWidth = this.viewSize - titleConfig.maxWidth;
				this.setFactSetWidthSize(titleConfig.maxWidth, currentValueWidth);
			} else {
				let currentTitleWidth = 0.8 * this.viewSize;
				let currentValueWidth = this.viewSize - currentTitleWidth;
				this.setFactSetWidthSize(currentTitleWidth, currentValueWidth);
			}
		} else if (!Utils.isNullOrEmpty(valueConfig.maxWidth) && (valueConfig.maxWidth !== 0) && Utils.isaNumber(valueConfig.maxWidth)) {
			if (valueConfig.maxWidth < (0.8 * this.viewSize)) {
				let currentTitleWidth = this.viewSize - valueConfig.maxWidth;
				this.setFactSetWidthSize(currentTitleWidth, valueConfig.maxWidth);
			} else {
				let currentValueWidth = 0.8 * this.viewSize;
				let currentTitleWidth = this.viewSize - currentTitleWidth;
				this.setFactSetWidthSize(currentTitleWidth, currentValueWidth);
			}
		} else {
			this.setFactSetWidthSize('50%', '50%');
		}
	}

	setFactSetWidthSize(titleWidth, valueWidth) {
		this.setState({
			keyWidth: titleWidth,
			valueWidth: valueWidth
		})
	}

    /**
     * @description Renders the Fact key and column value after width values are calculated.
     */
	parsePayload = (factSetJson) => {
		renderedElement = [];
		if (!this.payload)
			return renderedElement;

		// host config
		let titleConfig = this.hostConfig.factSet.title;
		let valueConfig = this.hostConfig.factSet.value;
		factSetJson.facts.map((element, index) => {
			renderedElement.push(
				<View style={[styles.textContainer]} key={`FACT-${element.title}-${index}`}>
					<Label
						text={element.title}
						size={titleConfig.size}
						weight={titleConfig.weight}
						color={titleConfig.color}
						isSubtle={titleConfig.isSubtle}
						wrap={titleConfig.wrap}
						style={{ width: this.state.keyWidth }} />
					<Label
						text={element.value}
						size={valueConfig.size}
						weight={valueConfig.weight}
						color={valueConfig.color}
						isSubtle={valueConfig.isSubtle}
						wrap={valueConfig.wrap}
						style={[styles.valueTextStyle, { width: this.state.valueWidth }]} />
				</View>
			);
		});

		return renderedElement;
	}

    /**
     * @description conditional render to check if width value is found
     */
	internalRenderer(containerJson) {
		let factSetObject = null;
		factSetObject = this.parsePayload(containerJson)
		return (
			<ElementWrapper json={containerJson} isFirst={this.props.isFirst}>
				<View style={[styles.container]} onLayout={(event) => { this.measureView(event) }}>
					{factSetObject}
				</View>
			</ElementWrapper>
		);
	}

	render() {
		let factSetContainer = this.internalRenderer(this.props.json);
		return factSetContainer;
	}
};

const styles = StyleSheet.create({
	container: {
		flexDirection: Constants.FlexColumn,
		backgroundColor: 'transparent',
	},
	textContainer: {
		flexDirection: Constants.FlexRow,
		backgroundColor: 'transparent',
	},
	valueTextStyle: {
		paddingLeft: 5,
	}
});
