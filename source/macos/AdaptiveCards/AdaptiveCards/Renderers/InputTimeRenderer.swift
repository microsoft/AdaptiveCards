import AdaptiveCards_bridge
import AppKit

open class InputTimeRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = InputTimeRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let timeElement = element as? ACSTimeInput else {
            logError("Element is not of type ACSDateInput")
            return NSView()
        }

        // setting up basic properties for Input.Time Field
        let inputField: ACRDateField = {
            let view = ACRDateField(isTimeMode: true, config: config)
            let timeValue = valueByHoursAndMinutes(timeElement.getValue() ?? "")
            let timeMin = valueByHoursAndMinutes(timeElement.getMin() ?? "")
            let timeMax = valueByHoursAndMinutes(timeElement.getMax() ?? "")
            view.translatesAutoresizingMaskIntoConstraints = false
            view.maxDateValue = timeMax
            view.minDateValue = timeMin
            view.initialDateValue = timeValue
            view.placeholder = timeElement.getPlaceholder() ?? ""
            view.idString = timeElement.getId()
            view.isHidden = !timeElement.getIsVisible()
            return view
        }()
        
        rootView.addInputHandler(inputField)
        return inputField
    }
     // checking input time value and accepting only hours and minutes
    private func valueByHoursAndMinutes(_ value: String) -> String {
        let time = value.components(separatedBy: ":")
        if time.count > 2 {
            return("\(time[0]):\(time[1])")
        }
        return time.joined(separator: ":")
    }
}
