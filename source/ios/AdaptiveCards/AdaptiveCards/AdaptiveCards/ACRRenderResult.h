//
//  ACRRenderResult.h
//  ACRRenderResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

@class ACRViewController;
@class ACRRenderer;

#import <Foundation/Foundation.h>

@interface ACRRenderResult:NSObject

@property ACRViewController *viewcontroller;
@property BOOL succeeded;

@end    
