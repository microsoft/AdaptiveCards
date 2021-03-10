import AdaptiveCards_bridge
import AppKit

protocol ACRViewDelegate: AnyObject {
    func acrView(_ view: ACRView, didSelectOpenURL url: String, button: NSButton)
}

class ACRView: ACRColumnView {
    weak var delegate: ACRViewDelegate?
    private (set) var targets: [TargetHandler] = []
    
    init(style: ACSContainerStyle, hostConfig: ACSHostConfig) {
        super.init(style: style, parentStyle: nil, hostConfig: hostConfig, superview: nil)
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
    }
    
    func addTarget(_ target: TargetHandler) {
        targets.append(target)
    }
}

extension ACRView: TargetHandlerDelegate {
    func handleOpenURLAction(button: NSButton, urlString: String) {
        delegate?.acrView(self, didSelectOpenURL: urlString, button: button)
    }
}
