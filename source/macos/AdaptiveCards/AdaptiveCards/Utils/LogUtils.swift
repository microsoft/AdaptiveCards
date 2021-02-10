import Foundation

func logError(_ message: Any..., function: String = #function, file: String = #file, line: Int = #line) {
    logPrint(type: .error, message: message, function: function, file: file, line: line)
}

func logInfo(_ message: Any..., function: String = #function, file: String = #file, line: Int = #line) {
    logPrint(type: .info, message: message, function: function, file: file, line: line)
}

private enum LogType {
    case error, info
    
    var title: String {
        switch self {
        case .error: return "ERROR"
        case .info: return "INFO "
        }
    }
}

private func logPrint(type: LogType, message: [Any], function: String, file: String, line: Int) {
    let fileName = URL(string: file)?.lastPathComponent ?? file
    let joined = message.map { String(describing: $0) }.joined(separator: " ")
    print("\(type.title): #\(line) \(function) \(fileName): ", joined)
}
