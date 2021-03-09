import AdaptiveCards_bridge
import AppKit

protocol ACRContentHoldingViewProtocol {
    func addArrangedSubview(_ subview: NSView)
    func applyPadding(_ padding: CGFloat)
}

class ACRContentStackView: NSView, ACRContentHoldingViewProtocol {
    private (set) var stackViewLeadingConstraint: NSLayoutConstraint?
    private (set) var stackViewTrailingConstraint: NSLayoutConstraint?
    private (set) var stackViewTopConstraint: NSLayoutConstraint?
    private (set) var stackViewBottomConstraint: NSLayoutConstraint?
    
    let hostConfig: ACSHostConfig
    
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
        super.init(frame: .zero)
        initialize()
        wantsLayer = true
        if style != .none, let bgColor = hostConfig.getBackgroundColor(for: style) {
            layer?.backgroundColor = bgColor.cgColor
        }
    }
    
    init(style: ACSContainerStyle, parentStyle: ACSContainerStyle?, hostConfig: ACSHostConfig, superview: NSView?) {
        self.hostConfig = hostConfig
        super.init(frame: .zero)
        initialize()
        wantsLayer = true
        if style != .none {
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
        setupViews()
        setupConstraints()
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
    
    func addSeperator(_ separator: Bool) {
        guard separator else { return }
        let seperatorConfig = hostConfig.getSeparator()
        let lineThickness = seperatorConfig?.lineThickness
        let lineColor = seperatorConfig?.lineColor
        addSeperator(thickness: lineThickness ?? 1, color: lineColor ?? "#EEEEEE")
    }
    
    func addSpacing(_ spacing: ACSSpacing) {
        let spacingConfig = hostConfig.getSpacing()
        let spaceAdded: NSNumber
        switch spacing {
        case .default: spaceAdded = spacingConfig?.defaultSpacing ?? 0
        case .none: spaceAdded = 0
        case .small: spaceAdded = spacingConfig?.smallSpacing ?? 3
        case .medium: spaceAdded = spacingConfig?.mediumSpacing ?? 20
        case .large: spaceAdded = spacingConfig?.largeSpacing ?? 30
        case .extraLarge: spaceAdded = spacingConfig?.extraLargeSpacing ?? 40
        case .padding: spaceAdded = spacingConfig?.paddingSpacing ?? 20
        @unknown default:
            logError("Unknown padding!")
            spaceAdded = 0
        }
        addSpacing(spacing: CGFloat(truncating: spaceAdded))
    }
    
    func setCustomSpacing(spacing: CGFloat, after view: NSView) {
        stackView.setCustomSpacing(spacing, after: view)
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
        addSubview(stackView)
    }
    
    private func setupConstraints() {
        stackViewLeadingConstraint = stackView.leadingAnchor.constraint(equalTo: leadingAnchor)
        stackViewTrailingConstraint = stackView.trailingAnchor.constraint(equalTo: trailingAnchor)
        stackViewTopConstraint = stackView.topAnchor.constraint(equalTo: topAnchor)
        stackViewBottomConstraint = stackView.bottomAnchor.constraint(equalTo: bottomAnchor)
        
        guard let leading = stackViewLeadingConstraint, let trailing = stackViewTrailingConstraint, let top = stackViewTopConstraint, let bottom = stackViewBottomConstraint else { return }
        NSLayoutConstraint.activate([leading, trailing, top, bottom])
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
