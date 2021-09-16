import AdaptiveCards_bridge
import AppKit

// MARK: Class required for Horizontal Stack View
class ACRFactSetView: NSView {
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        // Should look for better solution
        guard let superview = superview else { return }
        widthAnchor.constraint(equalTo: superview.widthAnchor).isActive = true
    }
}
