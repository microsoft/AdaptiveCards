"use strict";
var Utils = require("../../Utils");
var vkbeautify = require("vkbeautify");
var HostContainer = (function () {
    function HostContainer(styleSheet) {
        this.supportsActionBar = false;
        this.styleSheet = styleSheet;
    }
    HostContainer.prototype.render = function (card, showXml) {
        if (showXml === void 0) { showXml = false; }
        // speech visualizer
        var element = document.createElement("div");
        element.className = "speechContainer";
        var button = document.createElement("button");
        var t = document.createTextNode("Speak");
        var text = card.renderSpeech();
        var output = new Array();
        if (text[0] == '<') {
            if (text.indexOf("<speak") != 0)
                text = '<speak>\n' + text + '\n</speak>\n';
            var parser = new DOMParser();
            var dom = parser.parseFromString(text, "text/xml");
            var nodes = dom.documentElement.childNodes;
            this.processNodes(nodes, output);
            var serializer = new XMLSerializer();
            text = vkbeautify.xml(serializer.serializeToString(dom));
            ;
        }
        else {
            output.push(text);
            text = vkbeautify.xml(text);
        }
        button.appendChild(t);
        button.addEventListener("click", function () {
            HostContainer.playNextTTS(output, 0);
        });
        Utils.appendChild(element, document.createElement("br"));
        Utils.appendChild(element, document.createElement("br"));
        Utils.appendChild(element, document.createElement("hr"));
        Utils.appendChild(element, button);
        if (showXml) {
            var pre = document.createElement("pre");
            Utils.appendChild(pre, document.createTextNode(text));
            Utils.appendChild(element, pre);
        }
        //appendChild(pre, document.createTextNode(text));
        var audio = document.createElement("audio");
        audio.id = 'player';
        audio.autoplay = true;
        Utils.appendChild(element, audio);
        return element;
    };
    // process SSML markup into an array of either 
    // * utterenance
    // * number which is delay in msg
    // * url which is an audio file 
    HostContainer.prototype.processNodes = function (nodes, output) {
        for (var i = 0; i < nodes.length; i++) {
            var node = nodes[i];
            if (node.nodeName == 'p') {
                this.processNodes(node.childNodes, output);
                output.push(250);
            }
            else if (node.nodeName == 's') {
                this.processNodes(node.childNodes, output);
                output.push(100);
            }
            else if (node.nodeName == 'break') {
                if (node.attributes["strength"]) {
                    var strength = node.attributes["strength"].nodeValue;
                    if (strength == "weak") {
                    }
                    else if (strength == "medium") {
                        output.push(50);
                    }
                    else if (strength == "strong") {
                        output.push(100);
                    }
                    else if (strength == "x-strong") {
                        output.push(250);
                    }
                }
                else if (node.attributes["time"]) {
                    output.push(JSON.parse(node.attributes["time"].value));
                }
            }
            else if (node.nodeName == 'audio') {
                if (node.attributes["src"]) {
                    output.push(node.attributes["src"].value);
                }
            }
            else if (node.nodeName == 'say-as') {
                this.processNodes(node.childNodes, output);
            }
            else if (node.nodeName == 'w') {
                this.processNodes(node.childNodes, output);
            }
            else if (node.nodeName == 'phoneme') {
                this.processNodes(node.childNodes, output);
            }
            else {
                output.push(node.nodeValue);
            }
        }
    };
    HostContainer.playNextTTS = function (output, iCurrent) {
        if (iCurrent < output.length) {
            var current = output[iCurrent];
            if (typeof current === "number") {
                setTimeout(function () {
                    HostContainer.playNextTTS(output, iCurrent + 1);
                }, current);
            }
            else {
                if (current.indexOf("http") == 0) {
                    var audio = document.getElementById('player');
                    audio.src = current;
                    audio.onended = function () {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    audio.onerror = function () {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    audio.play();
                }
                else {
                    var msg = new SpeechSynthesisUtterance();
                    //msg.voiceURI = 'native';
                    // msg.volume = 1; // 0 to 1
                    // msg.rate = 1; // 0.1 to 10
                    // msg.pitch = 2; //0 to 2
                    msg.text = current;
                    msg.lang = 'en-US';
                    msg.onerror = function (event) {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    msg.onend = function (event) {
                        HostContainer.playNextTTS(output, iCurrent + 1);
                    };
                    window.speechSynthesis.speak(msg);
                }
            }
        }
    };
    return HostContainer;
}());
exports.HostContainer = HostContainer;
//# sourceMappingURL=HostContainer.js.map