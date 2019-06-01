import { defined } from "./defined";
import { defaultValue } from "./defaultValue";
import { SchemaProperty } from "typed-schema";
import mdTable from "markdown-table";

export function createPropertiesSummary(properties, knownTypes, autoLink, includeVersion, elementVersion) {
	var md = '';

    if (properties !== undefined && Object.keys(properties).length > 0) {

        if (includeVersion && defined(elementVersion) && elementVersion != "1.0") {
            md += "#### Introduced in version " + elementVersion + "\n\n";
		}
		
		var formattedProperties = [];

        for (var name in properties) {
            if (properties.hasOwnProperty(name)) {
                var property = properties[name];
				var summary = getPropertySummary(property, knownTypes, autoLink);
				
				var formattedProperty:any = {
					Property: name,
					Type: summary.formattedType,
					Required: (summary.required === 'Yes' ? "Yes" : ' ') + summary.required,
					Description: summary.description
				};

				if (includeVersion) {
					formattedProperty.Version = defaultValue(defaultValue(property.version, elementVersion), "1.0");
				}

				formattedProperties.push(formattedProperty);
            }
		}

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

function getPropertySummary(property: SchemaProperty, knownTypes, autoLink) {
    var type:string = property.original.type;
    var formattedType = type;

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