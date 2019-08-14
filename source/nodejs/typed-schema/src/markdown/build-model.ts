// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as yaml from "js-yaml";
import { Schema } from "../Schema";
import { SchemaClass } from "../SchemaClass";
import { SchemaProperty } from "../SchemaProperty";
import * as glob from "glob";
import { defaultValue } from "./defaultValue";

var fs = require('fs');
var path = require('path');

export class BuildModelOptions {
	// These are all file paths
	schema: string;
	toc: string;
	rootDefinition: string;
	examplesPath?: string;
}

export function buildModel(options: BuildModelOptions) {

	var schemaFolder = options.schema;
	var toc = yaml.safeLoad(fs.readFileSync(options.toc));
	var rootDefinition = options.rootDefinition;

	var items = [];

	var schema: Schema = Schema.fromFolder(schemaFolder);

	for (var index in toc) {
		var rootObj = toc[index];

		var root = {
			title: getObjectName(rootObj),
			children: [],
			schema: schema
		};

		for (var definitionIndex in rootObj[root.title]) {

			var name = rootObj[root.title][definitionIndex];
			var objSchema = schema.getType(name);
			if (objSchema === undefined) {
				console.warn("WARN: Unable to locate schema definition for " + name);
				continue;
			}

			var definition: any = {
				type: objSchema
			};
			definition.name = name;
			definition.version = defaultValue(objSchema.original.version, "1.0");
			definition.examples = [];

			definition.description = objSchema.description;
			if (objSchema instanceof SchemaClass) {
				definition.properties = objSchema.getAllProperties();
			}

			if (options.examplesPath) {
				definition.examples = glob.sync(path.join(options.examplesPath, "/**/" + definition.name + ".json"), { nocase: false })
			}

			if (definition.properties) {
				var properties: Map<string, SchemaProperty> = definition.properties;
				properties.forEach((property, name) => {

					var anyProperty: any = property;
					anyProperty.cardExamples = [];
					if (options.examplesPath) {
						anyProperty.cardExamples = glob.sync(path.join(options.examplesPath, "**/" + definition.name + "." + name + ".json"), { nocase: false });
					}
				});
			}

			root.children.push(definition);

		}

		items.push(root);
	}

	return items;
}

function getObjectName(obj) {
	for (var property in obj)
		return property;
}