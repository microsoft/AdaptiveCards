"use strict";

import * as vscode from "vscode";
import { AdaptiveCardPanel } from "./adaptiveCardPanel";
import { CardProvider } from "./cardProvider";
import { AdaptiveCardsMain } from "./adaptiveCards";



// tslint:disable-next-line: typedef no-empty
export function activate(context: vscode.ExtensionContext) {
	const acm : AdaptiveCardsMain = new AdaptiveCardsMain(context,context.extensionPath);
	const cardProvider : CardProvider = new CardProvider(context,acm);
	vscode.window.registerTreeDataProvider("cardList", cardProvider);
	vscode.window.registerTreeDataProvider("cardListCMS", cardProvider);

	// register Url Handler for App
	vscode.window.registerUriHandler({
        handleUri(uri: vscode.Uri) {
			if(uri.toString().indexOf("adaptivecards") > 0) {
				var cardId = uri.path.replace("/","");
				acm.OpenRemoteCard(cardId);
				console.log(uri.path.replace("/",""));
				//vscode://tcdev.adaptivecards/5d51dd2e-4ff1-4cda-bc90-eaee20c5eb6b
			} else {
				// noting for us, just ignore
			}
        }
    });



	vscode.commands.registerCommand("cardList.refresh", task => {
		cardProvider.refresh();
		}
	);

	vscode.commands.registerCommand("cardList.showElement", card  => {
		acm.OpenCard(card.path);
	});


	let activeEditor = vscode.window.activeTextEditor;
	vscode.window.onDidChangeActiveTextEditor(
		editor => {
		  activeEditor = editor;
		  acm.OpenOrUpdatePanel("","");
		},
		null,
		context.subscriptions
	  );

	  vscode.workspace.onDidChangeTextDocument(
		event => {
		  if (activeEditor && event.document === activeEditor.document) {
			acm.OpenOrUpdatePanel("","");
		  }
		},
		null,
		context.subscriptions
	  );

}

// tslint:disable-next-line: typedef no-empty
export function deactivate() {}
