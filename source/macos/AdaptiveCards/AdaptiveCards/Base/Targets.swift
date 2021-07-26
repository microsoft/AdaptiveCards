import AdaptiveCards_bridge
import AppKit

class ActionOpenURLTarget: NSObject, TargetHandler {
    private (set) weak var delegate: TargetHandlerDelegate?
    let url: String
    
    init(element: ACSOpenUrlAction, delegate: TargetHandlerDelegate) {
        self.url = element.getUrl() ?? ""
        self.delegate = delegate
    }
    
    func configureAction(for button: NSButton) {
        button.target = self
        button.action = #selector(handleButtonAction(_:))
    }
    
    func handleSelectionAction(for actionView: NSView) {
        delegate?.handleOpenURLAction(actionView: actionView, urlString: url)
    }
    
    @objc private func handleButtonAction(_ sender: NSButton) {
        delegate?.handleOpenURLAction(actionView: sender, urlString: url)
    }
}
    
class ActionSubmitTarget: NSObject, TargetHandler {
    private (set) weak var delegate: TargetHandlerDelegate?
    let dataJson: String?
    
    init(element: ACSSubmitAction, delegate: TargetHandlerDelegate) {
        self.delegate = delegate
        self.dataJson = element.getDataJson()
    }
    
    func configureAction(for button: NSButton) {
        button.target = self
        button.action = #selector(handleButtonAction(_:))
    }
    
    func handleSelectionAction(for actionView: NSView) {
        delegate?.handleSubmitAction(actionView: actionView, dataJson: self.dataJson)
    }
    
    @objc private func handleButtonAction(_ sender: NSButton) {
        delegate?.handleSubmitAction(actionView: sender, dataJson: self.dataJson)
    }
}

class ActionToggleVisibilityTarget: NSObject, TargetHandler {
    private (set) weak var delegate: TargetHandlerDelegate?
    let toggleTargets: [ACSToggleVisibilityTarget]

    init(toggleTargets: [ACSToggleVisibilityTarget], delegate: TargetHandlerDelegate) {
        self.toggleTargets = toggleTargets
        self.delegate = delegate
    }
    
    func configureAction(for button: NSButton) {
        button.target = self
        button.action = #selector(handleButtonAction(_:))
    }
    
    func handleSelectionAction(for actionView: NSView) {
        delegate?.handleToggleVisibilityAction(actionView: actionView, toggleTargets: toggleTargets)
    }
    
    @objc private func handleButtonAction(_ sender: NSButton) {
        delegate?.handleToggleVisibilityAction(actionView: sender, toggleTargets: toggleTargets)
    }
}

class ActionShowCardTarget: NSObject, TargetHandler {
    private (set) weak var delegate: TargetHandlerDelegate?
    let showCard: ACSAdaptiveCard

    init(element: ACSAdaptiveCard, delegate: TargetHandlerDelegate) {
        self.showCard = element
        self.delegate = delegate
        assert(delegate is ShowCardTargetHandlerDelegate)
    }
    
    func configureAction(for button: NSButton) {
        button.target = self
        button.action = #selector(handleButtonAction(_:))
    }
    
    func handleSelectionAction(for actionView: NSView) { }
    
    @objc private func handleButtonAction(_ sender: NSButton) {
        guard let showCardHandler = delegate as? ShowCardTargetHandlerDelegate else {
            logError("delegate should be of type 'ShowCardHandlerDelegate'")
            return
        }
        showCardHandler.handleShowCardAction(button: sender, showCard: showCard)
    }
}
