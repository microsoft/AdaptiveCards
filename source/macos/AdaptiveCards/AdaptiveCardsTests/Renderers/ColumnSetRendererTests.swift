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
    
    func testHiddenAndIdPropertiesSet() {
        let columns: [FakeColumn] = [.make(id: "id1", isVisible: false), .make(id: "id2", isVisible: true)]
        columnSet = .make(columns: columns)
        
        let columnSetView = renderColumnSetView()
        let columnViews = columnSetView.arrangedSubviews
        XCTAssertEqual(columnViews.count, columns.count)
        
        XCTAssertEqual(columnViews[0].identifier?.rawValue, "id1")
        XCTAssertEqual(columnViews[1].identifier?.rawValue, "id2")
        
        XCTAssertTrue(columnViews[0].isHidden)
        XCTAssertFalse(columnViews[1].isHidden)
    }
    
    func testSelectActionTargetIsSet() {
        var columnSetView: ACRContentStackView!
        
        columnSet = .make(selectAction: FakeSubmitAction.make())
        columnSetView = renderColumnSetView()
        
        XCTAssertNotNil(columnSetView.target)
        XCTAssertTrue(columnSetView.target is ActionSubmitTarget)
        
        columnSet = .make(selectAction: FakeOpenURLAction.make())
        columnSetView = renderColumnSetView()
        
        XCTAssertNotNil(columnSetView.target)
        XCTAssertTrue(columnSetView.target is ActionOpenURLTarget)
        
        columnSet = .make(selectAction: FakeToggleVisibilityAction.make())
        columnSetView = renderColumnSetView()
        
        XCTAssertNotNil(columnSetView.target)
        XCTAssertTrue(columnSetView.target is ActionToggleVisibilityTarget)
        
        // ShowCard Action is not available as a SelectAction
        columnSet = .make(selectAction: FakeShowCardAction.make())
        columnSetView = renderColumnSetView()
    
        XCTAssertNil(columnSetView.target)
    }
    
    private func renderColumnSetView() -> ACRContentStackView {
        let view = columnSetRenderer.render(element: columnSet, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRContentStackView)
        guard let columnSetView = view as? ACRContentStackView else { fatalError() }
        return columnSetView
    }
}
