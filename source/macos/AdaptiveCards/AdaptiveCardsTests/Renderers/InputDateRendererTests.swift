@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class InputDateRendererTest: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var inputDate: FakeInputDate!
    private var inputDateRenderer: InputDateRenderer!

    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        inputDate = .make()
        inputDateRenderer = InputDateRenderer()
    }

    func testRendererSetsValue() {
        let val: String = "2000-10-12"
        inputDate = .make(value: val)

        let inputDateField = renderDateInput()
        XCTAssertEqual(inputDateField.dateValue, val)
    }

    func testRendererSetsPlaceholder() {
        let placeholderString: String = "Sample Placeholder"
        inputDate = .make(placeholder: placeholderString)

        let inputDateField = renderDateInput()
        XCTAssertEqual(inputDateField.placeholder, placeholderString)
    }

    func testRendererForMinValue() {
        let minVal: String = "1999-03-23"
        inputDate = .make(min: minVal)

        let inputDateField = renderDateInput()
        XCTAssertEqual(inputDateField.minDateValue, minVal)
    }

    func testRendererForMaxValue() {
        let maxValue: String = "2022-02-20"
        inputDate = .make(max: maxValue)

        let inputDateField = renderDateInput()
        XCTAssertEqual(inputDateField.maxDateValue, maxValue)
    }
    
    func testClearsText() {
        let val: String = "2000-11-23"
        inputDate = .make(value: val)

        let inputDateField = renderDateInput()
        inputDateField.clearButton.performClick()
        XCTAssertEqual(inputDateField.textField.stringValue, "")
        XCTAssertNil(inputDateField.dateValue)
        XCTAssertTrue(inputDateField.clearButton.isHidden)
    }
    
    func testClearButtonHiddenWithPlaceholder() {
        let placeholderString: String = "Sample Placeholder"
        inputDate = .make(placeholder: placeholderString)

        let inputDateField = renderDateInput()
        XCTAssertTrue(inputDateField.clearButton.isHidden)
    }
    
    func testClearButtonHiddenWithNoText() {
        inputDate = .make()
        
        let inputDateField = renderDateInput()
        XCTAssertTrue(inputDateField.clearButton.isHidden)
    }
    
    func testClearButtonVisibleWithText() {
        let val: String = "2000-02-10"
        inputDate = .make(value: val)
        
        let inputDateField = renderDateInput()
        XCTAssertFalse(inputDateField.clearButton.isHidden)
    }
    
    func testValueShownOnlyForRightInputFormat() {
        let val: String = "12/10/2000"
        inputDate = .make(value: val)

        let inputDateField = renderDateInput()
        XCTAssertNil(inputDateField.dateValue)
        XCTAssertEqual(inputDateField.textField.stringValue, "")
    }

    private func renderDateInput() -> ACRDateField {
        let view = inputDateRenderer.render(element: inputDate, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [], config: .default)

        XCTAssertTrue(view is ACRDateField)
        guard let inputDate = view as? ACRDateField else { fatalError() }
        return inputDate
    }
}

private extension NSButton {
    func performClick() {
        guard !isHidden else { return }
        if let target = target, let action = action {
            sendAction(action, to: target)
        }
    }
}
