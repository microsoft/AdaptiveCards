import AdaptiveCards_bridge
import AppKit

class TextInputRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = TextInputRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
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
        let textView = ACRTextInputView()
        var attributedInitialValue: NSMutableAttributedString
        
        textView.translatesAutoresizingMaskIntoConstraints = false
        textView.isBordered = true
        textView.isEditable = true

        if let maxLen = inputBlock.getMaxLength(), Int(truncating: maxLen) > 0 {
            textView.maxLen = Int(truncating: maxLen)
        }
        let action = inputBlock.getInlineAction()
        var renderButton: Bool = false
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
            if let placeholderString = inputBlock.getPlaceholder() {
                multilineView.setPlaceholder(placeholder: placeholderString)
            }
            if let valueString = inputBlock.getValue(), !valueString.isEmpty {
                multilineView.setValue(value: valueString, maximumLen: inputBlock.getMaxLength())
            }
            multilineView.maxLen = inputBlock.getMaxLength() as? Int ?? 0
            if renderButton {
                stackview.addArrangedSubview(multilineView)
                addInlineButton(parentview: stackview, view: multilineView, element: inputBlock, style: style, with: hostConfig)
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
        if renderButton {
            stackview.addArrangedSubview(textView)
            addInlineButton(parentview: stackview, view: textView, element: inputBlock, style: style, with: hostConfig)
            return stackview
        }
        return textView
    }
    private func addInlineButton(parentview: NSStackView, view: NSView, element: ACSTextInput, style: ACSContainerStyle, with hostConfig: ACSHostConfig) {
        let action = element.getInlineAction()
        let button = NSButton(title: action?.getTitle() ?? "", target: self, action: Selector(("test")))
        let attributedString: NSMutableAttributedString
        attributedString = NSMutableAttributedString(string: button.title)
        if let colorHex = hostConfig.getForegroundColor(style, color: .default, isSubtle: true), let textColor = ColorUtils.color(from: colorHex) {
            attributedString.addAttributes([.foregroundColor: textColor], range: NSRange(location: 0, length: attributedString.length))
        }
        parentview.addArrangedSubview(button)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.isBordered = false
        button.bottomAnchor.constraint(equalTo: view.bottomAnchor).isActive = true
        button.widthAnchor.constraint(lessThanOrEqualTo: view.widthAnchor, multiplier: 0.5).isActive = true
        button.attributedTitle = attributedString
        // image icon
        if let imageIcon = action?.getIconUrl(), !imageIcon.isEmpty {
            guard let url = URL(string: imageIcon) else { return }
            DispatchQueue.global().async {
                guard let data = try? Data(contentsOf: url) else { return }
                DispatchQueue.main.async {
                    let image = NSImage(data: data)
                    image?.size = .init(width: button.bounds.width, height: button.bounds.height)
                    button.image = image
                }
            }
        }
    }
}
class ACRTextInputView: NSTextField, NSTextFieldDelegate {
    var maxLen: Int = 0
    
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
}
