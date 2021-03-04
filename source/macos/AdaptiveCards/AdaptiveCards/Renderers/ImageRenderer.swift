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
        let imageView = NSImageView(image: image)
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
    
        wrappingView.addSubview(imageView)
        
        // Image View anchors
        imageView.leadingAnchor.constraint(equalTo: wrappingView.leadingAnchor).isActive = true
        imageView.trailingAnchor.constraint(equalTo: wrappingView.trailingAnchor).isActive = true
        imageView.topAnchor.constraint(equalTo: wrappingView.topAnchor).isActive = true
        imageView.bottomAnchor.constraint(equalTo: wrappingView.bottomAnchor).isActive = true
        
        var radius: CGFloat = 0
        if imageProperties.acsImageSize == ACSImageSize.stretch {
            wrappingView.widthAnchor.constraint(equalToConstant: parent.fittingSize.width).isActive = true
            wrappingView.heightAnchor.constraint(equalTo: wrappingView.widthAnchor, multiplier: ImageUtils.getAspectRatio(from: cgsize).width).isActive = true
            radius = parent.fittingSize.width / 2.0
        } else if imageProperties.hasExplicitDimensions {
            wrappingView.widthAnchor.constraint(equalToConstant: imageProperties.pixelWidth).isActive = true
            wrappingView.heightAnchor.constraint(equalToConstant: imageProperties.pixelHeight).isActive = true
            radius = imageProperties.pixelWidth / 2.0
        } else {
            wrappingView.widthAnchor.constraint(equalToConstant: cgsize.width).isActive = true
            wrappingView.heightAnchor.constraint(equalToConstant: cgsize.height).isActive = true
            radius = cgsize.width / 2.0
        }
        
        if imageElement.getStyle() == .person {
            imageView.layer?.cornerRadius = radius
        }
        
        return wrappingView
    }
}
