import AdaptiveCards_bridge
import AppKit

class ColumnSetRenderer: BaseCardElementRendererProtocol {
    static let shared = ColumnSetRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let columnSet = element as? ACSColumnSet else {
            logError("Element is not of type ACSColumnSet")
            return NSView()
        }
        let columnSetView = ACRContentStackView(style: columnSet.getStyle(), hostConfig: hostConfig)
        columnSetView.translatesAutoresizingMaskIntoConstraints = false
        columnSetView.orientation = .horizontal
        columnSetView.distribution = .fillEqually
        
        var numberOfAutoItems = 0
        var numberOfStretchItems = 0
        var numberOfWeightedItems = 0
        let totalColumns = columnSet.getColumns().count
        for (index, column) in columnSet.getColumns().enumerated() {
            let width = ColumnWidth(columnWidth: column.getWidth(), pixelWidth: column.getPixelWidth())
            
            if width.isWeighted { numberOfWeightedItems += 1 }
            if width == .stretch { numberOfStretchItems += 1 }
            if width == .auto { numberOfAutoItems += 1 }
            
            let columnView = ColumnRenderer.shared.render(element: column, with: hostConfig, style: columnSet.getStyle(), rootView: rootView, parentView: columnSetView, inputs: [])
            
            // Check if has extra properties else add column view
            guard index > 0, column.getSpacing() != .none, !column.getSeparator() else {
                columnSetView.addArrangedSubview(columnView)
                continue
            }
            let wrappingView = ACRContentStackView(style: column.getStyle(), hostConfig: hostConfig)
            wrappingView.translatesAutoresizingMaskIntoConstraints = false
            wrappingView.orientation = .horizontal
            wrappingView.addSpacing(column.getSpacing())
            wrappingView.addSeperator(column.getSeparator())
            
            wrappingView.addArrangedSubview(columnView)
            columnView.trailingAnchor.constraint(equalTo: wrappingView.trailingAnchor).isActive = true
            columnSetView.addArrangedSubview(wrappingView)
        }
        
        // Only one is weighted and others are stretch
        let isSpecialAllStretch = numberOfWeightedItems == 1 && numberOfStretchItems == totalColumns - 1
        
        if numberOfStretchItems == totalColumns || isSpecialAllStretch {
            columnSetView.distribution = .fillEqually
        } else if numberOfAutoItems == totalColumns {
            columnSetView.distribution = .gravityAreas
        } else {
            let arrangedSubviews = columnSetView.arrangedSubviews
            guard arrangedSubviews.count == totalColumns else {
                logError("ArrangedSubViews count mismatch")
                return columnSetView
            }
            columnSetView.distribution = .fill
            
            var weightedColumnViews: [NSView] = []
            var weightedValues: [CGFloat] = []
            var firstWeightedValue: CGFloat?
            
            for (index, column) in columnSet.getColumns().enumerated() {
                guard let width = column.getWidth(), let weighted = Int(width) else { continue }
                weightedColumnViews.append(arrangedSubviews[index])
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
            
            if numberOfStretchItems > 1 {
                let stretchColumnIndices = getIndicesOfStretchedColumns(of: columnSet)
                guard numberOfStretchItems == stretchColumnIndices.count else {
                    logError("indices count must be equal to numberOfStretchItems here")
                    return columnSetView
                }
                
                for index in (1 ..< stretchColumnIndices.count) {
                    arrangedSubviews[stretchColumnIndices[index]].widthAnchor.constraint(equalTo: arrangedSubviews[stretchColumnIndices[0]].widthAnchor).isActive = true
                }
            }
        }
        
        columnSetView.setupSelectAction(selectAction: columnSet.getSelectAction(), rootView: rootView)
        
        return columnSetView
    }
    
    private func getIndicesOfStretchedColumns(of columnSet: ACSColumnSet) -> [Int] {
        return columnSet.getColumns().enumerated().compactMap { index, column in
            let width = ColumnWidth(columnWidth: column.getWidth(), pixelWidth: column.getPixelWidth())
            return width == .stretch ? index : nil
        }
    }
}
