import AdaptiveCards_bridge
import AppKit

class BaseCardElementRenderer {
    func updateView(view: NSView, element: ACSBaseCardElement, style: ACSContainerStyle, hostConfig: ACSHostConfig, isfirstElement: Bool) -> NSView {
        let updatedView = ACRContentStackView(style: style, hostConfig: hostConfig)
        
        // For Spacing
        if !isfirstElement {
            updatedView.addSpacing(element.getSpacing())
        }
        
        if let elem = element as? ACSImage {
            switch elem.getHorizontalAlignment() {
            case .center: updatedView.alignment = .centerX
            case .right: updatedView.alignment = .trailing
            default: updatedView.alignment = .leading
            }
        }
        
        // For seperator
        if element.getSeparator(), !isfirstElement {
            updatedView.addSeperator(true)
        }
        
        view.identifier = .init(element.getId() ?? "")
        updatedView.isHidden = !element.getIsVisible()
        
        // Input label handling
        if let inputElement = element as? ACSBaseInputElement, let label = inputElement.getLabel(), !label.isEmpty {
            let attributedString = NSMutableAttributedString(string: label)
            if let colorHex = hostConfig.getForegroundColor(style, color: .default, isSubtle: true), let textColor = ColorUtils.color(from: colorHex) {
                attributedString.addAttributes([.foregroundColor: textColor], range: NSRange(location: 0, length: attributedString.length))
            }
            let labelView = NSTextField(labelWithAttributedString: attributedString)
            labelView.isEditable = false
            updatedView.addArrangedSubview(labelView)
            updatedView.setCustomSpacing(spacing: 3, after: labelView)
        }
        
        updatedView.addArrangedSubview(view)
        if view is ACRContentStackView {
            view.widthAnchor.constraint(equalTo: updatedView.widthAnchor).isActive = true
        }
        return updatedView
    }
}
