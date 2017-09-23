"use strict";
var defined = require('./defined');
var defaultValue = require('./defaultValue');
var style = require('./style');
var clone = require('./clone');
var docModel = require('./docModel');

module.exports = {
    generateMarkdown
};

function generateMarkdown(options) {
 
    var model = docModel.getModel(options.schema, options.toc, options.rootObject);
    
    var md = '';
    // todo Microsoft adaptive card scehma
    md += getTableOfContentsMarkdown(model);
    md += getSchemaMarkdown(model);
    return md;
}

function getSchemaMarkdown(model) {
   var md =  "";

    for (var k in model) {
        var root = model[k];
        md += style.getHeaderMarkdown(root.title, 1);

        for (var c in root.children) {
            var child = root.children[c];
            
            md += style.getSectionMarkdown(child.name, 2);

            md += child.description + "\n\n";
            md += createPropertiesSummary(child.properties) + "\n";
        }
    }
    return md;
}

/**
* @function getTableOfContentsMarkdown
* Print a table of contents indicating (and linking to) all of the types that are documented
* @return {string} The markdown for the table of contents.
*/
function getTableOfContentsMarkdown(model) {
    var md = "";

    for (var k in model) {
        var root = model[k];
        md += root.title + "\n";

        for (var c in root.children) {
            var child = root.children[c];
            md += style.bulletItem(style.getTOCLink(child.name, child.name) + " - " + child.description, 1);
        }

        md += "\n";    
    }


    return md;
}


function createPropertiesSummary(properties, knownTypes, autoLink) {
    var md = '';

    if (properties !== undefined && Object.keys(properties).length > 0) {

        md += '|Property|Type|Required|Description|\n';
        md += '|--------|----|--------|-----------|\n';

        for (var name in properties) {
            if (properties.hasOwnProperty(name)) {
                var property = properties[name];
                var summary = getPropertySummary(property, knownTypes, autoLink);

                md += '|' + style.propertyNameSummary(name) +
                    '|' + summary.formattedType +
                    '|' + (summary.required === 'Yes' ? style.requiredIcon : '') + summary.required +
                    '|' + defaultValue(defaultValue(summary.title, summary.description), '') + '\n';
            }
        }

        md += '\n';
    }

    return md;
}



/**
* @function autoLinkDescription
* This will take a string that describes a type that may potentially reference _other_ types, and then
* automatically add markdown link refences to those other types inline. This is an admittedly simple
* (and potentially buggy) approach to the problem, but seems sufficient.
* @param  {string} description The string that should be auto-linked
* @param  {string[]} knownTypes  Array of known strings that are types that should be auto-linked if found.
* If there are multiple types with the same starting root string, it's imperative that the array is sorted such that the longer names are ordered first.
* @param  {string} autoLink Enum value indicating how the auto-linking should be handled.
* @return {string} The auto-linked description.
*/
function autoLinkDescription(description, knownTypes, autoLink) {
    for (var type in knownTypes) {
        description = style.linkType(description, type, autoLink);
    }

    return description;
}



function getPropertySummary(property, knownTypes, autoLink) {
    var type = defaultValue(property.realType, 'any');
    var formattedType = style.typeValue(type);

    if (type === 'array') {
        var insideBrackets = '';
        if ((defined(property.minItems)) && (property.minItems === property.maxItems)) {
            // Min and max are the same so the array is constant size
            insideBrackets = property.minItems;
        } else if (defined(property.minItems) && defined(property.maxItems)) {
            // Min and max define a range
            insideBrackets = property.minItems + '-' + property.maxItems;
        } else if (defined(property.minItems)) {
            // Only min is defined
            insideBrackets = property.minItems + '-*';
        } else if (defined(property.maxItems)) {
            // Only max is defined
            insideBrackets = '*-' + property.maxItems;
        }

        var arrayInfo = '[' + insideBrackets + ']';

        if (defined(property.items) && defined(property.items.type)) {
            if ((property.items.type === 'object') && defined(property.items.title)) {
                type = property.items.title;
                formattedType = style.linkType(type, type, autoLink) + ' ';

                type += arrayInfo;
                formattedType += style.typeValue(arrayInfo);
            } else {
                type = property.items.type;
                formattedType = style.typeValue(type) + ' ';

                type += arrayInfo;
                formattedType += style.typeValue(arrayInfo);
            }
        } else {
            type += arrayInfo;
            formattedType = style.typeValue(type);
        }
    }

    var description = autoLinkDescription(property.description, knownTypes, autoLink);

    var required;
    if (defined(property.required) && (property.required)) {
        required = 'Yes';
    } else {
        var propertyDefault = property.default;
        if (defined(propertyDefault)) {
            var defaultString;
            if (Array.isArray(propertyDefault)) {
                defaultString = '[' + propertyDefault.toString() + ']';
            } else if (typeof propertyDefault === 'object') {
                defaultString = JSON.stringify(propertyDefault);
            } else {
                defaultString = propertyDefault;
            }

            required = 'No, default: ' + style.defaultValue(defaultString, type);
        } else {
            required = 'No';
        }
    }

    return {
        type: type,
        formattedType: formattedType,
        description: description,
        required: required
    };
}
