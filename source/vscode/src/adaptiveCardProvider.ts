'use strict';

import * as vscode from 'vscode';
import * as path from 'path';

export class AdaptiveCardDocumentContentProvider implements vscode.TextDocumentContentProvider {
    private _onDidChange = new vscode.EventEmitter<vscode.Uri>();

    public constructor(private _context: vscode.ExtensionContext) {}

    public provideTextDocumentContent(uri: vscode.Uri): string {
        return this.createAdaptiveCardSnippet();
    }

    get onDidChange(): vscode.Event<vscode.Uri> {
        return this._onDidChange.event;
    }

    public update(uri: vscode.Uri) {
        this._onDidChange.fire(uri);
    }

    private createAdaptiveCardSnippet() {
        return this.extractSnippet();
    }

    private extractSnippet(): string {
        let editor = vscode.window.activeTextEditor;
        let text = editor ? editor.document.getText() : '';
        let fileName = editor ? editor.document.fileName : '';
        let snippet = this.snippet(fileName, text);
        return snippet;
    }

    private errorSnippet(error: string): string {
        return `
                <body>
                    ${error}
                </body>`;
    }

    private getPath(p: string): string {
        return path.join(this._context.extensionPath, p);
    }

    private snippet(fileName, json): string {
        return `<!DOCTYPE html>
        <html>
            <head>
                <link rel="stylesheet" type="text/css" href="${this.getPath('media/export.css')}">
                <script src="${this.getPath('node_modules/adaptive-cards/dist/adaptive-cards.js')}"></script>
            </head>
            <body>
                <h1>Adaptive Card Preview</h1>
                <div id='previewDiv' style="background-color:white;margin:8px 0px 20px 0px;"></div>
                <script>
                    document.getElementById('previewDiv').appendChild(new AdaptiveCards.JsonParser().parse(${json}).render());
                    AdaptiveCards.AdaptiveCard.onExecuteAction = function(action) 
                    {
                        alert(JSON.stringify(action));
                    };
                </script>
            </body>
        </html>`;
    }
}