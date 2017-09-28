"use strict"
var fs = require('fs');
var path = require('path');
var refParser = require('json-schema-ref-parser');
var yaml = require('js-yaml');
var defined = require('../lib/defined');
var defaultValue = require('../lib/defaultValue');
var clone = require('./clone');
var glob = require("glob");

module.exports = buildModel;

function buildModel(options) {

    return new Promise(function (resolve, reject) {

        var rawSchema = JSON.parse(fs.readFileSync(options.schema));
        var toc = yaml.safeLoad(fs.readFileSync(options.toc));
        var rootDefinition = defaultValue(options.rootDefinition, null);

        var items = [];

        refParser.dereference(rawSchema)
            .then(function (schema) {

                for (var index in toc) {
                    var rootObj = toc[index];

                    var root = {
                        title: getObjectName(rootObj),
                        children: []
                    };

                    for (var definitionIndex in rootObj[root.title]) {

                        var name = rootObj[root.title][definitionIndex];
                        var objSchema = schema.definitions[name];
                        if (objSchema === undefined) {
                            console.warn("WARN: Unable to locate schema definition for " + name);
                            continue;
                        }

                        var definition = clone(objSchema);
                        definition.name = name;
                        definition.examples = [];

                        if (objSchema !== undefined) {
                            objSchema = resolveInheritance(objSchema);

                            if (definition.name === rootDefinition) {
                                mergeProperties(objSchema.properties, schema.properties);
                            }

                            definition.title = objSchema.title;
                            definition.description = defaultValue(objSchema.description, objSchema.title);
                            definition.properties = objSchema.properties;

                            if (defined(options.examplesPath)) {
                                definition.examples = glob.sync(path.join(options.examplesPath, "/**/" + definition.name + ".json"), { nocase: false })
                            }

                            for (var name in definition.properties) {
                                if (definition.properties.hasOwnProperty(name)) {
                                    var property = definition.properties[name];
                                    property.name = name;
                                    property.realType = getPropertyType(property);
                                    property.examples = [];
                                    property.required = objSchema.required && objSchema.required.indexOf(name) > -1;

                                    // Get the types of elements allowed in an array
                                    if (property.type === "array") {
                                        if (property.items.anyOf) {
                                            property.itemTypes = property.items.anyOf.map(function (p) {
                                                if (p.properties.type) {
                                                    // Only get the first enum out, but this should be improved later
                                                    return p.properties.type.enum;
                                                }
                                            });
                                        }
                                        else {
                                            var arrayItemProperties = property.items.properties;
                                            if (arrayItemProperties && arrayItemProperties.type) {
                                                property.itemTypes = arrayItemProperties.type.enum;
                                            }
                                        }

                                        if (defined(options.examplesPath)) {
                                            property.examples = glob.sync(path.join(options.examplesPath, "**/" + definition.name + "." + name + ".json"), { nocase: false });
                                        }
                                    }
                                }
                            }
                            root.children.push(definition);
                        }
                    }

                    items.push(root);

                }

                resolve(items);
            })
            .catch(function (err) {
                reject(err);
            });
    });
}



function getObjectName(obj) {
    for (var property in obj)
        return property;
}


function resolveInheritance(derived) {
    if (derived.allOf !== undefined) {
        for (var k in derived.allOf) {
            mergeProperties(derived.properties, derived.allOf[k].properties);
        }
    }

    return derived;
}



/**
* @function mergeProperties
* Recusively takes properties within a schema reference ("the base") and merges the contents of
* those properties into the derived schema.
* @param  {object} derived - The schema that contains a reference to the 'base' schema.
* @param  {object} base - The schema that was being referenced by 'derived'.
* @return {object} The merged schema with the 'base' schema reference removed since the contents
* have been merged into 'derived'.
*/
function mergeProperties(derived, base) {
    for (var name in base) {
        if (base.hasOwnProperty(name)) {
            var baseProperty = base[name];

            // Inherit from the base schema.  The derived joins existing values if it has the same property.
            if (typeof baseProperty === 'object') {
                if (Array.isArray(baseProperty)) {
                    derived[name] = defaultValue(derived[name], []);
                    var cloned = clone(baseProperty, true);
                    derived[name] = derived[name].concat(cloned);
                } else {
                    derived[name] = defaultValue(derived[name], {});
                    var derivedProperty = derived[name];

                    for (var n in baseProperty) {
                        var cloned = clone(baseProperty[n], true);
                        if (baseProperty.hasOwnProperty(n)) {
                            if (defined(derivedProperty[n])) {
                                // Don't overwrite with base?
                                //derivedProperty[n] = Object.assign(derivedProperty[n], cloned);
                                //derivedProperty[n] = cloned;
                            } else {
                                derivedProperty[n] = cloned;
                            }
                        }
                    }
                }
            } else {
                var cloned = clone(baseProperty, true);
                if (!defined(derived[name])) {
                    derived[name] = cloned;
                }
            }
        }
    }
}

/**
 * @function getPropertyType
 * Determines the type of of a property, taking into account that it
 * might be defined within an anyOf property for enum values.
 * @param  {object} schema The schema object that may be of an enum type.
 * @return {string} The type of the enum
 */
function getPropertyType(schema) {
    // For non-anyOf enum types, the type will be a regular property on the object.
    var type = schema.type;

    // string / enums
    var enumValues = schema['enum'];
    if (defined(enumValues)) {
        if (enumValues.length == 1)
            return "**\"" + enumValues[0] + "\"**";
    }

    // arrays
    if (type == 'array') {
        var s = "";
    }

    if (defined(type)) {
        return type;
    }

    // For enums stored using anyOf, we'll need to get it from within anyOf.
    var propertyAnyOf = schema['anyOf'];
    if (!defined(propertyAnyOf)) {
        return undefined;
    }

    // The type will be defined as one of the objects contained within
    // the anyOf property, and the only property within that object with
    // a property name "type" indicating the type of the enum value.
    var length = propertyAnyOf.length;
    for (var i = 0; i < length; ++i) {
        type = propertyAnyOf[i]['type'];;
        if (defined(type)) {
            break;
        }
    }

    return type;
}