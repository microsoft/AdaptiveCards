/**
 * ChoiceSet Component.
 *
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputchoiceset
 */

import React, {PureComponent} from 'react';
import {
	StyleSheet,
	Text,
	View,
	Picker,
	TouchableOpacity,
	Image,
	Platform,
	TextInput,
	ScrollView,
	Modal
} from 'react-native';

import ElementWrapper from '../../elements/element-wrapper';
import Checkbox from './check-box';
import { InputContextConsumer } from '../../../utils/context';
import * as Utils from '../../../utils/util';
import * as Constants from '../../../utils/constants';
import * as Enums from '../../../utils/enums';
import { StyleManager } from '../../../styles/style-config';
import { HostConfigManager } from '../../../utils/host-config';
import InputLabel from "../input-label";

const DropDownImage = './assets/dropdown.png';
const CompactStyle = "compact";


export class ChoiceSetInput extends React.PureComponent {

	styleConfig = StyleManager.getManager().styles;
	constructor(props) {
		super(props);
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
			isError: this.isRequired ? this.validate() : false,
			pickerInputText: undefined,
			pickerChoicesArr: [],
		}
	}

	componentDidMount(){
		if(this.payload.choicesSource != undefined){
			if(this.payload.choicesSource.type = 'Data.Query'){
				fetch('https://tygu9.sse.codesandbox.io').then((response) => response.json())//link to fetch the items
				.then((json) => {
				  json.data.map((data,index)=>{
					  this.choices.push(data);
					  this.forceUpdate();
					  this.dynamicChoiceData = true;
				  })
				}).catch((e)=>{
					//console.log(e);
				})
			};
		};
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


	setPickerValue(addInputItem) {
		if (this.state.pickerInputText == undefined) {
			this.setState({
				pickerInputText: this.getPickerSelectedValue(this.state.selectedPickerValue,
					addInputItem)
			})
			this.setState({ pickerChoicesArr: this.choices })
			return (this.getPickerSelectedValue(this.state.selectedPickerValue,
				addInputItem))
		}
		else {
			return (this.state.pickerInputText)
		}
	}
	/**
	 * @description Renders Picker component as per the json
	 */
	renderPickerComponent(addInputItem) {
		if(this.payload.choicesSource == undefined)
		{
			return (
				<View style={styles.containerView}>
					{(Platform.OS === Constants.PlatformIOS) && <TouchableOpacity
						activeOpacity={1}
						onPress={onPress}>
						<View style={styles.touchView}>
							<Text
								style={[styles.text, this.styleConfig.defaultFontConfig]}
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
						<View style={styles.pickerContainer}>
							<Picker
								mode={'dropdown'}
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
						</View>
					}
				</View>
			)
		}
		else
		return (
			<View style={styles.containerView}>
				{(Platform.OS === Constants.PlatformIOS) && <View>
					<View style={{ flexDirection: "row", display: "flex", width: "100%", backgroundColor: 'white', borderWidth: 1, borderColor: "black",position:'relative' }}>
						<TextInput
							value={this.setPickerValue(addInputItem)}
							onChangeText={(text) => {
								if (!this.state.isPickerSelected) {

									this.setState({ isPickerSelected: true })
								}
								this.setState({
									selectedPickerValue: text,
									isError: false,
									pickerInputText: text
								})
									var searchResult = this.choices.filter(function (e) {
										return e.title.includes(text);
									});
									this.setState({ pickerChoicesArr: searchResult })

							}}
							style={[styles.text, this.styleConfig.defaultFontConfig], styles.autoCompPicker}
							accessible={true}
						>
						</TextInput>


					</View>
				</View>}
				{this.state.isPickerSelected &&
					<ScrollView style={{ width: '100%', height: 200, backgroundColor: 'white',elevation:1}}>
						{this.state.pickerChoicesArr.map((item, key) => (
							<TouchableOpacity key={key} style={{ height: 40, backgroundColor: 'white',marginVertical:5, justifyContent: "center", borderColor: "#dadde1", borderWidth: 1 }}
								onPress={() => {
									var itemValue =
									 this.state.pickerChoicesArr[key].value;
									this.setState({
										selectedPickerValue: itemValue,
										isError: false
									})
									addInputItem(this.id, { value: itemValue, errorState: false });
									this.setState({ pickerInputText: this.getPickerSelectedValue(itemValue, addInputItem) })
									onPress();
								}}
							>
								<Text style={{ marginLeft: 2 }}>{item.title}</Text>
							</TouchableOpacity>
						)
						)}
					</ScrollView>
				}
				{/* {((Platform.OS === Constants.PlatformIOS) ? this.state.isPickerSelected : true) &&
					<View style={styles.pickerContainer}>
						<Picker
							mode={'dropdown'}
							selectedValue={this.getPickerInitialValue(addInputItem)}
							onValueChange={
								(itemValue) => {
									this.setState({
										selectedPickerValue: itemValue,
										isError: false
									})
									addInputItem(this.id, { value: itemValue, errorState: false });
									this.setState({pickerInputText:this.getPickerSelectedValue(itemValue,addInputItem)})
								}}>
							{this.state.pickerChoicesArr.map((item, key) => (
								<Picker.Item
								    onPress={()=>{console.log('ji');}}
									label={item.title}
									value={item.value} key={key}
								/>
								)
							)}
						</Picker>
					</View>
				} */}
			</View>
		)
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

		if (HostConfigManager.supportsInteractivity() === false) {
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
				isPickerSelected: !this.state.isPickerSelected,
				pickerChoicesArr:this.choices
			})
		}

		return (
			<InputContextConsumer>
				{({ addInputItem }) => (
					<ElementWrapper json={this.payload} style={styles.containerView} isError={this.state.isError} isFirst={this.props.isFirst}>
						<InputLabel isRequired={this.isRequired} label={label} />
						<View
							accessible={true}
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
	pickerContainer: {
		backgroundColor: Constants.EmphasisColor,
	},
	touchView: {
		flexDirection: Constants.FlexRow,
		justifyContent: Constants.SpaceBetween,
		alignItems: Constants.FlexEnd,
		backgroundColor: Constants.EmphasisColor,
	},
	text: {
		color: 'black',
		textAlign: Constants.LeftAlign,
		marginTop: 10,
		marginLeft: 8,
		height: 30,
	},
	button: {
		height: 30,
		width: 30,
		marginBottom: 8,
		marginRight: 8,
		backgroundColor: Constants.EmphasisColor,
	},
	autoCompPicker: {
		backgroundColor: 'white',
		height: 30,
		flex: 1,
		width: '100%',
	}
});
