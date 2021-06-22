import AppKit

class ACRScrollView: NSScrollView {
    var disableScroll: Bool = false
    
    override func scrollWheel(with event: NSEvent) {
        if !disableScroll {
            super.scrollWheel(with: event)
        } else {
            nextResponder?.scrollWheel(with: event)
        }
    }
}
