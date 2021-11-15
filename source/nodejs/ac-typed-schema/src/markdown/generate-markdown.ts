// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { I18n } from "i18n";
import { defined } from "./defined";
import { defaultValue } from "./defaultValue";
import { SchemaClass } from "../SchemaClass";
import { SchemaEnum } from "../SchemaEnum";
import { SchemaLiteral } from "../SchemaLiteral";
import { SchemaProperty } from "../SchemaProperty";
import { SchemaPropertyType } from "../SchemaPropertyType";
import * as path from "path";
import * as console from "console";
import * as mdTable from "markdown-table";
import * as style from "./style";

const getPreviewMarkDown = (version: string) => {
    return `<span class="ac-schema-version-${version?.replace(/\./, '-')}"></span>`
}

class MarkdownConfig {
    private _locale : string = "en";
    private _i18n : I18n;

    constructor() {
        this._i18n = new I18n();
        this._i18n.configure({
            locales: ['en', 'de', 'sp'],
            directory: path.join(__dirname, '../../src/markdown/languages'),
            syncFiles: true
        });
    }

    get i18n() {
        return this._i18n;
    }

    get locale() {
        return this._locale;
    }

    set locale(value: string) {
        this._locale = value;
        this.i18n.setLocale(this.locale);
    }
}

let markdownConfig = new MarkdownConfig();
export { markdownConfig };

const __ = markdownConfig.i18n.__;
export { __ };

export function createPropertiesSummary(classDefinition: SchemaClass, knownTypes, autoLink, includeVersion, elementVersion) {
	var md = '';

	var properties: Map<string, SchemaProperty> = classDefinition.getAllProperties();
	if (properties !== undefined && properties.size > 0) {

		// Re-order so that required properties are up front
		// (Otherwise if there's an inherited required property, it'll be at bottom)
		properties = sortProperties(properties);

		if (includeVersion && defined(elementVersion) && elementVersion != "1.0") {
			md += __("**Introduced in version %s**\n\n", elementVersion);
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
				Required: __("Yes"),
				Description: __("Must be `\"%s\"`.", classDefinition.type)
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
				Property: style.propertyNameSummary(name) + getPreviewMarkDown(summary.version),
				Type: summary.formattedType,
				Required: summary.required,
				Description: __(summary.description)
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
				formattedProperty.Required = __("Yes");
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
			md += "\n" + __("### Inherited properties") + "\n\n";
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
	for (let propName in formattedProperties[0]) {
		headerRow.push(__(propName));
	}
	tableData.push(headerRow);

	formattedProperties.forEach((formattedProperty) => {
		var dataRow = [];
		for (let propName in formattedProperty) {
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
			Description: __(val.description)
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
	for (let propName in rows[0]) {
		headerRow.push(propName);
	}
	tableData.push(headerRow);

	rows.forEach((row) => {
		var dataRow = [];
		for (let propName in row) {
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

	var description = __(property.description);

	var required: string;

	if (defined(property.required) && (property.required)) {
		required = __("Yes");
	} else {
		var propertyDefault = property.default;
		if (defined(propertyDefault)) {
			required = __("No, default: %s", style.defaultValue(propertyDefault));
		} else {
			required = __("No");
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
		description: __(description),
		required: required,
		version: version
	};
}

export function createPropertiesDetails(classDefinition: SchemaClass, headerLevel: number, knownTypes, autoLink, includeVersion: boolean, elementVersion: string) {
	var md = '';

	var properties = classDefinition.getAllProperties();
	properties.forEach((property, name) => {
		md += createPropertyDetails(property, headerLevel, knownTypes, autoLink, includeVersion, elementVersion);
	});

	return md + '\n';
}

export function createPropertyDetails(property: SchemaProperty, headerLevel: number, knownTypes, autoLink, includeVersion: boolean, elementVersion: string, includeHeader: boolean = true) {
	var md = '';

	var summary = getPropertySummary(property, knownTypes, autoLink, elementVersion);

	if (includeHeader) {
		md += style.getHeaderMarkdown(property.name, headerLevel); // Includes ending newlines
	}

	// TODO: Add plugin point for custom JSON schema properties like gltf_*
	var detailedDescription = property.description;
	if (defined(detailedDescription)) {
		md += __(detailedDescription) + '\n\n';
	} else if (defined(summary.description)) {
		md += __(summary.description) + '\n\n';
	}

	md += __("* %s: %s\n", style.propertyDetails('Type'), summary.formattedType);

	if (includeVersion) {
		if (summary.version != elementVersion) {
			md += __("* %s : %s\n", style.propertyDetails("Version"), summary.version);
		}
	}

	md += __("* %s: %s\n", style.propertyDetails('Required'), summary.required);

	var hasComplexTypes = propertyHasComplexTypes(property);

	if (hasComplexTypes) {
		var allowedValues: string[] = getAllowedValuesForProperty(property, summary, includeVersion);
		if (allowedValues.length > 0) {
			md += __("* %s:", style.propertyDetails('Allowed values'));
			allowedValues.forEach(allowedValue => {
				md += `\n  * ${allowedValue}`;
			});
		}
	}

	return md + '\n';
}

export function createPropertyDetailsHeader(property: SchemaProperty, headerLevel: number) {
	return style.getHeaderMarkdown(property.name, headerLevel);
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
					descriptions.push(__("Added in version %s.", enumValue.original.version));
				}
			}

			if (enumValue.description && enumValue.description.length > 0) {
				descriptions.push(__(enumValue.description));
			}

			if (descriptions.length > 0) {
				allowedValues.push(__("%s: %s", style.enumValue(enumValue.value), descriptions.join(" ")));
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
