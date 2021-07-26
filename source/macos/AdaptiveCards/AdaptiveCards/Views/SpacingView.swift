import AppKit

class SpacingView: NSView {
    init() {
        super.init(frame: .zero)
        translatesAutoresizingMaskIntoConstraints = false
    }
    
    init(orientation: NSUserInterfaceLayoutOrientation, spacing: CGFloat) {
        super.init(frame: .zero)
        translatesAutoresizingMaskIntoConstraints = false
        let anchor = orientation == .horizontal ? widthAnchor : heightAnchor
        anchor.constraint(equalToConstant: spacing).isActive = true
    }
    
    convenience init(asSeparatorViewWithThickness thickness: CGFloat, color: String, orientation: NSUserInterfaceLayoutOrientation) {
        self.init(orientation: orientation, spacing: thickness)
        wantsLayer = true
        layer?.backgroundColor = ColorUtils.color(from: color)?.cgColor ?? .black
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
