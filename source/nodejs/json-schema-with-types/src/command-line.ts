import * as tschema from "./json-schema-with-types";

let process;

var folderToTransform = process.argv[0];
var primaryTypeName = process.argv[1];

var transformed = tschema.transformFolder(folderToTransform, primaryTypeName);

console.log(JSON.stringify(transformed, null, 2));