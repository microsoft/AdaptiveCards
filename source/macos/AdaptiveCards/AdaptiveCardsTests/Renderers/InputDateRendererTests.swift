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
        let val: String = "23/11/2000"
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
        let minVal: String = "23/11/1999"
        inputDate = .make(min: minVal)

        let inputDateField = renderDateInput()
        XCTAssertEqual(inputDateField.minDateValue, minVal)
    }

    func testRendererForMaxValue() {
        let maxValue: String = "23/11/2022"
        inputDate = .make(max: maxValue)

        let inputDateField = renderDateInput()
        XCTAssertEqual(inputDateField.maxDateValue, maxValue)
    }

    private func renderDateInput() -> ACRDateField {
        let view = inputDateRenderer.render(element: inputDate, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [])

        XCTAssertTrue(view is ACRDateField)
        guard let inputDate = view as? ACRDateField else { fatalError() }
        return inputDate
    }
}

