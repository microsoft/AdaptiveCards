import AdaptiveCards_bridge
import AppKit

protocol ACRViewDelegate: AnyObject {
    func acrView(_ view: ACRView, didSelectOpenURL url: String, button: NSButton)
}

protocol ACRViewResourceResolverDelegate: AnyObject {
    func resolve(_ adaptiveCard: ImageResourceHandlerView, dimensionsForImageWith key: ResourceKey) -> NSSize?
    func resolve(_ adaptiveCard: ImageResourceHandlerView, requestImageFor key: ResourceKey)
}

class ACRView: ACRColumnView {
    weak var delegate: ACRViewDelegate?
    weak var resolverDelegate: ACRViewResourceResolverDelegate?
    
    private (set) var targets: [TargetHandler] = []
    private var previousCardView = NSView()
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
//        let showcard = AdaptiveCardRenderer.shared.renderAdaptiveCard(showCard, with: hostConfig, width: 335)
//
//        if button.state == .on {
//            showcard.layer?.backgroundColor = ColorUtils.hoverColorOnMouseEnter().cgColor
//            showcard.translatesAutoresizingMaskIntoConstraints = false
//
//            addArrangedSubview(showcard)
//            previousCardView = showcard
//        } else {
//            previousCardView.isHidden = true
//        }
    }
    
    func handleOpenURLAction(button: NSButton, urlString: String) {
        delegate?.acrView(self, didSelectOpenURL: urlString, button: button)
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
