import AdaptiveCards_bridge
import AppKit

class ACRFactTextField: NSView {
    @IBOutlet private var contentView: NSView!
    @IBOutlet private var labelTextField: NSTextField!
    
    init() {
        super.init(frame: .zero)
        guard let bundle = Bundle(identifier: "com.test.test.AdaptiveCards") else {
            logError("Bundle is nil")
            return
        }
        bundle.loadNibNamed("ACRFactTextField", owner: self, topLevelObjects: nil)
        setupViews()
        setupConstraints()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func setupViews() {
        addSubview(contentView)
    }
    
    private func setupConstraints() {
        contentView.translatesAutoresizingMaskIntoConstraints = false
        labelTextField.translatesAutoresizingMaskIntoConstraints = false
        
        contentView.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        contentView.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        contentView.topAnchor.constraint(equalTo: topAnchor).isActive = true
        contentView.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        
        labelTextField.leadingAnchor.constraint(equalTo: contentView.leadingAnchor).isActive = true
        labelTextField.topAnchor.constraint(equalTo: contentView.topAnchor).isActive = true
        labelTextField.bottomAnchor.constraint(equalTo: contentView.bottomAnchor).isActive = true
        labelTextField.trailingAnchor.constraint(equalTo: contentView.trailingAnchor).isActive = true
        
        labelTextField.setContentCompressionResistancePriority(.required, for: .vertical)
        labelTextField.alignment = .left
    }
    
    func setupTitleString(with fontSize: NSNumber?) {
        labelTextField.font = NSFont.boldSystemFont(ofSize: CGFloat(truncating: fontSize ?? 12))
    }
    
    var isEmpty: Bool {
        return labelTextField.stringValue.isEmpty
    }
    
    var textColor: NSColor {
        get { return labelTextField.textColor ?? .black }
        set { labelTextField.textColor = newValue }
    }
    
    var plainTextValue: String? {
        get { return labelTextField.stringValue }
        set {
            labelTextField.allowsEditingTextAttributes = false
            labelTextField.stringValue = newValue ?? ""
        }
    }
    var attributedTextValue: NSAttributedString? {
        get { return labelTextField.attributedStringValue }
        set {
            labelTextField.allowsEditingTextAttributes = true
            labelTextField.attributedStringValue = newValue ?? NSAttributedString(string: "")
        }
    }
}

// MARK: Class required for Horizontal Stack View
class ACRFactSetView: NSView {
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        // Should look for better solution
        guard let superview = superview else { return }
        widthAnchor.constraint(equalTo: superview.widthAnchor).isActive = true
    }
}
