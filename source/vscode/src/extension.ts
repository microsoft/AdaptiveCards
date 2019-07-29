'use strict';

import * as vscode from 'vscode';
import { AdaptiveCardPanel } from './adaptiveCardPanel';

const path = require('path');

export function activate(context: vscode.ExtensionContext) {
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
