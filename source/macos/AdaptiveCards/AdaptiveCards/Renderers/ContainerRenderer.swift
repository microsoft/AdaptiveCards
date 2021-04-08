import AdaptiveCards_bridge
import AppKit

class ContainerRenderer: BaseCardElementRendererProtocol {
    static let shared = ContainerRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let container = element as? ACSContainer else {
            logError("Element is not of type ACSContainer")
            return NSView()
        }
        
        let containerView = ACRColumnView(style: container.getStyle(), parentStyle: style, hostConfig: hostConfig, superview: rootView, needsPadding: container.getPadding())
        containerView.translatesAutoresizingMaskIntoConstraints = false
        
        containerView.bleed = container.getBleed()
        
        // add selectAction
        containerView.setupSelectAction(container.getSelectAction(), rootView: rootView)
        
        var leadingBlankSpace: NSView?
        if container.getVerticalContentAlignment() == .center || container.getVerticalContentAlignment() == .bottom {
            let view = NSView()
            containerView.addArrangedSubview(view)
            leadingBlankSpace = view
        }
        
        for (index, item) in container.getItems().enumerated() {
            let isFirstElement = index == 0
            let renderer = RendererManager.shared.renderer(for: item.getType())
            let view = renderer.render(element: item, with: hostConfig, style: container.getStyle(), rootView: rootView, parentView: containerView, inputs: [])
            let viewWithInheritedProperties = BaseCardElementRenderer().updateView(view: view, element: item, rootView: rootView, style: container.getStyle(), hostConfig: hostConfig, isfirstElement: isFirstElement)
            containerView.addArrangedSubview(viewWithInheritedProperties)
            BaseCardElementRenderer.shared.configBleed(collectionView: view, parentView: containerView, with: hostConfig, element: item, parentElement: container)
        }
        
        let verticalAlignment = container.getVerticalContentAlignment()
        // Dont add the trailing space if the vertical content alignment is top/default
        if verticalAlignment == .center, let topView = leadingBlankSpace {
            let view = NSView()
            view.translatesAutoresizingMaskIntoConstraints = false
            topView.translatesAutoresizingMaskIntoConstraints = false
            containerView.addArrangedSubview(view)
            view.heightAnchor.constraint(equalTo: topView.heightAnchor).isActive = true
        }
        containerView.wantsLayer = true
        
        if let minHeight = container.getMinHeight(), let heightPt = CGFloat(exactly: minHeight), heightPt > 0 {
            containerView.heightAnchor.constraint(greaterThanOrEqualToConstant: heightPt).isActive = true
        }
        return containerView
    }
}
