import * as Controls from "../../adaptivecards-controls/src/adaptivecards-controls";

export function sayHello() {
    let colorPickerPanel = new Controls.ColorPickerPanel();

    document.getElementById("colorPickerPanel").appendChild(colorPickerPanel.renderedElement);

    let colorPicker = new Controls.ColorPicker();
    colorPicker.placeholderText = "Pick a color";

    colorPicker.attach(document.getElementById("colorPicker"));
}

window.onload = function() {
    sayHello();
};