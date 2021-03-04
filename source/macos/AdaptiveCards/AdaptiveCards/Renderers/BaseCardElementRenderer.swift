import AdaptiveCards_bridge
import AppKit

class BaseCardElementRenderer {
    func updateView(view: NSView, element: ACSBaseCardElement, style: ACSContainerStyle, hostConfig: ACSHostConfig, isfirstElement: Bool) -> NSView {
        let updatedView = ACRContentStackView(style: style, hostConfig: hostConfig)
        
        // For Spacing
        if !isfirstElement {
            let spacingConfig = hostConfig.getSpacing()
            let spaceAdded: NSNumber
            switch element.getSpacing() {
            case .default:
                spaceAdded = spacingConfig?.defaultSpacing ?? 0
            case .none:
                spaceAdded = 0
            case .small:
                spaceAdded = spacingConfig?.smallSpacing ?? 3
            case .medium:
                spaceAdded = spacingConfig?.mediumSpacing ?? 20
            case .large:
                spaceAdded = spacingConfig?.largeSpacing ?? 30
            case .extraLarge:
                spaceAdded = spacingConfig?.extraLargeSpacing ?? 40
            case .padding:
                spaceAdded = spacingConfig?.paddingSpacing ?? 20
            @unknown default:
                logError("Unknown padding!")
                spaceAdded = 0
            }
            updatedView.addSpacing(spacing: CGFloat(truncating: spaceAdded))
        }
        
        // For seperator
        if element.getSeparator(), !isfirstElement {
            let seperatorConfig = hostConfig.getSeparator()
            let lineThickness = seperatorConfig?.lineThickness
            let lineColor = seperatorConfig?.lineColor
            updatedView.addSeperator(thickness: lineThickness ?? 1, color: lineColor ?? "#EEEEEE")
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
            updatedView.setCustomSpacing(spacing: 3, view: labelView)
        }
        updatedView.addArrangedSubview(view)
        return updatedView
    }
}
