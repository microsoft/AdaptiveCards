import AdaptiveCards_bridge
import AppKit

class ACRBackgroundImageView: NSView, CALayerDelegate {
    public var image: NSImage? {
        didSet {
            setupBGImage()
        }
    }
    public var fillMode = ACSImageFillMode.cover
    public var horizontalAlignment = ACSHorizontalAlignment.left
    public var verticalAlignment = ACSVerticalAlignment.top
    
    private var bgImageLayer = CALayer()
    private var ratio = CGFloat(1)
    
    public required init?(coder: NSCoder) {
        super.init(coder: coder)
        initialize()
    }
    
    override init(frame: NSRect) {
        super.init(frame: frame)
        initialize()
    }
    
    private func initialize() {
        wantsLayer = true
        layer?.delegate = self
        layer?.masksToBounds = true
        bgImageLayer.masksToBounds = false
        bgImageLayer.shadowOffset = NSSize.zero
        bgImageLayer.shadowColor = NSColor.clear.cgColor
        bgImageLayer.frame = NSRect(x: 0, y: 0, width: frame.width, height: frame.height)
        layer?.insertSublayer(bgImageLayer, below: layer)
        setupBGImage()
    }
    
    private func setupBGImage() {
        guard let image = image else { return }
        /* In this block of code, the basic approach used to implement the alignment is that the layer is padded with image on the horizontal or vertical (whichever required) axes with the image pattern. After this is done, based on the requirements, the origin of the layer is offsetted so as to create the desired placement of the image pattern based on the vertical alignment, horizontal alignment, and fill modes. */

        switch fillMode {
        case .cover:
            ratio = max(bounds.height / image.size.height, bounds.width / image.size.width)
            image.size = .init(width: image.size.width * ratio, height: image.size.height * ratio)
            bgImageLayer.frame = .init(x: 0, y: 0, width: image.size.width, height: image.size.height)
            
            switch verticalAlignment {
            case .center:
                bgImageLayer.frame.origin.y -= (image.size.height - bounds.height) / 2
            case .bottom:
                bgImageLayer.frame.origin.y += (bounds.height - image.size.height)
            default:
                break
            }
            
            switch horizontalAlignment {
            case .center:
                bgImageLayer.frame.origin.x -= (image.size.width - bounds.width) / 2
            case .right:
                bgImageLayer.frame.origin.x += (bounds.width - image.size.width)
            default:
                break
            }
        
        case .repeatHorizontally:
            bgImageLayer.frame = NSRect(x: 0, y: 0, width: bounds.width + image.size.width, height: image.size.height)
            
            switch verticalAlignment {
            case .center:
                bgImageLayer.frame.origin.y += (bounds.height - image.size.height) / 2
            case .bottom:
                bgImageLayer.frame.origin.y += (bounds.height - image.size.height)
            default:
                break
            }
            
            switch horizontalAlignment {
            case .center:
                var offset = (0.5 - (bounds.width / (2 * image.size.width)).truncatingRemainder(dividingBy: 1))
                offset = offset > 0 ? offset : (1 + offset)
                bgImageLayer.frame.origin.x -= offset * image.size.width
            case .right:
                bgImageLayer.frame.origin.x -= (1 - ((bounds.width / image.size.width).truncatingRemainder(dividingBy: 1))) * image.size.width
            default:
                break
            }
        
        case .repeatVertically:
            bgImageLayer.frame = NSRect(x: 0, y: 0, width: image.size.width, height: image.size.height + bounds.height)
            
            switch verticalAlignment {
            case .center:
                var offset = (0.5 - ((bounds.height / (2 * image.size.height)).truncatingRemainder(dividingBy: 1.0)))
                offset = offset > 0 ? offset : (1 + offset)
                bgImageLayer.frame.origin.y -= offset * image.size.height
            case .bottom:
                bgImageLayer.frame.origin.y -= (1 - ((bounds.height / image.size.height).truncatingRemainder(dividingBy: 1))) * image.size.height
            default:
                break
            }
            
            switch horizontalAlignment {
            case .center:
                bgImageLayer.frame.origin.x += (bounds.width - image.size.width) / 2
            case .right:
                bgImageLayer.frame.origin.x += (bounds.width - image.size.width)
            default:
                break
            }
            
        case .repeat:
            bgImageLayer.frame = NSRect(x: 0, y: 0, width: image.size.width + bounds.width, height: image.size.height + bounds.height)
            
            switch verticalAlignment {
            case .center:
                var offset = (0.5 - ((bounds.height / (2 * image.size.height)).truncatingRemainder(dividingBy: 1.0)))
                offset = offset > 0 ? offset : (1 + offset)
                bgImageLayer.frame.origin.y -= offset * image.size.height
            case .bottom:
                bgImageLayer.frame.origin.y -= (1 - ((bounds.height / image.size.height).truncatingRemainder(dividingBy: 1))) * image.size.height
            default:
                break
            }
            
            switch horizontalAlignment {
            case .center:
                var offset = (0.5 - (bounds.width / (2 * image.size.width)).truncatingRemainder(dividingBy: 1))
                offset = offset > 0 ? offset : (1 + offset)
                bgImageLayer.frame.origin.x -= offset * image.size.width
            case .right:
                bgImageLayer.frame.origin.x -= (1 - ((bounds.width / image.size.width).truncatingRemainder(dividingBy: 1))) * image.size.width
            default:
                break
            }
        @unknown default:
            fatalError()
        }
        bgImageLayer.backgroundColor = NSColor(patternImage: image).cgColor
    }
}
