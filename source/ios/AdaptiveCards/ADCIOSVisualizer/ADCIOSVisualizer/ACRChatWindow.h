//
//  ACRChatWindow
//  ACRChatWindow.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACFramework.h>
#import <UIKit/UIKit.h>

@interface ACRChatWindow : NSObject <UITableViewDataSource, UITableViewDelegate>

extern NSString *identifier;

@property NSObject<ACRActionDelegate> *adaptiveCardsDelegates;

- (instancetype)init:(CGFloat)width;
- (void)insertCard:(NSString *)card;
- (void)deleteAllRows:(UITableView *)tableView;

@end
