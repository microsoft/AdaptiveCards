/**
 * Markdown Formatter for text.
 */

import React from 'react';
import {
	StyleSheet,
	Text,
	Linking
} from 'react-native';
import PropTypes from 'prop-types';

let SPECIAL_CHAR_REGEX = new RegExp("[^a-z\\\\s\\d]", 'gi');

export default class MarkdownFormatter extends React.PureComponent {
	matchedIndices = [];
	matchesFound = [];
	matchesStyleTypes = [];
	matchesStyles = [];

	text = '';
	patterns = [];
	styles = [];
	styleTypes = [];

	// regex configs for supported markdowns
	MD_FORMATTER_CONFIG = [
		{
			type: 'numbered',
			styles: [],
			pattern: ['^\\d+\.\\s+(.*)'],
			patternType: 'custom',
			groups: 1,
		},
		{
			type: 'numbered',
			styles: [],
			pattern: ['[\\r,\\n]\\d+\.\\s+(.*)'],
			patternType: 'custom',
			groups: 1,
		},
		{
			type: 'bullet',
			styles: [],
			pattern: ['^-\\s+(.*)'],
			patternType: 'custom',
			groups: 1,
		},
		{
			type: 'bullet',
			styles: [],
			pattern: ['[\\n,\\r]-\\s+(.*)'],
			patternType: 'custom',
			groups: 1,
		},
		{
			type: 'bold',
			styles: [styles.boldText],
			pattern: ['**'],
			patternType: 'symmetric',
			groups: 1,
		},
		{
			type: 'italic',
			styles: [styles.italicText],
			pattern: ['_'],
			patternType: 'symmetric',
			groups: 1,
		},
		{
			type: 'hyperlink',
			styles: [styles.hyperlinkText],
			pattern: ['[]()'],
			patternType: 'asymmetric',
			groups: 2,
		},
	];

	constructor(props) {
		super(props);

		this.numberOfLines = props.numberOfLines;
		this.userStyles = props.defaultStyles;
		this.text = props.text;
		this.regexArray = this.MD_FORMATTER_CONFIG;

		this.init();
	}

	render() {
		this.preprocessor();

		for (var i = 0; i <= this.styleTypes.length - 1; i++) {
			this.parseText(this.styleTypes[i], this.styles[i], this.patterns[i]);
		}

		return (
			this.renderText(this.text)
		);
	}

	/**
	 * @description Initialize the regex patterns based on the configs
	 */
	init() {
		for (var i = 0; i < this.regexArray.length; i++) {
			let pattern = this.regexArray[i].pattern;
			let patternType = this.regexArray[i].patternType;
			let groups = this.regexArray[i].groups;

			switch (patternType) {
				case 'start-end':
					pattern = pattern[0].replace(SPECIAL_CHAR_REGEX, "\\$&") + '(?= )(.*?)' + pattern[1].replace(SPECIAL_CHAR_REGEX, "\\$&");
					break;
				case 'symmetric':
					pattern = pattern[0].replace(SPECIAL_CHAR_REGEX, "\\$&") + '(.*?)' + pattern[0].replace(SPECIAL_CHAR_REGEX, "\\$&");
					break;
				case 'asymmetric':
					pattern = pattern[0].replace(SPECIAL_CHAR_REGEX, "\\$&");
					let regexForm = '';
					p = this.regexArray[i].pattern[0];
					for (var j = 0; j < p.length; j++) {
						regexForm = regexForm + "\\" + p[j];
					}
					// create all group regex
					let part = regexForm.length / groups;
					let regex = "";
					for (var j = 0; j < groups; j++) {
						let group = regexForm.substring(part * j, part * (j + 1));
						let middleIndex = group.length / 2;
						let firstHalf = group.substring(0, middleIndex);
						let secondHalf = group.substring(middleIndex, group.length);
						let middle = (j < middleIndex) ? group.substring(0, middleIndex) : group.substring(middleIndex, group.length);
						regex = regex + firstHalf + '([^' + middle + ']+)' + secondHalf;
					}
					pattern = regex;
					break;
				case 'custom':
				default:
					pattern = pattern[0];
					break;
			}

			this.patterns.push(RegExp(pattern, 'ig'));
			this.styles.push(this.regexArray[i].styles);
			this.styleTypes.push(this.regexArray[i].type);
		}
	}

	/**
	 * @description Process the input text for any non-matching (\n or \r) pattern for list-item markdown.
	 * 				This would remove the newline characters (\n or \r) which doesn't match the list-item regexp.
	 * 				This is required without which <Text/> renders new lines for non-matching scenarios too.
	 */
	preprocessor = () => {
		// non-matching strings are captured with the help of (?!) negative lookahead
		let unorderedRegExp = new RegExp('[\\n\\r](?!-\\s)(.*)', 'igm');
		let orderedRegExp = new RegExp('[\\n\\r](?!\\d.\\s)(.*)', 'igm');

		// holds the strings that begin with (\n or \r) that neither match unordered nor ordered patters.
		let matched = [];

		while ((parsed = unorderedRegExp.exec(this.text)) !== null) {
			var resultString = parsed[0];
			var matchedOrdered = resultString.match(orderedRegExp);
			if (matchedOrdered) {
				matched.push(parsed);
			}
		}

		// slice the new line character and update the text
		matched.forEach(value => {
			if (this.text[value.index] === '\n' || this.text[value.index] === '\r') {
				this.text = this.text.slice(0, value.index) + " " + this.text.slice(value.index + 1);
			}
		});
	}

	/**
	 * @description This function find the matches and perform any removal / addition of characters
	 * 				according to the markdown. 
	 * 				Example: Remove ** for bold; Add bullet / tab for list-item;
	 * @param {string} type - Type of the markdown config
	 * @param {object} styles - Style object of correspoding type
	 * @param {RegExp} pattern - RegExp to match
	 */
	parseText = (type, styles, pattern) => {
		let text = this.text;

		while ((parsed = pattern.exec(text)) !== null) {
			this.matchedIndices.push(parsed.index);
			let spacesToBeAdded = Math.abs(parsed[0].length - parsed[1].length);
			let spacesStr = ""

			for (var i = 0; i < spacesToBeAdded; i++) {
				spacesStr = spacesStr + " ";
			}
			this.text = text.replace(parsed[0], parsed[1] + spacesStr)
			this.matchesStyleTypes.push(type + "Text");
			this.matchesStyles.push(styles);

			if (type === 'bullet') {
				parsed[1] = '\t\u2022\t' + parsed[1];
			} else if (type === 'numbered') {
				var regex = /\d+\.\s+/i;
				parsed[1] = parsed[0].replace(regex, '\t$&\t');
			}
			this.matchesFound.push(parsed);
		}
	}

	/**
	 * @description Determine the text strings / styles and return the generated elements/
	 * @returns {Array} jsxArray - Array of created text elements
	 */
	renderText = () => {

		let jsxArray = [];
		let elementJsxArray = [];
		var elementStylesArray = [];
		let elementLinksArray = [];
		let remainingText = this.text;
		let processedText = "";

		//arrange matches to process left to right
		let sortedMatchedIndices = [...this.matchedIndices].sort(function (a, b) { return a - b });

		if (this.matchesFound.length < 1) {
			jsxArray.push(
				<Text key={'text'} style={this.userStyles} numberOfLines={this.numberOfLines}>
					{remainingText}
				</Text>
			);
		} else {
			// let lastIdx = -1;
			for (var i = 0; i <= this.matchedIndices.length - 1; i++) {
				if (this.matchesFound[i]) {
					idx = this.matchedIndices.indexOf(sortedMatchedIndices[i]);

					//check if previous elementJsxArray is or has the current match
					let lastIdx = this.matchedIndices.indexOf(sortedMatchedIndices[i - 1]);
					if (i !== 0) {
						if (idx === lastIdx) {
							idx = this.findNthIndexOfElement(this.matchedIndices, sortedMatchedIndices[i], 2);
						}
						let containsMatch = elementJsxArray[elementJsxArray.length - 1].indexOf(this.matchesFound[idx][0]);
						let isMatch = elementJsxArray[elementJsxArray.length - 1] === (this.matchesFound[idx][1]);
						let containsStyle = elementStylesArray[elementStylesArray.length - 1].indexOf(this.matchesStyleTypes[idx]);
						if ((containsMatch !== -1 && containsStyle === -1) || (isMatch && containsStyle === -1)) {
							let matchedStr = this.matchesFound[idx][0];
							let lastElement = elementJsxArray.pop()
							let modifiedElement = lastElement.replace(matchedStr, "");
							let dividedElements = this.splitValue(lastElement, lastElement.indexOf(matchedStr), matchedStr);
							let lastElementStyles = elementStylesArray.pop();
							if (modifiedElement !== "" && !isMatch) {
								elementJsxArray.push(dividedElements[0]);
								elementStylesArray.push(lastElementStyles);
								if (lastElementStyles.indexOf('hyperlinkText') !== -1) {
									elementLinksArray.push(this.matchesFound[lastIdx][2]);
								} else {
									elementLinksArray.push(null);
								}
							}
							elementJsxArray.push(this.matchesFound[idx][1]);
							let elementStyle = [this.matchesStyleTypes[idx]];
							elementStyle = elementStyle.concat(this.matchesStyles[idx]);
							elementStylesArray.push(elementStyle.concat(lastElementStyles));

							if (dividedElements.length > 1) {
								elementJsxArray.push(dividedElements[1]);

								elementStylesArray.push(lastElementStyles);

								if (lastElementStyles.indexOf('hyperlinkText') !== -1) {
									elementLinksArray.push(this.matchesFound[lastIdx][2]);
								} else {
									elementLinksArray.push(null);
								}
							}
							continue;
						}
					}

					// string before match
					let uptoIdx = this.matchesFound[idx].index - processedText.length;
					if (uptoIdx < 0) {
						continue;
					}
					let beforeMatchStr = remainingText.substring(0, uptoIdx);
					elementJsxArray.push(beforeMatchStr);
					elementStylesArray.push([null]);
					elementLinksArray.push(null);

					// matched string
					if (this.matchesStyleTypes[idx] === 'numberedText') {
						elementJsxArray.push(this.matchesFound[idx][1]);
					} else {
						elementJsxArray.push(this.matchesFound[idx][1]);
					}
					elementStylesArray.push([this.matchesStyleTypes[idx]].concat(this.matchesStyles[idx]));
					if (this.matchesStyleTypes[idx] === 'hyperlinkText') {
						elementLinksArray.push(this.matchesFound[idx][2]);
					} else {
						elementLinksArray.push(null);
					}

					let fromIdx = this.matchesFound[idx].index + this.matchesFound[idx][0].length - processedText.length;
					remainingText = remainingText.substring(fromIdx, remainingText.length);
					processedText = processedText + beforeMatchStr + this.matchesFound[idx][0];
				}
			}

			elementJsxArray.push(remainingText);
			elementStylesArray.push([null]);
			elementLinksArray.push(null);

			jsxArray.push(this.createJsx(elementJsxArray, elementStylesArray, elementLinksArray));
		}
		return jsxArray;
	}

	/**
	 * @description Create the actual <Text/> elements
	 * @returns {Array} fullJsx - Array of created elements
	 */
	createJsx = function (elementJsxArray, elementStylesArray, elementLinksArray) {
		// create jsx element 
		var tempJSX = [];
		var partialJsx = [];
		var WrapJsx = [];
		var fullJsx = [];
		elementJsxArray.map((eachWord, index) => {
			let key = 'text_' + index;

			if (elementStylesArray[index].indexOf('bulletText') !== -1 || elementStylesArray[index].indexOf('numberedText') !== -1) {
				tempJSX.push(<Text key={'list_item_' + index} style={[this.userStyles.concat(elementStylesArray[index])]}>{eachWord}</Text>)
			} else {
				tempJSX.push(<Text key={key} style={[elementStylesArray[index]]} onPress={() => this.addOnPress(elementLinksArray[index])}>{eachWord}</Text>)
			}
		});

		elementJsxArray.map((eachWord, index) => {
			let key = 'text__' + index;
			if (elementStylesArray[index].indexOf('bulletText') !== -1) {
				if (WrapJsx.length !== 0) {
					fullJsx.push(<Text key={key + WrapJsx.length + "wrap_list"} style={this.userStyles} >{WrapJsx}</Text>);
					WrapJsx = [];
				}
				partialJsx.push(tempJSX[index]);

			} else {
				if (partialJsx.length !== 0) {
					fullJsx.push(<Text key={key + "_list"} style={this.userStyles}><Text key={key + partialJsx.length + "_list"}>{partialJsx}</Text></Text>);
					partialJsx = [];
				}
				if (eachWord.trim() != "")
					WrapJsx.push(tempJSX[index]);
			}
		});

		if (fullJsx.length === 0) {
			fullJsx = <Text key={'text_' + fullJsx.length + tempJSX.length} style={this.userStyles} numberOfLines={this.numberOfLines}>{tempJSX}</Text>;
		} else if (WrapJsx.length !== 0) {
			fullJsx.push(<Text key={'text_' + fullJsx.length + WrapJsx.length} style={this.userStyles} numberOfLines={this.numberOfLines}>{WrapJsx}</Text>);
		}
		return fullJsx;
	}

	/**
	 * @description This open the link in default browser.
	 * @param {string} url - URL provided in the link markdown.
	 */
	addOnPress = (url) => {
		if (!url) {
			//Check for rich-text-block textRun action
			if (this.props.onClick) {
				this.props.onClick()
			}
			return null;
		} else {
			Linking.canOpenURL(url).then(supported => {
				if (!supported) {
					console.log('Can\'t handle url: ' + url);
					return null;
				} else {
					return Linking.openURL(url);
				}
			}).catch(err => console.error('An error occurred', err));
		}
	}

	/**
	 * @description Split the given string based on the starting index and delimiter.
	 * @param {string} str - Input string
	 * @param {number} index - Starting index for split
	 * @param {string} separator - Separator
	 * 
	 * @return {Array}
	 */
	splitValue(str, index, separator) {
		if (str.indexOf(separator) !== -1) {
			return [str.substring(0, index), str.substring(index + separator.length)];
		} else {
			return [str];
		}
	}

	/**
     * @description Finds the nth Index for Fact key and column value.
	 * @param {Array} arr - Input array
	 * @param {} - element
	 * @param {number} nthIndex
	 * 
	 * @return {number} index
     */
	findNthIndexOfElement(arr, element, nthIndex) {
		var index = -1;
		for (var i = 0, len = arr.length; i < len; i++) {
			if (i in arr && element === arr[i] && !--nthIndex) {
				index = i;
				break;
			}
		}
		return index;
	};
};

MarkdownFormatter.propTypes = {
	text: PropTypes.string.isRequired,
	defaultStyles: PropTypes.array,
	numberOfLines: PropTypes.number.isRequired,
};

const styles = StyleSheet.create({
	hyperlinkText: {
		color: 'blue',
		textDecorationLine: 'underline',
	},
	boldText: {
		fontWeight: 'bold',
	},
	italicText: {
		fontStyle: 'italic',
	},
});