@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ColumnSetRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var columnSet: FakeColumnSet!
    private var columnSetRenderer: ColumnSetRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        columnSet = .make()
        columnSetRenderer = ColumnSetRenderer()
    }
    
    func testAllStretchColumns() {
        let columns: [FakeColumn] = [.make(width: "stretch"), .make(width: "stretch"), .make(width: "stretch")]
        columnSet = .make(columns: columns)
        
        let columnSetView = renderColumnSetView()
        XCTAssertEqual(columnSetView.distribution, .fill)
    }
    
    func testAllAutoColumns() {
        let columns: [FakeColumn] = [.make(width: "auto"), .make(width: "auto"), .make(width: "auto")]
        columnSet = .make(columns: columns)
        
        let columnSetView = renderColumnSetView()
        XCTAssertEqual(columnSetView.distribution, .gravityAreas)
    }
    
    func testMixedWidthColumns() {
        let columns: [FakeColumn] = [.make(width: "auto"), .make(width: "stretch"), .make(width: "2")]
        columnSet = .make(columns: columns)
        
        let columnSetView = renderColumnSetView()
        XCTAssertEqual(columnSetView.distribution, .fill)
    }
    
    func testDefaultOrientation() {
        let columnStackView = renderColumnSetView()
        XCTAssertEqual(columnStackView.orientation, .horizontal)
    }
    
    private func renderColumnSetView() -> ACRContentStackView {
        let view = columnSetRenderer.render(element: columnSet, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [])
        
        XCTAssertTrue(view is ACRContentStackView)
        guard let columnSetView = view as? ACRContentStackView else { fatalError() }
        return columnSetView
    }
}
