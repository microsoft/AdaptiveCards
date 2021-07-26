import AdaptiveCards_bridge
import AppKit

class ACRView: ACRColumnView {
    weak var delegate: AdaptiveCardActionDelegate?
    weak var resolverDelegate: AdaptiveCardResourceResolver?
    weak var parent: ACRView?
    
    let renderConfig: RenderConfig

    private (set) var targets: [TargetHandler] = []
    private (set) var inputHandlers: [InputHandlingViewProtocol] = []
    private (set) var imageViewMap: [String: [ImageHoldingView]] = [:]
    private (set) var renderedShowCards: [NSView] = []
    private (set) var initialLayoutDone = false
    private var currentFocusedActionElement: NSCell?
    
    init(style: ACSContainerStyle, hostConfig: ACSHostConfig, renderConfig: RenderConfig) {
        self.renderConfig = renderConfig
        super.init(style: style, parentStyle: nil, hostConfig: hostConfig, superview: nil, needsPadding: true)
    }
    
    required init?(coder: NSCoder) {
        renderConfig = .default
        super.init(coder: coder)
    }
    
    private var previousBounds: NSRect?
    private var boundsBeforeShowCard: NSRect?
    override func layout() {
        super.layout()
        guard window != nil else { return }
        if let pBounds = previousBounds, bounds.height != pBounds.height {
            delegate?.adaptiveCard(self, didUpdateBoundsFrom: pBounds, to: bounds)
            initialLayoutDone = true
            parent?.resetKeyboardFocus()
            resetKeyboardFocus()
        }
        previousBounds = bounds
    }
    
    func addTarget(_ target: TargetHandler) {
        targets.append(target)
    }
    
    func addInputHandler(_ handler: InputHandlingViewProtocol) {
        inputHandlers.append(handler)
    }
    
    func resolveAttributedString(for htmlString: String) -> NSAttributedString? {
        return resolverDelegate?.adaptiveCard(self, attributedStringFor: htmlString)
    }
    
    func registerImageHandlingView(_ view: ImageHoldingView, for url: String) {
        if imageViewMap[url] == nil {
            imageViewMap[url] = []
        }
        imageViewMap[url]?.append(view)
    }
    
    func getImageDimensions(for url: String) -> NSSize? {
        return resolverDelegate?.adaptiveCard(self, dimensionsForImageWith: url)
    }
    
    func dispatchResolveRequests() {
        for url in imageViewMap.keys {
            resolverDelegate?.adaptiveCard(self, requestImageFor: url)
        }
    }
    
    func resetKeyboardFocus() {
        guard isInitialLayoutComplete, let lastFocusedElement = currentFocusedActionElement else { return }
        lastFocusedElement.setAccessibilityFocused(true)
        currentFocusedActionElement = nil
    }
    
    private var isInitialLayoutComplete: Bool {
        guard let firstOpenChildCard = renderedShowCards.first(where: { !$0.isHidden }) as? ACRView else {
            return initialLayoutDone
        }
        return firstOpenChildCard.initialLayoutDone && initialLayoutDone
    }
    
    private func findSubview(with identifier: String) -> NSView? {
        func subview(with id: String, in view: NSView) -> NSView? {
            if view.subviews.isEmpty {
                return nil
            }
            for sView in view.subviews {
                if sView.identifier?.rawValue == identifier {
                    return sView
                }
                if let inSubview = subview(with: id, in: sView) {
                    return inSubview
                }
            }
            return nil
        }
        return subview(with: identifier, in: self)
    }
    
    private func submitCardInputs(actionView: NSView, dataJSON: String?) {
        var dict = [String: Any]()
        
        // recursively fetch input handlers dictionary from the parent
        var rootView = self
        var parentView: ACRView? = self
        repeat {
            if let handlers = parentView?.inputHandlers {
                for handler in handlers {
                    guard handler.isValid else { continue }
                    dict[handler.key] = handler.value
                }
            }
            if let curr = parentView, curr.parent == nil {
                rootView = curr
            }
            parentView = parentView?.parent
        } while parentView != nil
      
        if let data = dataJSON?.data(using: String.Encoding.utf8), let dataJsonDict = try? JSONSerialization.jsonObject(with: data, options: []) as? [String: Any] {
            dict.merge(dataJsonDict) { current, _ in current }
        }
        delegate?.adaptiveCard(rootView, didSubmitUserResponses: dict, actionView: actionView)
    }
    
    private func toggleVisibity(of targets: [ACSToggleVisibilityTarget]) {
        var toggledContentStackViews: [(ACRContentStackView, Bool)] = []
        for target in targets {
            guard let id = target.getElementId(), let toggleView = findSubview(with: id) else {
                logError("Target with ID '\(target.getElementId() ?? "nil")' not found for toggleVisibility.")
                continue
            }
            let oldHiddenValue = toggleView.isHidden
            switch target.getIsVisible() {
            case .isVisibleToggle:
                toggleView.isHidden.toggle()
            case .isVisibleTrue:
                toggleView.isHidden = false
            case .isVisibleFalse:
                toggleView.isHidden = true
            @unknown default:
                logError("Unknown ToggleIsVisible value \(target.getIsVisible())")
            }
            if let contentStackView = toggleView as? ACRContentStackView {
                toggledContentStackViews.append((contentStackView, oldHiddenValue))
            }
        }
        
        // Must be refreshed only after all elements hidden states are updated.
        for (contentStackView, oldHiddenValue) in toggledContentStackViews {
            contentStackView.refreshOnVisibilityChange(from: oldHiddenValue)
        }
    }
}

extension ACRView: ACRActionSetViewDelegate {
    func actionSetView(_ view: ACRActionSetView, didOpenURLWith actionView: NSView, urlString: String) {
        delegate?.adaptiveCard(self, didSelectOpenURL: urlString, actionView: actionView)
    }
    
    func actionSetView(_ view: ACRActionSetView, didSubmitInputsWith actionView: NSView, dataJson: String?) {
        submitCardInputs(actionView: actionView, dataJSON: dataJson)
    }
    
    func actionSetView(_ view: ACRActionSetView, didToggleVisibilityActionWith actionView: NSView, toggleTargets: [ACSToggleVisibilityTarget]) {
        toggleVisibity(of: toggleTargets)
    }
    
    func actionSetView(_ view: ACRActionSetView, willShowCardWith button: NSButton) {
        boundsBeforeShowCard = bounds
        if let buttonCell = button.cell, buttonCell.isAccessibilityFocused() {
            currentFocusedActionElement = buttonCell
        }
    }
    
    func actionSetView(_ view: ACRActionSetView, didShowCardWith button: NSButton) {
        delegate?.adaptiveCard(self, didShowCardWith: button, previousHeight: boundsBeforeShowCard?.height ?? -1, newHeight: bounds.height)
    }
    
    func actionSetView(_ view: ACRActionSetView, renderShowCardFor cardData: ACSAdaptiveCard) -> NSView {
        let cardView = AdaptiveCardRenderer.shared.renderShowCard(cardData, with: hostConfig, parent: self, config: renderConfig)
        renderedShowCards.append(cardView)
        return cardView
    }
}

extension ACRView: TargetHandlerDelegate {
    func handleToggleVisibilityAction(actionView: NSView, toggleTargets: [ACSToggleVisibilityTarget]) {
        toggleVisibity(of: toggleTargets)
    }
    
    func handleOpenURLAction(actionView: NSView, urlString: String) {
        delegate?.adaptiveCard(self, didSelectOpenURL: urlString, actionView: actionView)
    }
    
    func handleSubmitAction(actionView: NSView, dataJson: String?) {
        submitCardInputs(actionView: actionView, dataJSON: dataJson)
    }
}

extension ACRView: ImageResourceHandlerView {
    func setImage(_ image: NSImage, for url: String) {
        guard let imageViews = imageViewMap[url] else {
            logError("No views registered for url '\(url)'")
            return
        }
        DispatchQueue.main.async {
            for imageView in imageViews {
                imageView.setImage(image)
            }
        }
    }
    
    func setImage(_ image: NSImage, forURLsContaining matcher: @escaping (String) -> Bool) {
        DispatchQueue.global().async { [weak self] in
            guard let self = self else { return }
            self.imageViewMap.keys
                .filter { matcher($0) }
                .forEach { self.setImage(image, for: $0) }
            
            self.renderedShowCards
                .compactMap { $0 as? ImageResourceHandlerView }
                .forEach { $0.setImage(image, forURLsContaining: matcher) }
        }
    }
}
