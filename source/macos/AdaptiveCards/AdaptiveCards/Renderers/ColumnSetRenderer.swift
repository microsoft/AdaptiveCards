import AdaptiveCards_bridge
import AppKit

class ColumnSetRenderer: BaseCardElementRendererProtocol {
    static let shared = ColumnSetRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let columnSet = element as? ACSColumnSet else {
            logError("Element is not of type ACSColumnSet")
            return NSView()
        }
        let columnSetView = ACRContentStackView(style: columnSet.getStyle(), parentStyle: style, hostConfig: hostConfig, superview: parentView, needsPadding: columnSet.getPadding())
        columnSetView.translatesAutoresizingMaskIntoConstraints = false
        columnSetView.orientation = .horizontal
        let gravityArea: NSStackView.Gravity = columnSet.getHorizontalAlignment() == .center ? .center: (columnSet.getHorizontalAlignment() == .right ? .trailing: .leading)
        
        var numberOfAutoItems = 0
        var numberOfStretchItems = 0
        var numberOfWeightedItems = 0
        let totalColumns = columnSet.getColumns().count
        var columnViews: [NSView] = []
        for (index, column) in columnSet.getColumns().enumerated() {
            let width = ColumnWidth(columnWidth: column.getWidth(), pixelWidth: column.getPixelWidth())
            
            if width.isWeighted { numberOfWeightedItems += 1 }
            if width == .stretch { numberOfStretchItems += 1 }
            if width == .auto { numberOfAutoItems += 1 }
            
            let columnView = ColumnRenderer.shared.render(element: column, with: hostConfig, style: columnSet.getStyle(), rootView: rootView, parentView: columnSetView, inputs: [], config: config)
            
            // Check if has extra properties else add column view
            columnViews.append(columnView)
            guard index > 0, (column.getSpacing() != .none || column.getSeparator()), !column.getItems().isEmpty else {
                columnSetView.addView(columnView, in: gravityArea)
                BaseCardElementRenderer.shared.configBleed(collectionView: columnView, parentView: columnSetView, with: hostConfig, element: column, parentElement: columnSet)
                continue
            }
            let wrappingView = ACRContentStackView(style: column.getStyle(), hostConfig: hostConfig)
            wrappingView.translatesAutoresizingMaskIntoConstraints = false
            wrappingView.orientation = .horizontal
            wrappingView.addSpacing(column.getSpacing())
            wrappingView.addSeperator(column.getSeparator())
            
            wrappingView.addArrangedSubview(columnView)
            columnView.trailingAnchor.constraint(equalTo: wrappingView.trailingAnchor).isActive = true
            columnSetView.addView(wrappingView, in: gravityArea)
            BaseCardElementRenderer.shared.configBleed(collectionView: columnView, parentView: columnSetView, with: hostConfig, element: column, parentElement: columnSet)
        }
        
        // Add SelectAction
        columnSetView.setupSelectAction(columnSet.getSelectAction(), rootView: rootView)
        
        if numberOfStretchItems == totalColumns && !columnViews.isEmpty {
            let firstColumn = columnViews[0]
            for index in (1..<columnViews.count) {
                columnViews[index].widthAnchor.constraint(equalTo: firstColumn.widthAnchor).isActive = true
            }
            columnSetView.distribution = .fill
        } else if numberOfAutoItems == totalColumns {
            columnSetView.distribution = .gravityAreas
        } else if numberOfStretchItems == 0 && numberOfWeightedItems == 0 {
            columnSetView.distribution = .gravityAreas
        } else {
            guard columnViews.count == totalColumns else {
                logError("ArrangedSubViews count mismatch")
                return columnSetView
            }
            columnSetView.distribution = .fill
            
            var weightedColumnViews: [NSView] = []
            var weightedValues: [CGFloat] = []
            var firstWeightedValue: CGFloat?
            
            for (index, column) in columnSet.getColumns().enumerated() {
                guard let width = column.getWidth(), let weighted = Int(width) else { continue }
                weightedColumnViews.append(columnViews[index])
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
                    columnViews[stretchColumnIndices[index]].widthAnchor.constraint(equalTo: columnViews[stretchColumnIndices[0]].widthAnchor).isActive = true
                }
            }
        }
        columnSetView.setVerticalHuggingPriority(100)
        return columnSetView
    }
    
    private func getIndicesOfStretchedColumns(of columnSet: ACSColumnSet) -> [Int] {
        return columnSet.getColumns().enumerated().compactMap { index, column in
            let width = ColumnWidth(columnWidth: column.getWidth(), pixelWidth: column.getPixelWidth())
            return width == .stretch ? index : nil
        }
    }
}
