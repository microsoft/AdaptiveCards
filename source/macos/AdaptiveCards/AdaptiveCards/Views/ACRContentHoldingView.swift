import AdaptiveCards_bridge
import AppKit

class ACRImageWrappingView: NSView, SelectActionHandlingProtocol {
    private weak var _viewgroup: ACRContentStackView?
    private weak var _imageViewHeightConstraint: NSLayoutConstraint?
    private weak var _heightConstraint: NSLayoutConstraint?
    weak var imageView: NSImageView?
    var imageProperties: ACRImageProperties?
    var target: TargetHandler?
    
    var isImageSet = false
    var isPersonStyle = false

    override public init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
    }

    public required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    required init(imageProperties: ACRImageProperties, imageView: NSImageView, viewgroup: ACRContentStackView) {
        let frame = CGRect(x: 0, y: 0, width: imageProperties.contentSize.width, height: imageProperties.contentSize.height)
        super.init(frame: frame)
        needsLayout = true
        self.imageProperties = imageProperties
        self.imageView = imageView
        _viewgroup = viewgroup
        self.addSubview(imageView)
        setupTrackingArea()
    }
    
    override func layout() {
        super.layout()
        if isPersonStyle {
            let subview = self.subviews[0]
            let radius = subview.bounds.size.width / 2
            subview.wantsLayer = true
            subview.layer?.cornerRadius = radius
            subview.layer?.masksToBounds = true
        }
    }
    
    override var intrinsicContentSize: NSSize {
        guard let size = imageProperties?.contentSize else {
            return super.intrinsicContentSize
        }
        return size.width > 0 ? size : super.intrinsicContentSize
    }
    
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        guard let hasExpilicitDimension = imageProperties?.hasExplicitDimensions, !hasExpilicitDimension else { return }
        setWidthConstraintWithSuperView()
    }

    private func setWidthConstraintWithSuperView() {
        guard let superView = self.superview else { return }
        if isImageSet {
            // when actual image or its dimensions are available
            if imageProperties?.acsImageSize != .stretch {
                widthAnchor.constraint(greaterThanOrEqualTo: superView.widthAnchor).isActive = true
            } else {
                widthAnchor.constraint(equalTo: superView.widthAnchor).isActive = true
            }
        } else {
            widthAnchor.constraint(equalTo: superView.widthAnchor).isActive = true
        }
    }
    
    override func mouseDown(with event: NSEvent) {
        super.mouseDown(with: event)
        guard let target = target else { return }
        target.handleSelectionAction(for: self)
    }
    
    override func hitTest(_ point: NSPoint) -> NSView? {
        guard target != nil, frame.contains(point) else { return super.hitTest(point) }
        return self
    }
    
    private func setupTrackingArea() {
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
    }
    
    private var previousBackgroundColor: CGColor?
    override func mouseEntered(with event: NSEvent) {
        guard let columnView = event.trackingArea?.owner as? ACRImageWrappingView, target != nil else { return }
        previousBackgroundColor = columnView.layer?.backgroundColor
        columnView.layer?.backgroundColor = ColorUtils.hoverColorOnMouseEnter().cgColor
    }
    
    override func mouseExited(with event: NSEvent) {
        guard let columnView = event.trackingArea?.owner as? ACRImageWrappingView, target != nil else { return }
        columnView.layer?.backgroundColor = previousBackgroundColor ?? .clear
    }
 }
