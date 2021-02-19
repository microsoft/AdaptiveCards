@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class MultilineInputTextRendererTest: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var inputText: FakeInputText!
    private var multilineInputTextRenderer: TextInputRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        inputText = .make()
        multilineInputTextRenderer = TextInputRenderer()
    }
    
    func testSetPlaceholder() throws {
        let placeholderString: String = "Sample Placeholder"
        inputText = .make(placeholderString: placeholderString, isMultiline: true)
        
        let inputTextField = renderTextInput()
        XCTAssertEqual(inputTextField.textView.placeholderAttrString , NSMutableAttributedString(string: placeholderString, attributes: [.foregroundColor: NSColor.placeholderTextColor]))
    }
    
    func testRendersValue() throws {
        let valueString: String = "somevalue"
        inputText = .make(value: valueString, isMultiline: true)
        
        let inputTextField = renderTextInput()
        XCTAssertEqual(inputTextField.textView.string, valueString)
    }
    
    func testMaxLengthinInitialValue() throws {
        let valueString: String = "a long string of characters"
        inputText = .make(value: valueString, isMultiline: true, maxLength: NSNumber(10))
        
        let inputTextField = renderTextInput()
        XCTAssertEqual(inputTextField.textView.string, "a long str")
    }
    
    
    
    private func renderTextInput() -> ACRMultilineInputTextView {
        let view = multilineInputTextRenderer.render(element: inputText, with: hostConfig, style: .default, rootView: NSView(), parentView: NSView(), inputs: [])
        
        XCTAssertTrue(view is ACRMultilineInputTextView)
        guard let inputText = view as? ACRMultilineInputTextView else { fatalError() }
        return inputText
    }
}
