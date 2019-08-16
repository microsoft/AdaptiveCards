using System;

using UIKit;
using Foundation;
using ObjCRuntime;
using CoreGraphics;
using CoreFoundation;

namespace AdaptiveCards.Rendering.Xamarin.iOS
{
    // @interface ACOBaseActionElement : NSObject
    [BaseType(typeof(NSObject))]
    interface ACOBaseActionElement
    {
        // @property ACRActionType type;
        [Export("type", ArgumentSemantic.Assign)]
        ACRActionType Type { get; set; }

        // -(NSString *)title;
        [Export("title")]
        string Title { get; }

        // -(NSString *)elementId;
        [Export("elementId")]
        string ElementId { get; }

        // -(NSString *)url;
        [Export("url")]
        string Url { get; }

        // -(NSString *)data;
        [Export("data")]
        string Data { get; }

        // -(NSData *)additionalProperty;
        [Export("additionalProperty")]
        NSData AdditionalProperty { get; }
    }


    // @protocol ACRActionDelegate
    [Protocol, Model]
    [BaseType(typeof(NSObject))]
    interface ACRActionDelegate
    {
        // @required -(void)didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action;
        [Abstract]
        [Export("didFetchUserResponses:action:")]
        void DidFetchUserResponses(ACOAdaptiveCard card, ACOBaseActionElement action);

        // @required -(void)didFetchSecondaryView:(ACOAdaptiveCard *)card navigationController:(UINavigationController *)naviationController;
        [Abstract]
        [Export("didFetchSecondaryView:navigationController:")]
        void DidFetchSecondaryView(ACOAdaptiveCard card, UINavigationController naviationController);

        // @optional -(void)didLoadElements;
        [Export("didLoadElements")]
        void DidLoadElements();
    }

    // @interface ACRParseWarning : NSObject
    [BaseType(typeof(NSObject))]
    interface ACRParseWarning
    {
        // @property (readonly) ACRParseWarningStatusCode statusCode;
        [Export("statusCode")]
        ACRParseWarningStatusCode StatusCode { get; }

        // @property (readonly) NSString * reason;
        [Export("reason")]
        string Reason { get; }
    }

    // @interface ACOAdaptiveCardParseResult : NSObject
    [BaseType(typeof(NSObject))]
    interface ACOAdaptiveCardParseResult
    {
        // @property ACOAdaptiveCard * card;
        [Export("card", ArgumentSemantic.Assign)]
        ACOAdaptiveCard Card { get; set; }

        // @property BOOL isValid;
        [Export("isValid")]
        bool IsValid { get; set; }

        [Export("parseErrors")]
        NSError[] ParseErrors { get; }

        // @property (readonly) NSArray<ACRParseWarning *> * parseWarnings;
        [Export("parseWarnings")]
        ACRParseWarning[] ParseWarnings { get; }
    }

    // @interface ACOAdaptiveCard : NSObject
    [BaseType(typeof(NSObject))]
    interface ACOAdaptiveCard
    {
        // +(ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;
        [Static]
        [Export("fromJson:")]
        ACOAdaptiveCardParseResult FromJson(string payload);

        // -(NSArray *)getInputs;
        [Export("getInputs")]
        NSArray Inputs { get; }

        // -(NSData *)inputs
        [Export("inputs")]
        NSData InputsAsMap { get; }
    }

    // @interface ACOHostConfigParseResult : NSObject
    [BaseType(typeof(NSObject))]
    interface ACOHostConfigParseResult
    {
        // @property ACOHostConfig * config;
        [Export("config", ArgumentSemantic.Assign)]
        ACOHostConfig Config { get; set; }

        // @property BOOL isValid;
        [Export("isValid")]
        bool IsValid { get; set; }

        // @property (readonly) NSArray<NSError *> * parseErrors;
        [Export("parseErrors")]
        NSError[] ParseErrors { get; }
    }

    // @interface ACOHostConfig : NSObject
    [BaseType(typeof(NSObject))]
    interface ACOHostConfig
    {
        // +(ACOHostConfigParseResult *)fromJson:(NSString *)payload;
        [Static]
        [Export("fromJson:")]
        ACOHostConfigParseResult FromJson(string payload);
    }

    // @interface ACRViewController : UIViewController
    [BaseType(typeof(UIViewController))]
    interface ACRViewController
    {
        // -(instancetype)init:(ACOAdaptiveCard *)card hostconfig:(ACOHostConfig *)config frame:(CGRect)frame delegate:(id<ACRActionDelegate>)acrActionDelegate;
        [Export("init:hostconfig:frame:delegate:")]
        IntPtr Constructor(ACOAdaptiveCard card, ACOHostConfig config, CGRect frame, ACRActionDelegate acrActionDelegate);
    }

    // @interface ACRRenderResult : NSObject
    [BaseType(typeof(NSObject))]
    interface ACRRenderResult
    {
        // @property ACRView * view;
        [Export("view", ArgumentSemantic.Assign)]
        ACRView View { get; set; }

        // @property ACRViewController * viewcontroller;
        [Export("viewcontroller", ArgumentSemantic.Assign)]
        ACRViewController Viewcontroller { get; set; }

        // @property BOOL succeeded;
        [Export("succeeded")]
        bool Succeeded { get; set; }
    }

    // @interface ACRRenderer : NSObject
    [BaseType(typeof(NSObject))]
    interface ACRRenderer
    {
        // +(ACRRenderResult *)render:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config frame:(CGRect)frame;
        [Static]
        [Export("render:config:widthConstraint:")]
        ACRRenderResult Render(ACOAdaptiveCard card, ACOHostConfig config, nfloat widthConstraint);

        // +(ACRRenderResult *)render:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config widthConstraint:(float)width delegate:(id<ACRActionDelegate>)acrActionDelegate;
        [Static]
        [Export("render:config:widthConstraint:delegate:")]
        ACRRenderResult Render(ACOAdaptiveCard card, ACOHostConfig config, nfloat widthConstraint, ACRActionDelegate acrActionDelegate);


        // +(ACRRenderResult *)renderAsViewController:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config frame:(CGRect)frame delegate:(id<ACRActionDelegate>)acrActionDelegate;
        [Static]
        [Export("renderAsViewController:config:frame:delegate:")]
        ACRRenderResult RenderAsViewController(ACOAdaptiveCard card, ACOHostConfig config, CGRect frame, ACRActionDelegate acrActionDelegate);
    }

    // @interface ACRView : UIView
    [BaseType(typeof(UIView))]
    interface ACRView
    {
        [Wrap("WeakAcrActionDelegate")]
        ACRActionDelegate AcrActionDelegate { get; set; }

        // @property (weak) id<ACRActionDelegate> acrActionDelegate;
        [NullAllowed, Export("acrActionDelegate", ArgumentSemantic.Weak)]
        NSObject WeakAcrActionDelegate { get; set; }

        // -(instancetype)init:(ACOAdaptiveCard *)card hostconfig:(ACOHostConfig *)config frame:(CGRect)frame;
        [Export("init:hostconfig:frame:")]
        IntPtr Constructor(ACOAdaptiveCard card, ACOHostConfig config, CGRect frame);

        // -(NSMutableDictionary *)getImageMap;
        [Export("getImageMap")]
        NSMutableDictionary ImageMap { get; }

        // -(dispatch_queue_t)getSerialQueue;
        [Export("getSerialQueue")]
        DispatchQueue SerialQueue { get; }

        // -(NSMutableDictionary *)getTextMap;
        [Export("getTextMap")]
        NSMutableDictionary TextMap { get; }

        // -(dispatch_queue_t)getSerialTextQueue;
        [Export("getSerialTextQueue")]
        DispatchQueue SerialTextQueue { get; }

        // -(ACOAdaptiveCard *)card;
        [Export("card")]
        ACOAdaptiveCard Card { get; }
    }
}
