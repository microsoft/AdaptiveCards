@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class InputNumberRendererTest: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var inputNumber: FakeInputNumber!
    private var inputNumberRenderer: InputNumberRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        inputNumber = .make()
        inputNumberRenderer = InputNumberRenderer()
    }
    
    func testRendererSetsValue() {
        let val: NSNumber = 25
        inputNumber = .make(value: val)
        
        let inputNumberField = renderNumberInput()
        XCTAssertEqual(inputNumberField.inputValue, val.doubleValue)
    }
    
    func testRendererSetsPlaceholder() {
        let placeholderString: String = "Sample Placeholder"
        inputNumber = .make(placeholder: placeholderString)
        
        let inputNumberField = renderNumberInput()
        XCTAssertEqual(inputNumberField.placeholder, placeholderString)
    }
    
    func testRendererIfValueIsVisible() {
        let placeholderString: String = "Sample Placeholder"
        let val: NSNumber = 23.4
        inputNumber = .make(value: val, placeholder: placeholderString)
        
        let inputNumberField = renderNumberInput()
        XCTAssertEqual(inputNumberField.inputValue, val.doubleValue)
    }
    
    func testRendererIfInputFieldIsHidden() {
        inputNumber = .make(visible: false)
        
        let inputNumberField = renderNumberInput()
        XCTAssertEqual(inputNumberField.isHidden, true)
    }
    
    func testRendererForMinValue() {
        let minVal: NSNumber = -5
        let val: NSNumber = 20
        inputNumber = .make(value: val, min: minVal)
        
        let inputNumberField = renderNumberInput()
        // min value is equal to stepper min value
        XCTAssertEqual(inputNumberField.minValue, minVal.doubleValue)
        // min value is not equal to input value
        XCTAssertTrue(inputNumberField.inputValue != minVal.doubleValue)
    }
    
    func testRendererForMaxValue() {
        let maxValue: NSNumber = 100
        let val: NSNumber = 20
        inputNumber = .make(value: val, max: maxValue)
        
        let inputNumberField = renderNumberInput()
        // max value is equal to stepper max value
        XCTAssertEqual(inputNumberField.maxValue, maxValue.doubleValue)
        // max value is not equal to input value
        XCTAssertTrue(inputNumberField.inputValue != maxValue.doubleValue)
    }
    
    func testRendererIfTruncatesExtraZeros() {
        let val: NSNumber = 20.00
        inputNumber = .make(value: val)
        
        let inputNumberField = renderNumberInput()
        XCTAssertEqual(inputNumberField.inputString, "20.0")
    }
       
    private func renderNumberInput() -> ACRNumericTextField {
        let view = inputNumberRenderer.render(element: inputNumber, with: hostConfig, style: .default, rootView: NSView(), parentView: NSView(), inputs: [])
        
        XCTAssertTrue(view is ACRNumericTextField)
        guard let inputNumber = view as? ACRNumericTextField else { fatalError() }
        return inputNumber
    }
}

