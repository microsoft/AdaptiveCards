import React from "react";
import { Label } from '../elements';
import { Registry } from '../registration/registry';
import { StyleManager } from '../../styles/style-config';
import * as Constants from '../../utils/constants';
import * as Utils from '../../utils/util';

export default class InputLabel extends React.Component {

	styleConfig = StyleManager.getManager().styles;

	constructor(props) {
		super(props);
		this.label = props.label || Constants.EmptyString;
		this.wrap = props.wrap || false;
		this.style = props.style || {};
	}

	render() {
		const { label, wrap, style } = this;
		if (label == Constants.EmptyString) return null;
		else {
			if (typeof label == Constants.TypeString) {
				return (
					<Label
						text={label}
						style={[this.styleConfig.defaultFontConfig, style]}
						wrap={wrap} />
				);
			} else if (typeof label == Constants.TypeObject && this.isValidLabelType(label.type)) {
				let children = [];
				if (!Utils.isNullOrEmpty(label)) {
					children = Registry.getManager().parseRegistryComponents([label], this.context.onParseError);
				}
				return children.map((ChildElement, index) => React.cloneElement(ChildElement));
			} else return null;
		}
	}

	isValidLabelType = type => {
		return !Utils.isNullOrEmpty(type) && (type == Constants.TypeTextBlock || type == Constants.TypeRichTextBlock);
	}
}