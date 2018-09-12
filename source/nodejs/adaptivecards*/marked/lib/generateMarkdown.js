"use strict";

var fs = require('fs');
var defined = require('./defined');
var defaultValue = require('./defaultValue');
var style = require('./style');
var clone = require('./clone');
var buildModel = require('./buildModel');

module.exports = {
    generateMarkdown,
    getSchemaMarkdown,
    createPropertiesSummary,
    createPropertiesDetails,
    createPropertyDetails,
    getExampleForProperty
};

function generateMarkdown(options) {
    return new Promise(function (resolve, reject) {

        buildModel(options).then(function (model) {

            var md = '';
            // todo Microsoft adaptive card scehma
            md += getTableOfContentsMarkdown(model);
            md += getSchemaMarkdown(model);

            resolve(md);

        }).catch(function (err) {

            reject(err);

        });
    });
}

function getSchemaMarkdown(model) {
    var md = "";

    for (var k in model) {
        var root = model[k];
        md += style.getHeaderMarkdown(root.title, 1);

        for (var c in root.children) {
            var child = root.children[c];

            md += style.getSectionMarkdown(child.name, 2);

            md += child.description + "\n\n";
            md += createPropertiesSummary(child.properties, null, true, true, child.version) + "\n";

            // TODO: refactor this to be a "summary-only" generation
            //md += createPropertiesDetails(child) + "\n"
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


function createPropertiesSummary(properties, knownTypes, autoLink, includeVersion, elementVersion) {
    var md = '';

    if (properties !== undefined && Object.keys(properties).length > 0) {

        md += '|Property|Type|Required|Description|';
        if(includeVersion) {
            md += 'Version|';
        }
        md += '\n';
        md += '|--------|----|--------|-----------|';
        if(includeVersion) {
            md += '-------|';
        }
        md += '\n';

        for (var name in properties) {
            if (properties.hasOwnProperty(name)) {
                var property = properties[name];
                var summary = getPropertySummary(property, knownTypes, autoLink);

                md += '|' + style.propertyNameSummary(name) +
                    '|' + summary.formattedType +
                    '|' + (summary.required === 'Yes' ? style.requiredIcon : ' ') + summary.required +
                    '|' + defaultValue(defaultValue(summary.title, summary.description), '&nbsp;');

                if(includeVersion) {
                    md += '|' +  defaultValue(defaultValue(property.version, elementVersion), "1.0");
                }

                md += '\n';
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

        // Custom logic to calculate the types of items in the array
        if (property.itemTypes) {
            // Split on . so Action.Submit => Action
            var t = property.itemTypes[0];
            if (property.itemTypes.length > 1 && t[0].indexOf(".") > -1) {
                t = t[0].split(".")[0];
            }
            formattedType = "`" + t + "[]`";
        } else {
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


function createPropertiesDetails(schema, headerLevel, knownTypes, autoLink) {
    var md = '';

    var properties = schema.properties;
    for (var name in properties) {
        if (properties.hasOwnProperty(name)) {
            var property = properties[name];
            md += createPropertyDetails(property, headerLevel, knownTypes, autoLink);
        }
    }

    return md + '\n';
}

function createPropertyDetails(property, headerLevel, knownTypes, autoLink) {
    var md = '';

    var summary = getPropertySummary(property, knownTypes, autoLink);
    var type = summary.type;

    md += style.getHeaderMarkdown(property.name, headerLevel) + (summary.required === 'Yes' ? style.requiredIcon : '') + '\n\n';

    // TODO: Add plugin point for custom JSON schema properties like gltf_*
    var detailedDescription = autoLinkDescription(property.gltf_detailedDescription, knownTypes, autoLink);
    if (defined(detailedDescription)) {
        md += detailedDescription + '\n';
    } else if (defined(summary.description)) {
        md += summary.description + '\n';
    }

    md += '* ' + style.propertyDetails('Type') + ': ' + summary.formattedType + '\n';

    var uniqueItems = property.uniqueItems;
    if (defined(uniqueItems) && uniqueItems) {
        md += '   * Each element in the array must be unique.\n';
    }

    // TODO: items is a full schema
    var items = property.items;
    if (defined(items)) {
        var itemsExclusiveMinimum = (defined(items.exclusiveMinimum) && items.exclusiveMinimum);
        var minString = itemsExclusiveMinimum ? 'greater than' : 'greater than or equal to';

        var itemsExclusiveMaximum = (defined(items.exclusiveMaximum) && items.exclusiveMaximum);
        var maxString = itemsExclusiveMaximum ? 'less than' : 'less than or equal to';

        if (defined(items.minimum) && defined(items.maximum)) {
            md += '   * Each element in the array must be ' + minString + ' ' + style.minMax(items.minimum) + ' and ' + maxString + ' ' + style.minMax(items.maximum) + '.\n';
        } else if (defined(items.minimum)) {
            md += '   * Each element in the array must be ' + minString + ' ' + style.minMax(items.minimum) + '.\n';
        } else if (defined(items.maximum)) {
            md += '   * Each element in the array must be ' + maxString + ' ' + style.minMax(items.maximum) + '.\n';
        }

        if (defined(items.minLength) && defined(items.maxLength)) {
            md += '   * Each element in the array must have length between ' + style.minMax(items.minLength) + ' and ' + style.minMax(items.maxLength) + '.\n';
        } else if (defined(items.minLength)) {
            md += '   * Each element in the array must have length greater than or equal to ' + style.minMax(items.minLength) + '.\n';
        } else if (defined(items.maxLength)) {
            md += '   * Each element in the array must have length less than or equal to ' + style.minMax(items.maxLength) + '.\n';
        }

        var itemsString = getEnumString(items, type, 3);
        if (defined(itemsString)) {
            md += '   * Each element in the array must be one of the following values:\n' + itemsString;
        }
    }

    md += '* ' + style.propertyDetails('Required') + ': ' + summary.required + '\n';

    var minimum = property.minimum;
    if (defined(minimum)) {
        var exclusiveMinimum = (defined(property.exclusiveMinimum) && property.exclusiveMinimum);
        md += '* ' + style.propertyDetails('Minimum') + ': ' + style.minMax((exclusiveMinimum ? ' > ' : ' >= ') + minimum) + '\n';
    }

    var maximum = property.maximum;
    if (defined(maximum)) {
        var exclusiveMaximum = (defined(property.exclusiveMaximum) && property.exclusiveMaximum);
        md += '* ' + style.propertyDetails('Maximum') + ': ' + style.minMax((exclusiveMaximum ? ' < ' : ' <= ') + maximum) + '\n';
    }

    var format = property.format;
    if (defined(format)) {
        md += '* ' + style.propertyDetails('Format') + ': ' + format + '\n';
    }

    // TODO: maxLength
    var minLength = property.minLength;
    if (defined(minLength)) {
        md += '* ' + style.propertyDetails('Minimum Length') + style.minMax(': >= ' + minLength) + '\n';
    }

    var enumString = getEnumString(property, type, 1);
    if (defined(enumString)) {
        md += '* ' + style.propertyDetails('Allowed values') + ':\n' + enumString;
    }

    var additionalProperties = property.additionalProperties;
    if (defined(additionalProperties) && (typeof additionalProperties === 'object')) {
        var additionalPropertiesType = getPropertyType(additionalProperties);
        if (defined(additionalPropertiesType)) {
            // TODO: additionalProperties is really a full schema
            var formattedType = style.typeValue(additionalPropertiesType)
            if ((additionalProperties.type === 'object') && defined(property.title)) {
                formattedType = style.linkType(property.title, property.title, autoLink);
            }

            md += '* ' + style.propertyDetails('Type of each property') + ': ' + formattedType + '\n';
        }
    }

    // TODO: fix adding samples later
    // property.examples.forEach(function (example, i) {
    //     if (i == 0) {
    //         md += "\n" + style.getHeaderMarkdown("Example", 3);
    //     }

    //     md += getExampleForProperty(example);
    // });


    return md + '\n';
}

function getExampleForProperty(example) {

    var exampleContent = fs.readFileSync(example, "utf8");
    // TODO: Support other types of example languages
    return style.typeValue(exampleContent, "json");
}

/**
 * @function getEnumString
 * Gets the string describing the possible enum values.
 * Will try getting the information from the enum/gltf_enumNames properties, but if they don't exist,
 * it will fall back to trying to get the values from the anyOf object.
 * @param  {object} schema The schema object that may be of an enum type.
 * @param  {string} type The name of the object type for the enum values (e.g. string, integer, etc..)
 * @param  {integer} depth How deep the bullet points for enum values should be.  Maximum is 2.
 * @return {string} A string that enumerates all the possible enum values for this schema object.
 */
function getEnumString(schema, type, depth) {
    var propertyEnum = schema['enum'];
    if (!defined(propertyEnum)) {
        // It's possible that the enum value is defined using the anyOf construct instead.
        return getAnyOfEnumString(schema, type, depth);
    }

    var propertyEnumNames = schema['gltf_enumNames'];

    var allowedValues = '';
    var length = propertyEnum.length;
    for (var i = 0; i < length; ++i) {
        var element = style.enumElement(propertyEnum[i], type);
        if (defined(propertyEnumNames)) {
            element += " " + propertyEnumNames[i];
        }

        allowedValues += style.bulletItem(element, depth);
    }
    return allowedValues;
}

/**
 * @function getAnyOfEnumString
 * Gets the string describing the possible enum values, if they are defined within a JSON anyOf object.
 * @param  {object} schema The schema object that may be of an enum type.
 * @param  {string} type The name of the object type for the enum values (e.g. string, integer, etc..)
 * @param  {integer} depth How deep the bullet points for enum values should be.  Maximum is 2.
 * @return {string} A string that enumerates all the possible enum values for this schema object.
 */
function getAnyOfEnumString(schema, type, depth) {
    var propertyAnyOf = schema['anyOf'];
    if (!defined(propertyAnyOf)) {
        return undefined;
    }

    var allowedValues = '';
    var length = propertyAnyOf.length;
    for (var i = 0; i < length; ++i) {
        var element = propertyAnyOf[i];
        var enumValue = element['enum'];
        var enumDescription = element['description'];

        // The likely scenario when there's no enum value is that it's the object
        // containing the _type_ of the enum.  Otherwise, it should be an array with
        // a single value in it.
        if (!defined(enumValue) || !Array.isArray(enumValue) || enumValue.length === 0) {
            continue;
        }

        var enumString = style.enumElement(enumValue[0], type);
        if (defined(enumDescription)) {
            enumString += " " + enumDescription;
        }

        allowedValues += style.bulletItem(enumString, depth);
    }

    return allowedValues;
}
