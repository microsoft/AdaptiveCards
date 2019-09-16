//
//  ACRRenderResult.h
//  ACRRenderResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

@class ACRView;
@class ACRRenderer;

#import "ACRViewController.h"
#import <Foundation/Foundation.h>

@interface ACRRenderResult : NSObject

@property ACRView *view;
@property ACRViewController *viewcontroller;
@property BOOL succeeded;

@end
