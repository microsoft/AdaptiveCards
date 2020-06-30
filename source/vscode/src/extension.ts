"use strict";

import * as vscode from "vscode";
import { AdaptiveCardPanel } from "./adaptiveCardPanel";
import { CardProvider } from "./cardProvider";
import { AdaptiveCardsMain } from "./adaptiveCards";
import { WebViews } from "./webviews";
// tslint:disable-next-line: typedef no-empty
export function activate(context: vscode.ExtensionContext) {
	const acm : AdaptiveCardsMain = new AdaptiveCardsMain(context,context.extensionPath);
	const cardProvider : CardProvider = new CardProvider(context,acm);
	vscode.window.registerTreeDataProvider("cardList", cardProvider);

	vscode.commands.registerCommand("cardList.showElement", card  => {
		acm.OpenCard(card.path);
	});
}

// tslint:disable-next-line: typedef no-empty
export function deactivate() {}
