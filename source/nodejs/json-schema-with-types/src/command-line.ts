import * as tschema from "./json-schema-with-types";

declare var process;

var folderToTransform = process.argv[2];
var primaryTypeName = process.argv[3];

var transformed = tschema.transformFolder(folderToTransform, primaryTypeName);

console.log(JSON.stringify(transformed, null, 2));