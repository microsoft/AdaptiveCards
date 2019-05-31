import * as tschema from "./typed-schema";

declare var process;

var folderToTransform = process.argv[2];
var primaryTypeName = process.argv[3].split(",");
var defaultPrimaryType:string|null = null;
if (process.argv.length > 4) {
	defaultPrimaryType = process.argv[4];
}
var typePropertyName:string|null = null;
if (process.argv.length > 5) {
	typePropertyName = process.argv[5];
}

var transformed = tschema.transformFolder(folderToTransform, primaryTypeName, defaultPrimaryType, typePropertyName);

console.log(JSON.stringify(transformed, null, 2));