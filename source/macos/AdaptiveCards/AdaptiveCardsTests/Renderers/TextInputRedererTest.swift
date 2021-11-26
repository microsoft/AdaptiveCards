@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class TextInputRendererTest: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var inputText: FakeInputText!
    private var textInputRenderer: TextInputRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        inputText = .make()
        textInputRenderer = TextInputRenderer()
    }
    
    func testSetPlaceholder() throws {
        let placeholderString: String = "Sample Placeholder"
        inputText = .make(placeholderString: placeholderString)
        
        let inputTextField = renderTextInput()
        XCTAssertEqual(inputTextField.placeholderString , placeholderString)
    }
    
    func testRendersValue() throws {
        let valueString: String = "somevalue"
        inputText = .make(value: valueString)
        
        let inputTextField = renderTextInput()
        XCTAssertEqual(inputTextField.stringValue, valueString)
    }
    
    func testMaxLengthinInitialValue() throws {
        let valueString: String = "a long string of characters"
        inputText = .make(value: valueString, maxLength: NSNumber(10))
        
        let inputTextField = renderTextInput()
        XCTAssertEqual(inputTextField.stringValue, "a long str")
    }
    
    func testSetAccessibilityValue() {
        let valueString: String = "somevalue"
        inputText = .make(value: valueString)
        
        let inputTextField = renderTextInput()
        XCTAssertEqual(inputTextField.accessibilityChildren()?.count, 1)
        XCTAssertEqual(inputTextField.accessibilityTitle(), "Text Field")
        XCTAssertEqual(inputTextField.accessibilityValue(), "somevalue")
    }
    
    private func renderTextInput() -> ACRTextInputView {
        let view = textInputRenderer.render(element: inputText, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRTextInputView)
        guard let inputText = view as? ACRTextInputView else { fatalError() }
        return inputText
    }
}


    
