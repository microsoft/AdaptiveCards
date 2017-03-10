import * as Adaptive from "../../Adaptive";
import * as Utils from "../../Utils";

import * as vkbeautify from "vkbeautify";

declare var SpeechSynthesisUtterance: any;

export abstract class HostContainer {
    readonly styleSheet: string;

    supportsActionBar: boolean = false;

    constructor(styleSheet: string) {
        this.styleSheet = styleSheet;
    }

    applyOptions() {
        Adaptive.AdaptiveCard.renderOptions.defaultActionButtonStyle = Adaptive.ActionButtonStyle.Link;
        Adaptive.AdaptiveCard.renderOptions.defaultTextColor = Adaptive.TextColor.Dark;
    }

    render(card: Adaptive.AdaptiveCard, showXml: boolean = false): HTMLElement {
        // speech visualizer
        let element = document.createElement("div");
        element.className = "speechContainer";

        let button = document.createElement("button");
        button.className = "button";
        button.innerText = "Speak this card";

        let t = document.createTextNode("Speak");
        let text = card.renderSpeech();
        let output = new Array<any>();

        if (text[0] == '<') {
            if (text.indexOf("<speak") != 0) {
                text = '<speak>\n' + text + '\n</speak>\n';
            }

            let parser = new DOMParser();
            let dom = parser.parseFromString(text, "text/xml");
            let nodes = dom.documentElement.childNodes;

            this.processNodes(nodes, output);

            let serializer = new XMLSerializer();
            
            text = vkbeautify.xml(serializer.serializeToString(dom));;
        }
        else {
            output.push(text);
            text = vkbeautify.xml(text);
        }

        // button.appendChild(t);
        button.addEventListener("click", function () {
            HostContainer.playNextTTS(output, 0);
        });

        Utils.appendChild(element, document.createElement("br"));
        Utils.appendChild(element, document.createElement("br"));
        // Utils.appendChild(element, document.createElement("hr"));
        
        Utils.appendChild(element, button);

        if (showXml) {
            let pre = document.createElement("pre");
            Utils.appendChild(pre, document.createTextNode(text));
            Utils.appendChild(element, pre);
        }

        //appendChild(pre, document.createTextNode(text));
        let audio = document.createElement("audio");
        audio.id = 'player';
        audio.autoplay = true;

        Utils.appendChild(element, audio);

        return element;
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

    static playNextTTS(output: any[], iCurrent: number) {
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
}

