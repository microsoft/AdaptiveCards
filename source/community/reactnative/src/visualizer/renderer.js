/**
 * Render the adaptive card for the given payload.
 */

import React from 'react';
import {
    View,
    Text,
    StyleSheet,
    Button,
    Platform,
    Alert,
    Linking,
    ScrollView
} from 'react-native';
import PropTypes from 'prop-types';
import * as ACData from 'adaptivecards-templating';
import AdaptiveCard from '../adaptive-card';
import { RatingRenderer } from './rating-renderer';
import { Registry } from '../components/registration/registry';
import * as Utils from '../utils/util';
import { Grey300 } from '../utils/constants';
import * as Constants from './constants';
import { CustomActionRenderer } from './custom-action-renderer';
import { CustomTextBlockRenderer } from './custom-text-block';
import { CustomActionButtonRenderer } from './custom-action-button';
import { CustomImageRenderer } from './custom-image';

export default class Renderer extends React.Component {

    static propTypes = {
        isDataBinding: PropTypes.bool
    };

    static defaultProps = {
        isDataBinding: false
    };

    state = {
        isJSONVisible: false
    }

    customHostConfig = {
        hostCapabilities: {
            adaptiveCards: '1.2',
            acTest: '1.3'
        },
        fontFamily: "Helvetica",
        supportsInteractivity: true,
        actions: {
            actionsOrientation: "Horizontal",
            actionAlignment: "Stretch"
        },
        fontSizes: {
            small: 12,
            default: 14,
            medium: 17,
            large: 21,
            extraLarge: 26
        }
    }

    customThemeConfig = {
        button: {
            backgroundColor: '#66BB6A'
        },
        input: {
            placeholderTextColor: Grey300
        },
        inputDate: {
            placeholderTextColor: Grey300
        },
        inputTime: {
            placeholderTextColor: Grey300
        }
    }

    constructor(props) {
        super(props);
        this.payload = props.payload;
        this.dataJson = props?.dataJson;
        this.onModalClose = props.onModalClose;
    }

    getTemplatePayload(templatejson, datajson) {
        try {

            const template = new ACData.Template(templatejson);

            templatePayload = template.expand({
                $root: datajson
            });
            return templatePayload;
        } catch (error) {
        }
    }

    bindPayloadWithData() {
        if(this.payload && this.dataJson) {
            this.payload = this.getTemplatePayload(this.payload, this.dataJson);
            return;
        }

        // Create a Template instance from the template payload
        var template = new ACData.Template(this.payload);

        // Create a data binding context, and set its $root property to the
        // data object to bind the template to
        var context = {
            $root: {
                "name": "Matt",
                "photo": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg",
                "manager": {
                    "name": "Thomas",
                    "title": "PM Lead"
                },
                "message": "{\"type\":\"Deployment\",\"buildId\":\"9542982\",\"releaseId\":\"129\",\"buildNumber\":\"20180504.3\",\"releaseName\":\"Release-104\",\"repoProvider\":\"GitHub\"}",
                "peers": [
                    {
                        "name": "Lei",
                        "title": "Sr Program Manager"
                    },
                    {
                        "name": "Andrew",
                        "title": "Program Manager II"
                    },
                    {
                        "name": "Mary Anne",
                        "title": "Program Manager"
                    }
                ],
                "stockName": "Microsoft Corp (NASDAQ: MSFT)",
                "stockValue": "75.30",
                "title": "Publish Adaptive Card Schema",
                "description": "Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation.",
                "creator": {
                    "name": "Matt Hidinger",
                    "profileImage": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
                },
                "createdUtc": "2017-02-14T06:08:39Z",
                "viewUrl": "https://adaptivecards.io",
                "properties": [
                    { "key": "Board", "value": "Adaptive Cards" },
                    { "key": "List", "value": "Backlog" },
                    { "key": "Assigned to", "value": "Matt Hidinger" },
                    { "key": "Due date", "value": "Not set" }
                ],
                "cafeName": "Cafe 34",
                "cafeDescription": "Open Mon-Fri from 9am - 2pm",
                "cafeteriaImage": "https://th.bing.com/th/id/R.f70650f59a71616da0d8f4b5c73e9f60?rik=g02xYdIzQX5Img&riu=http%3a%2f%2fwww.designtechnikblog.ch%2fwp-content%2fuploads%2f2018%2f02%2f7486f09c-1dce-478b-99aa-0a142c9e9165.jpg&ehk=wNERHkKGpde%2bmt9lefTeLF88%2br6OFdhUKNG8oEExDg8%3d&risl=&pid=ImgRaw&r=0",
                "menu":[
                    {
                        "image": "https://i.pinimg.com/originals/22/28/af/2228afa177aa08b6664c76bd9d7ec56c.jpg",
                        "station": "Station 1",
                        "name": "Korean",
                        "description": "Chili Pickled Cabbage, Pork Bulgogi, Korean Barbecue, Fried..."
                    },
                    {
                        "image": "https://th.bing.com/th/id/R.611dd20fbfc894b973b662498027721f?rik=Ev8dUaRZCrpnTg&riu=http%3a%2f%2fdimondcafeoakland.com%2fuploads%2f3%2f4%2f7%2f7%2f34778011%2f8770113.jpg&ehk=ZSUEdr0fuSpjM22rivCpa7O8UlMNQfRozIW9UKogB1o%3d&risl=&pid=ImgRaw&r=0",
                        "station": "Station 2",
                        "name": "Mexican",
                        "description": "Enchiladas, Street tacos, Guacamole"
                    },
                    {
                        "image": "https://th.bing.com/th/id/OIP.NqBIh7UiCM7KRxnn6ijgRwAAAA?pid=ImgDet&rs=1",
                        "station": "Station 3",
                        "name": "Grille",
                        "description": "Selection of burgers, French fries, Fountain drinks."
                    },
                    {
                        "image": "https://th.bing.com/th/id/OIP.gHJJCykFexBZTex15nhCPAAAAA?pid=ImgDet&w=300&h=300&rs=1",
                        "station": "Station 3",
                        "name": "in.gredients",
                        "description": "Enchiladas, Street tacos, Guacamole"
                    }
                ]
            }
        }

        // "Expand" the template - this generates the final payload for the Adaptive Card,
        // ready to render with this payload
        this.payload = template.expand(context);
    }

    render() {
        //Register Custom Components
        Registry.getManager().registerComponent('RatingBlock', RatingRenderer);

        //Register Custom Text Block Components
        // Registry.getManager().registerComponent('TextBlock', CustomTextBlockRenderer);

        //Register Custom Action Button Components
        Registry.getManager().registerComponent('CustomActionButton', CustomActionButtonRenderer);

        //Register Custom Image Components
        Registry.getManager().registerComponent('CustomImage', CustomImageRenderer);

        //Register Custom Actions
        Registry.getManager().registerComponent('Action.Custom', CustomActionRenderer);
        let { isJSONVisible } = this.state;

        //We will update the payload with method bindPayloadWithData, if isDataBinding is true.
        this.props.isDataBinding && this.bindPayloadWithData()

        return (
            <View style={styles.container}>
                <View style={styles.header}>
                    <Button title="Close" onPress={this.onModalClose} />
                    <Text style={styles.title}>Adaptive Card</Text>
                    <Button title={isJSONVisible ? 'Card' : 'Json'} onPress={this.toggleJSONView} />
                </View>
                {isJSONVisible ?
                    <ScrollView contentContainerStyle={styles.jsonContainer}>
                        <Text style={{ fontFamily: 'Courier New' }}>
                            {JSON.stringify(this.props.payload, null, '  ')}
                        </Text>
                    </ScrollView>
                    :
                    <AdaptiveCard
                        payload={this.payload}
                        onExecuteAction={this.onExecuteAction}
                        hostConfig={this.customHostConfig}
                        themeConfig={this.customThemeConfig}
                        onParseError={this.onParseError}
                        // cardScrollEnabled={false} //we can also set the scrollEnabled for the adaptive card. Default value is true
                        // contentContainerStyle={{ flexGrow: 1, justifyContent: 'space-between' }} //we can also set the contentContainer Style for the adaptive card
                        // containerStyle={{width:100, height: 100, flexGrow:1, backgroundColor: 'lightblue'}} //we can also set the style for the adaptive card
                        // contentHeight={500} //we can also set the height of the adaptive card
                        ref="adaptiveCardRef" />
                }
            </View>
        );
    }

    /**
     * @description Handler for the payload actions.
     * @param {object} actionObject - Details and data about the action.
     */
    onExecuteAction = (actionObject) => {
        if (actionObject.type === "Action.Submit") {
            Alert.alert(
                'Rendered Submit',
                JSON.stringify(actionObject.data),
                [
                    { text: actionObject.title, onPress: () => console.log('OK Pressed') },
                ],
                { cancelable: false }
            )
        } else if (actionObject.type === "Action.Execute") {
            Alert.alert(
                'Rendered Univeral Action',
                JSON.stringify(actionObject.data) + "\n Verb is " + actionObject.verb,
                [
                    { text: actionObject.title, onPress: () => console.log('OK Pressed') },
                ],
                { cancelable: false }
            )
        } else if (actionObject.type === "Action.OpenUrl" && !Utils.isNullOrEmpty(actionObject.url)) {
            Linking.canOpenURL(actionObject.url).then(supported => {
                if (supported) {
                    Linking.openURL(actionObject.url).catch(() => {
                        console.log("Failed to open URI: " + actionObject.url)
                        this.alertAction(actionObject);
                    });
                } else {
                    console.log("Don't know how to open URI: " + actionObject.url);
                    this.alertAction(actionObject);
                }
            });
        } else this.alertAction(actionObject);

    }

    /**
     * @description Alert the action object 
     * @param {object} actionObject - Details and data about the action.
     */

    alertAction = (actionObject) => {
        Alert.alert(
            'Action',
            JSON.stringify(actionObject.data) + "\ntype: " + actionObject.type,
            [
                { text: "Okay", onPress: () => console.log('OK Pressed') },
            ],
            { cancelable: false }
        )
    }

    /**
     * @description Handler for payload parsing errors(if any)
     * @param {object} errorObject - Details about the error.
     */
    onParseError = (errorObject) => {
        console.log("Error", JSON.stringify(errorObject.message));
    }

    /**
     * @description Toggle the view state between card and its payload.
     */
    toggleJSONView = () => {
        this.setState({
            isJSONVisible: !this.state.isJSONVisible
        })
    }
}

const styles = StyleSheet.create({
    container: {
        padding: 10,
        flex: 1,
        ...Platform.select({
            ios: {
                paddingTop: 50,
                marginBottom: Constants.IosBottomMargin, //Adaptive card starts from 84 pixel so we gave margin bottom as 84. Its purely for our renderer app, it will not impact adaptive card.
            },
            android: {
                marginBottom: Constants.AndroidBottomMargin
            }
        }),
    },
    header: {
        flexDirection: 'row',
        alignItems: 'center',
        justifyContent: 'space-between',
        marginBottom: 10
    },
    title: {
        fontSize: 20,
        flexGrow: 1,
        textAlign: 'center'
    },
    jsonContainer: {
        backgroundColor: '#f7f7f7',
    }
});