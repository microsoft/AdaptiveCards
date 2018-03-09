//
//  ACRRenderResult.h
//  ACRRenderResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

@class ACRView;
@class ACRRenderer;

#import <Foundation/Foundation.h>

@interface ACRRenderResult:NSObject

@property ACRView *viewcontroller;
@property BOOL succeeded;

@end    
