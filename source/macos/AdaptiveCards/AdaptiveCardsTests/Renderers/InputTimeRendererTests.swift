@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class InputTimeRendererTest: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var inputTime: FakeInputTime!
    private var inputTimeRenderer: InputTimeRenderer!

    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        inputTime = .make()
        inputTimeRenderer = InputTimeRenderer()
    }
    
    func testRendererSetsValue() {
        let val: String = "15:30:32"
        inputTime = .make(value: val)
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "HH:mm"

        let inputTimeField = renderTimeInput()
        XCTAssertEqual(inputTimeField.datePickerCalendar.dateValue, dateFormatter.date(from: "15:30"))
        XCTAssertEqual(inputTimeField.datePickerTextfield.dateValue, dateFormatter.date(from: "15:30"))
        XCTAssertEqual(inputTimeField.dateValue, "15:30")
    }

    func testRendererSetsPlaceholder() {
        let placeholderString: String = "Sample Placeholder"
        inputTime = .make(placeholder: placeholderString)

        let inputTimeField = renderTimeInput()
        XCTAssertEqual(inputTimeField.placeholder, placeholderString)
    }
    
    func testRendererForMinValue() {
        let minVal: String = "09:30:23"
        inputTime = .make(min: minVal)

        let inputTimeField = renderTimeInput()
        XCTAssertEqual(inputTimeField.minDateValue, "09:30")
    }

    func testRendererForMaxValue() {
        let maxValue: String = "16:00:23"
        inputTime = .make(max: maxValue)

        let inputTimeField = renderTimeInput()
        XCTAssertEqual(inputTimeField.maxDateValue, "16:00")
    }
    
    func testClearsText() {
        let val: String = "16:23:30"
        inputTime = .make(value: val)

        let inputTimeField = renderTimeInput()
        inputTimeField.textField.clearButton.performClick()
        XCTAssertNil(inputTimeField.dateValue)
        XCTAssertEqual(inputTimeField.textField.stringValue, "")
        XCTAssertTrue(inputTimeField.textField.clearButton.isHidden)
    }
    
    func testClearButtonHiddenWithPlaceholder() {
        let placeholderString: String = "Sample Placeholder"
        inputTime = .make(placeholder: placeholderString)

        let inputTimeField = renderTimeInput()
        XCTAssertTrue(inputTimeField.textField.clearButton.isHidden)
    }

    func testClearButtonHiddenWithNoText() {
        inputTime = .make()

        let inputTimeField = renderTimeInput()
        XCTAssertTrue(inputTimeField.textField.clearButton.isHidden)
    }

    func testClearButtonVisibleWithText() {
        let val: String = "4:30"
        inputTime = .make(value: val)

        let inputTimeField = renderTimeInput()
        XCTAssertFalse(inputTimeField.textField.clearButton.isHidden)
    }
    
    func testValueShownOnlyForRightInputFormat() {
        let val: String = "5:30am"
        inputTime = .make(value: val)

        let inputTimeField = renderTimeInput()
        XCTAssertNil(inputTimeField.dateValue)
        XCTAssertEqual(inputTimeField.textField.stringValue, "")
    }
    
    func testCurrentTimeInPopOverDefault() {
        inputTime = .make()
        
        let inputTimeField = renderTimeInput()
        
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "HH:mm"
        XCTAssertEqual(dateFormatter.string(from: inputTimeField.datePickerCalendar.dateValue), dateFormatter.string(from: Date()))
        XCTAssertEqual(dateFormatter.string(from: inputTimeField.datePickerTextfield.dateValue), dateFormatter.string(from: Date()))
    }

    private func renderTimeInput() -> ACRDateField {
        let view = inputTimeRenderer.render(element: inputTime, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [], config: .default)

        XCTAssertTrue(view is ACRDateField)
        guard let inputTime = view as? ACRDateField else { fatalError() }
        return inputTime
    }
}
