@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ACRChoiceSetViewtests: XCTestCase {
    private var choiceSetView: ACRChoiceSetView!
    private var renderConfig: RenderConfig!
    
    override func setUp() {
        super.setUp()
        renderConfig = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: .default,checkBoxButtonConfig: nil, radioButtonConfig: nil, localisedStringConfig: nil)
        choiceSetView = ACRChoiceSetView(renderConfig: renderConfig)
    }
    
    func testRadioButtonClickAction() {
        choiceSetView.isRadioGroup = true
        let button1 = choiceSetView.setupButton(attributedString: NSMutableAttributedString(string: "1"), value: "Button1")
        let button2 = choiceSetView.setupButton(attributedString: NSMutableAttributedString(string: "2"), value: "Button2")
        // The clicking of the button is handled in ACRChoiceButton and ACRChoiceSetView parallely, with ACRChoiceSetView only making sure the previous radio button is turned off when another radio button is pressed
        // Therefore, to click on the button, button.performClick() is called, and to turn the other button off, choiceSetView.acrChoiceButtondidSelect() is called
        
        button1.button.performClick(nil)
        XCTAssertEqual(button1.state, .on)
        XCTAssertEqual(button2.state, .off)
        choiceSetView.acrChoiceButtonDidSelect(button1)
        XCTAssertEqual(button1.state, .on)
        XCTAssertEqual(button2.state, .off)
        choiceSetView.acrChoiceButtonDidSelect(button2)
        button2.button.performClick(nil)
        XCTAssertEqual(button1.state, .off)
        XCTAssertEqual(button2.state, .on)
    }
    
    func testChoiceSetRadioButtonAccessibility() {
        choiceSetView.isRadioGroup = true
        let button1 = choiceSetView.setupButton(attributedString: NSMutableAttributedString(string: "Button1"), value: "1")
        let button2 = choiceSetView.setupButton(attributedString: NSMutableAttributedString(string: "Button2"), value: "2")
        
        XCTAssertEqual(button1.accessibilityRole(), .radioButton)
        XCTAssertEqual(button1.accessibilityLabel(), "Button1")
        XCTAssertEqual(button2.accessibilityLabel(), "Button2")
    }
    
    func testChoiceSetCheckBoxButtonAccessibility() {
        choiceSetView.isRadioGroup = false
        let button1 = choiceSetView.setupButton(attributedString: NSMutableAttributedString(string: "Button1"), value: "1")
        let button2 = choiceSetView.setupButton(attributedString: NSMutableAttributedString(string: "Button2"), value: "2")
        
        XCTAssertEqual(button1.accessibilityRole(), .checkBox)
        XCTAssertEqual(button1.accessibilityLabel(), "Button1")
        XCTAssertEqual(button2.accessibilityLabel(), "Button2")
    }
}
