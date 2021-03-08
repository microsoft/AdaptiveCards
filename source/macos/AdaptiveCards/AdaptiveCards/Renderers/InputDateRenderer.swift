import AdaptiveCards_bridge
import AppKit

open class InputDateRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = InputDateRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let dateElement = element as? ACSDateInput else {
            logError("Element is not of type ACSDateInput")
            return NSView()
        }

        // setting up basic properties for Input.Date Field
        let inputField: ACRDateField = {
            let view = ACRDateField()
            view.translatesAutoresizingMaskIntoConstraints = false
            view.maxDateValue = dateElement.getMax() ?? ""
            view.minDateValue = dateElement.getMin() ?? ""
            view.dateValue = dateElement.getValue() ?? ""
            view.placeholder = dateElement.getPlaceholder() ?? ""
            return view
        }()
        return inputField
    }
}
