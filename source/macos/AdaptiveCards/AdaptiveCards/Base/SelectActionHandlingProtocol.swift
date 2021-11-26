import AdaptiveCards_bridge
import AppKit

protocol SelectActionHandlingProtocol: AnyObject {
    var target: TargetHandler? { get set }
    func getTargetHandler(for selectAction: ACSBaseActionElement?, rootView: ACRView) -> TargetHandler?
    func setupSelectAction(_ selectAction: ACSBaseActionElement?, rootView: ACRView)
    func setupSelectActionAccessibility(on view: NSView, for selectAction: ACSBaseActionElement?)
}

extension SelectActionHandlingProtocol {
    func getTargetHandler(for selectAction: ACSBaseActionElement?, rootView: ACRView) -> TargetHandler? {
        guard let selectAction = selectAction else { return nil }
        var target: TargetHandler?
        switch selectAction.getType() {
        case .openUrl:
            guard let openURLAction = selectAction as? ACSOpenUrlAction else { break }
            target = ActionOpenURLTarget(element: openURLAction, delegate: rootView)
            
        case .submit:
            guard let submitAction = selectAction as? ACSSubmitAction else { break }
            target = ActionSubmitTarget(element: submitAction, delegate: rootView)
            
        case .toggleVisibility:
            guard let toggleAction = selectAction as? ACSToggleVisibilityAction else { break }
            target = ActionToggleVisibilityTarget(toggleTargets: toggleAction.getTargetElements(), delegate: rootView)
            
        default:
            break
        }
        return target
    }
    
    func setupSelectAction(_ selectAction: ACSBaseActionElement?, rootView: ACRView) {
        guard let actionTarget = getTargetHandler(for: selectAction, rootView: rootView) else { return }
        target = actionTarget
        rootView.addTarget(actionTarget)
    }
    
    func setupSelectActionAccessibility(on view: NSView, for selectAction: ACSBaseActionElement?) {
        guard let selectAction = selectAction else { return }
        view.setAccessibilityElement(true)
        view.setAccessibilityRole(.link)
        switch selectAction.getType() {
        case .openUrl:
            view.setAccessibilityLabel("You are on a URL")
        case .submit:
            view.setAccessibilityLabel("You are on a Submit Action")
        case .toggleVisibility:
            view.setAccessibilityLabel("You are on a Visibility Toggle")
        default:
            logError("Unhandled Select Action Present in card")
        }
    }
}
