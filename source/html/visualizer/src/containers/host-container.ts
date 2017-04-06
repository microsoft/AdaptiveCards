import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";
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

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        return null;
    }

    protected renderSpeech(speechString: string, showXml: boolean = false): HTMLElement {
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

        Utils.appendChild(element, button);

        if (showXml) {
            let pre = document.createElement("pre");
            Utils.appendChild(pre, document.createTextNode(speechString));
            Utils.appendChild(element, pre);
        }

        var audio = document.createElement("audio");
        audio.id = 'player';
        audio.autoplay = true;

        Utils.appendChild(element, audio);

        return element;
    }

    readonly styleSheet: string;

    supportsActionBar: boolean = false;

    constructor(styleSheet: string) {
        this.styleSheet = styleSheet;
    }

    applyOptions() {
        Adaptive.AdaptiveCard.renderOptions.defaultTextColor = Adaptive.TextColor.Dark;
    }

    render(renderedCard: HTMLElement, speechString: string, showSpeechXml: boolean = false): HTMLElement {
        var element = document.createElement("div");
        var renderedContainer = this.renderContainer(renderedCard);

        if (renderedContainer) {
            element.appendChild(renderedContainer);

            var separator = document.createElement("div");
            separator.style.height = "20px";

            element.appendChild(separator);
        }

        element.appendChild(this.renderSpeech(speechString));

        return element;
    }
}

