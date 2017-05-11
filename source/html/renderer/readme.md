`<!DOCTYPE html>
        <html>
            <head>
                <link rel="stylesheet" type="text/css" href="${this.getPath('media/export.css')}">
                <script src="${this.getPath('node_modules/adaptive-cards/dist/adaptive-cards.js')}"></script>
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
                            small: 12,
                            normal: 14,
                            medium: 17,
                            large: 21,
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

                    AdaptiveCards.AdaptiveCard.onExecuteAction = function (action) {
                        var message = "Action executed\n";
                        message += "    Title: " + action.title + "\n";

                        if (action instanceof AdaptiveCards.OpenUrlAction) {
                            message += "    Type: OpenUrl\n";
                            message += "    Url: " + action.url + "\n";
                        }
                        else if (action instanceof AdaptiveCards.SubmitAction) {
                            message += "    Type: Submit";
                            message += "    Data: " + JSON.stringify(action.data);
                        }
                        else if (action instanceof AdaptiveCards.HttpAction) {
                            var httpAction = action;
                            message += "    Type: Http\n";
                            message += "    Url: " + httpAction.url + "\n";
                            message += "    Method: " + httpAction.method + "\n";
                            message += "    Headers:\n";

                            for (var i = 0; i < httpAction.headers.length; i++) {
                                message += "        " + httpAction.headers[i].name + ": " + httpAction.headers[i].value + "\n";
                            }
                            message += "    Body: " + httpAction.body + "\n";
                        }
                        else {
                            message += "    Type: <unknown>";
                        }

                        alert(message);
                    }

                    var adaptiveCard = new AdaptiveCards.AdaptiveCard();
                    adaptiveCard.parse({
	"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	"type": "AdaptiveCard",
	"body": [
		{
			"type": "Container",
			"speak": "<s>Card created by Miguel Garcia: Publish Adaptive Card schema</s>",
			"items": [
				{
					"type": "TextBlock",
					"text": "Card created: Publish Adaptive Card schema",
					"weight": "bolder",
					"size": "medium"
				},
				{
					"type": "ColumnSet",
					"columns": [
						{
							"type": "Column",
							"size": "auto",
							"items": [
								{
									"type": "Image",
									"url": "http://connectorsdemo.azurewebsites.net/images/MSC12_Oscar_002.jpg",
									"size": "small",
									"style": "person"
								}
							]
						},
						{
							"type": "Column",
							"size": "stretch",
							"items": [
								{
									"type": "TextBlock",
									"text": "**Miguel Garcia**",
									"wrap": true
								},
								{
									"type": "TextBlock",
									"separation": "none",
									"text": "Created {{DATE(2017-02-14T06:08:39Z,Long)}} {{TIME(2017-02-14T06:08:39Z)}}",
									"isSubtle": true,
									"wrap": true
								}
							]
						}
					]
				}
			]
		},
		{
			"type": "Container",
			"items": [
				{
					"type": "TextBlock",
					"text": "Now that we have define the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation.",
					"speak": "",
					"wrap": true
				},
				{
					"type": "FactSet",
					"speak": "It has been assigned to: David Claux",
					"facts": [
						{
							"title": "Board:",
							"value": "Adaptive Card"
						},
						{
							"title": "List:",
							"value": "Backlog"
						},
						{
							"title": "Assigned to:",
							"value": "David Claux"
						},
						{
							"title": "Due date:",
							"value": "Not set"
						}
					]
				}
			]
		}
	],
	"actions": [
		{
			"type": "Action.ShowCard",
			"title": "Set due date",
			"card": {
				"type": "AdaptiveCard",
				"body": [
					{
						"type": "Input.Date",
						"id": "dueDate",
						"title": "Select due date"
					}
				],
				"actions": [
				    {
				        "type": "Action.Http",
				        "title": "OK",
				        "url": "http://xyz.com",
                        "headers": {
							"content-type": "application/json"
						},
						"body": "{ 'comment' : '{{comment.value}}' }"
				    }
				]
			}
		},
		{
			"type": "Action.ShowCard",
			"title": "Comment",
			"card": {
				"type": "AdaptiveCard",
				"body": [
					{
						"type": "Input.Text",
						"id": "comment",
						"isMultiline": true,
						"placeholder": "Enter your comment"
					}
				],
				"actions": [
					{
						"type": "Action.Http",
						"method": "POST",
						"title": "OK",
						"url": "http://xyz.com",
						"headers": {
							"content-type": "application/json"
						},
						"body": "{ 'comment' : '{{comment.value}}' }"
					}
				]
			}
		},
		{
			"type": "Action.OpenUrl",
			"title": "View",
			"url": "http://foo.com"
		}
	]
});
                    var renderedCard = adaptiveCard.render();
                    
                    document.getElementById('previewDiv').appendChild(renderedCard);
                    AdaptiveCards.AdaptiveCard.onExecuteAction = function(action) 
                    {
                        alert(JSON.stringify(action));
                    };
                </script>
            </body>
        </html>