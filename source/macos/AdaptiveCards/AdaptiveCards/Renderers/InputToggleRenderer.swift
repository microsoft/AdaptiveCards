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
        var attributedString: NSMutableAttributedString
        // NSButton for checkbox
        let inputToggleView = ACRInputToggleView(checkboxWithTitle: inputToggle.getTitle() ?? "", target: self, action: nil)
        inputToggleView.translatesAutoresizingMaskIntoConstraints = false
        // adding attributes to the string
        let paragraphStyle = NSMutableParagraphStyle()
        paragraphStyle.firstLineHeadIndent = 10
        attributedString = NSMutableAttributedString(string: inputToggle.getTitle() ?? "", attributes: [.paragraphStyle: paragraphStyle])
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
        // Wrap
        if inputToggle.getWrap() {
        }
        return inputToggleView
     }
}

class ACRInputToggleView: NSButton {
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        // Should look for better solution
        guard let superview = superview else { return }
        leadingAnchor.constraint(equalTo: superview.leadingAnchor).isActive = true
    }
}
