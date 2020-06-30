// This script will be run within the webview itself
// It cannot access the main VS Code APIs directly.
(function () {
       const vscode = acquireVsCodeApi();
       $(document).ready(function(){
               
            // Create an AdaptiveCard instance
            var adaptiveCard = new AdaptiveCards.AdaptiveCard();

            // Use Fabric controls when rendering Adaptive Cards
            //ACFabric.useFabricComponents();

            // Example Host Config from MS Teams Dark
            var hostConfig = {
                "choiceSetInputValueSeparator": ",",
                "supportsInteractivity": true,
                "spacing": {
                    "small": 8,
                    "default": 12,
                    "medium": 16,
                    "large": 20,
                    "extraLarge": 24,
                    "padding": 16
                },
                "separator": {
                    "lineThickness": 1,
                    "lineColor": "#EEEEEE"
                },
                "fontStyles": {
                    "default": {
                        "fontFamily": "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif",
                        "fontSizes": {
                            "small": 12,
                            "default": 14,
                            "medium": 14,
                            "large": 18,
                            "extraLarge": 24
                        },
                        "fontWeights": {
                            "lighter": 200,
                            "default": 400,
                            "bolder": 600
                        }
                    },
                    "monospace": {
                        "fontFamily": "'Courier New', Courier, monospace",
                        "fontSizes": {
                            "small": 12,
                            "default": 14,
                            "medium": 14,
                            "large": 18,
                            "extraLarge": 24
                        },
                        "fontWeights": {
                            "lighter": 200,
                            "default": 400,
                            "bolder": 600
                        }
                    }
                },
                "imageSizes": {
                    "small": 24,
                    "medium": 36,
                    "large": 100
                },
                "containerStyles": {
                    "default": {
                        "foregroundColors": {
                            "default": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "dark": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "light": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "accent": {
                                "default": "#ffa6a7dc",
                                "subtle": "#ff8b8cc7"
                            },
                            "good": {
                                "default": "#ff92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#fff8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#ffd74654",
                                "subtle": "#e5d74654"
                            }
                        },
                        "backgroundColor": "#ff2d2c2c"
                    },
                    "emphasis": {
                        "foregroundColors": {
                            "default": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "dark": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "light": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "accent": {
                                "default": "#ffa6a7dc",
                                "subtle": "#ff8b8cc7"
                            },
                            "good": {
                                "default": "#ff92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#fff8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#ffd74654",
                                "subtle": "#e5d74654"
                            }
                        },
                        "backgroundColor": "#ff292828"
                    },
                    "accent": {
                        "backgroundColor": "#C7DEF9",
                        "foregroundColors": {
                            "default": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "dark": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "light": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "accent": {
                                "default": "#ffa6a7dc",
                                "subtle": "#ff8b8cc7"
                            },
                            "good": {
                                "default": "#ff92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#fff8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#ffd74654",
                                "subtle": "#e5d74654"
                            }
                        }
                    },
                    "good": {
                        "backgroundColor": "#CCFFCC",
                        "foregroundColors": {
                            "default": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "dark": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "light": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "accent": {
                                "default": "#ffa6a7dc",
                                "subtle": "#ff8b8cc7"
                            },
                            "good": {
                                "default": "#ff92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#fff8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#ffd74654",
                                "subtle": "#e5d74654"
                            }
                        }
                    },
                    "attention": {
                        "backgroundColor": "#FFC5B2",
                        "foregroundColors": {
                            "default": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "dark": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "light": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "accent": {
                                "default": "#ffa6a7dc",
                                "subtle": "#ff8b8cc7"
                            },
                            "good": {
                                "default": "#ff92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#fff8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#ffd74654",
                                "subtle": "#e5d74654"
                            }
                        }
                    },
                    "warning": {
                        "backgroundColor": "#FFE2B2",
                        "foregroundColors": {
                            "default": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "dark": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "light": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "accent": {
                                "default": "#ffa6a7dc",
                                "subtle": "#ff8b8cc7"
                            },
                            "good": {
                                "default": "#ff92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#fff8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#ffd74654",
                                "subtle": "#e5d74654"
                            }
                        }
                    }
                },
                "actions": {
                    "maxActions": 6,
                    "spacing": "Default",
                    "buttonSpacing": 8,
                    "showCard": {
                        "actionMode": "Inline",
                        "inlineTopMargin": 16,
                        "style": "emphasis"
                    },
                    "preExpandSingleShowCardAction": false,
                    "actionsOrientation": "Horizontal",
                    "actionAlignment": "Left"
                },
                "adaptiveCard": {
                    "allowCustomStyle": false
                },
                "imageSet": {
                    "imageSize": "Medium",
                    "maxImageHeight": 100
                },
                "factSet": {
                    "title": {
                        "size": "Default",
                        "color": "Default",
                        "isSubtle": false,
                        "weight": "Bolder",
                        "warp": true
                    },
                    "value": {
                        "size": "Default",
                        "color": "Default",
                        "isSubtle": false,
                        "weight": "Default",
                        "warp": true
                    },
                    "spacing": 16
                }
            };
            adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(hostConfig);
        
            // Adaptive Cards - Actions
            adaptiveCard.onExecuteAction = function (action) {
                  vscode.postMessage({
                     command: 'action',
                     text: JSON.stringify(action._processedData)
                 })
            };

            var cardPayload = $('#divData').text();
            // Parse the card payload
            adaptiveCard.parse(JSON.parse(cardPayload));

            // Render the card to an HTML element:
            var renderedCard = adaptiveCard.render();

            $('#exampleDiv').append(renderedCard).show();
       })

}());