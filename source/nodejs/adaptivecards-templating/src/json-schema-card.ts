// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { IAdaptiveCard, ICardElement, IChoiceSetInput, IContainer, INumberInput, ITextInput, ITimeInput, IToggleInput } from 'adaptivecards/src/schema';
import { JSONSchema7, JSONSchema7Definition, JSONSchema7Type } from 'json-schema';


// JSON Schema Card
// generates an Adaptive Card given a JSON schema
export function JSONSchemaCard(schema: JSONSchema7): IAdaptiveCard | undefined {
	try {
		return {
			type: "AdaptiveCard",
			body: [
				JSONSchemaCardObject(schema, '', 0),
			],
		}
	} catch (e) {
		console.error(e);
		return undefined;
	}
}


// JSON Schema Elements

function JSONSchemaCardElement(schema: JSONSchema7Definition, path: string, depth: number): ICardElement {
    if (typeof (schema) === "boolean") return null;
    switch (schema.type) {
        case "array":
            if (Array.isArray(schema.items)) {
                return JSONSchemaCardTuple(schema, path, depth);
            } else {
                return JSONSchemaCardList(schema, path, depth);
            }
        case "object":
            return JSONSchemaCardObject(schema, path, depth);
        case "boolean":
            return JSONSchemaCardBoolean(schema, path)
        case "integer":
        case "number":
            return JSONSchemaCardNumber(schema, path)
        case "string":
            if (schema.enum) {
                return JSONSchemaCardChoiceSet(schema, path)
            } else {
                return JSONSchemaCardText(schema, path)
            }
        case "date-time":
        case "time":
        case "date":
            return JSONSchemaCardTime(schema, path)
        default:
            return null;
    }
}

function encodeProperty(property: string) {
    return encodeURIComponent(property).replace('.', '%2e')
}

function textSizeAtDepth(depth: number) {
    switch (depth) {
        case 0:
            "large"
        case 1:
            "medium"
        default:
            "small"
    }
}

function JSONSchemaFieldTitle(schema: JSONSchema7, path: string, depth: number): ICardElement[] {
    return [
        schema.title ? {
            type: "TextBlock",
            size: textSizeAtDepth(depth),
            text: schema.title,
        } : null,
        schema.description ? {
            type: "TextBlock",
            size: textSizeAtDepth(depth + 1),
            isSubtle: true,
            wrap: true,
            text: schema.description,
        } : null,
    ]
}

function JSONSchemaCardTuple(schema: JSONSchema7, path: string, depth: number): IContainer {
    if (!Array.isArray(schema.items)) return null;
    return {
        type: "Container",
        items: [
            ...JSONSchemaFieldTitle(schema, path, depth),
            ...schema.items?.map((item: JSONSchema7Definition, idx: number) => {
                return JSONSchemaCardElement(item, `${path}[${idx}]`, depth + 1)
            }) ?? [],
        ],
    }
}

function JSONSchemaCardList(schema: JSONSchema7, path: string, depth: number): IContainer {
    return {
        type: "Container",
        items: [
            ...JSONSchemaFieldTitle(schema, path, depth),
            // TODO not implemented
        ],
    }
}

function JSONSchemaCardObject(schema: JSONSchema7, path: string, depth: number): IContainer {
    return {
        type: "Container",
        items: [
            ...JSONSchemaFieldTitle(schema, path, depth),
            ...schema.required?.map((property: string) => {
                return JSONSchemaCardElement(schema.properties[property], `${path}.${encodeProperty(property)}`, depth + 1)
            }) ?? [],
        ],
    }
}

function JSONSchemaCardBoolean(schema: JSONSchema7, path: string): IToggleInput {
    return {
        type: "Input.Toggle",
        id: path,
        title: schema.title,
        label: schema.description,
        value: schema.default as string,
    }
}

function JSONSchemaCardNumber(schema: JSONSchema7, path: string): INumberInput {
    return {
        type: "Input.Number",
        id: path,
        title: schema.title,
        placeholder: schema.description,
        value: schema.default as string,
        min: schema.exclusiveMinimum ?? schema.minimum,
        max: schema.exclusiveMaximum ?? schema.maximum,
    }
}

function JSONSchemaCardChoiceSet(schema: JSONSchema7, path: string): IChoiceSetInput {
    return {
        type: "Input.ChoiceSet",
        id: path,
        title: schema.title,
        choices: schema.enum.map((item: JSONSchema7Type) => {
            return {
                title: item as string,
                value: item as string,
            }
        }),
        placeholder: schema.description,
        value: schema.default as string,
    }
}

function JSONSchemaCardText(schema: JSONSchema7, path: string): ITextInput {
    return {
        type: "Input.Text",
        id: path,
        title: schema.title,
        placeholder: schema.description,
        value: schema.default as string,
        maxLength: schema.maxLength,
        regex: schema.pattern,
    }
}

function JSONSchemaCardTime(schema: JSONSchema7, path: string): ITimeInput {
    return {
        type: "Input.Time",
        id: path,
        title: schema.title,
        placeholder: schema.description,
        value: schema.default as string,
    }
}
