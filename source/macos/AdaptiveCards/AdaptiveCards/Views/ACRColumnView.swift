import AdaptiveCards_bridge
import AppKit

protocol ACRContentHoldingViewProtocol {
    func addArrangedSubview(_ subview: NSView)
    func applyPadding(_ padding: CGFloat)
}

class ACRContentStackView: NSView, ACRContentHoldingViewProtocol, SelectActionHandlingProtocol {
    private (set) var stackViewLeadingConstraint: NSLayoutConstraint?
    private (set) var stackViewTrailingConstraint: NSLayoutConstraint?
    private (set) var stackViewTopConstraint: NSLayoutConstraint?
    private (set) var stackViewBottomConstraint: NSLayoutConstraint?
    private (set) var style: ACSContainerStyle?
    let hostConfig: ACSHostConfig
    var target: TargetHandler?
    
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
    
    private (set) lazy var showCardStackView: NSStackView = {
        let view = NSStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.orientation = .vertical
        view.alignment = .leading
        view.spacing = 0
        return view
    }()
    
    private (set) lazy var backgroundImageView: ACRBackgroundImageView = {
        let view = ACRBackgroundImageView()
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    init(style: ACSContainerStyle, hostConfig: ACSHostConfig) {
        self.hostConfig = hostConfig
        self.style = style
        super.init(frame: .zero)
        initialize()
    }
    
    init(style: ACSContainerStyle, parentStyle: ACSContainerStyle?, hostConfig: ACSHostConfig, superview: NSView?) {
        self.hostConfig = hostConfig
        self.style = style
        super.init(frame: .zero)
        initialize()
        if style != .none && style != parentStyle {
            if let bgColor = hostConfig.getBackgroundColor(for: style) {
                layer?.backgroundColor = bgColor.cgColor
            }
            // set border color
            if let borderColorHex = hostConfig.getBorderColor(style), let borderColor = ColorUtils.color(from: borderColorHex) {
                layer?.borderColor = borderColor.cgColor
            }
            // set border width
            if let borderWidth = hostConfig.getBorderThickness(style) {
                layer?.borderWidth = CGFloat(truncating: borderWidth)
            }
            // add padding
            if let paddingSpace = hostConfig.getSpacing()?.paddingSpacing, let padding = CGFloat(exactly: paddingSpace) {
                applyPadding(padding)
            }
        }
    }
    
    required init?(coder: NSCoder) {
        self.hostConfig = ACSHostConfig() // TODO: This won't work
        super.init(coder: coder)
        initialize()
    }
    
    private func initialize() {
        wantsLayer = true
        setupViews()
        setupConstraints()
        setupTrackingArea()
    }
    
    func addArrangedSubview(_ subview: NSView) {
        stackView.addArrangedSubview(subview)
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
    
    func setupBackgroundImageProperties(_ properties: ACSBackgroundImage) {
        backgroundImageView.fillMode = properties.getFillMode()
        backgroundImageView.horizontalAlignment = properties.getHorizontalAlignment()
        backgroundImageView.verticalAlignment = properties.getVerticalAlignment()
        heightAnchor.constraint(greaterThanOrEqualToConstant: 30).isActive = true
    }
    
    private func addSeperator(thickness: NSNumber, color: String) {
        let seperatorView = NSBox()
        seperatorView.boxType = .custom
        let anchor = orientation == .horizontal ? seperatorView.widthAnchor : seperatorView.heightAnchor
        anchor.constraint(equalToConstant: CGFloat(truncating: thickness)).isActive = true
        seperatorView.borderColor = ColorUtils.color(from: color) ?? .black
        stackView.addArrangedSubview(seperatorView)
        stackView.setCustomSpacing(3, after: seperatorView)
    }
    
    private func addSpacing(spacing: CGFloat) {
        let spacingView = NSBox()
        spacingView.boxType = .custom
        let anchor = orientation == .horizontal ? spacingView.widthAnchor : spacingView.heightAnchor
        anchor.constraint(equalToConstant: spacing).isActive = true
        spacingView.borderColor = .clear
        stackView.addArrangedSubview(spacingView)
    }
    
    private func setupViews() {
        addSubview(backgroundImageView)
        addSubview(stackView)
        addSubview(showCardStackView)
    }
    
    private func setupConstraints() {
        stackViewLeadingConstraint = stackView.leadingAnchor.constraint(equalTo: leadingAnchor)
        stackViewTrailingConstraint = stackView.trailingAnchor.constraint(equalTo: trailingAnchor)
        stackViewTopConstraint = stackView.topAnchor.constraint(equalTo: topAnchor)
        stackViewBottomConstraint = stackView.bottomAnchor.constraint(equalTo: showCardStackView.topAnchor)
        
        backgroundImageView.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        backgroundImageView.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        backgroundImageView.topAnchor.constraint(equalTo: topAnchor).isActive = true
        backgroundImageView.bottomAnchor.constraint(equalTo: showCardStackView.topAnchor).isActive = true

        showCardStackView.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        showCardStackView.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        showCardStackView.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        
        guard let leading = stackViewLeadingConstraint, let trailing = stackViewTrailingConstraint, let top = stackViewTopConstraint, let bottom = stackViewBottomConstraint else { return }
        NSLayoutConstraint.activate([leading, trailing, top, bottom])
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
        guard let columnView = event.trackingArea?.owner as? ACRColumnView, target != nil else { return }
        previousBackgroundColor = columnView.layer?.backgroundColor
        columnView.layer?.backgroundColor = ColorUtils.hoverColorOnMouseEnter().cgColor
    }
    
    override func mouseExited(with event: NSEvent) {
        guard let columnView = event.trackingArea?.owner as? ACRColumnView, target != nil else { return }
        columnView.layer?.backgroundColor = previousBackgroundColor ?? .clear
    }
}

enum ColumnWidth: Equatable {
    case stretch, auto, fixed(_ width: CGFloat), weighted(_ weight: Int)
    
    var isWeighted: Bool {
        switch self {
        case .weighted: return true
        default: return false
        }
    }
    
    var huggingPriority: NSLayoutConstraint.Priority {
        switch self {
        case .auto: return .init(252)
        case .stretch: return .init(249)
        default: return .defaultLow
        }
    }
    
    init(columnWidth: String?, pixelWidth: NSNumber?) {
        if let width = pixelWidth, let float = CGFloat(exactly: width), float > 0 {
            self = .fixed(float)
            return
        }
        if let width = columnWidth, let weight = Int(width) {
            self = .weighted(weight)
            return
        }
        self = columnWidth == "auto" ? .auto : .stretch
    }
    
    static func == (lhs: ColumnWidth, rhs: ColumnWidth) -> Bool {
        switch (lhs, rhs) {
        case (.stretch, .stretch),
             (.auto, .auto): return true
        case let (.fixed(widthA), .fixed(widthB)): return widthA == widthB
        case let (.weighted(weightA), .weighted(weightB)): return weightA == weightB
        default: return false
        }
    }
}

class ACRColumnView: ACRContentStackView {
    enum Constants {
        static let minWidth: CGFloat = 30
    }
    
    private lazy var widthConstraint = widthAnchor.constraint(equalToConstant: Constants.minWidth)
    private (set) var columnWidth: ColumnWidth = .weighted(1)
    
    override init(style: ACSContainerStyle, parentStyle: ACSContainerStyle?, hostConfig: ACSHostConfig, superview: NSView?) {
        super.init(style: style, parentStyle: parentStyle, hostConfig: hostConfig, superview: superview)
        initialize()
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        initialize()
    }
    
    private func initialize() {
        // Always to have some minimum width
        let minWidthConstraint = widthAnchor.constraint(greaterThanOrEqualToConstant: Constants.minWidth)
        minWidthConstraint.priority = .defaultHigh
        minWidthConstraint.isActive = true
    }
    
    override func addArrangedSubview(_ subview: NSView) {
        manageWidth(of: subview)
        super.addArrangedSubview(subview)
        if subview is ACRContentStackView {
            subview.widthAnchor.constraint(equalTo: stackView.widthAnchor).isActive = true
        }
    }
    
    func configureColumnProperties(for view: NSView) {
        manageWidth(of: view)
    }
    
    func setWidth(_ width: ColumnWidth) {
        columnWidth = width
        manageWidth(of: self)
        manageWidth(of: stackView)
    }
    
    private func manageWidth(of view: NSView) {
        switch columnWidth {
        case .fixed(let widthSize):
            widthConstraint.constant = widthSize
            widthConstraint.isActive = true
            
        case .auto:
            view.setContentHuggingPriority(columnWidth.huggingPriority, for: .horizontal)
            view.setContentCompressionResistancePriority(.defaultHigh, for: .horizontal)
            widthConstraint.isActive = false
            
        case .stretch:
            view.setContentHuggingPriority(columnWidth.huggingPriority, for: .horizontal)
            view.setContentCompressionResistancePriority(.defaultLow, for: .horizontal)
            widthConstraint.isActive = false
            
        case .weighted:
            widthConstraint.isActive = false
        }
    }
}
