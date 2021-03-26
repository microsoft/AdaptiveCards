import AdaptiveCards_bridge
import AppKit

protocol ACRViewDelegate: AnyObject {
    func acrView(_ view: ACRView, didSelectOpenURL url: String, actionView: NSView)
    func acrView(_ view: ACRView, didSubmitUserResponses dict: [String: Any], actionView: NSView)
}

protocol ACRViewResourceResolverDelegate: AnyObject {
    func resolve(_ adaptiveCard: ImageResourceHandlerView, dimensionsForImageWith key: ResourceKey) -> NSSize?
    func resolve(_ adaptiveCard: ImageResourceHandlerView, requestImageFor key: ResourceKey)
}

class ACRView: ACRColumnView {
    typealias ShowCardItems = (id: NSNumber, button: NSButton, showCard: NSView)
    
    weak var delegate: ACRViewDelegate?
    weak var resolverDelegate: ACRViewResourceResolverDelegate?

    private (set) var targets: [TargetHandler] = []
    private (set) var inputHandlers: [InputHandlingViewProtocol] = []
    private (set) var showCardsMap: [NSNumber: NSView] = [:]
    private (set) var currentShowCardItems: ShowCardItems?
	private (set) var imageViewMap: [String: [NSImageView]] = [:]
    
    init(style: ACSContainerStyle, hostConfig: ACSHostConfig) {
        super.init(style: style, parentStyle: nil, hostConfig: hostConfig, superview: nil)
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
    }
    
    func addTarget(_ target: TargetHandler) {
        targets.append(target)
    }
    
    func addInputHandler(_ handler: InputHandlingViewProtocol) {
        inputHandlers.append(handler)
    }
    
    func getImageView(for key: ResourceKey) -> NSImageView {
        let imageView: NSImageView
        if let dimensions = resolverDelegate?.resolve(self, dimensionsForImageWith: key) {
            let image = NSImage(size: dimensions)
            imageView = NSImageView(image: image)
        } else {
            imageView = NSImageView()
        }

        if imageViewMap[key.url] == nil { imageViewMap[key.url] = [] }
        imageViewMap[key.url]?.append(imageView)
        
        resolverDelegate?.resolve(self, requestImageFor: key)
        return imageView
    }
}

extension ACRView: TargetHandlerDelegate {
    func handleShowCardAction(button: NSButton, showCard: ACSAdaptiveCard) {
        guard let cardId = showCard.getInternalId()?.hash() else {
            logError("Card InternalID is nil")
            return
        }
        
        func manageShowCard(with id: NSNumber) {
            let cardView = showCardsMap[id] ?? AdaptiveCardRenderer.shared.renderShowCard(showCard, with: hostConfig, parent: self)
            showCardsMap[cardId] = cardView
            currentShowCardItems = (cardId, button, cardView)
            cardView.isHidden = false
            return
        }
        
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
    }
    
    func handleOpenURLAction(actionView: NSView, urlString: String) {
        delegate?.acrView(self, didSelectOpenURL: urlString, actionView: actionView)
    }
    
    func handleSubmitAction(actionView: NSView, dataJson: String?) {
        var dict = [String: Any]()
        for handler in inputHandlers {
            guard handler.isValid else { continue }
            dict[handler.key] = handler.value
        }
        
        if let data = dataJson?.data(using: String.Encoding.utf8), let dataJsonDict = try? JSONSerialization.jsonObject(with: data, options: []) as? [String: Any] {
            dict.merge(dataJsonDict) { current, _ in current }
        }
        delegate?.acrView(self, didSubmitUserResponses: dict, actionView: actionView)
    }
}

extension ACRView: ImageResourceHandlerView {
    func setImage(_ image: NSImage, for key: ResourceKey) {
        guard let imageViews = imageViewMap[key.url] else {
            return
        }
        // handling image resourve type
        if key.type == .image {
            for imageView in imageViews {
                if imageView.image == nil {
                    // update constraints only when image view does not contain an image
                    ImageRenderer.shared.configUpdateForImage(image: image, imageView: imageView)
                }
                imageView.image = image
            }
        }
    }
}
