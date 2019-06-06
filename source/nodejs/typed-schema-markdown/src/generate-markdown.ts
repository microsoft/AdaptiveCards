import { defined } from "./defined";
import { defaultValue } from "./defaultValue";
import { SchemaProperty, SchemaClass, SchemaEnum, SchemaPropertyType, SchemaLiteral } from "typed-schema";
import * as mdTable from "markdown-table";
import * as style from "./style";

export function createPropertiesSummary(classDefinition: SchemaClass, knownTypes, autoLink, includeVersion, elementVersion) {
	var md = '';

	var properties = classDefinition.getAllProperties();
    if (properties !== undefined && properties.size > 0) {

        if (includeVersion && defined(elementVersion) && elementVersion != "1.0") {
            md += "#### Introduced in version " + elementVersion + "\n\n";
		}

		var formattedProperties = [];
		
		var needsType = classDefinition.type == "AdaptiveCard";
		if (!needsType) {
			classDefinition.getAllExtended().forEach(extended => {
				if (extended.type == "BlockElement" || extended.type == "Action") {
					needsType = true;
				}
			});
		}

		if (needsType) {
			var formattedTypeProperty:any = {
				Property: "**type**",
				Type: "`\"" + classDefinition.type + "\"`",
				Required: "Yes",
				Description: "Must be `\"" + classDefinition.type + "\"`."
			};

			if (includeVersion) {
				formattedTypeProperty.Version = elementVersion;
			}

			formattedProperties.push(formattedTypeProperty);
		}

        properties.forEach((property, name) => {
			var summary = getPropertySummary(property, knownTypes, autoLink, elementVersion);
			
			var formattedProperty:any = {
				Property: style.propertyNameSummary(name),
				Type: summary.formattedType,
				Required: summary.required,
				Description: summary.description
			};

			// Special case version property on Adaptive Card to be required.
			// It's actually not required in ShowCard, so in schema it's not required,
			// but for docs we want to show it as required
			if (classDefinition.type == "AdaptiveCard" && name == "version") {
				formattedProperty.Required = "Yes";
			}

			if (includeVersion) {
				formattedProperty.Version = summary.version;
			}

			formattedProperties.push(formattedProperty);
		});

		// Data needs to be formatted as follows for use with markdown library
		/*
			table([
			['Branch', 'Commit'],
			['master', '0123456789abcdef'],
			['staging', 'fedcba9876543210']
			])
		*/
		var tableData = [];
		var headerRow = [];
		for (var propName in formattedProperties[0]) {
			headerRow.push(propName);
		}
		tableData.push(headerRow);

		formattedProperties.forEach((formattedProperty) => {
			var dataRow = [];
			for (var propName in formattedProperty) {
				dataRow.push(formattedProperty[propName]);
			}
			tableData.push(dataRow);
		});
		
		// Format as markdown table
		md += mdTable(tableData, {
			pad: false
		});

        md += '\n';
    }

    return md;
}

export function createEnumSummary(enumType: SchemaEnum) {
	var md = '';

	var rows = [ ];

	enumType.values.forEach(val => {
		var row = {
			Value: "`\"" + val.value + "\"`",
			Description: val.description
		};

		rows.push(row);
	});

	// Data needs to be formatted as follows for use with markdown library
	/*
		table([
		['Branch', 'Commit'],
		['master', '0123456789abcdef'],
		['staging', 'fedcba9876543210']
		])
	*/
	var tableData = [];
	var headerRow = [];
	for (var propName in rows[0]) {
		headerRow.push(propName);
	}
	tableData.push(headerRow);

	rows.forEach((row) => {
		var dataRow = [];
		for (var propName in row) {
			dataRow.push(row[propName]);
		}
		tableData.push(dataRow);
	});
	
	// Format as markdown table
	md += mdTable(tableData, {
		pad: false
	});

	md += '\n';

    return md;
}

function getPropertySummary(property: SchemaProperty, knownTypes, autoLink, elementVersion: string) {
	var type:string = property.original.type;
	
	property.shorthands.forEach(shorthand => {
		type += `|${shorthand.original.type}`;
	});

    var formattedType = "`" + replacePipes(type) + "`";

    var description = property.description;

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

            required = 'No, default: ' + defaultString;
        } else {
            required = 'No';
        }
	}
	
	var version = defaultValue(defaultValue(property.original.version, elementVersion), "1.0");
	var topLevelVersion = version;

	var includeShorthandVersions = false;
	property.shorthands.forEach(shorthand => {
		var shorthandVersion = defaultValue(shorthand.original.version, topLevelVersion);
		if (includeShorthandVersions || topLevelVersion != shorthandVersion) {
			version += `, ${shorthandVersion}`;
			includeShorthandVersions = true;
		}
	});

    return {
        type: type,
        formattedType: formattedType,
        description: description,
		required: required,
		version: version
    };
}

function replacePipes(type: string) {
	return type.replace("|", ", ");
}

export function createPropertiesDetails(classDefinition: SchemaClass, headerLevel: number, knownTypes, autoLink, includeVersion: boolean, elementVersion: string) {
    var md = '';

	var properties = classDefinition.getAllProperties();
	properties.forEach((property, name) => {
		md += createPropertyDetails(property, headerLevel, knownTypes, autoLink, includeVersion, elementVersion);
	});

    return md + '\n';
}

export function createPropertyDetails(property: SchemaProperty, headerLevel: number, knownTypes, autoLink, includeVersion: boolean, elementVersion: string) {
    var md = '';

    var summary = getPropertySummary(property, knownTypes, autoLink, elementVersion);
    var type = summary.type;

    md += style.getHeaderMarkdown(property.name, headerLevel) + '\n\n';

    // TODO: Add plugin point for custom JSON schema properties like gltf_*
    var detailedDescription = property.description;
    if (defined(detailedDescription)) {
        md += detailedDescription + '\n';
    } else if (defined(summary.description)) {
        md += summary.description + '\n';
    }

	md += '* ' + style.propertyDetails('Type') + ': ' + summary.formattedType + '\n';
	
	if (includeVersion) {
		if (summary.version != elementVersion) {
			md += `* ${style.propertyDetails("Version")} : ${summary.version}\n`;
		}
	}

    md += '* ' + style.propertyDetails('Required') + ': ' + summary.required + '\n';

    // var minimum = property.minimum;
    // if (defined(minimum)) {
    //     var exclusiveMinimum = (defined(property.exclusiveMinimum) && property.exclusiveMinimum);
    //     md += '* ' + style.propertyDetails('Minimum') + ': ' + style.minMax((exclusiveMinimum ? ' > ' : ' >= ') + minimum) + '\n';
    // }

    // var maximum = property.maximum;
    // if (defined(maximum)) {
    //     var exclusiveMaximum = (defined(property.exclusiveMaximum) && property.exclusiveMaximum);
    //     md += '* ' + style.propertyDetails('Maximum') + ': ' + style.minMax((exclusiveMaximum ? ' < ' : ' <= ') + maximum) + '\n';
    // }

    // var format = property.format;
    // if (defined(format)) {
    //     md += '* ' + style.propertyDetails('Format') + ': ' + format + '\n';
    // }

    // TODO: maxLength
    // var minLength = property.minLength;
    // if (defined(minLength)) {
    //     md += '* ' + style.propertyDetails('Minimum Length') + style.minMax(': >= ' + minLength) + '\n';
	// }
	
	var hasComplexTypes = false;

	var allTypes:SchemaPropertyType[] = property.getAllTypes();
	allTypes.forEach(propertyType => {
		if (propertyType.type instanceof SchemaClass || propertyType.type instanceof SchemaEnum) {
			hasComplexTypes = true;
		}
	});

	if (hasComplexTypes) {
		var allowedValues:string[] = [];
		allTypes.forEach(propertyType => {
			if (propertyType.type instanceof SchemaEnum) {
				propertyType.type.values.forEach(enumValue => {
					if (enumValue.description && enumValue.description.length > 0) {
						allowedValues.push(style.enumValue(enumValue.value) + ": " + enumValue.description);
					} else {
						allowedValues.push(style.enumValue(enumValue.value));
					}
				});
			} else if (propertyType.type instanceof SchemaClass) {
				if (propertyType.type.implementations.length > 0) {
					propertyType.type.implementations.forEach(implementation => {
						allowedValues.push(style.type(implementation.type));
					});
				} else {
					allowedValues.push(style.type(propertyType.type.type));
				}
			} else if (propertyType.type instanceof SchemaLiteral) {
				allowedValues.push(style.type(propertyType.type.type));
			} else {
				throw new Error("Unknown type");
			}
		});
		if (allowedValues.length > 0) {
			md += '* ' + style.propertyDetails('Allowed values') + ':';
			allowedValues.forEach(allowedValue => {
				md += `\n  * ${allowedValue}`;
			});
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