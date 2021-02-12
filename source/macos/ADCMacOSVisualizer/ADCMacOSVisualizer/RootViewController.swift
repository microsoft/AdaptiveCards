import AdaptiveCards
import Cocoa

class RootViewController: NSViewController, NSTableViewDelegate, NSTableViewDataSource {
    @IBOutlet var tableView: NSTableView!
    @IBOutlet var stackView: NSStackView!
    @IBOutlet var textView: NSTextView!
    
    var items: [String] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let main = Bundle.main
        let filesManager = FileManager.default
        guard let sample = main.resourcePath?.appending("/samples") else { return }
        do {
            let samples = try filesManager.contentsOfDirectory(atPath: sample)
            items = samples.sorted()
        } catch {
            print(error)
        }
        tableView.rowHeight = 32
    }
    
    // MARK: Private Methods
    private func renderCard(with jsonString: String) {
        let result = AdaptiveCard.from(jsonString: jsonString)
        guard let card = result.getAdaptiveCard() else {
            print("RENDER FAILED")
            return
        }
        print("ELEMENTS:")
        card.getBody().forEach { print($0.getTypeString() ?? "nil") }
        card.getBody().forEach { print(type(of: $0)) }
        
        switch AdaptiveCard.parseHostConfig(from: hostConfig) {
        case .success(let config):
            print("PARSED HOSTCONFIG")
            print("Font family - \(config.getFontFamily() ?? "nil")")
            
            let cardView = AdaptiveCard.render(card: card, with: config, width: 335)
            if let renderedView = stackView.arrangedSubviews.first {
                renderedView.removeFromSuperview()
            }
            stackView.addArrangedSubview(cardView)
            
        case .failure(let error):
            print("Failure: \(error.localizedDescription)")
        }
    }

    @IBAction private func handleRenderAction(_ sender: Any) {
        renderCard(with: textView.string)
    }
    
    // MARK: TableView Datasource
    func numberOfRows(in tableView: NSTableView) -> Int {
        return items.count
    }
    
    func tableView(_ tableView: NSTableView, objectValueFor tableColumn: NSTableColumn?, row: Int) -> Any? {
        return items[row]
    }
    
    func tableViewSelectionDidChange(_ notification: Notification) {
        let selectedRowNum = tableView.selectedRow
        let path = "/samples/\(items[selectedRowNum])"
        let parts = path.components(separatedBy: ".")
        guard let filepath = Bundle.main.path(forResource: parts[0], ofType: "json") else {
            print("File Not found: \(items[selectedRowNum])")
            return
        }
        do {
            let contents = try String(contentsOfFile: filepath)
            renderCard(with: contents)
            textView.string = contents
        } catch {
            print(error)
        }
    }
}
