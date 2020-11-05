//
//  ACRChatWindow
//  ACRChatWindow.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACFramework.h>
#import <UIKit/UIKit.h>

@interface ACRChatWindow : NSObject <UITableViewDataSource, UITableViewDelegate>

@property NSObject<ACRActionDelegate> *adaptiveCardsDelegates;

- (void)insertCard:(NSString *)card;

@end
