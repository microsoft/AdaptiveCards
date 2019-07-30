// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SchemaClass } from "./SchemaClass";
import { SchemaType } from "./SchemaType";
import { SchemaEnum } from "./SchemaEnum";

var fs = require("fs");
var path = require("path");

export class Schema {
	private _typeDictionary: Map<string, SchemaType> = new Map<string, SchemaType>();

	constructor(types: any[]) {

		types.forEach(type => {
			this._typeDictionary.set(type.type, this.parse(type));
		});

		// Resolve types
		this._typeDictionary.forEach(type => {
			type.resolve(this._typeDictionary);
		});

		this._typeDictionary.forEach(type => {
			if (type instanceof SchemaClass) {
				type.resolveImplementations(this._typeDictionary);
			}
		});
	}

	parse(sourceObj: any): SchemaType {
		if (sourceObj.classType === "Enum") {
			return new SchemaEnum(sourceObj);
		} else if (sourceObj.classType === "Class" || sourceObj.classType === undefined) {
			return new SchemaClass(sourceObj);
		} else {
			throw new Error("Unknown classType " + sourceObj.classType);
		}
	}

	get typeDictionary() {
		return this._typeDictionary;
	}

	getType(typeName: string): SchemaType {
		var answer = this._typeDictionary.get(typeName);
		if (answer === undefined) {
			var knownTypes = "";
			this._typeDictionary.forEach((value, key) => {
				if (knownTypes.length > 0) {
					knownTypes += ", ";
				}
				knownTypes += key;
			});
			throw new Error("Type " + typeName + " could not be found. Known types: " + knownTypes);
		}
		return answer;
	}

	static fromFolder(folder: string) {
		var files = Schema.getAllFiles(folder);
		var types: any[] = [];
		files.forEach((filePath) => {
			if (filePath.endsWith(".json")) {
				var fileTxt = fs.readFileSync(filePath, "utf8");
				var type = JSON.parse(fileTxt);

				// Infer type name from file name if not specified
				if (!type.type) {
					var stat = fs.statSync(filePath);
					if (stat) {
						type.type = path.basename(filePath, ".json");
					}
				}

				types.push(type);
				types[type.type] = type;
			}
		});
		return new Schema(types);
	}

	private static getAllFiles(dir: string) {
		// https://stackoverflow.com/questions/5827612/node-js-fs-readdir-recursive-directory-search
		var results = [];
		var list = fs.readdirSync(dir);
		list.forEach(function (file) {
			file = dir + '/' + file;
			var stat = fs.statSync(file);
			if (stat && stat.isDirectory()) {
				/* Recurse into a subdirectory */
				results = results.concat(Schema.getAllFiles(file));
			} else {
				/* Is a file */
				results.push(file);
			}
		});
		return results;
	}
}