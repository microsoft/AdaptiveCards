import * as Adaptive from "adaptivecards";
import * as vkbeautify from "vkbeautify";

export abstract class HostContainer {
    private _cardHost: HTMLElement;

    readonly name: string;
    readonly styleSheet: string;

    constructor(name: string, styleSheet: string) {
        this.name = name;
        this.styleSheet = styleSheet;

        this._cardHost = document.createElement("div");
    }

    abstract renderTo(hostElement: HTMLElement);

    private static playNextTTS(output: any[], iCurrent: number) {
        if (iCurrent < output.length) {
            let current = output[iCurrent];
            if (typeof current === "number") {
                setTimeout(() => {
                    HostContainer.playNextTTS(output, iCurrent + 1);
                }, current);
            } else {
                if (current.indexOf("http") == 0) {
                    let audio: any = document.getElementById('player');
                    audio.src = current;
                    audio.onended = () => {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    audio.onerror = () => {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    audio.play();
                } else {
                    let msg = new SpeechSynthesisUtterance();
                    msg.text = current;
                    msg.lang = 'en-US';
                    msg.onerror = () => {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    msg.onend = () => {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    (<any>window).speechSynthesis.speak(msg);
                }
            }
        }
    }

    public initialize() {
        Adaptive.AdaptiveCard.elementTypeRegistry.reset();
        Adaptive.AdaptiveCard.actionTypeRegistry.reset();
        Adaptive.AdaptiveCard.useAutomaticContainerBleeding = false;
        Adaptive.AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = true;
    }

    public parseElement(element: Adaptive.CardElement, json: any) {
        // Do nothing in base implementation
    }

    public anchorClicked(rootCard: Adaptive.AdaptiveCard, anchor: HTMLAnchorElement): boolean {
        // Not handled by the host container by default
        return false;
    }

    private processNodes(nodes: NodeList, output: any[]): void {
        for (let i = 0; i < nodes.length; i++) {
            let node = nodes[i];

            if (node.nodeName == "p") {
                this.processNodes(node.childNodes, output);
                output.push(250);
            }
            else if (node.nodeName == "s") {
                this.processNodes(node.childNodes, output);
                output.push(100);
            }
            else if (node.nodeName == "break" && node instanceof Element) {
                if (node.attributes["strength"]) {
                    let strength = node.attributes["strength"].nodeValue;

                    if (strength == "weak") {
                        // output.push(50);
                    } else if (strength == "medium") {
                        output.push(50);
                    } else if (strength == "strong") {
                        output.push(100);
                    } else if (strength == "x-strong") {
                        output.push(250);
                    }
                }
                else if (node.attributes["time"]) {
                    output.push(JSON.parse(node.attributes["time"].value));
                }
            }
            else if (node.nodeName == "audio" && node instanceof Element) {
                if (node.attributes["src"]) {
                    output.push(node.attributes["src"].value);
                }
            }
            else if (node.nodeName == "say-as") {
                this.processNodes(node.childNodes, output);
            }
            else if (node.nodeName == "w") {
                this.processNodes(node.childNodes, output);
            }
            else if (node.nodeName == "phoneme") {
                this.processNodes(node.childNodes, output);
            }
            else {
                output.push(node.nodeValue);
            }
        }
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig({
            preExpandSingleShowCardAction: false,
            spacing: {
                small: 3,
                default: 8,
                medium: 20,
                large: 30,
                extraLarge: 40,
                padding: 20
            },
            separator: {
                lineThickness: 1,
                lineColor: "#EEEEEE"
            },
            supportsInteractivity: true,
            fontFamily: "Segoe UI",
            fontSizes: {
                small: 12,
                default: 14,
                medium: 17,
                large: 21,
                extraLarge: 26
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 600
            },
            containerStyles: {
                default: {
                    backgroundColor: "#00000000",
                    foregroundColors: {
                        default: {
                            default: "#333333",
                            subtle: "#EE333333"
                        },
                        accent: {
                            default: "#2E89FC",
                            subtle: "#882E89FC"
                        },
                        attention: {
                            default: "#FFD800",
                            subtle: "#DDFFD800"
                        },
                        good: {
                            default: "#00FF00",
                            subtle: "#DD00FF00"
                        },
                        warning: {
                            default: "#FF0000",
                            subtle: "#DDFF0000"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "08000000",
                    foregroundColors: {
                        default: {
                            default: "#333333",
                            subtle: "#EE333333"
                        },
                        accent: {
                            default: "#2E89FC",
                            subtle: "#882E89FC"
                        },
                        attention: {
                            default: "#FFD800",
                            subtle: "#DDFFD800"
                        },
                        good: {
                            default: "#00FF00",
                            subtle: "#DD00FF00"
                        },
                        warning: {
                            default: "#FF0000",
                            subtle: "#DDFF0000"
                        }
                    }
                }
            },
            imageSizes: {
                small: 40,
                medium: 80,
                large: 160
            },
            actions: {
                maxActions: 5,
                spacing: Adaptive.Spacing.Default,
                buttonSpacing: 20,
                showCard: {
                    actionMode: Adaptive.ShowCardActionMode.Inline,
                    inlineTopMargin: 16
                },
                actionsOrientation: Adaptive.Orientation.Horizontal,
                actionAlignment: Adaptive.ActionAlignment.Left
            },
            adaptiveCard: {
                allowCustomStyle: false
            },
            imageSet: {
                imageSize: Adaptive.Size.Medium,
                maxImageHeight: 100
            },
            factSet: {
                title: {
                    color: Adaptive.TextColor.Default,
                    size: Adaptive.TextSize.Default,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Bolder,
                    wrap: true,
                    maxWidth: 150
                },
                value: {
                    color: Adaptive.TextColor.Default,
                    size: Adaptive.TextSize.Default,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Default,
                    wrap: true
                },
                spacing: 10
            }
        });
    }

    protected renderSpeech(speechString: string, showXml: boolean = false): HTMLElement {
        if (!speechString) {
            return null;
        }

        var element = document.createElement("div");

        var button = document.createElement("button");
        button.className = "button";
        button.innerText = "Speak this card";

        var t = document.createTextNode("Speak");
        var output = new Array<any>();

        if (speechString[0] == '<') {
            if (speechString.indexOf("<speak") != 0) {
                speechString = '<speak>\n' + speechString + '\n</speak>\n';
            }

            var parser = new DOMParser();
            var dom = parser.parseFromString(speechString, "text/xml");
            var nodes = dom.documentElement.childNodes;

            this.processNodes(nodes, output);

            var serializer = new XMLSerializer();

            speechString = vkbeautify.xml(serializer.serializeToString(dom));;
        }
        else {
            output.push(speechString);
            speechString = vkbeautify.xml(speechString);
        }

        button.addEventListener("click", function () {
            HostContainer.playNextTTS(output, 0);
        });

        element.appendChild(button);

        if (showXml) {
            let pre = document.createElement("pre");
            pre.appendChild(document.createTextNode(speechString));
            element.appendChild(pre);
        }

        var audio = document.createElement("audio");
        audio.id = 'player';
        audio.autoplay = true;

        element.appendChild(audio);

        return element;
    }

    supportsActionBar: boolean = false;

    get cardHost(): HTMLElement {
        return this._cardHost;
    }
}

