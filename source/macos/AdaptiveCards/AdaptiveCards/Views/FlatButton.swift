// This file is taken from GitHub - https://www.github.com/OskarGroth/FlatButton
// Needful changes were made to the original file
// swiftlint:disable all

import AppKit
import Cocoa
import QuartzCore

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
    public var showsIcon: Bool = false
    internal var chevronSetupFlag: Bool = true
    public var iconImageName: String = "attachment"
    public var iconPositioned: NSControl.ImagePosition = .imageLeft
    public var momentary: Bool = true {
        didSet {
            animateColor(state == .on)
        }
    }
    public var onAnimationDuration: Double = 0
    public var offAnimationDuration: Double = 0.1
    public var glowRadius: CGFloat = 0 {
        didSet {
            containerLayer.shadowRadius = glowRadius
            animateColor(state == .on)
        }
    }
    public var glowOpacity: Float = 0 {
        didSet {
            containerLayer.shadowOpacity = glowOpacity
            animateColor(state == .on)
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
            animateColor(state == .on)
        }
    }
    public var activeBorderColor: NSColor = .white {
        didSet {
            animateColor(state == .on)
        }
    }
    public var buttonColor: NSColor = .white {
        didSet {
            animateColor(state == .on)
        }
    }
    public var activeButtonColor: NSColor = .white {
        didSet {
            animateColor(state == .on)
        }
    }
    public var iconColor: NSColor = .gray {
        didSet {
            animateColor(state == .on)
        }
    }
    public var activeIconColor: NSColor = .black {
        didSet {
            animateColor(state == .on)
        }
    }
    public var textColor: NSColor = .gray {
        didSet {
            animateColor(state == .on)
        }
    }
    public var activeTextColor: NSColor = .gray {
        didSet {
            animateColor(state == .on)
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
    override open var isEnabled: Bool {
        didSet {
            alphaValue = isEnabled ? 1 : 0.5
        }
    }
    
    public var contentInsets: NSEdgeInsets = NSEdgeInsets(top: 5, left: 20, bottom: 5, right: 20) {
        didSet {
            // TODO: Use this
        }
    }

    // MARK: Setup & Initialization
    
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
        positionTitleAndImage()
    }
    
    func positionTitleAndImage() {
        let attributes = [NSAttributedString.Key.font: font as Any]
        let titleSize = title.size(withAttributes: attributes)
        var titleRect = NSRect(x: 0, y: 0, width: titleSize.width, height: titleSize.height)
        var imageRect = iconLayer.frame
        var chevronRect = chevronLayer.frame
        var length : Float = 0
        var divisions = 3
        var hSpacing = round(((bounds.width) - (imageRect.width + titleSize.width + chevronRect.width)) / CGFloat(divisions))
        let vSpacing = round(((bounds.height) - (imageRect.height + titleSize.height)) / 3)
        if iconLayer.frame.width > 0 && showsChevron && (imagePosition == .imageLeft || imagePosition == .imageRight) {
            divisions = 4
            hSpacing = round(((bounds.width) - (imageRect.width + titleSize.width + chevronRect.width)) / CGFloat(divisions))
        }
        length += showsChevron ? Float(chevronLayer.frame.width) : 0
        length += showsIcon ? Float(iconLayer.frame.width) : 0
        length += Float(titleLayer.frame.width)
        length += Float(hSpacing * CGFloat(divisions))
        if let currentLayer = layer {
            currentLayer.frame = NSRect(x: currentLayer.frame.minX, y: currentLayer.frame.minY, width: CGFloat(length), height: bounds.height)
        }
        containerLayer.frame = NSRect(x: 0, y: 0, width: bounds.width, height: bounds.height)
        switch imagePosition {
        case .imageAbove:
            titleRect.origin.y = (vSpacing * 1.75) + imageRect.height
            titleRect.origin.x = hSpacing + round(imageRect.width / 2)
            imageRect.origin.y = vSpacing * 1.75
            imageRect.origin.x = hSpacing + round((titleRect.width - imageRect.width) / 2) + round(imageRect.width / 2)
            if showsChevron {
                chevronRect.origin.y = round((containerLayer.bounds.height - chevronRect.height) / 2)
                chevronRect.origin.x = round((hSpacing * 2) + titleSize.width + (imageRect.width / 2))
            }
        case .imageBelow:
            titleRect.origin.y = round(vSpacing * 2.5)
            titleRect.origin.x = hSpacing + round(imageRect.width / 2)
            imageRect.origin.y = round(vSpacing * 2.5) + titleRect.height
            imageRect.origin.x = hSpacing + round((titleRect.width - imageRect.width) / 2) + round(imageRect.width / 2)
            if showsChevron {
                chevronRect.origin.y = round((containerLayer.bounds.height - chevronRect.height) / 2)
                chevronRect.origin.x = round((hSpacing * 2) + titleSize.width + (imageRect.width / 2))
            }
        case .imageLeft:
            titleRect.origin.y = round((containerLayer.bounds.height - titleSize.height) / 2)
            titleRect.origin.x = round((hSpacing * 2) + imageRect.width)
            imageRect.origin.y = round((containerLayer.bounds.height - imageRect.height) / 2)
            imageRect.origin.x = hSpacing
            if showsChevron {
                chevronRect.origin.y = round((containerLayer.bounds.height - chevronRect.height) / 2)
                chevronRect.origin.x = round((hSpacing * 3) + titleSize.width + imageRect.width)
                if chevronSetupFlag {
                    chevronSetupFlag = false
                    containerLayer.frame.size.width += chevronRect.width
                }
            }
            
        case .imageRight:
            titleRect.origin.y = round((containerLayer.bounds.height - titleSize.height) / 2)
            titleRect.origin.x = hSpacing
            imageRect.origin.y = round((containerLayer.bounds.height - imageRect.height) / 2)
            imageRect.origin.x = (hSpacing * 2) + titleRect.width
            if showsChevron {
                chevronRect.origin.y = round((containerLayer.bounds.height - chevronRect.height) / 2)
                chevronRect.origin.x = round((hSpacing * 3) + titleSize.width + imageRect.width)
                if chevronSetupFlag {
                    chevronSetupFlag = false
                    containerLayer.frame.size.width += chevronRect.width
                }
            }
            
        default:
            if showsChevron {
                titleRect.origin.y = round((containerLayer.bounds.height - titleSize.height) / 2)
                titleRect.origin.x = round(hSpacing)
                chevronRect.origin.y = round((containerLayer.bounds.height - chevronRect.height) / 2)
                chevronRect.origin.x = round((hSpacing * 2) + titleSize.width)
            } else {
                titleRect.origin.y = round((containerLayer.bounds.height - titleSize.height) / 2)
                titleRect.origin.x = round((containerLayer.bounds.width - titleSize.width) / 2)
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
        image.size.width = (bounds.height / image.size.height) * image.size.width * 0.5
        image.size.height = bounds.height * 0.5
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
    
    func drawsChevron(_ nameOfFile: String) {
        if showsChevron {
            guard let bundle = Bundle(identifier: "com.test.test.AdaptiveCards"),
                  let path = bundle.path(forResource: nameOfFile, ofType: "png") else {
                logError("image not found")
                return
            }
            let chevIcon = NSImage(byReferencing: URL(fileURLWithPath: path))
            let maskLayer = CALayer()
            chevIcon.size.width = (bounds.height / chevIcon.size.height) * chevIcon.size.width * 0.5
            chevIcon.size.height = bounds.height * 0.5
            let chevIconSize = chevIcon.size
            let chevIconRect: NSRect = .init(x: 0, y: 0, width: chevIconSize.width, height: chevIconSize.height)
            let chevRef = chevIcon
            maskLayer.contents = chevRef
            chevronLayer.frame = chevIconRect
            maskLayer.frame = chevIconRect
            chevronLayer.mask = maskLayer
            chevronLayer.backgroundColor = NSColor.white.cgColor
        } else {
            return
        }
        positionTitleAndImage()
    }

    private func setupTrackingArea() {
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
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
    
    public func animateColor(_ isOn: Bool) {
        removeAnimations()
        let duration = isOn ? onAnimationDuration : offAnimationDuration
        let bgColor = isOn ? activeButtonColor : buttonColor
        let titleColor = isOn ? activeTextColor : textColor
        let imageColor = isOn ? activeIconColor : iconColor
        let borderColor = isOn ? activeBorderColor : self.borderColor
        layer?.backgroundColor = bgColor.cgColor
        layer?.borderColor = borderColor.cgColor
        titleLayer.foregroundColor = titleColor.cgColor
        
        if alternateImage == nil {
            iconLayer.backgroundColor = imageColor.cgColor
        } else {
            iconLayer.backgroundColor = iconColor.cgColor
            alternateIconLayer.animate(color: isOn ? activeIconColor.cgColor : NSColor.clear.cgColor, keyPath: "backgroundColor", duration: duration)
        }
        
        // Shadows
        
        if glowRadius > 0, glowOpacity > 0 {
            containerLayer.animate(color: isOn ? activeIconColor.cgColor : NSColor.clear.cgColor, keyPath: "shadowColor", duration: duration)
        }
    }

    // MARK: Interaction
    
    public func setOn(_ isOn: Bool) {
        let nextState = isOn ? NSControl.StateValue.on : NSControl.StateValue.off
        if nextState != state {
            state = nextState
            animateColor(state == .on)
        }
    }
    
    override open func hitTest(_ point: NSPoint) -> NSView? {
        return isEnabled ? super.hitTest(point) : nil
    }
    
    override open func mouseDown(with event: NSEvent) {
        if isEnabled {
            mouseDown = true
            setOn(state == .on ? false : true)
        }
        if state == .on {
            drawsChevron("arrowup")
        }
        else {
            drawsChevron("arrowdown")
        }
    }
    
    override open func mouseEntered(with event: NSEvent) {
        if mouseDown {
            setOn(state == .on ? false : true)
        }
    }
    
    override open func mouseExited(with event: NSEvent) {
        if mouseDown {
            setOn(state == .on ? false : true)
            mouseDown = false
        }
    }
    
    override open func mouseUp(with event: NSEvent) {
        if mouseDown {
            mouseDown = false
            if momentary {
                setOn(state == .on ? false : true)
            }
            _ = target?.perform(action, with: self)
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
    
    override open func draw(_ dirtyRect: NSRect) {
    }
    
    override open func layout() {
        super.layout()
        positionTitleAndImage()
    }
    
    override open func updateLayer() {
        self.updateLayer()
    }
}
