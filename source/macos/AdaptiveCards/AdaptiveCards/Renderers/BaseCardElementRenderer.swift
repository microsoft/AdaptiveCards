import AdaptiveCards_bridge
import AppKit

class BaseCardElementRenderer {
    func updateView(view: NSView, element: ACSBaseCardElement, style: ACSContainerStyle, hostConfig: ACSHostConfig, isfirstElement: Bool) -> NSView {
        // Can't do this as updatedView needed for spacing when no property set
//        if isfirstElement || !element.getSeparator() {
//            return view
//        }
        
        let updatedView = ACRContentStackView()
        
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
        updatedView.addArrangedSubview(view)
        updatedView.isHidden = !element.getIsVisible()
        
        return updatedView
    }
}
