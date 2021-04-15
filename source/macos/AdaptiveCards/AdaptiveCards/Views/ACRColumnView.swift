import AdaptiveCards_bridge
import AppKit

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
    private lazy var backgroundImageViewBottomConstraint = backgroundImageView.bottomAnchor.constraint(equalTo: bottomAnchor)
    private lazy var backgroundImageViewTopConstraint = backgroundImageView.topAnchor.constraint(equalTo: topAnchor)
    private lazy var backgroundImageViewLeadingConstraint = backgroundImageView.leadingAnchor.constraint(equalTo: leadingAnchor)
    private lazy var backgroundImageViewTrailingConstraint = backgroundImageView.trailingAnchor.constraint(equalTo: trailingAnchor)
    
    private (set) var columnWidth: ColumnWidth = .weighted(1)
    private lazy var minWidthConstraint: NSLayoutConstraint = {
        let constraint = widthAnchor.constraint(greaterThanOrEqualToConstant: Constants.minWidth)
        constraint.priority = .defaultHigh
        return constraint
    }()
    
    private (set) lazy var backgroundImageView: ACRBackgroundImageView = {
        let view = ACRBackgroundImageView()
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    override func addArrangedSubview(_ subview: NSView) {
        // Activate min Width constraint only if column has a non-image subview
        // Because - column can be empty                        -> should have zero content size
        //         - image can have dimensions less than 30 pts -> should match image content size
        let contentStackView = subview as? ACRContentStackView
        if !(contentStackView?.arrangedSubviews.first is ACRImageWrappingView || subview is ACRImageWrappingView) {
            minWidthConstraint.isActive = true
        }
        
        manageWidth(of: subview)
        super.addArrangedSubview(subview)
        if subview is ACRContentStackView {
            subview.widthAnchor.constraint(equalTo: stackView.widthAnchor).isActive = true
        }
    }
    
    override func setupViews() {
        addSubview(backgroundImageView)
        super.setupViews()
    }
    
    override func setupConstraints() {
        super.setupConstraints()
        backgroundImageViewTopConstraint.isActive = true
        backgroundImageViewLeadingConstraint.isActive = true
        backgroundImageViewTrailingConstraint.isActive = true
        backgroundImageViewBottomConstraint.isActive = true
    }
    
    override func anchorBottomConstraint(with anchor: NSLayoutAnchor<NSLayoutYAxisAnchor>) {
        super.anchorBottomConstraint(with: anchor)
        backgroundImageViewBottomConstraint.isActive = false
        backgroundImageViewBottomConstraint = backgroundImageView.bottomAnchor.constraint(equalTo: anchor)
        backgroundImageViewBottomConstraint.isActive = true
    }
    
    func setupBackgroundImageProperties(_ properties: ACSBackgroundImage) {
        backgroundImageView.fillMode = properties.getFillMode()
        backgroundImageView.horizontalAlignment = properties.getHorizontalAlignment()
        backgroundImageView.verticalAlignment = properties.getVerticalAlignment()
        heightAnchor.constraint(greaterThanOrEqualToConstant: 30).isActive = true
    }
    
    func configureColumnProperties(for view: NSView) {
        manageWidth(of: view)
    }
    
    func setWidth(_ width: ColumnWidth) {
        columnWidth = width
        manageWidth(of: self)
        manageWidth(of: stackView)
    }
    
    func setMinimumHeight(_ height: NSNumber?) {
        guard let height = height, let heightPt = CGFloat(exactly: height), heightPt > 0 else { return }
        heightAnchor.constraint(greaterThanOrEqualToConstant: heightPt).isActive = true
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
    
    func bleedBackgroundImage(padding: CGFloat, top: Bool, bottom: Bool, leading: Bool, trailing: Bool, paddingBottom: CGFloat, with anchor: NSLayoutAnchor<NSLayoutYAxisAnchor>) {
        backgroundImageViewTopConstraint.constant = top ? -padding : 0
        backgroundImageViewTrailingConstraint.constant = trailing ? padding : 0
        backgroundImageViewLeadingConstraint.constant = leading ? -padding : 0
        backgroundImageViewBottomConstraint.isActive = false
        backgroundImageViewBottomConstraint = backgroundImageView.bottomAnchor.constraint(equalTo: anchor, constant: bottom ?  padding : 0)
        backgroundImageViewBottomConstraint.isActive = true
    }
}
