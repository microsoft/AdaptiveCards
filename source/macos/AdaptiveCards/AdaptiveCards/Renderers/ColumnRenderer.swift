import AdaptiveCards_bridge
import AppKit

class ColumnRenderer: BaseCardElementRendererProtocol {
    static let shared = ColumnRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let column = element as? ACSColumn else {
            logError("Element is not of type ACSColumn")
            return NSView()
        }
        
        let columnView = ACRColumnView(style: style, hostConfig: hostConfig)
        columnView.translatesAutoresizingMaskIntoConstraints = false
        columnView.setWidth(ColumnWidth(columnWidth: column.getWidth(), pixelWidth: column.getPixelWidth()))
        
        for item in column.getItems() {
            let renderer = RendererManager.shared.renderer(for: item.getType())
            let view = renderer.render(element: item, with: hostConfig, style: style, rootView: rootView, parentView: columnView, inputs: [])
            columnView.addArrangedSubview(view)
        }
        return columnView
    }
}
