import AdaptiveCards_bridge
import AppKit

class ImageRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = ImageRenderer()
    let sample = "https://messagecardplayground.azurewebsites.net/assets/TxP_Flight.png"
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let imageElement = element as? ACSImage else {
            logError("Element is not of type ACSImage")
            return NSView()
        }
        // Fetching images from remote URL for testing purposes (Blocks main thread)
        // This will be removed and changed to Resource Resolver or similar mechanism to resolve content
        // swiftlint:disable force_cast
        let url = URL(string: imageElement.getUrl() ?? self.sample)
        let image = NSImage(byReferencing: url as! URL)
        // swiftlint:enable force_cast
                
        // Setting up image Properties
        let imageProperties = ACRImageProperties(element: imageElement, config: hostConfig, image: image, parentView: parentView)
        let cgsize = imageProperties.contentSize

        // Setting up ImageView based on Image Properties
        let imageView = NSImageView(frame: NSRect(x: 0, y: 0, width: cgsize.width, height: cgsize.height))
        imageView.image = image
        imageView.translatesAutoresizingMaskIntoConstraints = false
        imageView.layer?.masksToBounds = true
        
        if imageProperties.isAspectRatioNeeded {
            // when either width or height px is available
            // this will provide content aspect fill scaling
            imageView.imageScaling = .scaleProportionallyUpOrDown
        } else {
            // content aspect fit behaviour
            imageView.imageScaling = .scaleAxesIndependently
        }
        
        guard let parent = rootView as? ACRContentStackView else {
            logError("Parent is not of type ACRContentStackView")
            return NSView()
        }
    
        // Setting up content holder view
        let wrappingView = ACRContentHoldingView(imageProperties: imageProperties, imageView: imageView, viewgroup: parent)
        wrappingView.translatesAutoresizingMaskIntoConstraints = false
    
        // Background color attribute
        if let backgroundColor = imageElement.getBackgroundColor() {
            imageView.wantsLayer = true
            if let color = ColorUtils.color(from: backgroundColor) {
                imageView.layer?.backgroundColor = color.cgColor
            }
        }
    
        switch imageProperties.acsHorizontalAlignment {
        case .center: imageView.centerXAnchor.constraint(equalTo: wrappingView.centerXAnchor).isActive = true
        case .right: imageView.trailingAnchor.constraint(equalTo: wrappingView.trailingAnchor).isActive = true
        default: imageView.leadingAnchor.constraint(equalTo: wrappingView.leadingAnchor).isActive = true
        }
        
        wrappingView.heightAnchor.constraint(equalTo: imageView.heightAnchor).isActive = true
        if imageProperties.acsImageSize == ACSImageSize.stretch {
            wrappingView.widthAnchor.constraint(greaterThanOrEqualTo: imageView.widthAnchor).isActive = true
        } else {
            wrappingView.widthAnchor.constraint(equalTo: imageView.widthAnchor).isActive = true
        }
        
        let imagePriority = getImageViewLayoutPriority(wrappingView)
        if imageProperties.acsImageSize != ACSImageSize.stretch {
            imageView.setContentHuggingPriority(imagePriority, for: .horizontal)
            imageView.setContentHuggingPriority(NSLayoutConstraint.Priority.defaultHigh, for: .vertical)
            imageView.setContentCompressionResistancePriority(imagePriority, for: .horizontal)
            imageView.setContentCompressionResistancePriority(imagePriority, for: .vertical)
        }
        
        configUpdateForImage(element: imageElement, with: hostConfig, image: image, imageView: imageView, contendHoldingView: wrappingView)
        
        if imageElement.getStyle() == .person {
            wrappingView.isPersonStyle = true
        }
        
        return wrappingView
    }
    
    func configUpdateForImage(element: ACSImage, with hostConfig: ACSHostConfig, image: NSImage, imageView: NSImageView, contendHoldingView: ACRContentHoldingView) {
        let superView = contendHoldingView
        let imageProperties = superView.imageProperties
        imageProperties?.updateContentSize(size: image.size)
        let cgSize = imageProperties?.contentSize ?? CGSize.zero
        
        let priority = getImageViewLayoutPriority(superView)
        
        var constraints: [NSLayoutConstraint] = []
        
        constraints.append(imageView.widthAnchor.constraint(equalToConstant: cgSize.width))
        constraints.append(imageView.heightAnchor.constraint(equalToConstant: cgSize.height))
        constraints[0].priority = priority
        constraints[1].priority = priority
        
        constraints.append(imageView.widthAnchor.constraint(equalTo: imageView.heightAnchor, multiplier: cgSize.width / cgSize.height, constant: 0))
        constraints.append(imageView.heightAnchor.constraint(equalTo: imageView.widthAnchor, multiplier: cgSize.height / cgSize.width, constant: 0))
        constraints[2].priority = priority + 2
        constraints[3].priority = priority + 2
        
        NSLayoutConstraint.activate(constraints)
                    
        superView.invalidateIntrinsicContentSize()
    }
    
    func getImageViewLayoutPriority(_ wrappingView: NSView) -> NSLayoutConstraint.Priority {
        let ACRColumnWidthPriorityStretch = 249
        let priority = wrappingView.contentHuggingPriority(for: .horizontal)
        return (Int(priority.rawValue) > ACRColumnWidthPriorityStretch) ? NSLayoutConstraint.Priority.defaultHigh : priority
    }
}
