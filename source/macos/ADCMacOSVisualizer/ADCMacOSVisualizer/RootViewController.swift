import Cocoa

class RootViewController: NSViewController, NSTableViewDelegate, NSTableViewDataSource {
    @IBOutlet var tableView: NSTableView!
        
    var items: [String] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let main = Bundle.main
        guard let sample = main.resourcePath?.appending("/samples") else {
            return
        }
        let filesManager = FileManager.default
        do {
            items = try filesManager.contentsOfDirectory(atPath: sample)
        } catch {
            print(error)
        }
        tableView.rowHeight = 32
    }

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
        if let filepath = Bundle.main.path(forResource: parts[0], ofType: "json") {
            do {
                let contents = try String(contentsOfFile: filepath)
                print(contents)
            } catch {
                print(error)
            }
        } else {
            print("Not found")
        }
    }
}
