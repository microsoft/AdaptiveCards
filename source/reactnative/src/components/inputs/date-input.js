/**
 * Date component based on the given payload.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputdate
 */

import React from 'react';
import {
    View, StyleSheet, TouchableOpacity, DatePickerIOS,
    DatePickerAndroid, Platform, TextInput, Modal, Button, ViewPropTypes
} from 'react-native';
import Input from './input';
import { InputContextConsumer } from '../../utils/context'
import * as Constants from '../../utils/constants';
import { StyleManager } from '../../styles/style-config'


export class DateInput extends React.Component {

    styleConfig = StyleManager.getManager().styles;

    constructor(props) {
        super(props);

        this.payload = props.json;
        this.id = Constants.EmptyString;
        this.placeHolder = Constants.EmptyString;
        this.type = Constants.EmptyString;
        this.modalButtonText = Constants.DoneString
        this.parseHostConfig();
    }

    /**
    * @description Parse hostconfig specific to this element
    */
    parseHostConfig() {
        this.id = this.payload.id;
        this.type = this.payload.type;
        this.placeholder = this.payload.placeholder;
        this.state = {
            chosenDate: this.payload.value ? this.parseDateString(this.payload.value) : new Date(),
            minDate: this.payload.min ? this.parseDateString(this.payload.min) : undefined,
            maxDate: this.payload.max ? this.parseDateString(this.payload.max) : undefined,
            modalVisible: false,
            value: this.payload.value ? this.payload.value : Constants.EmptyString
        }

        this.state.setDate = this.setDate.bind(this);
    }

    /**
     * @description Updates the selected date
     * @param {Date} newDate 
     */
    setDate(newDate) {
        this.setState({ chosenDate: newDate })
        this.setState({
            value: newDate.getFullYear() + "-" +
                `${newDate.getMonth() + 1}`.padStart(2, '0') + "-" +
                `${newDate.getDate()}`.padStart(2, '0')
        })
    }

    /**
     * @description Toggles the DatePicker model visibility.
     * @param {Boolean} visible 
     */
    setModalVisible(visible) {
        this.setState({ modalVisible: visible });
    }

    /**
     * @description Hides the DatePicker on close event
     */
    handleModalClose = () => {
        this.setState({ modalVisible: false })
    }

    /**
     * @description Updates the selected date from date picker model.
     */
    handleDateChange = date => this.setDate(date)

    /**
     * @description Displays Android Date Picker
     */
    async androidPicker() {
        try {
            const { action, year, month, day } = await DatePickerAndroid.open({
                // Use `new Date()` for current date.
                date: this.state.chosenDate,
                minDate: this.state.minDate,
                maxDate: this.state.maxDate,
            });
            if (action !== DatePickerAndroid.dismissedAction) {
                // Selected year, month (0-11), day
                this.setDate(new Date(year, month, day))
            }
        } catch ({ code, message }) {
            console.log('Cannot open date picker', message);
        }
    }

    /**
     * @description Displays Date Picker based on the platform.
     */
    showDatePicker = () => {
        if (Platform.OS === Constants.PlatformIOS) {
            this.setState({ modalVisible: true });
        } else {
            this.androidPicker()
        }
    }

    /**
     * @description Return Date object from string.
     * @param {String} dateString 
     */
    parseDateString(dateString) {
        elements = dateString.split('-');
        return new Date(elements[0], elements[1], elements[2])
    }

    render() {
        const {
            id,
            type,
            placeholder,
            modalButtonText
        } = this;

        if (!id || !type) {
            return null;
        }

        modalOverlayStyle = ViewPropTypes.style,
        modalStyle = ViewPropTypes.style,
        modalButtonStyle = ViewPropTypes.style,
        modalBtnContainer = ViewPropTypes.style

        return (
            <InputContextConsumer>
                {({addInputItem }) => (
            <Input json={this.payload}>
           
                <TouchableOpacity style={styles.inputWrapper}onPress={this.showDatePicker}>
                    {/* added extra view to fix touch event in ios . */}
                    <View pointerEvents='none' >
                        <TextInput
                            style={[styles.input,this.styleConfig.fontConfig]}
                            autoCapitalize={Constants.NoneString}
                            autoCorrect={false}
                            placeholder={placeholder}
                            textContentType={Constants.NoneString}
                            underlineColorAndroid={Constants.TransparentString}
                            value={this.state.value}>
                            {addInputItem(this.id, this.state.value)}
                        </TextInput>
                    </View>
                </TouchableOpacity>
                <Modal
                    animationType='slide'
                    transparent
                    visible={this.state.modalVisible}
                    onRequestClose={this.handleModalClose}>
                    <View style={[styles.overlay, modalOverlayStyle]}>
                        <View style={[styles.modal, modalStyle]}>
                            <View style={[styles.modalBtnContainer, modalBtnContainer]}>
                                <Button
                                    style={[modalButtonStyle]}
                                    title={modalButtonText}
                                    onPress={this.handleModalClose}
                                />
                            </View>
                            <DatePickerIOS
                                mode='date'
                                date={this.state.chosenDate || new Date()}
                                minimumDate={this.state.minDate}
                                maximumDate={this.state.maxDate}
                                onDateChange={this.handleDateChange} />
                        </View>
                    </View>
                </Modal>
            </Input>)}
        </InputContextConsumer>
        );
    }
}

const styles = StyleSheet.create({
    inputWrapper: {
        width: Constants.FullWidth,
        marginTop: 15,
    },
    input: {
        width: Constants.FullWidth,
        height: 44,
        padding: 5,
        borderWidth: 1,
        backgroundColor: Constants.WhiteColor,
        borderColor: Constants.LightGreyColor,
        borderRadius: 5,
    },
    overlay: {
        flex: 1,
        backgroundColor: 'rgba(0,0,0,.3)',
        alignItems: Constants.CenterString,
        justifyContent: Constants.FlexEnd
    },
    modal: { 
        backgroundColor: Constants.WhiteColor,
         height: 260, 
         width: Constants.FullWidth 
    },
    modalBtnContainer: {
        width: Constants.FullWidth,
        alignItems: Constants.CenterString,
        flexDirection: Constants.FlexRow,
        justifyContent: Constants.FlexEnd,
        paddingHorizontal: 15,
        marginTop: 15
    }
});
