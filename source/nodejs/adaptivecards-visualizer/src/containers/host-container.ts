import {
    AdaptiveCard,
    HostConfig,
    Size,
    TextSize,
    TextColor,
    TextWeight,
    Spacing,
    ShowCardActionMode,
    Orientation,
    ActionAlignment,
    CardElement
} from "adaptivecards";
import * as vkbeautify from "vkbeautify";

declare var SpeechSynthesisUtterance: any;

export abstract class HostContainer {
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
                    //msg.voiceURI = 'native';
                    // msg.volume = 1; // 0 to 1
                    // msg.rate = 1; // 0.1 to 10
                    // msg.pitch = 2; //0 to 2
                    msg.text = current;
                    msg.lang = 'en-US';
                    msg.onerror = (event) => {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    msg.onend = (event) => {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    (<any>window).speechSynthesis.speak(msg);
                }
            }
        }
    }

    // process SSML markup into an array of either 
    // * utterenance
    // * number which is delay in msg
    // * url which is an audio file 
    private processNodes(nodes: NodeList, output: any[]): void {
        for (let i = 0; i < nodes.length; i++) {
            let node = nodes[i];
            if (node.nodeName == 'p') {
                this.processNodes(node.childNodes, output);
                output.push(250);
            } else if (node.nodeName == 's') {
                this.processNodes(node.childNodes, output);
                output.push(100);
            } else if (node.nodeName == 'break') {
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
                } else if (node.attributes["time"]) {
                    output.push(JSON.parse(node.attributes["time"].value));
                }
            } else if (node.nodeName == 'audio') {
                if (node.attributes["src"]) {
                    output.push(node.attributes["src"].value);
                }
            } else if (node.nodeName == 'say-as') {
                this.processNodes(node.childNodes, output);
            } else if (node.nodeName == 'w') {
                this.processNodes(node.childNodes, output);
            } else if (node.nodeName == 'phoneme') {
                this.processNodes(node.childNodes, output);
            } else {
                output.push(node.nodeValue);
            }
        }
    }

    public initialize() {
        AdaptiveCard.elementTypeRegistry.reset();
        AdaptiveCard.actionTypeRegistry.reset();
        AdaptiveCard.useAutomaticContainerBleeding = false;
        AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = true;
    }

    public parseElement(element: CardElement, json: any) {
        // Do nothing in base implementation
    }

    public anchorClicked(rootCard: AdaptiveCard, anchor: HTMLAnchorElement): boolean {
        // Not handled by the host container by default
        return false;
    }

    public getHostConfig(): HostConfig {
        return new HostConfig({
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
                spacing: Spacing.Default,
                buttonSpacing: 20,
                showCard: {
                    actionMode: ShowCardActionMode.Inline,
                    inlineTopMargin: 16
                },
                actionsOrientation: Orientation.Horizontal,
                actionAlignment: ActionAlignment.Left
            },
            adaptiveCard: {
                allowCustomStyle: false
            },
            imageSet: {
                imageSize: Size.Medium,
                maxImageHeight: 100
            },
            factSet: {
                title: {
                    color: TextColor.Default,
                    size: TextSize.Default,
                    isSubtle: false,
                    weight: TextWeight.Bolder,
                    wrap: true,
                    maxWidth: 150
                },
                value: {
                    color: TextColor.Default,
                    size: TextSize.Default,
                    isSubtle: false,
                    weight: TextWeight.Default,
                    wrap: true
                },
                spacing: 10
            }
        });
    }

    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement): HTMLElement {
        return null;
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

    readonly styleSheet: string;

    supportsActionBar: boolean = false;

    constructor(styleSheet: string) {
        this.styleSheet = styleSheet;
    }

    render(adaptiveCard: AdaptiveCard, target: HTMLElement, showSpeechXml: boolean = false): HTMLElement {
        var element = document.createElement("div");
        target.appendChild(element);

        if (adaptiveCard) {
            var renderedContainer = this.renderContainer(adaptiveCard, element);

            if (renderedContainer) {
                var separator = document.createElement("div");
                separator.style.height = "20px";
                element.appendChild(separator);
            }

            var renderedSpeech = this.renderSpeech(adaptiveCard.renderSpeech());

            if (renderedSpeech) {
                element.appendChild(renderedSpeech);
            }
        }
        else {
            element.innerText = "The card is empty."
        }

        return element;
    }
}

