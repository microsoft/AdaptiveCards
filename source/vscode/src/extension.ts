'use strict';

import * as vscode from 'vscode';
import { AdaptiveCardPanel } from './adaptiveCardPanel';
import { CardProvider } from './cardProvider';
const path = require('path');

export function activate(context: vscode.ExtensionContext) {

	const cardProvider = new CardProvider(context);
	vscode.window.registerTreeDataProvider('cardList', cardProvider);


	// Register Url Handler for App
	vscode.window.registerUriHandler({
		handleUri(uri: vscode.Uri) {
			if(uri.toString().indexOf("VSCODE") > 0){
				vscode.window.showInformationMessage("Opening your card please wait...");
			}else{
				// Not yet implemented
			}
		}
	});


	vscode.commands.registerCommand('cardList.showElement', card  => {
		vscode.workspace.openTextDocument(card.path).then(card => {
			vscode.window.showTextDocument(card);
		  });
	});

    context.subscriptions.push(
        vscode.commands.registerCommand('adaptivecardviewer.open', () => {
            AdaptiveCardPanel.createOrShow(context.extensionPath);
        })
    );

    if (vscode.window.registerWebviewPanelSerializer) {
		// Make sure we register a serializer in activation event
		vscode.window.registerWebviewPanelSerializer(AdaptiveCardPanel.viewType, {
			async deserializeWebviewPanel(webviewPanel: vscode.WebviewPanel, state: any) {
				console.log(`Got state: ${state}`);
				AdaptiveCardPanel.revive(webviewPanel, context.extensionPath);
			}
		});
	}
}

export function deactivate() {
}
