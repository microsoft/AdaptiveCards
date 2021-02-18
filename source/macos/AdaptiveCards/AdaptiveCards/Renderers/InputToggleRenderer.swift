import AdaptiveCards_bridge
import AppKit

class InputToggleRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = InputToggleRenderer()
     
     func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
         guard let inputToggle = element as? ACSToggleInput else {
             logError("Element is not of type ACSToggleInput")
             return NSView()
         }
        // NSMutableAttributedString for the checkbox title
        let attributedString: NSMutableAttributedString
        // NSButton for checkbox
        let title = inputToggle.getTitle() ?? ""
        let resolvedTitle = inputToggle.getWrap() ? title + "\n" : title
        let inputToggleView = ACRInputToggleView(checkboxWithTitle: resolvedTitle, target: self, action: nil)
        inputToggleView.translatesAutoresizingMaskIntoConstraints = false
        // adding attributes to the string
        let paragraphStyle = NSMutableParagraphStyle()
        attributedString = NSMutableAttributedString(string: resolvedTitle, attributes: [.paragraphStyle: paragraphStyle])
        if let colorHex = hostConfig.getForegroundColor(style, color: .default, isSubtle: true), let textColor = ColorUtils.color(from: colorHex) {
            attributedString.addAttributes([.foregroundColor: textColor], range: NSRange(location: 0, length: attributedString.length))
        }
        // check for valueOn or valueOff attributes
        var defaultInputToggleStateValue: NSControl.StateValue = .on
        if inputToggle.getValue() != inputToggle.getValueOn() {
            defaultInputToggleStateValue = .off
        }
        inputToggleView.state = defaultInputToggleStateValue
        inputToggleView.attributedTitle = attributedString
        inputToggleView.wraps = inputToggle.getWrap()
        return inputToggleView
     }
}

class ACRInputToggleView: NSButton {
    public var wraps = false
    override var intrinsicContentSize: NSSize {
        guard wraps, let titleRect = cell?.titleRect(forBounds: bounds) else { return super.intrinsicContentSize }
        return NSSize(width: super.intrinsicContentSize.width, height: titleRect.height)
    }
}
