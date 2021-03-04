import AdaptiveCards_bridge
import AppKit

class ColumnSetRenderer: BaseCardElementRendererProtocol {
    static let shared = ColumnSetRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let columnSet = element as? ACSColumnSet else {
            logError("Element is not of type ACSColumnSet")
            return NSView()
        }
        let columnSetView = ACRStackView()
        columnSetView.translatesAutoresizingMaskIntoConstraints = false
        columnSetView.orientation = .horizontal
        columnSetView.distribution = .fillEqually
        columnSetView.alignment = .top
        columnSetView.spacing = 0
        
        var numberOfAutoItems = 0
        var numberOfStretchItems = 0
        var numberOfWeightedItems = 0
        let totalColumns = columnSet.getColumns().count
        for column in columnSet.getColumns() {
            let width = ColumnWidth(columnWidth: column.getWidth(), pixelWidth: column.getPixelWidth())
            
            if width.isWeighted { numberOfWeightedItems += 1 }
            if width == .stretch { numberOfStretchItems += 1 }
            if width == .auto { numberOfAutoItems += 1 }
            
            let columnView = ColumnRenderer.shared.render(element: column, with: hostConfig, style: style, rootView: rootView, parentView: columnSetView, inputs: [])
            columnSetView.addArrangedSubview(columnView)
        }
        
        // Only one is weighted and others are stretch
        let isSpecialAllStretch = numberOfWeightedItems == 1 && numberOfStretchItems == totalColumns - 1
        
        let totalAvailableWeight = getTotalAvailableWeight(from: columnSet.getColumns())
        if numberOfWeightedItems == totalColumns {
            columnSetView.distribution = .fill
            for (index, column) in columnSet.getColumns().enumerated() {
                guard let width = column.getWidth(), let weight = Int(width), index < columnSetView.arrangedSubviews.count else {
                    logError("Expected a weighted column here.")
                    continue
                }
                let columnView = columnSetView.arrangedSubviews[index]
                columnView.widthAnchor.constraint(equalTo: columnSetView.widthAnchor, multiplier: CGFloat(weight) / CGFloat(totalAvailableWeight)).isActive = true
            }
        } else if numberOfStretchItems == totalColumns || isSpecialAllStretch {
            columnSetView.distribution = .fillEqually
        } else if numberOfAutoItems == totalColumns {
            columnSetView.distribution = .gravityAreas
        } else {
            guard columnSetView.arrangedSubviews.count == totalColumns else {
                logError("ArrangedSubViews count mismatch")
                return columnSetView
            }
            columnSetView.distribution = .fill
            
            var weightedColumnViews: [NSView] = []
            var weightedValues: [CGFloat] = []
            var firstWeightedValue: CGFloat?
            
            for (index, column) in columnSet.getColumns().enumerated() {
                guard let width = column.getWidth(), let weighted = Int(width) else { continue }
                weightedColumnViews.append(columnSetView.arrangedSubviews[index])
                guard let baseWeight = firstWeightedValue else {
                    firstWeightedValue = CGFloat(weighted)
                    weightedValues.append(1)
                    continue
                }
                weightedValues.append(CGFloat(weighted) / baseWeight)
            }
            
            if weightedColumnViews.count > 1 {
                for index in (1 ..< weightedColumnViews.count) {
                    weightedColumnViews[index].widthAnchor.constraint(equalTo: weightedColumnViews[0].widthAnchor, multiplier: weightedValues[index]).isActive = true
                }
            }
        }
        
        return columnSetView
    }
    
    private func getTotalAvailableWeight(from columns: [ACSColumn]) -> Int {
        let weights = columns.compactMap { $0.getWidth() }
        let weighteds = weights.compactMap { Int($0) }
        return weighteds.reduce(0) { $0 + $1 }
    }
}

class ACRStackView: NSStackView {
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        // Should look for better solution
        guard let superview = superview else { return }
        widthAnchor.constraint(equalTo: superview.widthAnchor).isActive = true
    }
}
