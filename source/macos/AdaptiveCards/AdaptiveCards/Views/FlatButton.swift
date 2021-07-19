// This file is taken from GitHub - https://www.github.com/OskarGroth/FlatButton
// Needful changes were made to the original file
// swiftlint:disable all

import AppKit
import Cocoa
import QuartzCore
import Carbon.HIToolbox

extension CALayer {
    internal func animate(color: CGColor, keyPath: String, duration: Double) {
        if value(forKey: keyPath) as! CGColor? != color {
            let animation = CABasicAnimation(keyPath: keyPath)
            animation.toValue = color
            animation.fromValue = value(forKey: keyPath)
            animation.duration = duration
            animation.isRemovedOnCompletion = false
            animation.fillMode = CAMediaTimingFillMode.forwards
            add(animation, forKey: keyPath)
            setValue(color, forKey: keyPath)
        }
    }
}

open class FlatButton: NSButton, CALayerDelegate {
    internal var containerLayer = CALayer()
    internal var iconLayer = CAShapeLayer()
    internal var alternateIconLayer = CAShapeLayer()
    internal var chevronLayer = CAShapeLayer()
    internal var titleLayer = CATextLayer()
    internal var mouseDown: Bool = false
    internal var chevronSetupFlag: Bool = true
    private var isHover: Bool = false
    public var momentary: Bool = true {
        didSet {
            updateAppearance()
        }
    }
    public var onAnimationDuration: Double = 0
    public var offAnimationDuration: Double = 0.1
    public var glowRadius: CGFloat = 0 {
        didSet {
            containerLayer.shadowRadius = glowRadius
            updateAppearance()
        }
    }
    public var glowOpacity: Float = 0 {
        didSet {
            containerLayer.shadowOpacity = glowOpacity
            updateAppearance()
        }
    }
    public var cornerRadius: CGFloat = 16 {
        didSet {
            layer?.cornerRadius = cornerRadius
        }
    }
    public var borderWidth: CGFloat = 4 {
        didSet {
            layer?.borderWidth = borderWidth
        }
    }
    public var borderColor: NSColor = .darkGray {
        didSet {
            updateAppearance()
        }
    }
    public var selectedBorderColor: NSColor = .white {
        didSet {
            updateAppearance()
        }
    }
    public var buttonColor: NSColor = .white {
        didSet {
            updateAppearance()
        }
    }
    public var selectedButtonColor: NSColor = .white {
        didSet {
            updateAppearance()
        }
    }
    public var iconColor: NSColor = .gray {
        didSet {
            updateAppearance()
        }
    }
    public var selectedIconColor: NSColor = .black {
        didSet {
            updateAppearance()
        }
    }
    public var textColor: NSColor = .gray {
        didSet {
            updateAppearance()
        }
    }
    public var selectedTextColor: NSColor = .gray {
        didSet {
            updateAppearance()
        }
    }
    
    public var hoverButtonColor: NSColor = .white {
        didSet {
            updateAppearance()
        }
    }
    
    override open var title: String {
        didSet {
            setupTitle()
        }
    }
    override open var font: NSFont? {
        didSet {
            setupTitle()
        }
    }
    override open var frame: NSRect {
        didSet {
            positionTitleAndImage()
        }
    }
    override open var image: NSImage? {
        didSet {
            setupImage()
        }
    }
    override open var alternateImage: NSImage? {
        didSet {
            setupImage()
        }
    }
    open var showsChevron: Bool = false {
        didSet {
            drawsChevron("arrowdown")
        }
    }
    open var showsIcon: Bool = false {
        didSet {
            setupImage()
        }
    }
    override open var isEnabled: Bool {
        didSet {
            alphaValue = isEnabled ? 1 : 0.5
        }
    }
    
    override open var state: NSControl.StateValue {
        didSet {
            updateAppearance()
        }
    }
    
    public var contentInsets: NSEdgeInsets = NSEdgeInsets(top: 5, left: 16, bottom: 5, right: 16) {
        didSet {
            positionTitleAndImage()
        }
    }
    
    public var iconImageSize: NSSize = NSSize(width: 16, height: 16)
    public var chevronImageSize: NSSize = NSSize(width: 14, height: 14)
    private let horizontalInternalSpacing: CGFloat = 6
    private let verticalInternalSpacing: CGFloat = 3
    private var currentTrackingArea: NSTrackingArea?

    // MARK: Setup & Initialization
    
    public required init?(coder: NSCoder) {
        super.init(coder: coder)
        initialize()
    }
    
    override init(frame: NSRect) {
        super.init(frame: frame)
        initialize()
    }
    
    override open var intrinsicContentSize: NSSize {
        let attributes = [NSAttributedString.Key.font: font as Any]
        let titleSize = title.size(withAttributes: attributes)
        let insetsWidth = contentInsets.left + contentInsets.right
        let insetsHeight = contentInsets.top + contentInsets.bottom
        var totalWidth = titleSize.width + insetsWidth
        var totalHeight = titleSize.height + insetsHeight
        totalWidth += showsIcon && (imagePosition == .imageLeft || imagePosition == .imageRight) ? iconImageSize.width + horizontalInternalSpacing : 0
        totalWidth += showsChevron ? chevronImageSize.width + horizontalInternalSpacing : 0
        totalHeight += (imagePosition == .imageBelow || imagePosition == .imageAbove) ? iconImageSize.height : 0
        return NSSize(width: totalWidth, height: totalHeight)
    }
    
    private func initialize() {
        wantsLayer = true
        layer?.masksToBounds = false
        containerLayer.masksToBounds = false
        containerLayer.masksToBounds = true
        layer?.cornerRadius = 4
        layer?.borderWidth = 1
        layer?.delegate = self
        titleLayer.delegate = self
        if let scale = window?.backingScaleFactor {
            titleLayer.contentsScale = scale
        }
        iconLayer.delegate = self
        chevronLayer.delegate = self
        alternateIconLayer.delegate = self
        iconLayer.masksToBounds = true
        chevronLayer.masksToBounds = true
        alternateIconLayer.masksToBounds = true
        containerLayer.shadowOffset = NSSize.zero
        containerLayer.shadowColor = NSColor.clear.cgColor
        containerLayer.frame = NSRect(x: 0, y: 0, width: bounds.width, height: bounds.height)
        containerLayer.addSublayer(iconLayer)
        containerLayer.addSublayer(chevronLayer)
        containerLayer.addSublayer(alternateIconLayer)
        containerLayer.addSublayer(titleLayer)
        layer?.addSublayer(containerLayer)
        setupTitle()
        setupImage()
        setupTrackingArea()
        drawsChevron("arrowdown")
    }
    
    internal func setupTitle() {
        guard let font = font else {
            return
        }
        titleLayer.string = title
        titleLayer.font = font
        titleLayer.fontSize = font.pointSize
        titleLayer.truncationMode = .end
        positionTitleAndImage()
    }
    
    override open func updateTrackingAreas() {
        if let trackingArea = currentTrackingArea {
            removeTrackingArea(trackingArea)
        }
        
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
        currentTrackingArea = trackingArea
        
        if let location = window?.mouseLocationOutsideOfEventStream {
            let cLocation = convert(location, from: nil)
            NSPointInRect(cLocation, bounds) ? mouseEntered(with: NSApp.currentEvent ?? NSEvent()) : mouseExited(with: NSApp.currentEvent ?? NSEvent())
        }
        super.updateTrackingAreas()
    }
    
    func positionTitleAndImage() {
        let attributes = [NSAttributedString.Key.font: font as Any]
        var titleSize = title.size(withAttributes: attributes)
        var maxTitleWidth = bounds.width - (showsIcon && (imagePosition == .imageLeft || imagePosition == .imageRight) ? iconImageSize.width + horizontalInternalSpacing : 0) - ( contentInsets.left + contentInsets.right ) - (showsChevron ? chevronImageSize.width + horizontalInternalSpacing: 0)
        maxTitleWidth += 1
        titleSize.width = min(titleSize.width, maxTitleWidth)
        var titleRect = NSRect(x: 0, y: 0, width: titleSize.width, height: titleSize.height)
        var imageRect = iconLayer.frame
        var chevronRect = chevronLayer.frame
        var length : CGFloat = 0
        length += showsChevron ? chevronImageSize.width + horizontalInternalSpacing: 0
        length += showsIcon && (imagePosition == .imageLeft || imagePosition == .imageRight) ? iconImageSize.width + horizontalInternalSpacing : 0
        length += titleRect.width
        length += contentInsets.left + contentInsets.right
        var height : CGFloat = contentInsets.top + contentInsets.bottom + titleRect.height
        height += (imagePosition == .imageBelow || imagePosition == .imageAbove) ? iconImageSize.height + verticalInternalSpacing: 0
        let calculatedWidth = max(bounds.width, length) - 1
        if let currentLayer = layer {
            currentLayer.frame = NSRect(x: currentLayer.frame.minX, y: currentLayer.frame.minY, width: calculatedWidth, height: bounds.height)
        }
        if showsChevron || showsIcon {
            containerLayer.frame.size = NSSize(width: length, height: bounds.height)
            containerLayer.position = NSPoint(x: bounds.midX, y: bounds.midY)
        } else {
            containerLayer.frame = NSRect(x: 0, y: 0, width: bounds.width, height: bounds.height)
        }
        switch imagePosition {
        case .imageAbove:
            imageRect.origin.y = contentInsets.top
            imageRect.origin.x = contentInsets.left + round((titleRect.width - iconImageSize.width) / 2)
            titleRect.origin.y = imageRect.maxY + verticalInternalSpacing
            titleRect.origin.x = contentInsets.left
            if showsChevron {
                chevronRect.origin.y = round((bounds.height - chevronImageSize.height) / 2)
                chevronRect.origin.x = titleRect.maxX + horizontalInternalSpacing
            }
        case .imageBelow:
            titleRect.origin.y = contentInsets.top
            titleRect.origin.x = contentInsets.left
            imageRect.origin.y = titleRect.maxY + verticalInternalSpacing
            imageRect.origin.x = contentInsets.left + round((titleRect.width - iconImageSize.width) / 2)
            if showsChevron {
                chevronRect.origin.y = round((bounds.height - chevronRect.height) / 2)
                chevronRect.origin.x = titleRect.maxX + horizontalInternalSpacing
            }
        case .imageLeft:
            titleRect.origin.y = round((bounds.height - titleSize.height) / 2)
            titleRect.origin.x = contentInsets.left + iconImageSize.width + horizontalInternalSpacing
            imageRect.origin.y = round((bounds.height - iconImageSize.height) / 2)
            imageRect.origin.x = contentInsets.left
            if showsChevron {
                chevronRect.origin.y = round((bounds.height - chevronImageSize.height) / 2)
                chevronRect.origin.x = titleRect.maxX + horizontalInternalSpacing
                if chevronSetupFlag {
                    chevronSetupFlag = false
                    containerLayer.frame.size.width += chevronImageSize.width
                }
            }
            
        case .imageRight:
            if showsChevron {
                if chevronSetupFlag {
                    chevronSetupFlag = false
                    containerLayer.frame.size.width += chevronImageSize.width
                }
                chevronRect.origin.y = round((bounds.height - chevronImageSize.height) / 2)
                chevronRect.origin.x = contentInsets.left
                titleRect.origin.y = round((bounds.height - titleSize.height) / 2)
                titleRect.origin.x = chevronRect.maxX + horizontalInternalSpacing
                imageRect.origin.y = round((bounds.height - iconImageSize.height) / 2)
                imageRect.origin.x = titleRect.maxX + horizontalInternalSpacing
                }
            else {
                titleRect.origin.y = round((bounds.height - titleSize.height) / 2)
                titleRect.origin.x = contentInsets.left
                imageRect.origin.y = round((bounds.height - iconImageSize.height) / 2)
                imageRect.origin.x = titleRect.maxX + horizontalInternalSpacing
            }
        default:
            if showsChevron {
                titleRect.origin.y = round((bounds.height - titleSize.height) / 2)
                titleRect.origin.x = contentInsets.left
                chevronRect.origin.y = round((bounds.height - chevronImageSize.height) / 2)
                chevronRect.origin.x = titleRect.maxX + horizontalInternalSpacing
            } else {
                titleRect.origin.y = round((bounds.height - titleSize.height) / 2)
                titleRect.origin.x = round((bounds.width - titleSize.width) / 2)
            }
        }
        iconLayer.frame = imageRect
        alternateIconLayer.frame = imageRect
        chevronLayer.frame = chevronRect
        titleLayer.frame = titleRect
    }
    
    internal func setupImage() {
        guard let image = image else {
            return
        }
        let maskLayer = CALayer()
        image.size = iconImageSize
        let imageSize = image.size
        let imageRect: NSRect = .init(x: 0, y: 0, width: imageSize.width, height: imageSize.height)
        let imageRef = image
        maskLayer.contents = imageRef
        iconLayer.frame = imageRect
        maskLayer.frame = imageRect
        iconLayer.mask = maskLayer
        if let alternateImage = alternateImage {
            let altMaskLayer = CALayer()
            alternateImage.size.width = (containerLayer.bounds.height / alternateImage.size.height) * alternateImage.size.width * 0.5
            alternateImage.size.height = containerLayer.bounds.height * 0.5
            let altImageSize = alternateImage.size
            let altImageRect: NSRect = .init(x: 0, y: 0, width: altImageSize.width, height: altImageSize.height)
            let altImageRef = alternateImage
            altMaskLayer.contents = altImageRef
            alternateIconLayer.frame = altImageRect
            altMaskLayer.frame = altImageRect
            alternateIconLayer.mask = altMaskLayer
            alternateIconLayer.frame = altImageRect
        }
        positionTitleAndImage()
    }
    
    private func drawsChevron(_ nameOfFile: String) {
        guard showsChevron else { return }
        guard let chevIcon = BundleUtils.getImage(nameOfFile, ofType: "png") else { return }
        let maskLayer = CALayer()
        chevIcon.size = chevronImageSize
        let chevIconSize = chevIcon.size
        let chevIconRect: NSRect = .init(x: 0, y: 0, width: chevIconSize.width, height: chevIconSize.height)
        let chevRef = chevIcon
        maskLayer.contents = chevRef
        chevronLayer.frame = chevIconRect
        maskLayer.frame = chevIconRect
        chevronLayer.mask = maskLayer
        chevronLayer.backgroundColor = titleLayer.foregroundColor
        positionTitleAndImage()
    }

    private func setupTrackingArea() {
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
        currentTrackingArea = trackingArea
    }
    
    // MARK: Animations
    
    internal func removeAnimations() {
        layer?.removeAllAnimations()
        if layer?.sublayers != nil {
            for subLayer in (layer?.sublayers)! {
                subLayer.removeAllAnimations()
            }
        }
    }
    
    public func updateAppearance() {
        removeAnimations()
        let isOn = state == .on
        
        let duration = isOn ? onAnimationDuration : offAnimationDuration
        let bgColor = isOn ? selectedButtonColor : (mouseDown ? selectedButtonColor : (isHover ? hoverButtonColor : buttonColor))
        let titleColor = isOn ? selectedTextColor : (isHover ? selectedTextColor : textColor)
        let imageColor = isOn ? selectedIconColor : iconColor
        let borderColor = isOn ? selectedBorderColor : (isHover ? selectedBorderColor : self.borderColor)
        layer?.backgroundColor = bgColor.cgColor
        layer?.borderColor = borderColor.cgColor
        titleLayer.foregroundColor = titleColor.cgColor
        
        if alternateImage == nil {
            iconLayer.backgroundColor = imageColor.cgColor
        } else {
            iconLayer.backgroundColor = iconColor.cgColor
            alternateIconLayer.animate(color: isOn ? selectedIconColor.cgColor : NSColor.clear.cgColor, keyPath: "backgroundColor", duration: duration)
        }
        
        // Shadows
        
        if glowRadius > 0, glowOpacity > 0 {
            containerLayer.animate(color: isOn ? selectedIconColor.cgColor : NSColor.clear.cgColor, keyPath: "shadowColor", duration: duration)
        }
        
        drawsChevron(state == .on ? "arrowup" : "arrowdown")
    }

    // MARK: Interaction
    private func toggleState() {
        let nextState: NSButton.StateValue = state == .on ? .off : .on
        state = nextState
    }
    
    override open func hitTest(_ point: NSPoint) -> NSView? {
        return isEnabled ? super.hitTest(point) : nil
    }
    
    override open func mouseDown(with event: NSEvent) {
        if isEnabled {
            mouseDown = true
            updateAppearance()
        }
    }
    
    override open func mouseEntered(with event: NSEvent) {
        isHover = true
        updateAppearance()
    }
    
    override open func mouseExited(with event: NSEvent) {
        isHover = false
        if mouseDown {
            mouseDown = false
        }
        updateAppearance()
    }
    
    override open func mouseUp(with event: NSEvent) {
        if mouseDown {
            mouseDown = false
            if !momentary {
                toggleState()
            }
            updateAppearance()
            _ = target?.perform(action, with: self)
        }
    }
    
    override open func keyDown(with event: NSEvent) {
        super.keyDown(with: event)
        if event.keyCode == UInt16(kVK_Space) && momentary {
            updateAppearance()
        }
    }
    
    override open func keyUp(with event: NSEvent) {
        super.keyUp(with: event)
        if event.keyCode == UInt16(kVK_Space) && momentary {
            state = .off
        }
    }
    
    // MARK: Drawing
    override open func viewDidChangeBackingProperties() {
        super.viewDidChangeBackingProperties()
        if let scale = window?.backingScaleFactor {
            titleLayer.contentsScale = scale
            layer?.contentsScale = scale
            iconLayer.contentsScale = scale
        }
    }
    
    open func layer(_ layer: CALayer, shouldInheritContentsScale newScale: CGFloat, from window: NSWindow) -> Bool {
        return true
    }
    
    override open func draw(_ dirtyRect: NSRect) { } // Needs to be empty
    
    override open func layout() {
        super.layout()
        positionTitleAndImage()
    }
}
