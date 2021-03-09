@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ColumnRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var column: FakeColumn!
    private var columnRenderer: ColumnRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        column = .make()
        columnRenderer = ColumnRenderer()
    }
    
    func testAutoWidth() {
        column = .make(width: "auto")
        let columnView = renderColumnView()
        XCTAssertEqual(columnView.columnWidth, .auto)
        XCTAssertEqual(columnView.contentHuggingPriority(for: .horizontal), ColumnWidth.auto.huggingPriority)
        XCTAssertEqual(columnView.contentCompressionResistancePriority(for: .horizontal), .defaultHigh)
    }
    
    func testStretchWidth() {
        column = .make(width: "stretch")
        let columnView = renderColumnView()
        XCTAssertEqual(columnView.columnWidth, .stretch)
        XCTAssertEqual(columnView.contentHuggingPriority(for: .horizontal), ColumnWidth.stretch.huggingPriority)
        XCTAssertEqual(columnView.contentCompressionResistancePriority(for: .horizontal), .defaultLow)
    }
    
    func testWeightedWidth() {
        column = .make(width: "20")
        let columnView = renderColumnView()
        XCTAssertEqual(columnView.columnWidth, .weighted(20))
    }
    
    func testConstantWidth() {
        column = .make(width: "0", pixelWidth: 200)
        let columnView = renderColumnView()
        XCTAssertEqual(columnView.columnWidth, .fixed(200))
        XCTAssertEqual(columnView.fittingSize.width, 200)
    }
    
    func testMinHeight() {
        column = .make(minHeight: 200)
        let columnView = renderColumnView()
        XCTAssertEqual(columnView.fittingSize.height, 200)
    }
    
    func testVerticalContentAlignment() {
        var columnView = renderColumnView()
        XCTAssertEqual(columnView.arrangedSubviews.count, 0)
        
        column = .make(verticalContentAlignment: .center)
        columnView = renderColumnView()
        XCTAssertEqual(columnView.arrangedSubviews.count, 2)
        
        column = .make(verticalContentAlignment: .bottom)
        columnView = renderColumnView()
        XCTAssertEqual(columnView.arrangedSubviews.count, 1)
    }
    
    func testRendersItems() {
        column = .make(items: [FakeTextBlock.make(), FakeInputNumber.make()])
        let columnView = renderColumnView()
        XCTAssertEqual(columnView.arrangedSubviews.count, 2)
    }
    
    private func renderColumnView() -> ACRColumnView {
        let view = columnRenderer.render(element: column, with: hostConfig, style: .default, rootView: NSView(), parentView: NSView(), inputs: [])
        
        XCTAssertTrue(view is ACRContentStackView)
        guard let columnView = view as? ACRColumnView else { fatalError() }
        return columnView
    }
}
