import React from "react";
import {
	StyleSheet,
	Text,
	View
} from 'react-native';
import { Label } from '../elements';
import { Registry } from '../registration/registry';
import * as Constants from '../../utils/constants';
import { isNullOrEmpty } from '../../utils/util';
import { TextColor, ContainerStyle } from '../../utils/enums';

export default class InputLabel extends React.Component {

	constructor(props) {
		super(props);
		this.label = props.label || Constants.EmptyString;
		this.wrap = props.wrap || true;
		this.style = props.style || {};
		this.isRequired = props.isRequired || false;
		this.hostConfig = props.configManager.hostConfig;
		this.altText = props.altText;
		this.applyStyleConfig = props.applyStyleConfig;
	}

	render() {
		const { label, isRequired, wrap, style, applyStyleConfig } = this;

		// NOTE :: Do not apply label styles on Toggle, other Input's labels style is picked from themeconfig
		let computedStyle = style;
		if (typeof applyStyleConfig !== 'boolean' || applyStyleConfig) {
			computedStyle = this.props.configManager.styleConfig.inputLabel;
		}

		let inputLabel = null;
		if (label != Constants.EmptyString) {
			if (typeof label == Constants.TypeString) {
				inputLabel = (
					<Label
						text={label}
						style={[this.props.configManager.styleConfig.defaultFontConfig, computedStyle]}
						configManager={this.props.configManager}
						wrap={wrap}
						isRequired={!!isRequired}
						altText={this.props.altText} />
				);
			} else if (typeof label == Constants.TypeObject && this.isValidLabelType(label.type)) {
				let element = [];
				if (!isNullOrEmpty(label)) {
					element = Registry.getManager().parseRegistryComponents([label], this.context.onParseError);
				}
				if (element.length > 0) inputLabel = React.cloneElement(element[0], { configManager: this.props.configManager });
			}
		}
		if (inputLabel) {
			return (
				<View style={styles.container} accessible={typeof label == Constants.TypeString ? true: undefined}>
					<View>{inputLabel}</View>
				</View>
			);
		} else return inputLabel;
	}

	isValidLabelType = type => {
		return !isNullOrEmpty(type) && (type == Constants.TypeTextBlock || type == Constants.TypeRichTextBlock);
	}
}

const styles = StyleSheet.create({
	container: {
		flexDirection: Constants.FlexRow
	}
});