import AppKit

class ACRScrollView: NSScrollView {
    var disableScroll = false
    var focusRingCornerRadius: CGFloat = 0
    
    override func scrollWheel(with event: NSEvent) {
        if !disableScroll {
            super.scrollWheel(with: event)
        } else {
            nextResponder?.scrollWheel(with: event)
        }
    }
    
    override open func drawFocusRingMask() {
        let path = NSBezierPath(roundedRect: self.bounds, xRadius: focusRingCornerRadius, yRadius: focusRingCornerRadius)
        path.fill()
    }
}
