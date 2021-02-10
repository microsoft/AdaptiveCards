//
//  AppDelegate.swift
//  ADCMacOSVisualizer
//
//  Created by aksc on 13/01/21.
//

import Cocoa

class AppDelegate: NSObject, NSApplicationDelegate {
    var window: NSWindow?

    func applicationDidFinishLaunching(_ aNotification: Notification) {
        let minWindowSize = NSSize(width: 840, height: 540)
        window = NSWindow(contentRect: NSRect(origin: .zero, size: minWindowSize), styleMask: [.miniaturizable, .closable, .titled, .resizable], backing: .buffered, defer: false)
        window?.title = "ADCMacOSVisualizer"
        window?.minSize = minWindowSize
        window?.center()
        window?.contentViewController = MainViewController()
        window?.makeKeyAndOrderFront(nil)
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        // Insert code here to tear down your application
    }
}
