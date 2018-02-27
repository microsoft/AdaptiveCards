using System;

using UIKit;
using Foundation;
using ObjCRuntime;
using CoreGraphics;

namespace AdaptiveCards.Rendering.Xamarin.iOS
{
	// @protocol ACRActionDelegate
	[Protocol, Model]
	[BaseType(typeof(NSObject))]
	interface ACRActionDelegate
	{
		// @required -(void)didFetchUserResponses:(NSDictionary *)userResponses;
		[Abstract]
		[Export("didFetchUserResponses:")]
		void DidFetchUserResponses(NSDictionary userResponses);

		// @required -(void)didFetchHttpRequest:(NSURLRequest *)urlRequest;
		[Abstract]
		[Export("didFetchHttpRequest:")]
		void DidFetchHttpRequest(NSUrlRequest urlRequest);
	}

	// @interface ACOParseResult : NSObject
	[BaseType(typeof(NSObject))]
	interface ACOParseResult
	{
		// @property BOOL IsValid;
		[Export("IsValid")]
		bool IsValid { get; set; }
	}

	// @interface ACOAdaptiveCardParseResult : ACOParseResult
	[BaseType(typeof(ACOParseResult))]
	interface ACOAdaptiveCardParseResult
	{
		// @property ACOAdaptiveCard * card;
		[Export("card", ArgumentSemantic.Assign)]
		ACOAdaptiveCard Card { get; set; }
	}

	// @interface ACOAdaptiveCard : NSObject
	[BaseType(typeof(NSObject))]
	interface ACOAdaptiveCard
	{
		// +(ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;
		[Static]
		[Export("fromJson:")]
		ACOAdaptiveCardParseResult FromJson(string payload);
	}

	// @interface ACOHostConfigParseResult : ACOParseResult
	[BaseType(typeof(ACOParseResult))]
	interface ACOHostConfigParseResult
	{
		// @property ACOHostConfig * config;
		[Export("config", ArgumentSemantic.Assign)]
		ACOHostConfig Config { get; set; }
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
		[Wrap("WeakDelegate")]
		ACRActionDelegate Delegate { get; set; }

		// @property (weak) id<ACRActionDelegate> acrActionDelegate;
		[NullAllowed, Export("acrActionDelegate", ArgumentSemantic.Weak)]
		NSObject WeakDelegate { get; set; }

		// -(instancetype)init:(ACOAdaptiveCard *)card hostconfig:(ACOHostConfig *)config frame:(CGRect)frame;
		[Export("init:hostconfig:frame:")]
		IntPtr Constructor(ACOAdaptiveCard card, ACOHostConfig config, CGRect frame);
	}

	// @interface ACRRenderResult : NSObject
	[BaseType(typeof(NSObject))]
	interface ACRRenderResult
	{
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
		[Export("render:config:frame:")]
		ACRRenderResult Render(ACOAdaptiveCard card, ACOHostConfig config, CGRect frame);
	}
}
