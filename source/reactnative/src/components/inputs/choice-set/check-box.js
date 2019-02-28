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

const styles = StyleSheet.create({
	contentStyle: {
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

	componentWillMount() {
		this.setState({
			checked: this.props.checked
		});
	}

	componentWillReceiveProps(props) {
		this.setState({
			checked: props.checked
		})
	}

	onChange = () => {
		const newValue = !this.state.checked
		const { onChange } = this.props
		this.setState({ checked: newValue }, () => {
			onChange(newValue)
		})
	}

	renderCheckBoxIcon = () => {
		const { iconSize, isRadioButtonType } = this.props;

		return (
			<Image
				style={{ width: iconSize, height: iconSize }}
				source={isRadioButtonType ?
					this.state.checked ? require(CheckedRadioImage) :
						require(UncheckedRadioImage) :
					this.state.checked ? require(CheckedCheckBoxImage) :
						require(UncheckedCheckBoxImage)}
			/>
		)
	}

	renderContent = () => {
		const { labelStyle, label, wrapText } = this.props;
		const flexDirection = Constants.FlexRow;

		return (
			<View style={[styles.contentStyle, { flexDirection }]}>
				{this.renderCheckBoxIcon()}
				{
					label ? <Label text={label} style={labelStyle} wrap={wrapText} /> : null
				}
			</View>
		)
	}

	render() {
		const { style } = this.props;
		return (
			<TouchableOpacity activeOpacity={1}
				onPress={this.onChange.bind(this)}
				style={style}>
				{this.renderContent()}
			</TouchableOpacity>
		)
	}
}

export default CheckBox;
