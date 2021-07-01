import AdaptiveCards_bridge
import AppKit

protocol ACRViewDelegate: AnyObject {
    func acrView(_ view: ACRView, didSelectOpenURL url: String, actionView: NSView)
    func acrView(_ view: ACRView, didSubmitUserResponses dict: [String: Any], actionView: NSView)
    func acrView(_ view: ACRView, didShowCardWith actionView: NSView, previousHeight: CGFloat, newHeight: CGFloat)
    func acrView(_ view: ACRView, didUpdateBoundsFrom oldValue: NSRect, to newValue: NSRect)
}

protocol ACRViewResourceResolverDelegate: AnyObject {
    func resolve(_ adaptiveCard: ImageResourceHandlerView, dimensionsForImageWith url: String) -> NSSize?
    func resolve(_ adaptiveCard: ImageResourceHandlerView, requestImageFor url: String)
    func resolve(_ adaptiveCard: NSView, attributedStringFor htmlString: String) -> NSAttributedString?
}

class ACRView: ACRColumnView {
    typealias ShowCardItems = (id: NSNumber, button: NSButton, showCard: NSView)
    
    weak var delegate: ACRViewDelegate?
    weak var resolverDelegate: ACRViewResourceResolverDelegate?
    weak var parent: ACRView?
    
    let renderConfig: RenderConfig

    private (set) var targets: [TargetHandler] = []
    private (set) var inputHandlers: [InputHandlingViewProtocol] = []
    private (set) var imageSetDatasources: [ACRCollectionViewDatasource] = []
    private (set) var showCardsMap: [NSNumber: NSView] = [:]
    private (set) var currentShowCardItems: ShowCardItems?
	private (set) var imageViewMap: [String: [ImageHoldingView]] = [:]
    private var currentFocusedActionElement: NSCell?
    
    private (set) lazy var showCardStackView: NSStackView = {
        let view = NSStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.orientation = .vertical
        view.alignment = .leading
        view.spacing = 0
        return view
    }()
    
    init(style: ACSContainerStyle, hostConfig: ACSHostConfig, renderConfig: RenderConfig) {
        self.renderConfig = renderConfig
        super.init(style: style, parentStyle: nil, hostConfig: hostConfig, superview: nil, needsPadding: true)
    }
    
    required init?(coder: NSCoder) {
        renderConfig = .default
        super.init(coder: coder)
    }
    
    private var previousBounds: NSRect?
    override func layout() {
        super.layout()
        guard window != nil else { return }
        if let pBounds = previousBounds, bounds.height != pBounds.height {
            logInfo("AdaptiveCards: layout change called from \(pBounds.height) to \(bounds.height) for id: \(identifier?.rawValue ?? "nil")")
            delegate?.acrView(self, didUpdateBoundsFrom: pBounds, to: bounds)
            resetKeyboardFocus()
        }
        previousBounds = bounds
    }
    
    override func setupViews() {
        super.setupViews()
        addSubview(showCardStackView)
    }
    
    override func setupConstraints() {
        super.setupConstraints()
        anchorBottomConstraint(with: showCardStackView.topAnchor)
        showCardStackView.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        showCardStackView.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        showCardStackView.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
    }
    
    func addTarget(_ target: TargetHandler) {
        targets.append(target)
    }
    
    func addInputHandler(_ handler: InputHandlingViewProtocol) {
        inputHandlers.append(handler)
    }
    
    func addImageSetDatasource(_ datasource: ACRCollectionViewDatasource) {
        imageSetDatasources.append(datasource)
    }
    
    func addShowCard(_ cardView: ACRView) {
        cardView.parent = self
        showCardStackView.addArrangedSubview(cardView)
        cardView.widthAnchor.constraint(equalTo: showCardStackView.widthAnchor).isActive = true
    }
    
    func resolveAttributedString(for htmlString: String) -> NSAttributedString? {
        return resolverDelegate?.resolve(self, attributedStringFor: htmlString)
    }
    
    func registerImageHandlingView(_ view: ImageHoldingView, for url: String) {
        if imageViewMap[url] == nil {
            imageViewMap[url] = []
        }
        imageViewMap[url]?.append(view)
    }
    
    func getImageDimensions(for url: String) -> NSSize? {
        return resolverDelegate?.resolve(self, dimensionsForImageWith: url)
    }
    
    func dispatchResolveRequests() {
        for url in imageViewMap.keys {
            resolverDelegate?.resolve(self, requestImageFor: url)
        }
    }
    
    private func resetKeyboardFocus {
        currentFocusedActionElement?.setAccessibilityFocused(true)
        currentFocusedActionElement = nil
    }
}

extension ACRView: TargetHandlerDelegate {
    func handleShowCardAction(button: NSButton, showCard: ACSAdaptiveCard) {
        guard let cardId = showCard.getInternalId()?.hash() else {
            logError("Card InternalID is nil")
            return
        }
        
        if let buttonCell = button.cell, buttonCell.isAccessibilityFocused() {
            currentFocusedActionElement = buttonCell
        }
        
        func manageShowCard(with id: NSNumber) {
            let cardView = showCardsMap[id] ?? AdaptiveCardRenderer.shared.renderShowCard(showCard, with: hostConfig, parent: self, config: renderConfig)
            showCardsMap[cardId] = cardView
            currentShowCardItems = (cardId, button, cardView)
            cardView.isHidden = false
            return
        }
        
        let currHeight = bounds.height
        if button.state == .on {
            if let currentCardItems = currentShowCardItems {
                // Has a current open or closed showCard
                if currentCardItems.id == cardId {
                    // current card needs to be shown
                    currentCardItems.showCard.isHidden = false
                } else {
                    // different card needs to shown
                    currentCardItems.showCard.isHidden = true
                    currentCardItems.button.state = .off
                    manageShowCard(with: cardId)
                }
            } else {
                manageShowCard(with: cardId)
            }
        } else {
            currentShowCardItems?.showCard.isHidden = true
        }
        delegate?.acrView(self, didShowCardWith: button, previousHeight: currHeight, newHeight: bounds.height)
    }
    
    func handleOpenURLAction(actionView: NSView, urlString: String) {
        delegate?.acrView(self, didSelectOpenURL: urlString, actionView: actionView)
    }
    
    func handleSubmitAction(actionView: NSView, dataJson: String?) {
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
      
        if let data = dataJson?.data(using: String.Encoding.utf8), let dataJsonDict = try? JSONSerialization.jsonObject(with: data, options: []) as? [String: Any] {
            dict.merge(dataJsonDict) { current, _ in current }
        }
        delegate?.acrView(rootView, didSubmitUserResponses: dict, actionView: actionView)
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
            
            self.showCardsMap.values
                .compactMap { $0 as? ImageResourceHandlerView }
                .forEach { $0.setImage(image, forURLsContaining: matcher) }
        }
    }
}
