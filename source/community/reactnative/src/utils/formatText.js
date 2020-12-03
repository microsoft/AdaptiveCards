import React from 'react';
import {
	Text,
	Linking
} from 'react-native';
import * as Utils from './util';

BOLD_REGEX = /(?:[*]{2})(.*?)(?:[*]{2})/;
ITALIC_REGEX = /(?:[_]{1})(.*?)(?:[_]{1})/;
URL_REGEX = /\]\(((([A-Za-z]{3,9}:(?:\/\/)?)(?:[\-;:&=\+\$,\w]+@)?[A-Za-z0-9\.\-]+|(?:www\.|[\-;:&=\+\$,\w]+@)[A-Za-z0-9\.\-]+)((?:\/[\+~%\/\.\w\-_]*)?\??(?:[\-\+=&;%@\.\w_]*)#?(?:[\.\!\/\\\w]*))?)\)/;
PARENTHESIS_REGEX = /(?:[\()]{1})(.*?)(?:[\)]{1})/;
URL_LINK_REGEX = /\[[^\]]*\]\(\)/;

const KEY_BOLD = "bold";
const KEY_ITALIC = "italic";
const KEY_HYPERLINK = "hyperlink";

let indexToBeStyled = {};
let urlIndexToLinkMapping = {};

export const processMDText = text => {
	if (!text) return undefined;

	let processedMDText = processText(text);
	return processedMDText;
};

/**
 * @description This function processes the markdown elements and returns the TextComponent
 * @param {String} text 
 */
function processText(text) {
	let input = text;
	/**
	 * Identify words that are to be hyperlinked
	 */
	let urlLinks = [];
	let urlIndexes = [];

	while ((matches = URL_REGEX.exec(input)) != null) {
		input = input.replace(matches[1], '');
		let urlMatch = matches[1];
		urlLinks.push(matches[1]);
		if ((matches = URL_LINK_REGEX.exec(input)) != null) {
			let splitArrayURL = input.split(' ');
			let searchText = matches[0].replace(']()', '').replace(/\[/g, '');
			let urlMatchArray = matches[0].split(' ');
			let indexOfFirstWord = splitArrayURL.indexOf(urlMatchArray[0])
			urlMatchArray.forEach((word, index) => {
				let indexToPush = indexOfFirstWord + index;
				urlIndexes.push(indexToPush);
				urlIndexToLinkMapping[indexToPush] = urlMatch;
			})
			input = input.replace(matches[0], searchText);
		}
	}
	indexToBeStyled[KEY_HYPERLINK] = urlIndexes;

	let boldIndexes = [];
	while ((matches = BOLD_REGEX.exec(input)) != null) {
		let splitArrayBold = input.split(' ');
		let boldArray = matches[0].split(' ');
		let indexOfFirstWord = splitArrayBold.indexOf(boldArray[0])
		boldArray.forEach((word, index) => {
			boldIndexes.push(indexOfFirstWord + index);
		})
		input = input.replace(matches[0], matches[1]);
	}
	indexToBeStyled[KEY_BOLD] = boldIndexes;


	/**
	 * Identify words that are to be italicised
	 */
	var italicIndexes = [];

	while ((matches = ITALIC_REGEX.exec(input)) != null) {
		let splitArrayItalic = input.split(' ');
		let italicArray = matches[0].split(' ');
		let indexOfFirstWord = splitArrayItalic.indexOf(italicArray[0]);
		italicArray.forEach((word, index) => {
			italicIndexes.push(indexOfFirstWord + index);
		})
		input = input.replace(matches[0], matches[1]);
	}
	indexToBeStyled[KEY_ITALIC] = italicIndexes;

	/**
	 * Check if the word has to be styled, if not return a simple component
	 * otherwise add appropriate styling to the Text component
	 */
	let resultArray = input.split(' ');
	let combinedIndex = boldIndexes.concat(...italicIndexes, ...urlIndexes);
	let newResult = resultArray.map((eachWord, index) => {
		if (!combinedIndex.includes(index)) {
			return (<Text key={`text_${index}`}>{eachWord + ' '}</Text>);
		}
		else {
			let wordStyle = styleForWordWithIndex(index);
			if (wordStyle.isHyperLink) {
				console.log("isHyperLink", wordStyle.isHyperLink);
				const link = wordStyle.hyperLink;
				text = <Text style={wordStyle.style} key={`text_${index}`}
					onPress={() => Linking.openURL(link)}>
					{eachWord + ' '}
				</Text>
			}
			else {
				text = <Text key={`text_${index}`} style={wordStyle.style}>{eachWord + ' '}</Text>
			}
			return text;
		}
	})
	return newResult;
}

/**
 * @description This function returns the styles to be added for the specific word
 * @param {string} word
 */
function styleForWordWithIndex(wordIndex) {
	let boldStyle = [{ fontWeight: 'bold' }];
	let italicStyle = [{ fontStyle: 'italic' }];
	let hyperLinkStyle = [{ color: 'blue' }];
	let styleForWordWithIndex = {};
	let styles = [];
	let isLink;
	let link = ' ';

	if (!Utils.isNullOrEmpty(indexToBeStyled[KEY_BOLD]) &&
		(indexToBeStyled[KEY_BOLD].indexOf(wordIndex) !== -1)) {
		styles = styles.concat(boldStyle);
		isLink = false;
	}

	if (!Utils.isNullOrEmpty(indexToBeStyled[KEY_ITALIC]) &&
		indexToBeStyled[KEY_ITALIC].indexOf(wordIndex) !== -1) {
		styles = styles.concat(italicStyle);
		isLink = false;
	}

	if (!Utils.isNullOrEmpty(indexToBeStyled[KEY_HYPERLINK]) && indexToBeStyled[KEY_HYPERLINK].indexOf(wordIndex) !== -1) {
		styles = styles.concat(hyperLinkStyle);
		isLink = true;
		link = urlIndexToLinkMapping[wordIndex];
	}

	styleForWordWithIndex = { isHyperLink: isLink, style: styles, hyperLink: link };

	return styleForWordWithIndex;
}

export default processMDText;
