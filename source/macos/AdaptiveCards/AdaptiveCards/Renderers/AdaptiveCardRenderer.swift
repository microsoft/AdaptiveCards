import AdaptiveCards_bridge
import AppKit

class AdaptiveCardRenderer {
    static let shared = AdaptiveCardRenderer()
    weak var actionDelegate: AdaptiveCardActionDelegate?
    weak var resolverDelegate: AdaptiveCardResourceResolver?
    
    func renderAdaptiveCard(_ card: ACSAdaptiveCard, with hostConfig: ACSHostConfig, width: CGFloat) -> NSView {
        var style: ACSContainerStyle = .default
        if let colorConfig = hostConfig.getAdaptiveCard() {
            style = (colorConfig.allowCustomStyle && card.getStyle() != .none) ? card.getStyle() : .default
        }
        return renderAdaptiveCard(card, with: hostConfig, style: style, width: width)
    }
    
    func renderShowCard(_ card: ACSAdaptiveCard, with hostConfig: ACSHostConfig, parent: ACRView) -> NSView {
        var style: ACSContainerStyle = .default
        if let colorConfig = hostConfig.getAdaptiveCard() {
            let showCardStyle = hostConfig.getActions()?.showCard.style ?? .default
            style = colorConfig.allowCustomStyle ? card.getStyle() : showCardStyle
        }
        guard let cardView = renderAdaptiveCard(card, with: hostConfig, style: style) as? ACRView else {
            logError("renderAdaptiveCard should return ACRView")
            return NSView()
        }
        parent.addShowCard(cardView)
        return cardView
    }
    
    private func renderAdaptiveCard(_ card: ACSAdaptiveCard, with hostConfig: ACSHostConfig, style: ACSContainerStyle, width: CGFloat? = nil) -> NSView {
        let rootView = ACRView(style: style, hostConfig: hostConfig)
        rootView.translatesAutoresizingMaskIntoConstraints = false
        if let width = width {
            rootView.widthAnchor.constraint(equalToConstant: width).isActive = true
        }
        rootView.delegate = self
        rootView.resolverDelegate = self
           
        for (index, element) in card.getBody().enumerated() {
            let isFirstElement = index == 0
            let renderer = RendererManager.shared.renderer(for: element.getType())
            let view = renderer.render(element: element, with: hostConfig, style: style, rootView: rootView, parentView: rootView, inputs: [])
            let viewWithInheritedProperties = BaseCardElementRenderer.shared.updateView(view: view, element: element, style: style, hostConfig: hostConfig, isfirstElement: isFirstElement)
            rootView.addArrangedSubview(viewWithInheritedProperties)
        }
        
        if !card.getActions().isEmpty {
            let view = ActionSetRenderer.shared.renderActionButtons(actions: card.getActions(), with: hostConfig, style: style, rootView: rootView, parentView: rootView, inputs: [])
            // getting spacing from hostConfig
            if let verticalSpacing = hostConfig.getActions()?.spacing {
                let spacing = HostConfigUtils.getSpacing(verticalSpacing, with: hostConfig)
                // add vertical spacing b/w action button view and last BaseCard Element
                if let lastView = rootView.arrangedSubviews.last {
                    rootView.setCustomSpacing(spacing: CGFloat(truncating: spacing), after: lastView)
                }
            }
            rootView.addArrangedSubview(view)
        }
        
        // add selectAction
        rootView.setupSelectAction(selectAction: card.getSelectAction(), rootView: rootView)
        
        rootView.layoutSubtreeIfNeeded()
        return rootView
    }
}

extension AdaptiveCardRenderer: ACRViewDelegate {
    func acrView(_ view: ACRView, didSelectOpenURL url: String, actionView: NSView) {
        actionDelegate?.adaptiveCard(view, didSelectOpenURL: url, actionView: actionView)
    }
    
    func acrView(_ view: ACRView, didSubmitUserResponses dict: [String: Any], actionView: NSView) {
        actionDelegate?.adaptiveCard(view, didSubmitUserResponses: dict, actionView: actionView)
    }
}

extension AdaptiveCardRenderer: ACRViewResourceResolverDelegate {
    func resolve(_ adaptiveCard: ImageResourceHandlerView, requestImageFor key: ResourceKey) {
        resolverDelegate?.adaptiveCard(adaptiveCard, requestImageFor: key)
    }
    func resolve(_ adaptiveCard: ImageResourceHandlerView, dimensionsForImageWith key: ResourceKey) -> NSSize? {
        resolverDelegate?.adaptiveCard(adaptiveCard, dimensionsForImageWith: key)
    }
}
