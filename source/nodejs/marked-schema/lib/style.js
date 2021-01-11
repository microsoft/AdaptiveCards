"use strict";
var defined = require('./defined');
var defaultValue = require('./defaultValue');
var enums = require('./enums');

module.exports = {
    getHeaderMarkdown: getHeaderMarkdown,

    getSectionMarkdown: getSectionMarkdown,

    getLinkMarkdown: getLinkMarkdown,

    bulletItem: bulletItem,

    /**
    * @function bold
    * Bold the specified string
    * @param  {string} string - The string to be styled
    * @return {string} The string styled as bolded for display in markdown.
    */
    bold: styleBold,

    /**
    * @function type
    * Format the type heading for display in markdown
    * @param  {string} string - The type heading to be styled
    * @return {string} The type heading styled for display in markdown.
    */
    type: styleBold,

    /**
    * @function typeValue
    * Format a typeValue for display in markdown
    * @param  {string} string - The type value to be styled
    * @return {string} The typeValue styled for display in markdown.
    */
    typeValue: styleCode,

    /**
    * @function propertiesSummary
    * Format the summary of properties for display in markdown
    * @param  {string} string - The summary of properties to be styled
    * @return {string} The summary of properties styled for display in markdown.
    */
    propertiesSummary: styleBold,

    /**
    * @function propertyNameSummary
    * Format a property name for display in markdown
    * @param  {string} string - The property name summary to be styled
    * @return {string} The styled property name summary for display in markdown.
    */
    propertyNameSummary: styleBold,

    /**
    * @function propertiesDetails
    * Format the details of properties for display in markdown
    * @param  {string} string - The details of properties to be styled
    * @return {string} The details of properties styled for display in markdown.
    */
    propertiesDetails: styleBold,

    /**
    * @function propertyDetails
    * Format the details of a property for display in markdown
    * @param  {string} string - The property details to be styled
    * @return {string} The property details styled for display in markdown.
    */
    propertyDetails: styleBold,

    /**
    * @function propertyGltfWebGL
    * Format a glTF WebGL property for display in markdown
    * @param  {string} string - The glTF WebGL property to be styled
    * @return {string} The glTF WebGL property styled for display in markdown.
    */
    propertyGltfWebGL: styleBold,

    /**
    * @function defaultValue
    * Format a defaultValue for display in markdown
    * @param  {string} string - The default value
    * @param  {type} string - The type of the default value
    * @return {string} The default value styled for display in markdown.
    */
    defaultValue: styleCodeType,

    /**
    * @function enumElement
    * Format an enumElement for display in markdown
    * @param  {string} string - The enum element to be styled
    * @param  {type} string - The type of the enum element
    * @return {string} The enum element styled for display in markdown.
    */
    enumElement: styleCodeType,

    /**
    * @function minMax
    * Format a minimum or maximum value for display in markdown
    * @param  {int} value - The minimum/maximum value to be styled
    * @return {string} The minimum or maximum value styled for display in markdown.
    */
    minMax: styleCode,

    linkType: linkType,

    getTOCLink: getTOCLink,

    /**
    * @property {string} The markdown string used for displaying the icon used to indicate a value is required.
    */
    requiredIcon: ''
}

const REFERENCE = "schema-";

/**
* @function getHeaderMarkdown
* Gets the markdown syntax for the start of a header.
* @param  {int} level - The header lever that is being requested
* @return {string} The markdown string that should be placed prior to the title of the header
*/
function getHeaderMarkdown(content, level) {
    level = defaultValue(level, 2);

    var md = '';
    for (var i = 0; i < level; ++i) {
        md += '#';
    }

    md += " " + content + "\n\n";
    return md;
}

/**
* @function getSectionMarkdown
* Gets the markdown syntax for the start of a section.
* @param  {string} section - The name of the section
* @param  {int} level - The header lever that is being requested
* @return {string} The markdown string that should be placed as the start of the section
*/
function getSectionMarkdown(section, level) {
    var md = '';

    md += '<a name="' + REFERENCE + section.toLowerCase().replace(/ /g, '-') + '"></a>\n';
    md += getHeaderMarkdown(section, level);

    return md;
}

/**
* @function getSectionMarkdown
* Gets the markdown syntax for a bulleted item.
* @param  {string} item - The item being bulleted.
* @param  {int} indentationLevel - The number of indentation levels that should be applied
* @return {string} The markdown string representing the item as a bulleted item at the proper indentation.
*/
function bulletItem(item, indentationLevel) {
    indentationLevel = defaultValue(indentationLevel, 0);
    return (' '.repeat(indentationLevel * 3)) + '* ' + item + '\n';
}

/**
* @function getLinkMarkdown
* Creates a markdown link
* @param  {string} string - The string to be linked
* @param  {string} link - The link that should be applied to the string
* @return {string} The markdown with the specified string hyperlinked to the specified link.
*/
function getLinkMarkdown(string, link) {
    if ((!defined(string) || string.length === 0)) {
        return '';
    } else if ((!defined(link) || link.length === 0)) {
        return string;
    } else {
        return '[' + string + '](' + link + ')';
    }
}

/**
* @function styleBold
* Returns back a markdown string that bolds the provided string.
* @param  {string} string - The string to be bolded
* @return {string} The bolded string in markdown syntax
*/
function styleBold(string) {
    if (defined(string) && string.length > 0) {
        return '**' + string + '**';
    }

    return '';
}

/**
* @function styleCode
* Returns back a markdown string that displays the provided object as code.
* @param  {object} code - The object to be displayed as code. It might be a string, or a number, or ...
* @param  {string} codeLang - The language for the code. If specified will create a tripple back-tip
* @return {string} The code in markdown code syntax
*/
function styleCode(code, codeLang) {
    if (defined(code)) {
        // The object might be a string or it might be a number or something else.
        // Let's make sure it's a string first.
        var stringified = code.toString();

        if (stringified.length > 0) {
            if (defined(codeLang)) {
                return '```' + codeLang + '\n' + stringified + '```\n'; 
            }
            else {
                return '`' + stringified + '`';
            }
        }
    }

    return '';
}

/**
* @function styleCodeType
* Returns back a markdown string that displays the provided string as code.
* @param  {string} string - The string to be displayed as code
* @param  {string} type - The type of the content in string (if it's a literal string, it will be formatted differently)
* @return {string} The string in markdown code syntax
*/
function styleCodeType(string, type) {
    if (!defined(string) || string.length === 0) {
        return '';
    } else if (type === 'string') {
        return styleCode('"' + string + '"');
    }

    return styleCode(string);
}

/**
* @function linkType
* Finds any occurrence of type in the provided string, and adds a markdown link to it.
* @param  {string} string - The string that might be referencing a type
* @param  {string} type - The type whose reference within string should be linked.
* @param  {string} autoLink - The enum value indicating how the auto-linking should be handled.
* @return {string} The updated string, with any occurrences of the @type string linked via markdown.
*/
function linkType(string, type, autoLink) {
    if (defaultValue(autoLink, enums.autoLinkOption.off) === enums.autoLinkOption.off) {
        return string;
    } else if ((!defined(string) || string.length === 0)) {
        return string;
    } else if ((!defined(type) || type.length === 0)) {
        return string;
    } else {
        var typeLink = '#' + REFERENCE + type.toLowerCase().replace(/ /g, '-');

        if (autoLink === enums.autoLinkOption.aggressive) {
            var regExp = new RegExp('([^`\.]|^)' + type + '([ \.]|$)');
            return string.replace(regExp, "$1" + getLinkMarkdown(styleCode(type), typeLink) + "$2");
        } else {
            var regExp = new RegExp('`' + type + '`');
            return string.replace(regExp, getLinkMarkdown(styleCode(type), typeLink));
        }
    }
}

/**
* @function getTOCLink
* @param  {string} displayString The text to display in the link.
* @param  {string} type          The string to link to.
* @return {string} The markdown for a link with displayString text targeted at type.
*/
function getTOCLink(displayString, type) {
    if ((!defined(displayString) || displayString.length === 0)) {
        return displayString;
    } else if ((!defined(type) || type.length === 0)) {
        return displayString;
    } else {
        var typeLink = '#' + REFERENCE + type.toLowerCase().replace(/ /g, '-');
        return getLinkMarkdown(styleCode(displayString), typeLink);
    }
}
