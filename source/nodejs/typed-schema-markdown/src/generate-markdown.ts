import { defined } from "./defined";
import { defaultValue } from "./defaultValue";
import { SchemaProperty, SchemaClass, SchemaEnum } from "typed-schema";
import * as mdTable from "markdown-table";
import * as style from "./style";

export function createPropertiesSummary(classDefinition: SchemaClass, knownTypes, autoLink, includeVersion, elementVersion) {
	var md = '';

	var properties = classDefinition.getAllProperties();
    if (properties !== undefined && properties.size > 0) {

        if (includeVersion && defined(elementVersion) && elementVersion != "1.0") {
            md += "#### Introduced in version " + elementVersion + "\n\n";
		}
		
		var formattedTypeProperty:any = {
			Property: "**type**",
			Type: "`string`",
			Required: "Depends",
			Description: "Must be `\"" + classDefinition.type + "\"`."
		};

		if (includeVersion) {
			formattedTypeProperty.Version = "1.0";
		}
		var formattedProperties = [ formattedTypeProperty ];

        properties.forEach((property, name) => {
			var propertyOriginal: any = property.original;
			var summary = getPropertySummary(property, knownTypes, autoLink);
			
			var formattedProperty:any = {
				Property: style.propertyNameSummary(name),
				Type: summary.formattedType,
				Required: summary.required,
				Description: summary.description
			};

			if (includeVersion) {
				formattedProperty.Version = defaultValue(defaultValue(propertyOriginal.version, elementVersion), "1.0");
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

function getPropertySummary(property: SchemaProperty, knownTypes, autoLink) {
    var type:string = property.original.type;
    var formattedType = "`" + type + "`";

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

    return {
        type: type,
        formattedType: formattedType,
        description: description,
        required: required
    };
}