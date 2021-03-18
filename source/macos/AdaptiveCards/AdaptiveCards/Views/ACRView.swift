import AdaptiveCards_bridge
import AppKit

protocol ACRViewDelegate: AnyObject {
    func acrView(_ view: ACRView, didSelectOpenURL url: String, button: NSButton)
}

class ACRView: ACRColumnView {
    weak var delegate: ACRViewDelegate?
    private (set) var targets: [TargetHandler] = []
    private var previousCardView = NSView()
    
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
    func handleShowCardAction(button: NSButton, showCard: ACSAdaptiveCard) {
//        let showcard = AdaptiveCardRenderer.shared.renderAdaptiveCard(showCard, with: hostConfig, width: 335)
//
//        if button.state == .on {
//            showcard.layer?.backgroundColor = ColorUtils.hoverColorOnMouseEnter().cgColor
//            showcard.translatesAutoresizingMaskIntoConstraints = false
//
//            addArrangedSubview(showcard)
//            previousCardView = showcard
//        } else {
//            previousCardView.isHidden = true
//        }
    }
    
    func handleOpenURLAction(button: NSButton, urlString: String) {
        delegate?.acrView(self, didSelectOpenURL: urlString, button: button)
    }
}
