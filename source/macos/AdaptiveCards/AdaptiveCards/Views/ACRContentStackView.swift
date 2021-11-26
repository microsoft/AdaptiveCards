import AdaptiveCards_bridge
import AppKit

protocol ACRContentHoldingViewProtocol {
    func addArrangedSubview(_ subview: NSView)
    func applyPadding(_ padding: CGFloat)
}

class ACRContentStackView: NSView, ACRContentHoldingViewProtocol, SelectActionHandlingProtocol {
    private var stackViewLeadingConstraint: NSLayoutConstraint?
    private var stackViewTrailingConstraint: NSLayoutConstraint?
    private var stackViewTopConstraint: NSLayoutConstraint?
    private var stackViewBottomConstraint: NSLayoutConstraint?
    
    private var currentSpacingView: SpacingView?
    private var currentSeparatorView: SpacingView?
    
    let style: ACSContainerStyle
    let hostConfig: ACSHostConfig
    var target: TargetHandler?
    public var bleed = false
    
    public var orientation: NSUserInterfaceLayoutOrientation {
        get { return stackView.orientation }
        set {
            stackView.orientation = newValue
            stackView.alignment = newValue == .horizontal ? .top : .leading
        }
    }
    
    public var alignment: NSLayoutConstraint.Attribute {
        get { return stackView.alignment }
        set { stackView.alignment = newValue }
    }
    
    public var distribution: NSStackView.Distribution {
        get { return stackView.distribution }
        set { stackView.distribution = newValue }
    }
    
    public var arrangedSubviews: [NSView] {
        return stackView.arrangedSubviews
    }
    
    private (set) lazy var stackView: NSStackView = {
        let view = NSStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.orientation = .vertical
        view.alignment = .leading
        view.spacing = 0
        return view
    }()
    
    init(style: ACSContainerStyle, hostConfig: ACSHostConfig) {
        self.hostConfig = hostConfig
        self.style = style
        super.init(frame: .zero)
        initialize()
    }
    
    init(style: ACSContainerStyle, parentStyle: ACSContainerStyle?, hostConfig: ACSHostConfig, superview: NSView?, needsPadding: Bool) {
        self.hostConfig = hostConfig
        self.style = style
        super.init(frame: .zero)
        initialize()
        if needsPadding {
            if let bgColor = hostConfig.getBackgroundColor(for: style) {
                layer?.backgroundColor = bgColor.cgColor
            }
        /* Experimental Feature
            // set border color
            if let borderColorHex = hostConfig.getBorderColor(style), let borderColor = ColorUtils.color(from: borderColorHex) {
                layer?.borderColor = borderColor.cgColor
            }
            // set border width
            if let borderWidth = hostConfig.getBorderThickness(style) {
                layer?.borderWidth = CGFloat(truncating: borderWidth)
            }
        */
            // add padding
            if let paddingSpace = hostConfig.getSpacing()?.paddingSpacing, let padding = CGFloat(exactly: paddingSpace) {
                applyPadding(padding)
            }
        }
    }
    
    required init?(coder: NSCoder) {
        self.hostConfig = ACSHostConfig() // TODO: This won't work
        self.style = .none
        super.init(coder: coder)
        initialize()
    }
    
    private func initialize() {
        wantsLayer = true
        if !(self is ACRView) { // RootView should support clipping
            layer = NoClippingLayer()
        }
        setupViews()
        setupConstraints()
        setupTrackingArea()
    }
    
    func addArrangedSubview(_ subview: NSView) {
        stackView.addArrangedSubview(subview)
    }
    
    func addView(_ view: NSView, in gravity: NSStackView.Gravity) {
        stackView.addView(view, in: gravity)
    }
    
    func applyPadding(_ padding: CGFloat) {
        stackViewLeadingConstraint?.constant = padding
        stackViewTopConstraint?.constant = padding
        stackViewTrailingConstraint?.constant = -padding
        stackViewBottomConstraint?.constant = -padding
    }
    
    func setBleedProp(top: Bool, bottom: Bool, trailing: Bool, leading: Bool) {
        if top {
            stackViewTopConstraint?.constant = 0
        }
        if bottom {
            stackViewBottomConstraint?.constant = 0
        }
        if leading {
            stackViewLeadingConstraint?.constant = 0
        }
        if trailing {
            stackViewTrailingConstraint?.constant = 0
        }
    }
    
    func addSeperator(_ separator: Bool) {
        guard separator else { return }
        let seperatorConfig = hostConfig.getSeparator()
        let lineThickness = seperatorConfig?.lineThickness
        let lineColor = seperatorConfig?.lineColor
        addSeperator(thickness: lineThickness ?? 1, color: lineColor ?? "#EEEEEE")
    }
    
    func addSpacing(_ spacing: ACSSpacing) {
        let spaceAdded = HostConfigUtils.getSpacing(spacing, with: hostConfig)
        addSpacing(spacing: CGFloat(truncating: spaceAdded))
    }
    
    func setCustomSpacing(spacing: CGFloat, after view: NSView) {
        stackView.setCustomSpacing(spacing, after: view)
    }
    
    private func addSeperator(thickness: NSNumber, color: String) {
        let seperatorView = SpacingView(asSeparatorViewWithThickness: CGFloat(truncating: thickness), color: color, orientation: orientation)
        stackView.addArrangedSubview(seperatorView)
        stackView.setCustomSpacing(5, after: seperatorView)
        currentSeparatorView = seperatorView
    }
    
    private func addSpacing(spacing: CGFloat) {
        let spacingView = SpacingView(orientation: orientation, spacing: spacing)
        stackView.addArrangedSubview(spacingView)
        currentSpacingView = spacingView
    }
    
    private func setupTrackingArea() {
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
    }
    
    /// This method can be overridden, but not to be called from anywhere
    func setupViews() {
        addSubview(stackView)
    }
    
    /// This method can be overridden, but not to be called from anywhere
    func setupConstraints() {
        stackViewLeadingConstraint = stackView.leadingAnchor.constraint(equalTo: leadingAnchor)
        stackViewTrailingConstraint = stackView.trailingAnchor.constraint(equalTo: trailingAnchor)
        stackViewTopConstraint = stackView.topAnchor.constraint(equalTo: topAnchor)
        stackViewBottomConstraint = stackView.bottomAnchor.constraint(equalTo: bottomAnchor)
        
        guard let leading = stackViewLeadingConstraint, let trailing = stackViewTrailingConstraint, let top = stackViewTopConstraint, let bottom = stackViewBottomConstraint else { return }
        NSLayoutConstraint.activate([leading, trailing, top, bottom])
        stackView.setHuggingPriority(.fittingSizeCompression, for: .vertical)
        stackView.setContentHuggingPriority(.fittingSizeCompression, for: .vertical)
    }
    
    /// This method can be overridden, but not to be called from anywhere
    func anchorBottomConstraint(with anchor: NSLayoutAnchor<NSLayoutYAxisAnchor>) {
        stackViewBottomConstraint?.isActive = false
        stackViewBottomConstraint = stackView.bottomAnchor.constraint(equalTo: anchor)
        stackViewBottomConstraint?.isActive = true
    }
    
    func setVerticalHuggingPriority(_ rawValue: Float) {
        stackView.setHuggingPriority(NSLayoutConstraint.Priority(rawValue), for: .vertical)
    }
    
    func setMinimumHeight(_ height: NSNumber?) {
        guard let height = height, let heightPt = CGFloat(exactly: height), heightPt > 0 else { return }
        heightAnchor.constraint(greaterThanOrEqualToConstant: heightPt).isActive = true
    }
    
    func refreshOnVisibilityChange(from isHiddenOld: Bool) {
        // Ignore refresh if view is isHidden or state is not changed
        // Ignore refresh if view is not inside a stackView
        guard !isHidden, isHidden != isHiddenOld, let stackView = superview as? NSStackView else { return }
        
        // Spacer and Separator to be hidden only if this view is the first element of the parent stack
        // Ignore all Spacing to chack firstElement, as they're added for `verticalContentAlignment`. Refer ContainerRenderer / ColumnRenderer.
        let isFirstElement = stackView.arrangedSubviews.first { !$0.isHidden && !($0 is SpacingView) } == self
        currentSpacingView?.isHidden = isFirstElement
        currentSeparatorView?.isHidden = isFirstElement
    }
    
    // MARK: Mouse Events and SelectAction logics
    private var previousBackgroundColor: CGColor?
    override func mouseEntered(with event: NSEvent) {
        guard target != nil else { return }
        previousBackgroundColor = layer?.backgroundColor
        layer?.backgroundColor = ColorUtils.hoverColorOnMouseEnter().cgColor
    }
    
    override func mouseExited(with event: NSEvent) {
        guard target != nil else { return }
        layer?.backgroundColor = previousBackgroundColor ?? .clear
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
}

class NoClippingLayer: CALayer {
    override var masksToBounds: Bool {
        // swiftlint:disable unused_setter_value
        get { return false }
        set { }
    }
}
