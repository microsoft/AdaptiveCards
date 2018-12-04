/**
 * Container Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-container
 */

import React, { PureComponent } from "react";
import { View, ScrollView, Text, StyleSheet, Platform, Alert, Linking } from 'react-native';
import Input from '../inputs/input';
import { Registry } from '../registration/registry'
import { SelectAction } from '../actions'
import * as Constants from '../../utils/constants';


export class Container extends React.Component {
    
    constructor(props) {
        super(props);
        
        this.renderedElement = [];
        this.payload = props.json;
        this.selectionActionData = props.json.selectAction;
    }

    /**
     * @description Parse the given payload and render the card accordingly
     */
    parsePayload = (containerJson) => {
        if (!this.payload)
            return this.renderedElement;
        const register = new Registry();
        // parse elements
        containerJson.items.map((element, index) => {
            const Element = register.getComponentOfType(element.type);
            if (Element) {
                this.renderedElement.push(<Element json={element} key={`ELEMENT-${this.generateNumber()}`} />);
            } else {
                this.renderedElement.push(
                    <Text style={styles.highlight} key={`ELEMENT-${this.generateNumber()}`}>
                        I'm a 
                        <Text style={{ fontWeight: Constants.BoldWeight }}>
                            {element.type}
                        </Text>
                         element
                    </Text>);
            }
        });

        return this.renderedElement;
    }
    
    /**
     * @description Generates a random number
     */
    generateNumber = () => {
        min = 1;
        max = 100000;
        const rndNum = Math.floor(Math.random() * (max - min + 1) + min)
        return rndNum
    };

    internalRenderer(containerJson) {
        let backgroundStyle = containerJson.style == Constants.Emphasis ?
         styles.emphasisStyle : styles.defaultBGStyle;

        // TODO: verticalContentAlignment property is not considered for now as the container size is determined by its content.
        var containerContent = (<View style={[styles.container, backgroundStyle]}>
            <Input json={containerJson} style={backgroundStyle}>
                <ScrollView style={backgroundStyle}>
                    {this.parsePayload(containerJson)}
                </ScrollView>
            </Input>
        </View>);

        if (containerJson.selectAction === undefined) {
            return containerContent;
        } else {
            return <SelectAction selectActionData={containerJson.selectAction}>
                {containerContent}
            </SelectAction>;
        }
    }

    render() {
        let containerRender = this.internalRenderer(this.props.json);
        return containerRender;
    }
};

const styles = StyleSheet.create({
    container: {
        flex: 1,
        padding: 10,
    },
    defaultBGStyle: {
        backgroundColor: Constants.WhiteColor,
    },
    emphasisStyle: {
        backgroundColor: Constants.EmphasisColor,
    },
});