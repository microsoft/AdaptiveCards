/**
 * Markdown Formatter.
 */

import React from 'react';
import {
	StyleSheet,
	Text,
	Linking,
	View
} from 'react-native';
import PropTypes from 'prop-types';

BOLD_REGEX = RegExp('\\*\\*([^*]+)\\*\\*');
ITALIC_REGEX = RegExp('\\_([^_]+)\\_');
HYPERLINK_REGEX = RegExp('\\[([^\\[]+)\\]\\(([^\\)])\\)');
BULLET_REGEX = RegExp('\\-(.*?([a-z|\\s|.|\\d+]+))', 'i');

export default class MarkdownFormatter extends React.Component {

	static displayName = 'MarkdownFormatter';
	matchedIndices = [];
	matchesFound = [];
	matchesStyleTypes = [];
	matchesStyles = [];

	// formatter pattern configs
	MD_FORMATTER_CONFIG = [
		{
			type: 'bold',
			styles: [styles.boldText],
			pattern: '**',
			patternType: 'symmetric',
			groups: 1,
		},
		{
			type: 'italic',
			styles: [styles.italicText],
			pattern: '_',
			patternType: 'symmetric',
			groups: 1,
		},
		{
			type: 'hyperlink',
			styles: [styles.hyperlinkText],
			pattern: '[]()',
			patternType: 'asymmetric',
			groups: 2,
		},
	];

	constructor(props) {
		super(props);

		// props
		this.userStyles = props.defaultStyles;
		this.numberOfLines = props.numberOfLines;
		this.text = props.text;

		this.regexArray = this.MD_FORMATTER_CONFIG;

		// extracted regex
		this.patterns = [];
		this.styles = [];
		this.patternTypes = []
		this.styleTypes = [];

		for (var i = 0; i < this.regexArray.length; i++) {
			let pattern = this.regexArray[i].pattern;
			let patternType = this.regexArray[i].patternType;
			let groups = this.regexArray[i].groups;

			let regexForm = '';
			for (var j = 0; j < pattern.length; j++) {
				regexForm = regexForm + "\\" + pattern[j];
			}
			if (patternType === 'custom') {
				this.patterns[i] = pattern;
			} else if (patternType === "symmetric") {
				this.patterns[i] = RegExp(regexForm + '(.*?)' + regexForm);
			} else {
				// create all group regex
				let part = regexForm.length / groups;
				let regex = "";
				for (var j = 0; j < groups; j++) {
					let group = regexForm.substring(part * j, part * (j + 1));
					let firstHalf = group.substring(0, group.length / 2);
					let secondHalf = group.substring(group.length / 2, group.length);
					let middle = (j < groups / 2) ? group.substring(0, group.length / 2) : group.substring(group.length / 2, group.length);
					regex = regex + firstHalf + '([^' + middle + ']+)' + secondHalf;
				}
				this.patterns[i] = RegExp(regex);
			}
			this.styles[i] = this.regexArray[i].styles;
			this.styleTypes[i] = this.regexArray[i].type;
		}
	}

	render() {
		text = this.text;
		for (var i = 0; i <= this.styleTypes.length - 1; i++) {
			this.parseText(text, this.styleTypes[i], this.styles[i], this.patterns[i]);
		}

		return (
			this.renderText(this.text)
		);
	}

	parseText = (text, type, styles, pattern) => {
		while ((parsed = pattern.exec(text)) !== null) {
			if (type === 'hyperlinkText') {
				let swap = parsed[1];
				parsed[1] = parsed[0];
				parsed[0] = swap;
			}
			this.matchesFound.push(parsed);
			this.matchedIndices.push(parsed.index);
			let spacesToBeAdded = Math.abs(parsed[0].length - parsed[1].length);
			let spacesStr = ""
			for (var i = 0; i < spacesToBeAdded; i++) {
				spacesStr = spacesStr + " ";
			}
			text = text.replace(parsed[0], parsed[1] + spacesStr)
			this.matchesStyleTypes.push(type + "Text");
			this.matchesStyles.push(styles);
		}

		return text;
	}


	renderText = (text) => {
		let jsxArray = [];
		let elementJsxArray = [];
		var elementStylesArray = [];
		let elementLinksArray = [];
		let remainingText = text;
		let processedText = "";

		//arrange matches to process left to right
		let sortedMatchedIndices = [...this.matchedIndices].sort(function (a, b) { return a - b });
		console.log("matchedIndices: " + this.matchedIndices);

		if (this.matchesFound.length < 1) {
			jsxArray.push(
				<Text key={'text'} style={this.userStyles} numberOfLines={this.numberOfLines}>
					{text}
				</Text>
			);
		} else {
			// let lastIdx = -1;
			for (var i = 0; i <= this.matchedIndices.length - 1; i++) {
				if (this.matchesFound[i]) {
					console.log("match : " + this.matchesFound[i]);
					idx = this.matchedIndices.indexOf(sortedMatchedIndices[i]);
					// if(idx === lastIdx){
					//     idx = idx + 1;
					// }
					// lastIdx = idx;

					//check if previous elementJsxArray is or has the current match
					if (i !== 0) {
						let lastIdx = this.matchedIndices.indexOf(sortedMatchedIndices[i - 1]);
						// let containsMatch = this.matchesFound[lastIdx][0].indexOf(this.matchesFound[idx][0]);
						let containsMatch = elementJsxArray[elementJsxArray.length - 1].indexOf(this.matchesFound[idx][0]);
						let containsStyle = elementStylesArray[elementStylesArray.length - 1].indexOf(this.matchesStyleTypes[idx]);
						if (containsMatch !== -1 && containsStyle === -1) {
							let matchedStr = this.matchesFound[idx][0];
							let lastElement = elementJsxArray.pop()
							let modifiedElement = lastElement.replace(matchedStr, "");
							let dividedElements = this.splitValue(lastElement, lastElement.indexOf(matchedStr), matchedStr);
							let lastElementStyles = elementStylesArray.pop();
							if (modifiedElement !== "") {
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
					elementJsxArray.push(this.matchesFound[idx][1]);
					elementStylesArray.push([this.matchesStyleTypes[idx]].concat(this.matchesStyles[idx]));
					if (this.matchesStyleTypes[idx] === 'hyperlinkText') {
						elementLinksArray.push(this.matchesFound[idx][2]);
					} else {
						elementLinksArray.push(null);
					}

					let fromIdx = this.matchesFound[idx].index + this.matchesFound[idx][0].length - processedText.length;
					// if(fromIdx < 0){
					//     continue;
					// }
					remainingText = remainingText.substring(fromIdx, remainingText.length);
					processedText = processedText + beforeMatchStr + this.matchesFound[idx][0];

				}
			}

			//final string
			elementJsxArray.push(remainingText)
			elementStylesArray.push([null]);
			elementLinksArray.push(null);

			jsxArray.push(this.createJsx(elementJsxArray, elementStylesArray, elementLinksArray));
		}
		return <View style={this.userStyles} onLayout={this.props.onDidLayout}>{jsxArray}</View>;
	}

	createJsx = function (elementJsxArray, elementStylesArray, elementLinksArray) {
		// create jsx element 
		var partialJsx = [];
		var fullJsx = [];
		elementJsxArray.map((eachWord, index) => {
			let key = 'text_' + index;

			if (elementStylesArray[index].indexOf('bulletText') !== -1) {
				fullJsx.push(<Text key={key + partialJsx.length} style={this.userStyles} numberOfLines={this.numberOfLines}>{partialJsx}</Text>);

				fullJsx.push(<View key={key} style={this.userStyles}><Text key={'bullet_dot_' + index}>{'\u2022'}</Text><View key={'bullet_view_' + index} style={styles.textBlock}><Text key={'bullet_text_' + index} style={styles.normalText}>{eachWord}</Text></View></View>)

				partialJsx = [];
			} else {
				partialJsx.push(<Text key={key} style={elementStylesArray[index]} onPress={() => this.addOnPress(elementLinksArray[index])}>{eachWord}</Text>)
			}
		});
		if (fullJsx.length === 0) {
			fullJsx = <Text key={'text_' + fullJsx.length + partialJsx.length} style={this.userStyles} numberOfLines={this.numberOfLines}>{partialJsx}</Text>;
		} else if (partialJsx.length !== 0) {
			fullJsx.push(<Text key={'text_' + fullJsx.length + partialJsx.length} style={this.userStyles} numberOfLines={this.numberOfLines}>{partialJsx}</Text>);
		}
		return fullJsx;
	}

	addOnPress = (url) => {
		if (url === null) {
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
		// return (url === null) ? null : Linking.openURL(url).catch(err => console.error('An error occurred', err)); 
	}

	splitValue(str, index, separator) {
		if (str.indexOf(separator) !== -1) {
			return [str.substring(0, index), str.substring(index + separator.length)];
		} else {
			return [str];
		}
	}

};

MarkdownFormatter.propTypes = {
	text: PropTypes.string.isRequired,
	defaultStyles: PropTypes.array.isRequired,
	numberOfLines: PropTypes.number.isRequired,
};

const styles = StyleSheet.create({
	displayText: {
		flexDirection: 'column',
		flexWrap: 'wrap',
	},
	inlineText: {
		flexDirection: 'row',
		flexWrap: 'wrap',
	},

	bulletText: {
		margin: 1,
	},
	textWrapper: {
		flexWrap: 'wrap',
		alignItems: 'flex-start',
		flexDirection: 'row',
	},
	textBlock: {
		flexWrap: 'wrap',
		alignItems: 'flex-start',
		flexDirection: 'row',
		position: 'absolute',
		left: 10
	},
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
