import * as path from "path";
import * as vscode from "vscode";

/**
 * Manages cat coding webview panels
 */
export class AdaptiveCardPanel {
	/**
	 * Track the currently panel. Only allow a single panel to exist at a time.
	 */
    public static currentPanel: AdaptiveCardPanel | undefined;

    public static readonly viewType = "adaptiveCard";

    private readonly _panel: vscode.WebviewPanel;
    private readonly _extensionPath: string;
    private _disposables: vscode.Disposable[] = [];

    public static createOrShow(extensionPath: string) {
        const column = vscode.window.activeTextEditor
            ? vscode.window.activeTextEditor.viewColumn
            : undefined;

        // If we already have a panel, show it.
        if (AdaptiveCardPanel.currentPanel) {
            AdaptiveCardPanel.currentPanel._panel.reveal(column);
            return;
        }

        // Otherwise, create a new panel.
        const panel = vscode.window.createWebviewPanel(
            AdaptiveCardPanel.viewType,
            "Adaptive Card Preview",
            vscode.ViewColumn.Two,
            {
              // enable javascript in the webview
              enableScripts: true,
            }
        );

        AdaptiveCardPanel.currentPanel = new AdaptiveCardPanel(panel, extensionPath);
    }

    public static revive(panel: vscode.WebviewPanel, extensionPath: string) {
        AdaptiveCardPanel.currentPanel = new AdaptiveCardPanel(panel, extensionPath);
    }

    private constructor(panel: vscode.WebviewPanel, extensionPath: string) {
        this._panel = panel;
        this._extensionPath = extensionPath;

        // set the webview's initial html content
        this._update();

        // listen for when the panel is disposed
        // this happens when the user closes the panel or when the panel is closed programatically
        this._panel.onDidDispose(() => this.dispose(), null, this._disposables);

        vscode.window.onDidChangeActiveTextEditor((e) => this._update());
        vscode.workspace.onDidSaveTextDocument((e) => this._update());

        // update the content based on view changes
        this._panel.onDidChangeViewState(
            e => {
                if (this._panel.visible) {
                    this._update();
                }
            },
            null,
            this._disposables
        );

        // handle messages from the webview
        this._panel.webview.onDidReceiveMessage(
            message => {
                switch (message.command) {
                    case 'alert':
                        vscode.window.showErrorMessage(message.text);
                        return;
                }
            },
            null,
            this._disposables
        );
    }

    public doRefactor() {
        // Send a message to the webview webview.
        // You can send any JSON serializable data.
        this._panel.webview.postMessage({ command: 'refactor' });
    }

    public dispose() {
        AdaptiveCardPanel.currentPanel = undefined;

        // Clean up our resources
        this._panel.dispose();

        while (this._disposables.length) {
            const x = this._disposables.pop();
            if (x) {
                x.dispose();
            }
        }
    }

    private isAdaptiveCard(document: vscode.TextDocument, displayMessage: boolean = true): boolean {
        let isJson = document.languageId === 'json';
        let hasSchema = document.getText().indexOf('http://adaptivecards.io/schemas/adaptive-card.json') > 0;
        let isAdaptiveCard = (isJson || hasSchema);
        if (!isAdaptiveCard) {
            // vscode.window.showWarningMessage("Active editor doesn't show a AdaptiveCard JSON document.");
            return false;
        }
        return isAdaptiveCard;
    }

    private _update() {
        let editor = vscode.window.activeTextEditor;
        if (this.isAdaptiveCard(editor.document)) {

            let fileName = editor ? editor.document.fileName : '';
            let json = editor ? editor.document.getText() : '';

            this._panel.title = `Adaptive Card Preview`;
            this._panel.webview.html = this._getHtmlForWebview(path.basename(fileName), json);
        }
        else {
            this._panel.title = `Adaptive Card Preview`;
            this._panel.webview.html = "<html><body/>";
        }
    }

    private _getHtmlForWebview(filename: string, json: string) {
        // Local path to main script run in the webview
        const cssPath = vscode.Uri.file(
            path.join(this._extensionPath, 'media', 'export.css')
        );

        return `<!DOCTYPE html>
        <html>
            <head>
                <link rel="stylesheet" type="text/css" href="${cssPath}">
                <script type="text/javascript" src="https://unpkg.com/markdown-it/dist/markdown-it.min.js"></script>
                <script src="https://unpkg.com/adaptivecards/dist/adaptivecards.min.js"></script>
            </head>
            <body>
                <h1>${filename} Preview</h1>
                <div id='previewDiv' style="background-color:white;margin:8px 0px 20px 0px;"></div>
                <script>
                    var adaptiveCard = new AdaptiveCards.AdaptiveCard();
					adaptiveCard.hostConfig = new AdaptiveCards.HostConfig({
                        supportsInteractivity: true,
                        strongSeparation: {
                            spacing: 40,
                            lineThickness: 1,
                            lineColor: "#EEEEEE"
                        },
                        fontFamily: "Segoe UI",
                        fontSizes: {
                            small: 13,
                            normal: 15,
                            medium: 18,
                            large: 22,
                            extraLarge: 26
                        },
                        fontWeights: {
                            lighter: 200,
                            normal: 400,
                            bolder: 600
                        },
                        colors: {
                            dark: {
                                normal: "#333333",
                                subtle: "#EE333333"
                            },
                            light: {
                                normal: "#FFFFFF",
                                subtle: "#88FFFFFF"
                            },
                            accent: {
                                normal: "#2E89FC",
                                subtle: "#882E89FC"
                            },
                            attention: {
                                normal: "#cc3300",
                                subtle: "#DDcc3300"
                            },
                            good: {
                                normal: "#54a254",
                                subtle: "#DD54a254"
                            },
                            warning: {
                                normal: "#e69500",
                                subtle: "#DDe69500"
                            }
                        },
                        imageSizes: {
                            small: 40,
                            medium: 80,
                            large: 160
                        },
                        actions: {
                            maxActions: 5,
                            separation: {
                                spacing: 20
                            },
                            buttonSpacing: 10,
                            showCard: {
                                actionMode: "inlineEdgeToEdge",
                                inlineTopMargin: 16,
                                backgroundColor: "#08000000",
                                padding: {
                                    top: 16,
                                    right: 16,
                                    bottom: 16,
                                    left: 16
                                }
                            },
                            actionsOrientation: "horizontal",
                            actionAlignment: "stretch"
                        },
                        adaptiveCard: {
                            backgroundColor: "#00000000",
                            padding: {
                                left: 20,
                                top: 20,
                                right: 20,
                                bottom: 20
                            }
                        },
                        container: {
                            separation: {
                                spacing: 20
                            },
                            normal: {
                            },
                            emphasis: {
                                backgroundColor: "#EEEEEE",
                                borderColor: "#AAAAAA",
                                borderThickness: {
                                    top: 1,
                                    right: 1,
                                    bottom: 1,
                                    left: 1
                                },
                                padding: {
                                    top: 10,
                                    right: 10,
                                    bottom: 10,
                                    left: 10
                                }
                            }
                        },
                        textBlock: {
                            color: "dark",
                            separations: {
                                small: {
                                    spacing: 20,
                                },
                                normal: {
                                    spacing: 20
                                },
                                medium: {
                                    spacing: 20
                                },
                                large: {
                                    spacing: 20
                                },
                                extraLarge: {
                                    spacing: 20
                                }
                            }
                        },
                        image: {
                            size: "medium",
                            separation: {
                                spacing: 20
                            }
                        },
                        imageSet: {
                            imageSize: "medium",
                            separation: {
                                spacing: 20
                            }
                        },
                        factSet: {
                            separation: {
                                spacing: 20
                            },
                            title: {
                                color: "dark",
                                size: "normal",
                                isSubtle: false,
                                weight: "bolder",
                                wrap: true,
                                maxWidth: 150,
                            },
                            value: {
                                color: "dark",
                                size: "normal",
                                isSubtle: false,
                                weight: "normal",
                                wrap: true,
                            },
                            spacing: 10
                        },
                        input: {
                            separation: {
                                spacing: 20
                            }
                        },
                        columnSet: {
                            separation: {
                                spacing: 20
                            }
                        },
                        column: {
                            separation: {
                                spacing: 20
                            }
                        }
                    });

					adaptiveCard.parse(${json});
                    var renderedCard = adaptiveCard.render();

                    document.getElementById('previewDiv').appendChild(renderedCard);
                    AdaptiveCards.AdaptiveCard.onExecuteAction = function(action)
                    {
                        alert(JSON.stringify(action));
                    };

                </script>
            </body>
        </html>`;
    }
}

