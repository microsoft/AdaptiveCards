import AdaptiveCards_bridge
import AppKit

class BaseCardElementRenderer {
    static let shared = BaseCardElementRenderer()
    
    func updateView(view: NSView, element: ACSBaseCardElement, rootView: ACRView, style: ACSContainerStyle, hostConfig: ACSHostConfig, config: RenderConfig, isfirstElement: Bool) -> NSView {
        let updatedView = ACRContentStackView(style: style, hostConfig: hostConfig)
        
        // For Spacing
        if !isfirstElement {
            updatedView.addSpacing(element.getSpacing())
        }
        
        if let elem = element as? ACSImage {
            switch elem.getHorizontalAlignment() {
            case .center: updatedView.alignment = .centerX
            case .right: updatedView.alignment = .trailing
            default: updatedView.alignment = .leading
            }
        }
        
        if let collectionElement = element as? ACSCollectionTypeElement, let columnView = view as? ACRColumnView {
            if let backgroundImage = collectionElement.getBackgroundImage(), let url = backgroundImage.getUrl() {
                columnView.setupBackgroundImageProperties(backgroundImage)
                rootView.registerImageHandlingView(columnView.backgroundImageView, for: url)
            }
        }
        
        // For seperator
        if element.getSeparator(), !isfirstElement {
            updatedView.addSeperator(true)
        }
        
        view.identifier = .init(element.getId() ?? "")
        updatedView.isHidden = !element.getIsVisible()
        
        // Input label handling
        if config.supportsSchemeV1_3, let inputElement = element as? ACSBaseInputElement, let label = inputElement.getLabel(), !label.isEmpty {
            let attributedString = NSMutableAttributedString(string: label)
            if let colorHex = hostConfig.getForegroundColor(style, color: .default, isSubtle: false), let textColor = ColorUtils.color(from: colorHex) {
                attributedString.addAttributes([.foregroundColor: textColor], range: NSRange(location: 0, length: attributedString.length))
            }
            let labelView = NSTextField(labelWithAttributedString: attributedString)
            labelView.isEditable = false
            updatedView.addArrangedSubview(labelView)
            updatedView.setCustomSpacing(spacing: 3, after: labelView)
        }
        
        updatedView.addArrangedSubview(view)
        if view is ACRContentStackView {
            view.widthAnchor.constraint(equalTo: updatedView.widthAnchor).isActive = true
        }
        return updatedView
    }
    
    func configBleed(collectionView: NSView, parentView: ACRContentStackView, with hostConfig: ACSHostConfig, element: ACSBaseCardElement, parentElement: ACSBaseCardElement?) {
        guard let collection = element as? ACSCollectionTypeElement, collection.getBleed() else {
            return
        }
        guard let collectionView = collectionView as? ACRContentStackView else {
            logError("Container is not type of ACRContentStackView")
            return
        }
        // bleed specification requires the object that's asked to be bled to have padding
        if collection.getPadding() {
            let adaptiveBleedDirection = collection.getBleedDirection()
            let direction = ACRBleedDirection(rawValue: adaptiveBleedDirection.rawValue)
            
            // 1. create a background view (bv).
            // 2. Now, add bv to the parentView
            // bv is then pinned to the parentView to the bleed direction
            // bv gets current collection view's (cv) container style
            // container view's stack view (csv) holds content views, and bv dislpays
            // container style we transpose them, and get the final result
            
            if !collection.getCanBleed() {
                return
            }
            
            let top = ((direction.rawValue & ACRBleedDirection.ACRBleedToTopEdge.rawValue) != 0)
            let leading = ((direction.rawValue & ACRBleedDirection.ACRBleedToLeadingEdge.rawValue) != 0)
            let trailing = ((direction.rawValue & ACRBleedDirection.ACRBleedToTrailingEdge.rawValue) != 0)
            let bottom = ((direction.rawValue & ACRBleedDirection.ACRBleedToBottomEdge.rawValue) != 0)
            
            var padding: CGFloat = 0
            if let paddingSpace = hostConfig.getSpacing()?.paddingSpacing {
                padding = CGFloat(truncating: paddingSpace)
            }
            collectionView.setBleedProp(top: top, bottom: bottom, trailing: trailing, leading: leading)
            var paddingBottom: CGFloat = 0
            var bottomAnchor: NSLayoutAnchor<NSLayoutYAxisAnchor> = collectionView.bottomAnchor
            if bottom {
                // case 1: when parent style == none,
                // case 2: when parent is bleeding but, bottom bleed direction false
                // case 3: when parent bleeds till end and has bottom bleed direction true
                var parentBottomBleedDirection = false
                if let parent = parentElement as? ACSCollectionTypeElement {
                    let directionParent = parent.getBleedDirection()
                    parentBottomBleedDirection = (directionParent.rawValue & ACRBleedDirection.ACRBleedToBottomEdge.rawValue) != 0
                }
                if let parentCollection = parentElement as? ACSCollectionTypeElement {
                    paddingBottom = !parentCollection.getPadding() || (parentView.bleed && parentBottomBleedDirection
                    ) ? padding : 0
                }
                bottomAnchor = parentView.bottomAnchor
            }
            
            if collection.getBackgroundImage() != nil {
                guard let collectionView = collectionView as? ACRColumnView else {
                    logError("Collection View is not type of ACRColumnView")
                    return
                }
                collectionView.bleedBackgroundImage(padding: padding, top: top, bottom: bottom, leading: leading, trailing: trailing, paddingBottom: paddingBottom, with: bottomAnchor)
                return
            }
            let backgroundView = NSView()
            backgroundView.translatesAutoresizingMaskIntoConstraints = false
            
            // adding this above collectionView backgroundImage view
            collectionView.addSubview(backgroundView, positioned: .below, relativeTo: collectionView.stackView)
            backgroundView.wantsLayer = true
            backgroundView.layer?.backgroundColor = collectionView.layer?.backgroundColor
            
            backgroundView.topAnchor.constraint(equalTo: collectionView.topAnchor, constant: top ? -padding : 0).isActive = true
            backgroundView.leadingAnchor.constraint(equalTo: collectionView.leadingAnchor, constant: leading ? -padding : 0).isActive = true
            backgroundView.trailingAnchor.constraint(equalTo: collectionView.trailingAnchor, constant: trailing ?  padding : 0).isActive = true
            backgroundView.bottomAnchor.constraint(equalTo: bottomAnchor, constant: paddingBottom).isActive = true
            
            if let borderWidth = collectionView.layer?.borderWidth {
                backgroundView.layer?.borderWidth = borderWidth
            }
            
            if let borderColor = collectionView.layer?.borderColor {
                backgroundView.layer?.borderColor = borderColor
            }
        }
    }
}
