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

    let dateFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateFormat = "HH:mm"
        return formatter
    }()
    
    func testRendererSetsValue() {
        let val: String = "15:30"
        inputTime = .make(value: val)

        let inputTimeField = renderTimeInput()
        XCTAssertEqual(inputTimeField.dateValue, val)
    }

    func testRendererSetsPlaceholder() {
        let placeholderString: String = "Sample Placeholder"
        inputTime = .make(placeholder: placeholderString)

        let inputTimeField = renderTimeInput()
        XCTAssertEqual(inputTimeField.placeholder, placeholderString)
    }
    
    func testRendererForMinValue() {
        let minVal: String = "09:30"
        inputTime = .make(min: minVal)

        let inputTimeField = renderTimeInput()
        XCTAssertEqual(inputTimeField.minDateValue, minVal)
    }

    func testRendererForMaxValue() {
        let maxValue: String = "16:00"
        inputTime = .make(max: maxValue)

        let inputTimeField = renderTimeInput()
        XCTAssertEqual(inputTimeField.maxDateValue, maxValue)
    }

    private func renderTimeInput() -> ACRDateField {
        let view = inputTimeRenderer.render(element: inputTime, with: hostConfig, style: .default, rootView: NSView(), parentView: NSView(), inputs: [])

        XCTAssertTrue(view is ACRDateField)
        guard let inputTime = view as? ACRDateField else { fatalError() }
        return inputTime
    }
}

