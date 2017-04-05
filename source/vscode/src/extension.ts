'use strict';

import * as vscode from 'vscode';
import { AdaptiveCardDocumentContentProvider } from './adaptiveCardProvider';

const path = require('path');
export function activate(context: vscode.ExtensionContext) {

    let previewUri = vscode.Uri.parse('adaptivecard-preview://authority/adaptivecard-preview');

    let provider = new AdaptiveCardDocumentContentProvider(context);
    let registration = vscode.workspace.registerTextDocumentContentProvider('adaptivecard-preview', provider);

    vscode.workspace.onDidChangeTextDocument((e: vscode.TextDocumentChangeEvent) => {
        if (vscode.window.activeTextEditor) {
            if (e.document === vscode.window.activeTextEditor.document && !checkNoAdaptiveCard(vscode.window.activeTextEditor.document, false)) {
                provider.update(previewUri);
            }
        }
    });

    vscode.window.onDidChangeActiveTextEditor((textEditor: vscode.TextEditor) => {
        if (vscode.window.activeTextEditor) {
            if (textEditor.document === vscode.window.activeTextEditor.document && !checkNoAdaptiveCard(vscode.window.activeTextEditor.document, false)) {
                provider.update(previewUri);
                let auto = vscode.workspace.getConfiguration('adaptivecardviewer').get('enableautopreview');
                if (auto) {
                    return openPreview(previewUri, textEditor.document.fileName);
                }
            }
        }
    });

    let open = vscode.commands.registerTextEditorCommand('adaptivecardviewer.open', (te, t) => {
        if (checkNoAdaptiveCard(te.document))
            return;
        provider.update(previewUri);
        return openPreview(previewUri, te.document.fileName);
    });

    context.subscriptions.push(open);
}

function checkNoAdaptiveCard(document: vscode.TextDocument, displayMessage: boolean = true) {

    let isNGType = !(document.languageId === 'json') || document.getText().indexOf('https://microsoft.github.io/AdaptiveCards/schemas/adaptive-card.json') < 0;
    if (isNGType && displayMessage) {
        vscode.window.showWarningMessage("Active editor doesn't show a AdaptiveCard JSON document.");
    }
    return isNGType;
}

function openPreview(previewUri: vscode.Uri, fileName: string) {
    return vscode.commands.executeCommand('vscode.previewHtml', previewUri, 2, `Preview : ${fileName}`)
        .then(s => console.log('done.'), vscode.window.showErrorMessage);
}

export function deactivate() {
}
