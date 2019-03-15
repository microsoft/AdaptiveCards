/**
 * RichTextBlock Element.
 * 
 * Refer https://github.com/Microsoft/AdaptiveCards/issues/1933
 */

import React from 'react';
import {
    StyleSheet,
    Text
} from 'react-native';

import { Label } from './';
import { InputContextConsumer } from '../../utils/context';
import { HostConfigManager } from '../../utils/host-config';
import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';
import * as Enums from '../../utils/enums';
import * as Utils from '../../utils/util';

export class RichTextBlock extends React.Component {

    constructor(props) {
        super(props);
        this.payload = props.json;
    }

    getParagraphElements = () => {
        var paragraphElements = [];
        if (this.payload.paragraphs) {
            this.payload.paragraphs.forEach((paragraph, index) => {
                paragraphElements.push(
                    <Text key={"paragraph" + index}>
                        {this.getTextRunElements(paragraph)}
                    </Text>
                );
            })
        }
        return paragraphElements;
    }

    addActionElement = (selectAction) => {
        return (
            <InputContextConsumer>
                {({ onExecuteAction }) =>
                    <Text onPress={() => { (HostConfigManager.getHostConfig().supportsInteractivity === false) ? null : this.onClickHandle(onExecuteAction, selectAction) }}>
                        <Label
                            text={selectAction.title}
                            size={selectAction.size}
                            weight={selectAction.weight}
                            color={Enums.TextColor.Accent}
                            wrap={selectAction.wrap}
                            align={selectAction.horizontalAlignment}
                            maxLines={selectAction.maxLines}
                            style={styles.text} />
                    </Text>
                }
            </InputContextConsumer>
        );
    }

    /**
	 * @description Invoked on tapping the text with action
	 */
    onClickHandle(onExecuteAction, selectAction) {
        if (selectAction.type === Constants.ActionSubmit) {
            let actionObject = { "type": Constants.ActionSubmit, "data": selectAction.data };
            onExecuteAction(actionObject);
        } else if (selectAction.type === Constants.ActionOpenUrl && !Utils.isNullOrEmpty(selectAction.url)) {
            let actionObject = { "type": Constants.ActionOpenUrl, "url": selectAction.url };
            onExecuteAction(actionObject);
        }
    }

    getTextRunElements = (paragraph) => {
        var textRunElements = [];
        paragraph.inlines.forEach((textRun, index) => {
            if (textRun.type.toLowerCase() == Constants.TextRunString) {
                index > 0 && textRunElements.push(<Text key={"white-sapce-text" + index}>{" "}</Text>);
                let textRunStyle = textRun.highlight ? [styles.text, { backgroundColor: "#FFFF00" }] : styles.text;
                textRunElements.push(
                    <Label
                        key={Constants.TextRunString + index}
                        text={textRun.text}
                        size={textRun.size}
                        weight={textRun.weight}
                        color={textRun.color}
                        isSubtle={textRun.isSubtle}
                        wrap={textRun.wrap}
                        align={textRun.horizontalAlignment}
                        maxLines={textRun.maxLines}
                        style={textRunStyle} />
                );
                textRun.selectAction && textRunElements.push([<Text key={"white-sapce-text-action" + index}>{" "}</Text>, this.addActionElement(textRun.selectAction)]);
            }
        })
        return textRunElements;
    }

    render() {
        return (
            <ElementWrapper json={this.payload} style={styles.textContainer}>
                {this.getParagraphElements()}
            </ElementWrapper>
        );
    }
}

const styles = StyleSheet.create({
    textContainer: {
        width: Constants.FullWidth,
        alignItems: Constants.CenterString,
        backgroundColor: Constants.TransparentString,
    },
    text: {
        width: Constants.FullWidth
    }
});

