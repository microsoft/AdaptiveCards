//
//  ACRPresentationViewController.h
//  ACRPresentationViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ACRPresentationViewController : UIViewController

@property (readonly) NSString* jsonStr;

- (id) init:(NSString*) str;

@end
