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
    
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        setupViews()
        setupConstraints()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
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
    
    func addSeperator(thickness: NSNumber, color: String) {
        let seperatorView = NSBox()
        seperatorView.boxType = .custom
        seperatorView.heightAnchor.constraint(equalToConstant: CGFloat(truncating: thickness)).isActive = true
        seperatorView.borderColor = ColorUtils.color(from: color) ?? .black
        stackView.addArrangedSubview(seperatorView)
        stackView.setCustomSpacing(3, after: seperatorView)
    }
    
    func addSpacing(spacing: CGFloat) {
        let spacingView = NSBox()
        spacingView.boxType = .custom
        spacingView.heightAnchor.constraint(equalToConstant: spacing).isActive = true
        spacingView.borderColor = .clear
        stackView.addArrangedSubview(spacingView)
    }
    
    private lazy var stackView: NSStackView = {
        let view = NSStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.orientation = .vertical
        view.alignment = .leading
        view.spacing = 0 // TODO: Must be set by hostconfig
        return view
    }()
    
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
    
    // TODO: Figure out a way to set constraints without this method to avoid conflicts
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        guard let superview = superview else { return }
        widthAnchor.constraint(equalTo: superview.widthAnchor).isActive = true
    }
}

class ACRColumnView: ACRContentStackView { }

class ACRView: ACRColumnView {
    init(style: ACSContainerStyle, hostConfig: ACSHostConfig) {
        super.init(frame: .zero)
        wantsLayer = true
        if let bgColor = hostConfig.getBackgroundColor(for: style) {
            layer?.backgroundColor = bgColor.cgColor
        }
        if let paddingSpace = hostConfig.getSpacing()?.paddingSpacing, let padding = CGFloat(exactly: paddingSpace) {
            applyPadding(padding)
        }
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
