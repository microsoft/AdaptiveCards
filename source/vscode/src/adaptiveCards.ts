import * as vscode from "vscode";
import * as path from "path";
import * as fs from "fs";
import { WebViews } from "./webviews";

export class AdaptiveCardsMain {
    private readonly _extensionPath: string;
    private panel: vscode.WebviewPanel | undefined;
    public statusBarItem: vscode.StatusBarItem;
    public readonly _context: vscode.ExtensionContext;
    public WebViews: WebViews;

    constructor(private context: vscode.ExtensionContext,extensionPath: string) {
        this._context = context;
        this.context = context;
        this._extensionPath = extensionPath;
        this.WebViews = new WebViews(this._context, this._context.extensionPath);
    }


    // tslint:disable-next-line: typedef
    public async OpenOrUpdatePanel(cardPath: string, content: string) {
        const column : vscode.ViewColumn = vscode.ViewColumn.Beside;
        if(this.panel) {
            this.panel.reveal(column);
            this.panel.title = "Adaptive Card";
            this.panel.webview.html = await this.WebViews.GetWebViewContentAdaptiveCard(0);
        } else {
            this.panel = vscode.window.createWebviewPanel("ac.CardViewer","Adaptive Card",vscode.ViewColumn.Beside,{
                enableScripts: true,
                localResourceRoots: [
                    vscode.Uri.file(path.join(this._extensionPath, "media"))
                ]
            });
            this.panel.webview.html = await this.WebViews.GetWebViewContentAdaptiveCard(0);
            this.panel.onDidDispose ( task=> {
                this.dispose();
            });
        }
    }

    // tslint:disable-next-line: typedef
    public async OpenCard(path: string) {
        if (fs.existsSync(path)) {
			vscode.workspace.openTextDocument(path).then(async card => {
				vscode.window.showTextDocument(card, vscode.ViewColumn.One).then(async e => {
                    await this.OpenOrUpdatePanel("","");
                });
			  });
		} else {
			// tslint:disable-next-line: typedef
			let data = {};
			fs.writeFile(path, JSON.stringify(data),err => {
				vscode.workspace.openTextDocument(path).then(card => {
					vscode.window.showTextDocument(card, vscode.ViewColumn.One).then(async e => {
                        await this.OpenOrUpdatePanel("","");
                    });
				});
			});
		}
    }


    private _disposables: vscode.Disposable[] = [];
	// tslint:disable-next-line: typedef
	public dispose() {
		this.panel.dispose();
        this.panel = null;
		while (this._disposables.length) {
			const x : vscode.Disposable = this._disposables.pop();
			if (x) {
				x.dispose();
			}
		}
	}
}