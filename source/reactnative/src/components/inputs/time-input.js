/**
 * Date component based on the given payload.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputtime
 */

 import React from 'react';
import {
    View, StyleSheet, TouchableOpacity, DatePickerIOS, TimePickerAndroid,
    Platform, TextInput, Modal, Button, ViewPropTypes
} from 'react-native';
import Input from './input';
import { gethostConfig } from "../../utils/host-config";
import { InputContextConsumer } from '../../utils/context';
import * as Constants from '../../utils/constants';

const hostConfig = gethostConfig();

export class TimeInput extends React.Component {

    constructor(props) {
        super(props);
        
        this.payload = props.json;
        this.id = Constants.EmptyString;
        this.placeHolder = Constants.EmptyString;
        this.type = Constants.EmptyString;
        this.modalButtonText = Constants.DoneString;
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
            chosenTime: this.payload.value ? this.parseTimeString(this.payload.value) : new Date(),
            minTime: this.payload.min ? this.parseTimeString(this.payload.min) : undefined,
            maxTime: this.payload.max ? this.parseTimeString(this.payload.max) : undefined,
            modalVisible: false,
            value: this.payload.value ? this.payload.value : Constants.EmptyString
        }

        this.state.setTime = this.setTime.bind(this);
    }

    /**
     * @description Return Date object from string.
     * @param {String} timeString 
     */

    parseTimeString(timeString) {
        timeArray = timeString.split(':');
        date = new Date();
        date.setHours(Number.parseInt(timeArray[0], 10));
        date.setMinutes(Number.parseInt(timeArray[1], 10));
        return date;
    }

    /**
    * @description Binds the selected time
    * @param {Date} newTime 
    */
    setTime(newTime) {
        const updatedTime = ("0" + newTime.getHours()).slice(-2) + ":"
            + ("0" + newTime.getMinutes()).slice(-2);

        this.setState({
            chosenTime: newTime,
            value: updatedTime
        });
    }

    /**
     * @description Toggles the TimePicker model visibility.
     * @param {Boolean} visible 
     */

    setModalVisible(visible) {
        this.setState({ modalVisible: visible });
    }

    /**
     * @description Hides the TimePicker on close event
     */

    handleModalClose = () => {
        this.setState({ modalVisible: false })
    }

    /**
     * @description Updates the selected Time from Time picker model.
     */

    handleTimeChange = time => this.setTime(time)

    /**
    * @description Displays Android Time Picker
     */

    async androidPicker() {
        try {
            const { action, hour, minute } = await TimePickerAndroid.open({
                hour: this.state.chosenTime.getHours(),
                minute: this.state.chosenTime.getMinutes()
            });
            if (action !== TimePickerAndroid.dismissedAction) {
                // Selected hour (0-23), minute (0-59)
                var date = new Date();
                date.setHours(hour);
                date.setMinutes(minute);
                this.setTime(date)
            }
        } catch ({ code, message }) {
            console.warn('Cannot open time picker', message);
        }
    }

    /**
     * @description Displays Time Picker based on the platform.
     */

    showTimePicker = () => {
        if (Platform.OS === Constants.PlatformIOS) {
            this.setState({ modalVisible: true });
        } else {
            this.androidPicker()
        }
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
                {({ addInputItem }) => (
                 <Input json={this.payload}>
                    <TouchableOpacity style={styles.inputWrapper} onPress={this.showTimePicker}>
                        {/* added extra view to fix touch event in ios . */}
                        <View pointerEvents='none'>
                            <TextInput
                                style={styles.input}
                                autoCapitalize={Constants.NoneString}
                                autoCorrect={false}
                                placeholder={placeholder}
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
                                    mode={'time'}
                                    format={"HH:mm"}
                                    minDate={this.state.minTime}
                                    maxDate={this.state.maxTime}
                                    date={this.state.chosenTime || new Date()}
                                    onDateChange={this.handleTimeChange}
                                />
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
        fontSize: hostConfig.fontSizes.default,
        fontWeight: hostConfig.fontWeights.default.toString(),
        padding: 5,
        marginTop: 15,
        borderWidth: 1,
        backgroundColor: Constants.WhiteColor,
        borderRadius: 5,
        borderColor: Constants.LightGreyColor,

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
