// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { defined } from "./defined";
import { defaultValue } from "./defaultValue";
import { SchemaClass } from "../SchemaClass";
import { SchemaEnum } from "../SchemaEnum";
import { SchemaLiteral } from "../SchemaLiteral";
import { SchemaProperty } from "../SchemaProperty";
import { SchemaPropertyType } from "../SchemaPropertyType";
import * as mdTable from "markdown-table";
import * as style from "./style";

export function createPropertiesSummary(classDefinition: SchemaClass, knownTypes, autoLink, includeVersion, elementVersion) {
	var md = '';

	var properties: Map<string, SchemaProperty> = classDefinition.getAllProperties();
	if (properties !== undefined && properties.size > 0) {

		// Re-order so that required properties are up front
		// (Otherwise if there's an inherited required property, it'll be at bottom)
		properties = sortProperties(properties);

		if (includeVersion && defined(elementVersion) && elementVersion != "1.0") {
			md += "**Introduced in version " + elementVersion + "**\n\n";
		}

		var formattedProperties = [];

		var needsType = classDefinition.type == "AdaptiveCard";
		if (!needsType) {
			classDefinition.getAllExtended().forEach(extended => {
				if (extended.type == "Element"
					|| extended.type == "Action"
					|| extended.type == "Inline") {
					needsType = true;
				}
			});
		}

		if (needsType) {
			var formattedTypeProperty: any = {
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

		var firstInheritedFormattedProperty: any;

		properties.forEach((property, name) => {
			var summary = getPropertySummary(property, knownTypes, autoLink, elementVersion);

			var formattedProperty: any = {
				Property: style.propertyNameSummary(name),
				Type: summary.formattedType,
				Required: summary.required,
				Description: summary.description
			};

			// If we haven't reached the start of the inherited properties...
			// Note that inherited required properties are moved up to the front
			if (!firstInheritedFormattedProperty && !property.required && !classDefinition.properties.has(property.name)) {
				firstInheritedFormattedProperty = formattedProperty;
			}

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

		var mainFormattedProperties = [];
		var inheritedFormattedProperties = [];
		var reachedInherited = false;

		formattedProperties.forEach((formattedProperty) => {
			if (reachedInherited || formattedProperty == firstInheritedFormattedProperty) {
				reachedInherited = true;
				inheritedFormattedProperties.push(formattedProperty);
			} else {
				mainFormattedProperties.push(formattedProperty);
			}
		});

		// Format as markdown table
		if (mainFormattedProperties.length > 0) {
			md += createTable(mainFormattedProperties);
			md += '\n';
		}

		if (inheritedFormattedProperties.length > 0) {
			md += "\n### Inherited properties\n\n";
			md += createTable(inheritedFormattedProperties);
			md += "\n";
		}
	}

	return md;
}

function createTable(formattedProperties: any[]) {
	// Data needs to be formatted as follows for use with markdown library
	/*
		table([
		['Branch', 'Commit'],
		['main', '0123456789abcdef'],
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
	return mdTable(tableData, {
		pad: false
	});
}

function sortProperties(properties: Map<string, SchemaProperty>) {
	var sorted = new Map<string, SchemaProperty>();

	// Place required properties first
	properties.forEach((prop, name) => {
		if (prop.required) {
			sorted.set(name, prop);
		}
	});

	// Then place non-required properties
	properties.forEach((prop, name) => {
		if (!prop.required) {
			sorted.set(name, prop);
		}
	});

	return sorted;
}

export function createEnumSummary(enumType: SchemaEnum) {
	var md = '';
	var rows = [];

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
		['main', '0123456789abcdef'],
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
	var types: string[] = property.original.type.split("|");

	property.shorthands.forEach(shorthand => {
		types.push(...shorthand.original.type.split("|"));
	});

	// Format the types
	var formattedTypes: string[] = [];
	types.forEach(type => {
		formattedTypes.push(style.type(type));
	});

	var formattedType = formattedTypes.join(", ");

	var description = property.description;

	var required;
	if (defined(property.required) && (property.required)) {
		required = 'Yes';
	} else {
		var propertyDefault = property.default;
		if (defined(propertyDefault)) {
			required = 'No, default: ' + style.defaultValue(propertyDefault);
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
		type: types.join("|"),
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

	md += style.getHeaderMarkdown(property.name, headerLevel); // Includes ending newlines

	// TODO: Add plugin point for custom JSON schema properties like gltf_*
	var detailedDescription = property.description;
	if (defined(detailedDescription)) {
		md += detailedDescription + '\n\n';
	} else if (defined(summary.description)) {
		md += summary.description + '\n\n';
	}

	md += '* ' + style.propertyDetails('Type') + ': ' + summary.formattedType + '\n';

	if (includeVersion) {
		if (summary.version != elementVersion) {
			md += `* ${style.propertyDetails("Version")} : ${summary.version}\n`;
		}
	}

	md += '* ' + style.propertyDetails('Required') + ': ' + summary.required + '\n';

	var hasComplexTypes = propertyHasComplexTypes(property);

	if (hasComplexTypes) {
		var allowedValues: string[] = getAllowedValuesForProperty(property, summary, includeVersion);
		if (allowedValues.length > 0) {
			md += '* ' + style.propertyDetails('Allowed values') + ':';
			allowedValues.forEach(allowedValue => {
				md += `\n  * ${allowedValue}`;
			});
		}
	}

	return md + '\n';
}

export function propertyHasComplexTypes(property: SchemaProperty) {
	var answer = false;

	var allTypes: SchemaPropertyType[] = property.getAllTypes();
	allTypes.forEach(propertyType => {
		if (propertyType.type instanceof SchemaClass || propertyType.type instanceof SchemaEnum) {
			answer = true;
		}
	});

	return answer;
}

function getAllowedValuesForProperty(property: SchemaProperty, summary: any, includeVersion: boolean) {
	var allowedValues: string[] = [];

	property.getAllTypes().forEach(propertyType => {
		allowedValues.push(...getAllowedValuesForPropertyType(propertyType, summary, includeVersion));
	});

	return allowedValues;
}

function getAllowedValuesForPropertyType(propertyType: SchemaPropertyType, summary: any, includeVersion: boolean) {
	var allowedValues: string[] = [];

	if (propertyType.type instanceof SchemaEnum) {
		propertyType.type.values.forEach(enumValue => {
			var descriptions: string[] = [];

			if (includeVersion) {
				if (enumValue.original.version && enumValue.original.version !== summary.version) {
					descriptions.push(`Added in version ${enumValue.original.version}.`);
				}
			}

			if (enumValue.description && enumValue.description.length > 0) {
				descriptions.push(enumValue.description);
			}

			if (descriptions.length > 0) {
				allowedValues.push(style.enumValue(enumValue.value) + ": " + descriptions.join(" "));
			} else {
				allowedValues.push(style.enumValue(enumValue.value));
			}
		});
	} else if (propertyType.type instanceof SchemaClass) {
		allowedValues.push(...getAllowedValuesForClass(propertyType.type, summary, includeVersion));
	} else if (propertyType.type instanceof SchemaLiteral) {
		allowedValues.push(style.type(propertyType.type.type));
	} else {
		throw new Error("Unknown type");
	}

	return allowedValues;
}

function getAllowedValuesForClass(classType: SchemaClass, summary: any, includeVersion: boolean) {
	var answer: string[] = [];
	if (classType.implementations.length > 0) {
		classType.implementations.forEach(implementation => {
			answer.push(...getAllowedValuesForClass(implementation, summary, includeVersion));
		});
	} else {
		answer.push(style.type(classType.type));
		if (classType.shorthand) {
			answer.push(...getAllowedValuesForProperty(classType.shorthand, summary, includeVersion));
		}
	}
	return answer;
}
