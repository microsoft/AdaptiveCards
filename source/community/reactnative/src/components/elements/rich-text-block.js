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
import {
    InputContext,
    InputContextConsumer
} from '../../utils/context';
import { HostConfigManager } from '../../utils/host-config';
import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';
import * as Enums from '../../utils/enums';
import * as Utils from '../../utils/util';

export class RichTextBlock extends React.Component {

    hostConfig = HostConfigManager.getHostConfig();
    static contextType = InputContext;

    constructor(props) {
        super(props);
        this.payload = props.json;
        this.onExecuteAction = undefined;
    }

    /**
     * @description Return the paragraph element from the payload 
     * @returns {Array} Paragraph elements
     */
    getParagraphElements = () => {
        //Applying wrap and maxLines property for the paragraph
        let { wrap, maxLines } = this.payload;
        let numberOfLines = wrap ? (maxLines != undefined ? maxLines : 0) : 1;
        var paragraphElements = [];
        if (this.payload.paragraphs) {
            this.payload.paragraphs.forEach((paragraph, index) => {
                paragraphElements.push(
                    <Text key={"paragraph" + index} numberOfLines={numberOfLines}>
                        {this.getTextRunElements(paragraph)}
                    </Text >
                );
            })
        }
        return paragraphElements;
    }

    /**
     * @description Return the paragraph element from the payload 
     * @param {object} textRun - text run in the paragraph
     * @returns {object} constructed select Action component
     */
    addActionElement = (textRun, index) => {
        return (
            <Text key={"text-wrapper" + index} onPress={() => { this.onClickHandle(textRun.selectAction) }}>
                <Label
                    text={textRun.text}
                    size={textRun.size}
                    weight={textRun.weight}
                    color={Enums.TextColor.Accent}
                    isSubtle={textRun.isSubtle}
                    wrap={textRun.wrap}
                    align={textRun.horizontalAlignment}
                    maxLines={textRun.maxLines}
                    style={styles.text}
                    onClick={() => this.onClickHandle(textRun.selectAction)} />
            </Text>
        );
    }

    /**
     * @description Invoked on tapping the text with action
     * @param {object} selectAction - select action for the text run
     */
    onClickHandle(selectAction) {
        if (selectAction.type === Constants.ActionSubmit) {
            let actionObject = { "type": Constants.ActionSubmit, "data": selectAction.data };
            this.onExecuteAction(actionObject);
        } else if (selectAction.type === Constants.ActionOpenUrl && !Utils.isNullOrEmpty(selectAction.url)) {
            let actionObject = { "type": Constants.ActionOpenUrl, "url": selectAction.url };
            this.onExecuteAction(actionObject);
        }
    }

    /**
     * @description Return the TextRun element from the paragraph 
     * @param {object} paragraph - paragraph from the payload
     * @returns {Array} TextRun elements
     */
    getTextRunElements = (paragraph) => {
        var textRunElements = [];
        paragraph.inlines && paragraph.inlines.forEach((textRun, index) => {
            if (textRun.type.toLowerCase() == Constants.TextRunString) {
                index > 0 && textRunElements.push(<Text key={"white-sapce-text" + index}>{" "}</Text>);
                let textRunStyle = textRun.highlight ? [styles.text, { backgroundColor: this.hostConfig.richTextBlock.highlightColor }] : styles.text;
                textRunElements.push(
                    textRun.selectAction ? this.addActionElement(textRun, index) :
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
                            style={textRunStyle}
                        />
                );
            }
        })
        return textRunElements;
    }

    render() {
        return (<InputContextConsumer>
            {({ onExecuteAction }) => {
                this.onExecuteAction = onExecuteAction;
                return <ElementWrapper json={this.payload} style={styles.textContainer} isFirst={this.props.isFirst}>
                    {this.getParagraphElements()}
                </ElementWrapper>
            }}
        </InputContextConsumer>);
    }
}

const styles = StyleSheet.create({
    textContainer: {
        width: Constants.FullWidth,
        backgroundColor: Constants.TransparentString,
    },
    text: {
        width: Constants.FullWidth
    }
});

