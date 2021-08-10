/**
 * ChoiceSet Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputchoiceset
 */

import React from 'react';
import {
	StyleSheet,
	Text,
	View,
	TouchableOpacity,
	Image,
	Platform
} from 'react-native';
import { Picker } from '@react-native-picker/picker';
import ElementWrapper from '../../elements/element-wrapper';
import Checkbox from './check-box';
import { InputContextConsumer } from '../../../utils/context';
import * as Utils from '../../../utils/util';
import * as Constants from '../../../utils/constants';
import InputLabel from "../input-label";

const DropDownImage = './assets/dropdown.png';
const CompactStyle = "compact";

export class ChoiceSetInput extends React.Component {


	constructor(props) {
		super(props);

		this.hostConfig = props.configManager.hostConfig;
		this.styleConfig = props.configManager.styleConfig;

		this.id = Constants.EmptyString;
		this.isMultiSelect = Boolean;
		this.style = Constants.EmptyString;
		this.type = Constants.EmptyString;
		this.value = props.json.value;
		this.choices = [];
		this.payload = props.json;
		this.label = Constants.EmptyString;
		this.isRequired = this.payload.isRequired || false;

		this.state = {
			selectedPickerValue: Utils.isNullOrEmpty(props.json.value) ?
				props.json.choices[0].value : props.json.value,
			isPickerSelected: false,
			radioButtonIndex: undefined,
			activeIndex: undefined,
			checked: undefined,
			checkedValues: undefined,
			isError: this.isRequired ? this.validate() : false
		}
	}

	/**
	 * @description Parse hostConfig specific to this element
	 */
	parseHostConfig() {
		this.id = this.payload.id;
		this.type = this.payload.type;
		this.isMultiSelect = this.payload.isMultiSelect;
		this.style = this.payload.style;
		this.choices = this.payload.choices;
		this.wrapText = this.payload.wrap || false
		this.label = this.payload.label;
	}

	validate = () => {
		let isError = true;
		if (this.payload.isMultiSelect) {
			const array = this.getCheckedIndexes(this.value);
			if (array.length > 0) {
				for (key in array) {
					if ((this.payload.choices.find(choice => choice.value === array[key]))) {
						isError = false;
						break;
					}
				}
			}
		} else {
			let choiceName = this.payload.choices.find(choice => choice.value === this.value);
			isError = (CompactStyle === this.payload.style && Utils.isNullOrEmpty(this.value))
				? false : !choiceName;
		}
		return isError;
	}

	/**
	 * @description Fetches the value from the selected picker option
	 * @param {string} value 
	 */
	getPickerSelectedValue = (value, addInputItem) => {
		if (Utils.isNullOrEmpty(value))
			return Constants.EmptyString
		let choiceName = this.choices.find(choice => choice.value === value);
		addInputItem(this.id, { value: value, errorState: this.state.isError });
		return choiceName ? choiceName.title : Constants.EmptyString;
	}

	/**
	 * @description Fetches the initial value for the picker component
	 */
	getPickerInitialValue = (addInputItem) => {
		addInputItem(this.id, { value: this.state.selectedPickerValue, errorState: this.state.isError })
		return this.state.selectedPickerValue
	}

	/**
	 * @description Fetches the index of the selected radio button choice
	 * @param {string} value 
	 * @param {array} choiceArray
	 */
	getRadioButtonIndex = (value, choiceArray, addInputItem) => {
		if (Utils.isNullOrEmpty(value)) {
			addInputItem(this.id, { value: Constants.EmptyString, errorState: this.state.isError });
			return -1
		}
		addInputItem(this.id, { value: value, errorState: this.state.isError });

		for (var i = 0; i < choiceArray.length; i++) {
			if (choiceArray[i]["value"] === value) {
				return i;
			}
		}
		return -1;
	}

	/**
	 * @description Selects the checkBoxes for the initial set of values from json
	 * @param {string} value 
	 */
	setInitialCheckedValues = (value, addInputItem) => {
		var array = this.getCheckedIndexes(value);
		if (array.length > 0) {
			addInputItem(this.id, { value: value, errorState: this.state.isError })
			return array
		}
		addInputItem(this.id, { value: Constants.EmptyString, errorState: this.state.isError })
		return []
	}

	/**
	 * @description Fetches the indexes of selected checkbox options
	 * @param {string} value 
	 */
	getCheckedIndexes = (value) => {
		if (Utils.isNullOrEmpty(value)) {
			return []
		}
		var array = value.split(',')
		return array
	}

	/**
	 * @description Renders Picker component as per the json
	 */
	renderPickerComponent(addInputItem) {
		return (
			<View style={styles.containerView}>
				{(Platform.OS === Constants.PlatformIOS) && <TouchableOpacity
					activeOpacity={1}
					onPress={onPress}
					accessible={true}
					accessibilityRole={'button'}
					accessibilityState={{ expanded: this.state.isPickerSelected }}
				>
					<View style={this.styleConfig.dropdown}>
						<Text
							style={[this.styleConfig.dropdownText, this.styleConfig.defaultFontConfig]}
						>
							{this.getPickerSelectedValue(this.state.selectedPickerValue,
								addInputItem)
							}
						</Text>
						<Image
							style={styles.button}
							source={require(DropDownImage)}
						/>
					</View>
				</TouchableOpacity>}
				{((Platform.OS === Constants.PlatformIOS) ? this.state.isPickerSelected : true) &&
					this.getPickerComponent(addInputItem)
				}
			</View>
		)
	}

	getPickerComponent(addInputItem) {
		let picker = (
			<Picker
				mode={'dropdown'}
				itemStyle={this.styleConfig.picker}
				selectedValue={this.getPickerInitialValue(addInputItem)}
				onValueChange={
					(itemValue) => {
						this.setState({
							selectedPickerValue: itemValue,
							isError: false
						})
						addInputItem(this.id, { value: itemValue, errorState: false });
					}}>
				{this.choices.map((item, key) => (
					<Picker.Item
						label={item.title}
						value={item.value} key={key}
					/>)
				)}
			</Picker>
		);
		if (Platform.OS == Constants.PlatformAndroid) {
			picker = (
				<View style={this.styleConfig.dropdown}>
					{picker}
				</View>
			)
		}
		return picker;
	}

	/**
	 * @description Renders CheckBoxes component as per the json
	 */
	renderCheckBoxComponent(addInputItem) {
		return (
			<View style={styles.container}>
				{this.choices.map((item, index) => (
					<Checkbox
						style={styles.container}
						label={item.title}
						key={index}
						isRadioButtonType={true}
						index={index}
						configManager={this.props.configManager}
						wrapText={this.wrapText}
						checked={this.state.activeIndex == undefined ?
							index == this.getRadioButtonIndex(this.value,
								this.choices, addInputItem) :
							index == this.state.activeIndex}
						onChange={() => {
							this.setState({ activeIndex: index, isError: false })
							addInputItem(this.id, { value: item.value, errorState: false });
						}}
					/>
				))}
			</View>)
	}

	/**
	 * @description Renders Radio Button component as per the json
	 */
	renderRadioButtonComponent(addInputItem) {
		return (
			<View>
				{this.choices.map((item, index) => (
					<Checkbox
						style={styles.container}
						label={item.title}
						key={index}
						isRadioButtonType={false}
						configManager={this.props.configManager}
						index={index}
						wrapText={this.wrapText}
						checked={this.state.checkedValues == undefined ?
							this.setInitialCheckedValues(this.value,
								addInputItem).includes(item.value) :
							this.getCheckedIndexes(this.state.checkedValues).includes(item.value)}
						onChange={() => {
							let checkedArray = (this.state.checkedValues == undefined) ?
								this.getCheckedIndexes(this.value) :
								this.getCheckedIndexes(this.state.checkedValues)
							if (checkedArray.includes(item.value)) {
								let checkedIndex = checkedArray.indexOf(item.value)
								checkedArray.splice(checkedIndex, 1)
							} else {
								checkedArray.push(item.value)
							}
							let newValue = checkedArray.sort().join()
							let isError = this.isRequired ? checkedArray.length < 1 : false;
							this.setState({ checkedValues: newValue, isError: isError })
							addInputItem(this.id, { value: newValue, errorState: isError });
						}
						}
					/>
				))}
			</View>
		)
	}

	render() {

		if (!this.hostConfig.supportsInteractivity) {
			return null;
		}

		this.parseHostConfig();

		const {
			isMultiSelect,
			style,
			label
		} = this

		onPress = () => {
			this.setState({
				isPickerSelected: !this.state.isPickerSelected
			})
		}

		return (
			<InputContextConsumer>
				{({ addInputItem }) => (
					<ElementWrapper configManager={this.props.configManager} json={this.payload} style={styles.containerView} isError={this.state.isError} isFirst={this.props.isFirst}>
						<InputLabel configManager={this.props.configManager} isRequired={this.isRequired} label={label} />
						<View
							accessible={false}
							accessibilityLabel={this.payload.altText}
							style={styles.choiceSetView}>
							{!isMultiSelect ?
								((style == CompactStyle || style == undefined) ?
									this.renderPickerComponent(addInputItem) :
									this.renderCheckBoxComponent(addInputItem)) :
								this.renderRadioButtonComponent(addInputItem)
							}
						</View>
					</ElementWrapper>)}
			</InputContextConsumer>
		);
	}
}

const styles = StyleSheet.create({
	containerView: {
		alignSelf: Constants.AlignStretch,
		marginVertical: 3,
	},
	choiceSetView: {
		marginTop: 3
	},
	button: {
		height: 30,
		width: 30,
		marginBottom: 8,
		marginRight: 8,
	},
});
