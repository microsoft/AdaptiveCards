//
//  ACRRenderResult.h
//  ACRRenderResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

@class ACRView;
@class ACRRenderer;

#import <Foundation/Foundation.h>
#import "ACRViewController.h"

@interface ACRRenderResult:NSObject

@property ACRView *view;
@property ACRViewController *viewcontroller;
@property BOOL succeeded;
@property (weak) NSArray<ACOWarning *> *warnings;

@end
