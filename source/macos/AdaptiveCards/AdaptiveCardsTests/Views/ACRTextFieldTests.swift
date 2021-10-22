@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ACRTextFieldTests: XCTestCase {
    private var textField: ACRTextField!
    private var config: RenderConfig!
    private var delegate: FakeACRTextFieldDelegate!
    
    override func setUp() {
        super.setUp()
        let inputFieldConfig = InputFieldConfig(height: 26, leftPadding: 8, rightPadding: 8, yPadding: 0, focusRingCornerRadius: 8, borderWidth: 0.3, wantsClearButton: true, clearButtonImage: NSImage(), calendarImage: nil, clockImage: nil, font: .systemFont(ofSize: 14), highlightedColor: NSColor(red: 0, green: 0, blue: 0, alpha: 0.11), backgroundColor: NSColor(red: 1, green: 1, blue: 1, alpha: 1), borderColor: .black, activeBorderColor: .black, placeholderTextColor: NSColor.placeholderTextColor, multilineFieldInsets: NSEdgeInsets(top: 5, left: 10, bottom: 0, right: 0))
        config = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: inputFieldConfig, checkBoxButtonConfig: nil, radioButtonConfig: nil)
        textField = ACRTextField(config: config)
        delegate = FakeACRTextFieldDelegate()
    }
    
    func testClearButtonAbsentDefault() {
        XCTAssertTrue(textField.clearButton.isHidden)
    }
    
    func testClearButtonPresent() {
        textField.attributedStringValue = NSAttributedString(string: "Test")
        XCTAssertFalse(textField.clearButton.isHidden)
    }
    
    func testNoClearButtonDefaultRenderConfig() {
        textField = ACRTextField(config: .default)
        XCTAssertTrue(textField.subviews.isEmpty)
    }
    
    func testClearButtonPerformsDelete() {
        textField.attributedStringValue = NSAttributedString(string: "Test")
        XCTAssertFalse(textField.clearButton.isHidden)
        textField.clearButton.performClick()
        XCTAssertTrue(textField.clearButton.isHidden)
        XCTAssertEqual(textField.stringValue, "")
    }
    
    func testChangingRenderConfigChangesProperties() {
        let image = NSImage()
        let inputFieldConfig = InputFieldConfig(height: 40, leftPadding: 20, rightPadding: 20, yPadding: 0, focusRingCornerRadius: 10, borderWidth: 1, wantsClearButton: true, clearButtonImage: image, calendarImage: nil, clockImage: nil, font: .systemFont(ofSize: 10), highlightedColor: .blue, backgroundColor: .yellow, borderColor: .green, activeBorderColor: .black, placeholderTextColor: NSColor.placeholderTextColor, multilineFieldInsets: NSEdgeInsets(top: 5, left: 10, bottom: 0, right: 0))
        config = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: inputFieldConfig, checkBoxButtonConfig: nil, radioButtonConfig: nil)
        textField = ACRTextField(config: config)
        XCTAssertEqual(textField.fittingSize.height, 40)
        XCTAssertEqual(textField.cell?.titleRect(forBounds: textField.bounds).origin.x, 20)
        XCTAssertEqual(textField.font, .systemFont(ofSize: 10))
        XCTAssertEqual(textField.clearButton.image?.hash, image.hash)
    }
    
    func testDateFieldContainsClearButtonAlways() {
        let textField = ACRTextField(dateTimeFieldWith: .default)
        textField.stringValue = "test"
        XCTAssertEqual(textField.subviews.count, 1)
        XCTAssertEqual(textField.subviews[0].className, NSButtonWithImageSpacing().className)
        XCTAssertFalse(textField.clearButton.isHidden)
    }
    
    func testDateFieldLeftPadding() {
        let textField = ACRTextField(dateTimeFieldWith: .default)
        // Left padding 20 for the image
        XCTAssertEqual(textField.cell?.titleRect(forBounds: textField.bounds).origin.x, 20)
    }
    
    func testTextFieldDelegateCalled() {
        textField.textFieldDelegate = delegate
        textField.stringValue = "test"
        XCTAssertFalse(delegate.isTextFieldCalled)
        textField.clearButton.performClick()
        XCTAssertTrue(delegate.isTextFieldCalled)
        XCTAssertEqual(delegate.textFieldStringValue, "")
    }
}

private class FakeACRTextFieldDelegate: ACRTextFieldDelegate {
    var isTextFieldCalled = false
    var textFieldStringValue: String?
    func acrTextFieldDidSelectClear(_ textField: ACRTextField) {
        isTextFieldCalled = true
        textFieldStringValue = textField.stringValue
    }
}
