import AdaptiveCards_bridge
import AppKit

class TextInputRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = TextInputRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let inputBlock = element as? ACSTextInput else {
            logError("Element is not of type ACSTextInput")
            return NSView()
        }
        let stackview: NSStackView = {
            let view = NSStackView()
            view.orientation = .horizontal
            view.translatesAutoresizingMaskIntoConstraints = false
            return view
        }()
        let textView = ACRTextInputView(frame: .zero)
        textView.idString = inputBlock.getId()
        var attributedInitialValue: NSMutableAttributedString
        
        textView.translatesAutoresizingMaskIntoConstraints = false
        textView.isBordered = true
        textView.isEditable = true

        if let maxLen = inputBlock.getMaxLength(), Int(truncating: maxLen) > 0 {
            textView.maxLen = Int(truncating: maxLen)
        }
        let action = inputBlock.getInlineAction()
        var renderButton = false
        switch action {
        case is ACSOpenUrlAction:
            renderButton = true
        case is ACSToggleVisibilityAction:
            renderButton = true
        case is ACSSubmitAction:
            renderButton = true
        default:
            renderButton = false
        }
        
        if inputBlock.getIsMultiline() {
            let multilineView = ACRMultilineInputTextView()
            multilineView.setId(inputBlock.getId())
            multilineView.setVisibilty(to: inputBlock.getIsVisible())
            if let placeholderString = inputBlock.getPlaceholder() {
                multilineView.setPlaceholder(placeholder: placeholderString)
            }
            if let valueString = inputBlock.getValue(), !valueString.isEmpty {
                multilineView.setValue(value: valueString, maximumLen: inputBlock.getMaxLength())
            }
            multilineView.maxLen = inputBlock.getMaxLength() as? Int ?? 0
            // Add Input Handler
            
            rootView.addInputHandler(multilineView)
            if renderButton {
                stackview.addArrangedSubview(multilineView)
                addInlineButton(parentview: stackview, view: multilineView, element: inputBlock, style: style, with: hostConfig, rootview: rootView, config: config)
                return stackview
            }
            return multilineView
        } else {
            // Makes text remain in 1 line
            textView.cell?.usesSingleLineMode = true
            textView.maximumNumberOfLines = 1
            // Make text scroll horizontally
            textView.cell?.isScrollable = true
            textView.cell?.truncatesLastVisibleLine = true
            textView.cell?.lineBreakMode = .byTruncatingTail
            textView.isHidden = !inputBlock.getIsVisible()
        }
        // Create placeholder and initial value string if they exist
        if let placeholderString = inputBlock.getPlaceholder() {
            textView.placeholderString = placeholderString
        }
        
        if let valueString = inputBlock.getValue() {
            attributedInitialValue = NSMutableAttributedString(string: valueString)
            if let maxLen = inputBlock.getMaxLength(), Int(truncating: maxLen) > 0, attributedInitialValue.string.count > Int(truncating: maxLen) {
                attributedInitialValue = NSMutableAttributedString(string: String(attributedInitialValue.string.dropLast(attributedInitialValue.string.count - Int(truncating: maxLen))))
            }
            textView.attributedStringValue = attributedInitialValue
        }
        // Add Input Handler
        rootView.addInputHandler(textView)
        if renderButton {
            stackview.addArrangedSubview(textView)
            addInlineButton(parentview: stackview, view: textView, element: inputBlock, style: style, with: hostConfig, rootview: rootView, config: config)
            return stackview
        }
        return textView
    }
    
    private func addInlineButton(parentview: NSStackView, view: NSView, element: ACSTextInput, style: ACSContainerStyle, with hostConfig: ACSHostConfig, rootview: ACRView, config: RenderConfig) {
        guard let action = element.getInlineAction() else {
            return logError("InlineAction is nil")
        }
        let button = ACRButton(actionElement: action, iconPlacement: hostConfig.getActions()?.iconPlacement, buttonConfig: config.buttonConfig, style: .inline)
        if let iconUrl = action.getIconUrl(), !iconUrl.isEmpty {
            rootview.registerImageHandlingView(button, for: iconUrl)
        }
        
        button.cornerRadius = 0
        button.isBordered = false

        let attributedString: NSMutableAttributedString
        attributedString = NSMutableAttributedString(string: button.title)
        if let colorHex = hostConfig.getForegroundColor(style, color: .default, isSubtle: true), let textColor = ColorUtils.color(from: colorHex) {
            attributedString.addAttributes([.foregroundColor: textColor], range: NSRange(location: 0, length: attributedString.length))
        }
        parentview.addArrangedSubview(button)
        button.translatesAutoresizingMaskIntoConstraints = false
        
        if view is ACRMultilineInputTextView {
            button.setContentHuggingPriority(.required, for: .vertical)
            button.bottomAnchor.constraint(equalTo: view.bottomAnchor).isActive = true
        }
        button.widthAnchor.constraint(lessThanOrEqualTo: view.widthAnchor, multiplier: 0.5).isActive = true
        button.attributedTitle = attributedString
        
        // adding target to the Buttons
        switch action.getType() {
        case .openUrl:
            guard let openURLAction = action as? ACSOpenUrlAction else {
                logError("Element is not of type ACSOpenUrlAction")
                return
            }
            let target = ActionOpenURLTarget(element: openURLAction, delegate: rootview)
            target.configureAction(for: button)
            rootview.addTarget(target)
        case .submit:
            guard let submitAction = action as? ACSSubmitAction else {
                logError("Element is not of type ACSSubmitAction")
                return
            }
            let target = ActionSubmitTarget(element: submitAction, delegate: rootview)
            target.configureAction(for: button)
            rootview.addTarget(target)
        default:
            break
        }
    }
}
class ACRTextInputView: NSTextField, InputHandlingViewProtocol {
    var value: String {
        return stringValue
    }
    
    var key: String {
        guard let id = idString else {
            logError("ID must be set on creation")
            return ""
        }
        return id
    }
    
    var isValid: Bool {
        return !isHidden && !(superview?.isHidden ?? false)
    }
    
    var maxLen: Int = 0
    var idString: String?
    
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        setupTrackingArea()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func textDidChange(_ notification: Notification) {
        guard maxLen > 0  else { return } // maxLen returns 0 if propery not set
        // This stops the user from exceeding the maxLength property of Inut.Text if prroperty was set
        guard let textView = notification.object as? NSTextView, textView.string.count > maxLen else { return }
        textView.string = String(textView.string.dropLast())
        // Below check added to ensure prefilled value doesn't exceede the maxLength property if set
        if textView.string.count > maxLen {
            textView.string = String(textView.string.dropLast(textView.string.count - maxLen))
        }
    }
    
    func setupTrackingArea() {
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
    }
    
    override func mouseEntered(with event: NSEvent) {
        guard let textView = event.trackingArea?.owner as? ACRTextInputView else { return }
        textView.backgroundColor = ColorUtils.hoverColorOnMouseEnter()
    }
    
    override func mouseExited(with event: NSEvent) {
        guard let textView = event.trackingArea?.owner as? ACRTextInputView else { return }
        textView.backgroundColor = ColorUtils.hoverColorOnMouseExit()
    }
}
