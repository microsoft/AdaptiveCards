/**
 * CheckBox Component.
 */

import React from 'react';
import {
	View,
	Text,
	TouchableOpacity,
	StyleSheet,
	ViewPropTypes,
	Image
} from 'react-native';
import { Label } from '../../elements'
import PropTypes from 'prop-types';
import * as Constants from '../../../utils/constants';

const IMAGE_COLOR_PROPERTY = "tintColor";
const TEXT_COLOR_PROPERTY = "color";
const styles = StyleSheet.create({
	contentStyle: {
		marginVertical: 3,
		alignItems: Constants.CenterString
	},
	labelStyle: {
		fontSize: 16,
		marginLeft: 12
	}
});

const CheckedRadioImage = "./assets/checkedradio.png";
const UncheckedRadioImage = "./assets/uncheckedradio.png";
const CheckedCheckBoxImage = "./assets/checked.png";
const UncheckedCheckBoxImage = "./assets/unchecked.png";

class CheckBox extends React.PureComponent {

	constructor(props) {
		super(props);
		this.state = {
			checked: this.props.checked
		}
		this.styleConfig = props.configManager.styleConfig;
		this.hostConfig = props.configManager.hostConfig;
	}

	static propTypes = {
		style: ViewPropTypes.style,
		onChange: PropTypes.func.isRequired,
		checked: PropTypes.bool,
		wrapText: PropTypes.bool,
		isRadioButtonType: PropTypes.bool,
		labelStyle: Text.propTypes.style,
		iconSize: PropTypes.number,
	};

	static defaultProps = {
		style: {},
		checked: false,
		labelStyle: styles.labelStyle,
		iconSize: 28,
		wrapText: false,
	};

	static getDerivedStateFromProps(nextProps, prevState) {
		return { checked: nextProps.checked }
	}

	onChange = () => {
		const newValue = !this.state.checked
		const { onChange } = this.props
		this.setState({ checked: newValue }, () => {
			onChange(newValue)
		})
	}

	getModifiedStyles = (style, property) => {
		let modifiedStyles = { ...style };
		modifiedStyles[property] = this.state.checked ? modifiedStyles.activeColor : modifiedStyles.inactiveColor;
		delete modifiedStyles.inactiveColor;
		delete modifiedStyles.activeColor;
		if (property == TEXT_COLOR_PROPERTY && this.state.checked)
			modifiedStyles.fontWeight = this.hostConfig.fontStyles.default.fontWeights.bolder.toString();
		return modifiedStyles;
	}

	renderCheckBoxIcon = () => {
		const { isRadioButtonType } = this.props;
		const modifiedStyles = this.getModifiedStyles(isRadioButtonType ? this.styleConfig.radioButton : this.styleConfig.checkBox, IMAGE_COLOR_PROPERTY);
		return (
			<Image
				style={modifiedStyles}
				source={isRadioButtonType ?
					this.state.checked ? require(CheckedRadioImage) :
						require(UncheckedRadioImage) :
					this.state.checked ? require(CheckedCheckBoxImage) :
						require(UncheckedCheckBoxImage)}
			/>
		)
	}

	renderContent = () => {
		const { label, wrapText, isRadioButtonType, index } = this.props;
		const flexDirection = Constants.FlexRow;
		const modifiedStyles = this.getModifiedStyles(isRadioButtonType ? this.styleConfig.radioButtonText : this.styleConfig.checkBoxText, TEXT_COLOR_PROPERTY);
		return (
			<View style={[styles.contentStyle, { flexDirection }]}>
				{this.renderCheckBoxIcon()}
				{
					label ? <Label
						text={label}
						key={index + modifiedStyles.color}
						style={[modifiedStyles, this.styleConfig.defaultFontConfig]}
						configManager={this.props.configManager}
						wrap={wrapText} />
						: null
				}
			</View>
		)
	}

	render() {
		const { style } = this.props;
		return (
			<TouchableOpacity activeOpacity={1}
				onPress={this.onChange.bind(this)}
				style={style}
				accessibilityRole={this.props.isRadioButtonType ? 'radio' : 'checkbox'}
				accessibilityState={{checked: this.state.checked}}
				>
				{this.renderContent()}
			</TouchableOpacity>
		)
	}
}

export default CheckBox;
