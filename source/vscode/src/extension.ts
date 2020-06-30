"use strict";

import * as vscode from "vscode";
import { AdaptiveCardPanel } from "./adaptiveCardPanel";
import { CardProvider } from "./cardProvider";
import * as path from "path";
import * as fs from "fs";
import { AdaptiveCardsMain } from "./adaptiveCards";
// tslint:disable-next-line: typedef no-empty
export function activate(context: vscode.ExtensionContext) {
	const acm : AdaptiveCardsMain = new AdaptiveCardsMain(context,context.extensionPath);
	const cardProvider : CardProvider = new CardProvider(context,acm);
	vscode.window.registerTreeDataProvider("cardList", cardProvider);

	vscode.commands.registerCommand("cardList.showElement", card  => {
		if (fs.existsSync(card.path)) {
			vscode.workspace.openTextDocument(card.path).then(card => {
				vscode.window.showTextDocument(card);
			  });
		} else {
			// tslint:disable-next-line: typedef
			let data = {};
			fs.writeFile(card.path, JSON.stringify(data),err => {
				vscode.workspace.openTextDocument(card.path).then(card => {
					vscode.window.showTextDocument(card);
				});
			});
		}
	});
}

// tslint:disable-next-line: typedef no-empty
export function deactivate() {}
