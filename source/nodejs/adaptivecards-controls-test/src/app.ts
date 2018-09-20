import * as AdaptiveCardsControls from "adaptivecards-controls";

window.onload = function (e) {
    // MsControls.initializeControls();
    var checkBox = new AdaptiveCardsControls.CheckBox();
    // checkBox.onchange = (sender) => { alert("Changed!") };
    checkBox.attach(document.getElementById("myCheckBox"));

    new AdaptiveCardsControls.RadioButton().attach(document.getElementById("myRadioButton1"));
    new AdaptiveCardsControls.RadioButton().attach(document.getElementById("myRadioButton2"));
    new AdaptiveCardsControls.DropDown().attach(document.getElementById("myDropDown"));
    new AdaptiveCardsControls.DatePicker().attach(document.getElementById("myDatePicker"));

    var textBox = new AdaptiveCardsControls.TextBox();
    /*
    textBox.onChange = (sender) => {
        document.getElementById("myTextBoxOnChangeTest").innerText = sender.value;
    };
    */
    textBox.attach(document.getElementById("myTextBox"));

    var multilineTextBox = new AdaptiveCardsControls.TextBox();
    /*
    multilineTextBox.onChange = (sender) => {
        document.getElementById("myMultilineTextBoxOnChangeTest").innerText = sender.value;
    };
    */
    multilineTextBox.attach(document.getElementById("myMultilineTextBox"));
};