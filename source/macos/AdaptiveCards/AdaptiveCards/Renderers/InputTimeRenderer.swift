import AdaptiveCards_bridge
import AppKit

open class InputTimeRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = InputTimeRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let timeElement = element as? ACSTimeInput else {
            logError("Element is not of type ACSDateInput")
            return NSView()
        }

        // setting up basic properties for Input.Time Field
        let inputField: ACRDateField = {
            let view = ACRDateField()
            let timeValue = valueByAppendingMissingSeconds(timeElement.getValue() ?? "")
            let timeMin = valueByAppendingMissingSeconds(timeElement.getMin() ?? "")
            let timeMax = valueByAppendingMissingSeconds(timeElement.getMax() ?? "")
            view.isTimeMode = true
            view.translatesAutoresizingMaskIntoConstraints = false
            view.maxDateValue = timeMax
            view.minDateValue = timeMin
            view.dateValue = timeValue
            view.placeholder = timeElement.getPlaceholder() ?? ""
            view.idString = timeElement.getId()
            view.isHidden = !timeElement.getIsVisible()
            return view
        }()
        
        rootView.addInputHandler(inputField)
        return inputField
    }
    // if input time doesn't have seconds then this function appends seconds' value as 00
    private func valueByAppendingMissingSeconds(_ value: String) -> String {
        var time = value.components(separatedBy: ":")
        if time.count == 2 {
            time.append("00")
        }
        return time.joined(separator: ":")
    }
}
