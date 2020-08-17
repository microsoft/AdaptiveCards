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
                <script src="${this.getPath('node_modules/microsoft-adaptivecards/dist/adaptive-cards.js')}"></script>
            </head>
            <body>
                <h1>Adaptive Card Preview</h1>
                <div id='previewDiv' style="background-color:white;margin:8px 0px 20px 0px;"></div>
                <script>
                    AdaptiveCards.setHostConfig({
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
                                normal: "#028A02",
                                subtle: "#DD027502"
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

                    var adaptiveCard = new AdaptiveCards.AdaptiveCard();
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
