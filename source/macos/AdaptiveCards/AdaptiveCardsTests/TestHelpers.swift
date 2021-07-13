@testable import AdaptiveCards
import AppKit

extension NSButton {
    func performClick() {
        guard !isHidden else { return }
        if let flatButton = self as? FlatButton, !flatButton.momentary {
            state = state == .on ? .off : .on
        }
        if let target = target, let action = action {
            sendAction(action, to: target)
        }
    }
}

extension NSView {
    func buttonInHierachy(withTitle title: String) -> NSButton? {
        guard !subviews.isEmpty else {
            return nil
        }
        for subview in subviews {
            if let button = subview as? NSButton, button.title == title {
                return button
            }
            if let button = subview.buttonInHierachy(withTitle: title) {
                return button
            }
        }
        return nil
    }
}
