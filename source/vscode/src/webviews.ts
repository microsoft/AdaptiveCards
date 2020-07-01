import * as path from "path";
import * as vscode from "vscode";
import * as ACData from "adaptivecards-templating";
import { IEvaluationContext } from "adaptivecards-templating";


export class WebViews {
    private readonly _extensionPath: string;
    public readonly _context: vscode.ExtensionContext;

    constructor(private context: vscode.ExtensionContext,extensionPath: string) {
        this._context = context;
        this._extensionPath = extensionPath;
    }

    public async GetWebViewContentAdaptiveCard(taskItem: number, force: boolean = false)  {
        let editor = vscode.window.activeTextEditor;

        if (editor) {
        let document = editor.document;
        let template = new ACData.Template(document.getText());
        var context : IEvaluationContext = {$root: {}};
        var cardToRender = template.expand(context);

        // local path to main script run in the webview
        const scriptPathOnDisk = vscode.Uri.file(
            path.join(this._extensionPath, "media/js", "mainAdaptive.js")
        );
        // and the uri we use to load this script in the webview
        const scriptUri = scriptPathOnDisk.with({ scheme: "vscode-resource" });

        // jquery
        const jqueryPath = vscode.Uri.file(	path.join(this._extensionPath, "media/js", "jquery.min.js"));
        const jqueryUri = jqueryPath.with({ scheme: "vscode-resource" });

        // adaptiveCards
        let url = vscode.Uri.file(	path.join(this._extensionPath, "media/js", "fabric.min.js"));
        const FabricUri = url.with({ scheme: "vscode-resource" });

         url = vscode.Uri.file(	path.join(this._extensionPath, "media/js", "adaptivecards.min.js"));
        const ACUri = url.with({ scheme: "vscode-resource" });

        url = vscode.Uri.file(	path.join(this._extensionPath, "media/js", "adaptivecards-fabric.min.js"));
        const ACUFabricUri = url.with({ scheme: "vscode-resource" });

        url = vscode.Uri.file(	path.join(this._extensionPath, "media/js", "react.min.js"));
        const ReactUri = url.with({ scheme: "vscode-resource" });

        url = vscode.Uri.file(	path.join(this._extensionPath, "media/js", "react-dom.min.js"));
        const ReactDomUri = url.with({ scheme: "vscode-resource" });

        url = vscode.Uri.file(	path.join(this._extensionPath, "media/js", "markdown-it.min.js"));
        const MarkdownUri = url.with({ scheme: "vscode-resource" });

        url = vscode.Uri.file(	path.join(this._extensionPath, "media/css", "msteamsstyle.css"));
        const mainstyleUri = url.with({ scheme: "vscode-resource" });

        url = vscode.Uri.file(	path.join(this._extensionPath, "media/css", "fabric.components.min.css"));
        const FabricStyleUri = url.with({ scheme: "vscode-resource" });

        const ACstyle = vscode.Uri.file(	path.join(this._extensionPath, "media/css", "editormain.css"));
        const ACStyleUri = ACstyle.with({ scheme: "vscode-resource" });


        const nonce = this.getNonce();

        return `<!DOCTYPE html>
                <html lang="en">
                <head>
                    <meta charset="UTF-8">
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">
                    <title>Cat Coding</title>
                    <meta http-equiv="Content-Security-Policy" content="script-src 'nonce-${nonce}';style-src vscode-resource: 'unsafe-inline' http: https: data:;">

                    <link rel="stylesheet" href="${mainstyleUri}"  nonce="${nonce}"  type="text/css" />
                    <link rel="stylesheet" href="${ACStyleUri}"  nonce="${nonce}"  type="text/css" />
                    <link rel="stylesheet" href="${FabricStyleUri}"  nonce="${nonce}"  type="text/css" />
                </head>
                <body>
                    <div id="exampleDiv"></div>
                    <div id="out"></div>
                    <script nonce="${nonce}" src="${jqueryUri}"></script>
                    <script nonce="${nonce}" src="${ReactUri}"></script>
                    <script nonce="${nonce}" src="${ReactDomUri}"></script>

                    <script nonce="${nonce}" src="${FabricUri}"></script>
                    <script nonce="${nonce}" src="${ACUri}"></script>
                    <script nonce="${nonce}" src="${ACUFabricUri}"></script>

                    <script nonce="${nonce}" src="${MarkdownUri}"></script>
                    <script nonce="${nonce}" src="${scriptUri}"></script>
                    <div id="divData" style='display:none;'>
                        ${cardToRender}
                    </div>
                </body>
                </html>`;
        }
    }

    private getNonce() {
        let text = "";
        const possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        for (let i = 0; i < 32; i++) {
            text += possible.charAt(Math.floor(Math.random() * possible.length));
        }
        return text;
    }


}