import AdaptiveCards_bridge
import AppKit

class ActionOpenURLTarget: TargetHandler {
    weak var delegate: TargetHandlerDelegate?
    let url: String
    
    init(element: ACSOpenUrlAction, delegate: TargetHandlerDelegate) {
        self.url = element.getUrl() ?? ""
        self.delegate = delegate
    }
    
    func configureAction(for button: NSButton) {
        button.target = self
        button.action = #selector(handleButtonAction(_:))
    }
    
    @objc private func handleButtonAction(_ sender: NSButton) {
        delegate?.handleOpenURLAction(button: sender, urlString: url)
    }
}
