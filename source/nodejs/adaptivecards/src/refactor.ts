import * as fs from "fs";
import * as ts from "typescript";

const fileName = 'card-elements.ts';
let sourceFile = ts.createSourceFile(fileName, fs.readFileSync(fileName).toString(), ts.ScriptTarget.ES2015, /*setParentNodes */ true);

let prolog: string = "";
let declared_in_utility: Array<string> = [];

const preserve_for_prolog = (node: ts.Node) => {
	prolog += node.getFullText();
};

const create_prolog = () => {
	return prolog +
		"\nimport {" +
		declared_in_utility.join(",") +
		"} from './utility'\n\n";
};

let modules_created: {[key: string]: string} = {};
const move_to_its_own_file = (cl: ts.Node) => {
	let declaration_node = <ts.DeclarationStatement>cl;
	let declared_name = declaration_node.name.getFullText().trim();
	// TODO: make sure the declaration is exported
	let is_export = (cl.modifiers && cl.modifiers[0].kind == ts.SyntaxKind.ExportKeyword);
	let module_name = declared_name.toLowerCase();
	let file_name = module_name + ".ts";
	fs.writeFileSync(file_name, create_prolog() + (is_export ? "" : "export ") + cl.getFullText());
	modules_created[declared_name] = file_name;
	prolog += "import {" + declared_name + "} from './" + module_name + "'\n";
};

let prologued_utilty = false;
const move_to_utility_file = (cl: ts.Node) => {
	if (!prologued_utilty) {
		fs.writeFileSync("utility.ts", prolog + "\n\n");
		prologued_utilty = true;
	}
	if (ts.isVariableStatement(cl)) {
		let stmt = <ts.VariableStatement>cl;
		declared_in_utility.concat(stmt.declarationList.declarations.map(vd => vd.name.getFullText().trim()));
	}
	else {
		let declaration_node = <ts.DeclarationStatement>cl;
		if (declaration_node.name) {
			let declared_name = declaration_node.name.getFullText().trim();
			declared_in_utility.push(declared_name);
		}
		else {
			console.log(declaration_node.getFullText());
		}
	}
	fs.appendFileSync("utility.ts", cl.getFullText());
};

const ignore = () => null;

declare const process: { abort: ()=>any };
const show_error = (node: ts.Node) => { console.log("I have no rule for " + node.kind); process.abort(); }

// 229 - ClassDeclaration - move to its own file
// 238 - ImportDeclaration - preserve then copy on every file
// 228 - FunctionDeclaration - move to Utilty file
// 231 - TypeAliasDeclaration - move to utilty
// 208 - VariableStatement - move to Utilty file
// 230 - InterfaceDeclaration - move to its own file?
// 232 - EnumDeclaration - move to its own file?
// 1 - EndOfFileToken - do nothing

let kind_to_strategy: {[propname: number]: any} = {
	229: move_to_its_own_file,
	230: move_to_its_own_file,
	232: move_to_its_own_file,
	1: ignore,
	228: move_to_utility_file,
	208: move_to_utility_file,
	231: move_to_utility_file,
	238: preserve_for_prolog
};

// first pass - process all
sourceFile.forEachChild(node => {
	let strategy = kind_to_strategy[node.kind] || show_error;
	strategy(node);
});

