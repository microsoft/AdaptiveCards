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
import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';
import * as Enums from '../../utils/enums';
import * as Utils from '../../utils/util';

export class RichTextBlock extends React.Component {

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
                    <ParagraphElement index={index} numberOfLines={numberOfLines} paragraph={paragraph} thisArg={this} />
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
        let textRunStyle = textRun.underline ? [styles.text, styles.underlineStyle] : [styles.text];
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
                    style={textRunStyle}
                    configManager={this.props.configManager}
                    onClick={() => this.onClickHandle(textRun.selectAction)} />
            </Text>
        );
    }

    /**
     * @description Invoked on tapping the text with action
     * @param {object} selectAction - select action for the text run
     */
    onClickHandle(selectAction) {
        this.onExecuteAction({ ...selectAction });
    }

    /**
     * @description Return the TextRun element from the paragraph 
     * @param {object} paragraph - paragraph from the payload
     * @param {object} setLinks - A function that is called with the complete list of links in this paragraph. Of type {text: string; onClick: () => void}[]
     * @returns {Array} TextRun elements
     */
    getTextRunElements = (paragraph, setLinks) => {
        var textRunElements = [];
        var _links = [];
        paragraph.inlines && paragraph.inlines.forEach((textRun, index) => {
            if (textRun.type.toLowerCase() == Constants.TextRunString) {
                if (textRun.selectAction) {
                    _links.push({ text: textRun.text, onClick: () => { this.onClickHandle(textRun.selectAction) } })
                }

                index > 0 && textRunElements.push(<Text key={"white-sapce-text" + index}>{" "}</Text>);
                let textRunStyle = textRun.highlight ? [styles.text, { backgroundColor: this.props.configManager.hostConfig.richTextBlock.highlightColor }] : [styles.text];
                textRun.underline && textRunStyle.push(styles.underlineStyle);
                textRun.italic && textRunStyle.push(styles.italic);
                textRun.strikethrough && textRunStyle.push(styles.strikethrough);
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
                            configManager={this.props.configManager}
                        />
                );
            }
        });
        setLinks(_links);
        return textRunElements;
    }

    render() {
        if (!this.payload.paragraphs) {
            this.payload.paragraphs = [{ "inlines": this.payload.inlines }];
        }

        return (<InputContextConsumer>
            {({ onExecuteAction }) => {
                this.onExecuteAction = onExecuteAction;
                return <ElementWrapper configManager={this.props.configManager} json={this.payload} style={styles.textContainer} isFirst={this.props.isFirst}>
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
    },
    underlineStyle: {
        textDecorationLine: 'underline',
    },
    italic: {
        fontStyle: 'italic'
    },
    strikethrough: {
        textDecorationLine: 'line-through'
    }
});

/// props: {index: number, numberofLines: number, paragraph: the actual paragraph object, thisArg: 'this' of the parent RichTextBlock component}
function ParagraphElement(props) {
    /// Empty React components just for the purpose of providing screen reader focus to hyperlinks
    /// These are positioned on the lines which contain links using absolute positioning.
    const [accContainers, setAccContainers] = React.useState(undefined);

    /// Ref to List of links: Array of {text: string, onClick: () => void}
    const _links = React.useRef([]);
    /// Function to resolve the promise linksSetPromise
    const _resolveLinksSetPromise = React.useRef(undefined);
    /// Promise that is resolved once we have obtained the list of links.
    const _linksSetPromise = React.useRef(undefined);

    if (!_resolveLinksSetPromise.current) {
        const linksSetPromise = new Promise(function (resolve, reject) {
            _resolveLinksSetPromise.current = resolve;
        });
        _linksSetPromise.current = linksSetPromise;
    }

    function setLinks(links) {
        _links.current = links;
        _resolveLinksSetPromise.current();
    }

    /**
     * Adds the accessibility containers - i.e. empty containers just for bringing screen reader focus.
     * @param {*} lines - {text: string, width: number, height: number, y: number, x: number}[] Obtained from onTextLayout
     * @param {*} links - {text: string, onClick: () => void}[] - Array of an object 
     *  containing the string that was rendered as a link and the function to be called on click.
     */
    function addAccContainers(lines, links) {
        // Stores cumulative length of the ith line (1-indexed -> arr[1] means cumulative length upto 1st line)
        const cumulative_len = [0];
        // Concatenation of all the lines rendered.
        let concatenated_string = '';
        lines.forEach((line, index) => {
            cumulative_len.push(cumulative_len[index] + line.text.length);
            concatenated_string += line.text;
        });

        /// array of JSX.Element
        const _accViews = [];
        /// We are assuming that link is always contained in the concatenated string
        links.forEach((link, index) => {
            const start = concatenated_string.indexOf(link.text);
            const end = start + link.text.length - 1;
            const sIdx = indexLte(cumulative_len, start);
            const eIdx = indexLte(cumulative_len, end);
            const style = { height: lines[eIdx].y - lines[sIdx].y + lines[eIdx].height, width: lines[sIdx].width, position: 'absolute', top: 1 + lines[sIdx].y, left: lines[sIdx].x };

            // The link just spans a single line
            // This is slightly inaccurate, because it assumes each character occupies the same width, but this is the best we can do.
            if (sIdx === eIdx) {
                style.left = lines[sIdx].x + (lines[sIdx].width * (start - cumulative_len[sIdx]) / lines[sIdx].text.length);
                style.width = lines[sIdx].width * (link.text.length) / lines[sIdx].text.length;
            }

            _accViews.push((
                <Text key={"__Acc_View_rtb" + index}
                    style={style}
                    accessibilityLabel={link.text}
                    accessibilityRole='link'
                    accessible={true}
                    onPress={() => { link.onClick() }}>{' '}</Text>));

        });
        setAccContainers(_accViews);
    }
    // NOTE - If any padding/margin is applied to the root Text component, same should be applied to the styles of accessibility containers.
    return (
        <>
            <Text key={"paragraph" + props.index} numberOfLines={props.numberOfLines}
                onTextLayout={(event) => {
                    if (!accContainers) {
                        const lines = event.nativeEvent.lines;
                        _linksSetPromise.current.then(() => {
                            addAccContainers(lines, _links.current);
                        });
                    }
                }}
            >
                {props.thisArg.getTextRunElements(props.paragraph, setLinks)}
            </Text >
            {accContainers}
        </>
    )

}

/// Finds index of the greatest number <= key in an array sorted in increasing order.
function indexLte(array, key) {
    let low = 0;
    let high = array.length - 1;
    while (low < high) {
        const m = Math.floor((low + high) / 2);
        if (key === array[m]) {
            return m;
        } else if (key < array[m]) {
            high = m - 1;
        } else {
            low = m + 1;
        }
    }

    if (array[low] > key) {
        return Math.max(low - 1, 0)
    };

    return low;
}