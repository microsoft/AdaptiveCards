import AdaptiveCards_bridge
import AppKit

class AdaptiveCardRenderer {
    func renderAdaptiveCard(_ card: ACSAdaptiveCard, with hostConfig: ACSHostConfig, width: CGFloat) -> NSView {
        var style: ACSContainerStyle = .default
        if let colorConfig = hostConfig.getAdaptiveCard() {
            style = (colorConfig.allowCustomStyle && card.getStyle() != .none) ? card.getStyle() : .default
        }
        
        let rootView = ACRView(style: style, hostConfig: hostConfig)
        rootView.translatesAutoresizingMaskIntoConstraints = false
        rootView.widthAnchor.constraint(equalToConstant: width).isActive = true
        
        for (index, element) in card.getBody().enumerated() {
            if element.getType() == .columnSet {
                guard let columnSet = element as? ACSColumnSet else { continue }
                let columnStack = NSStackView()
                columnStack.spacing = 12
                columnStack.distribution = .fillEqually
                columnSet.getColumns().forEach { _ in
                    let view = NSView()
                    view.translatesAutoresizingMaskIntoConstraints = false
                    view.wantsLayer = true
                    view.heightAnchor.constraint(equalToConstant: 50).isActive = true
                    view.layer?.backgroundColor = NSColor.yellow.cgColor
                    columnStack.addArrangedSubview(view)
                }
                rootView.addArrangedSubview(columnStack)
                continue
            }
            
            let isFirstElement = index == 0
            
            let renderer = RendererManager.shared.renderer(for: element.getType())
            let view = renderer.render(element: element, with: hostConfig, style: style, rootView: rootView, parentView: rootView, inputs: [])
            let viewWithInheritedProperties = BaseCardElementRenderer().updateView(view: view, element: element, style: style, hostConfig: hostConfig, isfirstElement: isFirstElement)
            rootView.addArrangedSubview(viewWithInheritedProperties)
        }
        
        rootView.appearance = NSAppearance(named: .aqua)
        rootView.layoutSubtreeIfNeeded()
        return rootView
    }
}
