@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class MultiLineInputTextViewTests: XCTestCase {
    private var multiLineInputTextView: ACRMultilineInputTextView!
    private var renderConfig: RenderConfig!
    
    override func setUp() {
        super.setUp()
        renderConfig = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: setupInputField(), checkBoxButtonConfig: nil, radioButtonConfig: nil)
        multiLineInputTextView = ACRMultilineInputTextView(config: setupInputField())
    }
    
    func testLeftPadding() {
        XCTAssertEqual(multiLineInputTextView.textView.textContainerInset.width, renderConfig.inputFieldConfig.multilineFieldInsets.left)
    }
    
    func testTopPadding() {
        XCTAssertEqual(multiLineInputTextView.textView.textContainerInset.height, renderConfig.inputFieldConfig.multilineFieldInsets.top)
    }
    
    func testInitialBackgroundColor() {
        XCTAssertEqual(multiLineInputTextView.textView.backgroundColor, renderConfig.inputFieldConfig.backgroundColor)
    }
    
    func testHoverBackgroundColor() {
        multiLineInputTextView.mouseEntered(with: NSEvent())
        XCTAssertEqual(multiLineInputTextView.textView.backgroundColor, renderConfig.inputFieldConfig.highlightedColor)
    }
    
    func testHoverExitBackgroundColor() {
        multiLineInputTextView.mouseEntered(with: NSEvent())
        multiLineInputTextView.mouseExited(with: NSEvent())
        XCTAssertEqual(multiLineInputTextView.textView.backgroundColor, renderConfig.inputFieldConfig.backgroundColor)
    }
    
    func testBorderParameters() {
        XCTAssertEqual(multiLineInputTextView.layer?.borderWidth, renderConfig.inputFieldConfig.borderWidth)
        XCTAssertEqual(multiLineInputTextView.layer?.borderColor, renderConfig.inputFieldConfig.borderColor.cgColor)
    }
    
    func testFocusRingCornerRadius() {
        XCTAssertEqual(multiLineInputTextView.scrollView.focusRingCornerRadius, renderConfig.inputFieldConfig.focusRingCornerRadius)
    }
    
    private func setupInputField() -> InputFieldConfig{
        return InputFieldConfig(height: 0, leftPadding: 12, rightPadding: 8, yPadding: 0, focusRingCornerRadius: 8, borderWidth: 0.3, wantsClearButton: false, clearButtonImage: nil, calendarImage: nil, clockImage: nil, font: .systemFont(ofSize: 14), highlightedColor: NSColor(red: 1, green: 1, blue: 1, alpha: 0.11), backgroundColor: NSColor(red: 0.148, green: 0.148, blue: 0.148, alpha: 1), borderColor: NSColor(red: 1, green: 1, blue: 1, alpha: 0.9), activeBorderColor: NSColor(red: 1, green: 1, blue: 1, alpha: 0.9), placeholderTextColor: NSColor.placeholderTextColor, multilineFieldInsets: NSEdgeInsets(top: 5, left: 10, bottom: 0, right: 0))
    }
}
