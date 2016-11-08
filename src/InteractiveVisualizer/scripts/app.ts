/// <reference path="adaptiveCard.ts" />

var editor;
var markdownProcessor;

function renderCard() {
    try {
        let json: string = JSON.parse(editor.getValue());
        let cardTypeName: string = json["type"];

        if (cardTypeName === undefined) {
           cardTypeName = "AdaptiveCard";
        }

        let renderedCard: HTMLElement;

        switch (cardTypeName) {

            case "AdaptiveCard":
                let adaptiveCard = new AdaptiveCard();
                adaptiveCard.parse(json);

                renderedCard = adaptiveCard.render();
                break;
            default:
                throw new Error("Unknown card type: " + cardTypeName);
        }

        var node = document.getElementById('content');

        node.innerHTML = '';
        node.appendChild(renderedCard);

        var anchors = node.getElementsByTagName("a");

        for (var i = 0; i < anchors.length; i++) {
            anchors[i].target = "_blank";
        }

        var paragraphs = node.getElementsByTagName("p");

        for (var i = 0; i < paragraphs.length; i++) {
            paragraphs[i].style.margin = "0";
        }
    }
    catch (e) {
        document.getElementById('content').innerHTML = "Error: " + e.toString();
    }
}

function textareaChange() {
    renderCard();
}

function openFilePicker() {
    document.getElementById("filePicker").click();
}

function filePickerChanged(evt) {
    let filePicker = document.getElementById("filePicker") as HTMLInputElement;

    let file = filePicker.files[0];

    if (file) {
        let reader = new FileReader();

        reader.onload = function (e: ProgressEvent) {
            editor.session.setValue((e.target as FileReader).result);
        }

        reader.readAsText(file);
    }
    else {
        alert("Failed to load file");
    }
}

function processMarkdown(text: string): any {
    return markdownProcessor.render(text);
}

window.onload = () => {
    let filePicker = document.getElementById("filePicker");
    filePicker.addEventListener("change", filePickerChanged);

    renderCard();
};