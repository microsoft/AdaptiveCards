@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ACRTextFieldTests: XCTestCase {
    private var textField: ACRTextField!
    private var config: RenderConfig!
    
    override func setUp() {
        super.setUp()
        let inputFieldConfig = InputFieldConfig(height: 26, leftPadding: 8, rightPadding: 8, yPadding: 0, focusRingCornerRadius: 8, borderWidth: 0.3, wantsClearButton: true, clearButtonImage: NSImage(), font: .systemFont(ofSize: 14), highlightedColor: NSColor(red: 0, green: 0, blue: 0, alpha: 0.11), backgroundColor: NSColor(red: 1, green: 1, blue: 1, alpha: 1), borderColor: .black)
        config = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: inputFieldConfig, checkBoxButtonConfig: nil, radioButtonConfig: nil)
        textField = ACRTextField(frame: .zero, config: config)
    }
    
    func testClearButtonAbsentDefault() {
        XCTAssertTrue(textField.clearButton.isHidden)
    }
    
    func testClearButtonPresent() {
        textField.attributedStringValue = NSAttributedString(string: "Test")
        XCTAssertFalse(textField.clearButton.isHidden)
    }
    
    func testNoClearButtonDefaultRenderConfig() {
        textField = ACRTextField(frame: .zero, config: RenderConfig.default)
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
        let inputFieldConfig = InputFieldConfig(height: 40, leftPadding: 20, rightPadding: 20, yPadding: 0, focusRingCornerRadius: 10, borderWidth: 1, wantsClearButton: true, clearButtonImage: image, font: .systemFont(ofSize: 10), highlightedColor: .blue, backgroundColor: .yellow, borderColor: .green)
        let config = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: inputFieldConfig, checkBoxButtonConfig: nil, radioButtonConfig: nil)
        textField = ACRTextField(frame: .zero, config: config)
        XCTAssertEqual(textField.fittingSize.height, 40)
        XCTAssertEqual(textField.cell?.titleRect(forBounds: textField.bounds).origin.x, 20)
        XCTAssertEqual(textField.font, .systemFont(ofSize: 10))
        XCTAssertEqual(textField.clearButton.image?.hash, image.hash)
    }
}
