/// <reference path="adaptiveCard.ts" />
var editor;
var markdownProcessor;
function renderCard() {
    try {
        var json = JSON.parse(editor.getValue());
        var cardTypeName = json["type"];
        if (cardTypeName === undefined) {
            cardTypeName = "AdaptiveCard";
        }
        var renderedCard = void 0;
        switch (cardTypeName) {
            case "AdaptiveCard":
                var adaptiveCard = new AdaptiveCard();
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
    var filePicker = document.getElementById("filePicker");
    var file = filePicker.files[0];
    if (file) {
        var reader = new FileReader();
        reader.onload = function (e) {
            editor.session.setValue(e.target.result);
        };
        reader.readAsText(file);
    }
    else {
        alert("Failed to load file");
    }
}
function processMarkdown(text) {
    return markdownProcessor.render(text);
}
window.onload = function () {
    var filePicker = document.getElementById("filePicker");
    filePicker.addEventListener("change", filePickerChanged);
    renderCard();
};
//# sourceMappingURL=app.js.map