/**
 * FactSet Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-factset
 */

import React from 'react';
import {
    View,
    StyleSheet,
    Text,
    Dimensions
} from 'react-native';

import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';
import { StyleManager } from '../../styles/style-config';

export class FactSet extends React.Component {

    styleConfig = StyleManager.getManager().styles;

    constructor(props) {
        super(props);

        this.payload = props.json;
        // state
        this.state = {
            isMaximumWidthValueFound: false,
            keyWidth: 0,
            valueWidth: 0
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
            this.viewSize = event.nativeEvent.layout.width - 2 * styles.container.padding;
            this.checkForMaxWidth();
        }
    }

    /**
     * @description Measures the Fact Key size for Factset
     */
    measureKeyText(event) {
        if (event.nativeEvent.layout.width) {
            currentElementwidth = event.nativeEvent.layout.width;
            this.widthArray.push(currentElementwidth);
            this.checkForMaxWidth();
        }
    }

    checkForMaxWidth() {
        if (this.widthArray.length === this.payload.facts.length) {
            this.maxWidth = Math.max(...this.widthArray);
            this.adjustFactWidth();
        }
    }
    /**
     * @description Finds the width for Fact key and column value 
     */

    adjustFactWidth() {
        var keyWidthValue = null;
        if (this.maxWidth > this.viewSize / 2) {
            keyWidthValue = this.viewSize / 2;
        } else {
            keyWidthValue = this.maxWidth;
        }
        let valueWidthPx = this.viewSize - keyWidthValue;
        this.setState({
            isMaximumWidthValueFound: true,
            keyWidth: keyWidthValue,
            valueWidth: valueWidthPx
        })
    }

    /**
     * @description Temporary renderer to find Fact key and column value before values are knows
     */

    checkTheMaximumSizeRender() {
        var checkArray = [];
        this.widthArray = [];
        var viewWidth = Dimensions.get("window").width;
        this.props.json.facts.map((element, index) => {
            checkArray.push(
                <View style={[styles.textContainer]} key={`FACT--${index}`}>
                    <Text style={[styles.keyTextStyle, this.styleConfig.fontConfig]} numberOfLines={500}
                        onLayout={(event) => { this.measureKeyText(event) }}>
                        {element.title}
                    </Text>
                    <Text style={[styles.valueTextStyle, this.styleConfig.fontConfig]} numberOfLines={500}>
                        {element.value}
                    </Text>
                </View>
            );
        });
        return checkArray;
    }

    /**
     * @description Renders the Fact key and column value after width values are calculated.
     */
    parsePayload = (factSetJson) => {
        renderedElement = [];
        if (!this.payload)
            return renderedElement;
        factSetJson.facts.map((element, index) => {
            renderedElement.push(
                <View style={[styles.textContainer]} key={`FACT-${element.title}-${index}`}>
                    <Text style={[styles.keyTextStyle, this.styleConfig.fontConfig,
                    { width: this.state.keyWidth }]}
                        numberOfLines={500}>
                        {element.title}
                    </Text>
                    <Text style={[styles.valueTextStyle, this.styleConfig.fontConfig,
                    { width: this.state.valueWidth }]}
                        numberOfLines={500}>
                        {element.value}
                    </Text>
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
        if (!this.state.isMaximumWidthValueFound) {
            factSetObject = this.checkTheMaximumSizeRender();
        }
        else {
            factSetObject = this.parsePayload(containerJson)
        }

        return (
            <ElementWrapper json={containerJson}>
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
        flex: 1,
        flexDirection: Constants.FlexColumn,
        backgroundColor: 'transparent',
    },
    textContainer: {
        flexDirection: Constants.FlexRow,
        backgroundColor: 'transparent',
    },
    keyTextStyle: {
        fontWeight: Constants.BoldWeight,
    },
    valueTextStyle: {
        paddingLeft: 5,
    }
});
