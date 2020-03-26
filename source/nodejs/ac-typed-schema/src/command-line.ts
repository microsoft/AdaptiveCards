// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as tschema from "./typed-schema";
import { TransformOptions } from "./TransformOptions";

declare var process;

var folderToTransform = process.argv[2];
var primaryTypeName = process.argv[3].split(",");
var defaultPrimaryType: string | undefined = undefined;
if (process.argv.length > 4) {
	defaultPrimaryType = process.argv[4];
}
var typePropertyName: string | undefined = undefined;
if (process.argv.length > 5) {
	typePropertyName = process.argv[5];
}
var allowAdditionalProperties: boolean = false;
if (process.argv.length > 6 && process.argv[5] === "true") {
	allowAdditionalProperties = true;
}

var transformed = tschema.transformFolder(folderToTransform, {
	primaryTypeNames: primaryTypeName,
	defaultPrimaryTypeName: defaultPrimaryType,
	typePropertyName: typePropertyName,
	allowAdditionalProperties: allowAdditionalProperties
});

console.log(JSON.stringify(transformed, null, 2));