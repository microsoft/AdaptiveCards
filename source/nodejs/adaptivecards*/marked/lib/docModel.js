"use strict"
var defined = require('./defined');
var defaultValue = require('./defaultValue');
var clone = require('./clone');


module.exports = { getModel };

function getModel(schema, toc, defaultObject) {

    var items = [];

    for (var index in toc) {
        var rootObj = toc[index];

        var root = {
            title: getObjectName(rootObj),
            children: []
        };

        for (var childIndex in rootObj[root.title]) {

            var child = {
                name: rootObj[root.title][childIndex]
            };

            var objSchema = schema.definitions[child.name];
            if (objSchema !== undefined) {
                objSchema = resolveInheritance(objSchema);

                if(child.name == "AdaptiveCard") {
                    mergeProperties(objSchema.properties, schema.properties);
                }

                child.title = objSchema.title;
                child.description = defaultValue(objSchema.description, objSchema.title);
                child.properties = objSchema.properties;

                for (var p in child.properties) {
                    child.properties[p].realType = getPropertyType(child.properties[p]);
                }
                root.children.push(child);
            }

        }

        items.push(root);
    }

    return items;
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
    if(type == 'array') {
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