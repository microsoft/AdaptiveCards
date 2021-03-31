import AdaptiveCards_bridge
import AppKit

class ACRActionSetView: NSView {
    private lazy var stackview: NSStackView = {
        let view = NSStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    private var frameWidth: CGFloat = 0
    private var maxFrameWidth: CGFloat = 0
    private var renderAction: Bool = true
    
    public var totalWidth: CGFloat = 0
    public var actions: [NSView] = []
    public var elementSpacing: CGFloat = 0
    
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        addSubview(stackview)
        setupConstraints()
    }
    
    public required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func layout() {
        super.layout()
        frameWidth = frame.width
        if orientation == .horizontal, totalWidth > frameWidth, totalWidth > maxFrameWidth, frameWidth != 0 {
            maxFrameWidth = frameWidth
            customLayout()
        }
        if orientation == .horizontal, frameWidth != 0, renderAction {
            renderAction = false
            customLayout()
        }
    }
    
    private func setupConstraints() {
        stackview.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        stackview.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        stackview.topAnchor.constraint(equalTo: topAnchor).isActive = true
        stackview.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
    }
    
    private func removeElements() {
        for view in stackview.arrangedSubviews {
            view.removeFromSuperview()
        }
    }
    
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        guard let view = superview else { return }
        widthAnchor.constraint(equalTo: view.widthAnchor).isActive = true
    }
    
    private func customLayout() {
        print("@running custom layout")
        // first empty the stackview and remove all the views
        removeElements()
        var accumulatedWidth: CGFloat = 0
        
        // new child stackview for horizontal orientation
        var curview = NSStackView()
        curview.translatesAutoresizingMaskIntoConstraints = false
        curview.spacing = elementSpacing
        
        // adding new child stackview to parent stackview and the parent stackview will align child stackview vertically
        stackview.addArrangedSubview(curview)
        stackview.orientation = .vertical
        let gravityArea: NSStackView.Gravity = stackview.alignment == .centerY ? .center: (stackview.alignment == .trailing ? .trailing: .leading)
        totalWidth = 0
        for view in actions {
            accumulatedWidth += view.intrinsicContentSize.width
            totalWidth = max(totalWidth, accumulatedWidth)
            if accumulatedWidth > frameWidth {
                let newStackView: NSStackView = {
                    let view = NSStackView()
                    view.translatesAutoresizingMaskIntoConstraints = false
                    return view
                }()
                curview = newStackView
                curview.orientation = .horizontal
                curview.addView(view, in: gravityArea)
                curview.spacing = elementSpacing
                accumulatedWidth = 0
                accumulatedWidth += view.intrinsicContentSize.width
                accumulatedWidth += elementSpacing
                stackview.addArrangedSubview(curview)
            } else {
                curview.addView(view, in: gravityArea)
                accumulatedWidth += elementSpacing
            }
        }
    }
    
    var orientation: NSUserInterfaceLayoutOrientation {
        get { stackview.orientation }
        set {
            stackview.orientation = newValue
        }
    }
    
    var alignment: NSLayoutConstraint.Attribute {
        get { stackview.alignment }
        set {
            stackview.alignment = newValue
        }
    }
    
     var spacing: CGFloat {
        get { stackview.spacing }
        set {
            stackview.spacing = newValue
        }
    }
    
    func addArrangedSubView(_ view: NSView) {
        stackview.addArrangedSubview(view)
    }
}
