// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
$(function() {
	// Adaptive Cards
	AdaptiveCards.AdaptiveCard.onExecuteAction = function (action) {
		var message = "Action executed\n";
		message += "    Title: " + action.title + "\n";

		if (action instanceof AdaptiveCards.OpenUrlAction) {
			message += "    Type: Action.OpenUrl\n";
			message += "    Url: " + action.url + "\n";
		} else if (action instanceof AdaptiveCards.SubmitAction) {
			message += "    Type: Action.Submit";
			message += "    Data: " + JSON.stringify(action.data);
		} else {
			message += "    Type: <unknown>";
		}

		alert(message);
	};


	var hostConfig = {
		spacing: {
			small: 3,
			default: 8,
			medium: 20,
			large: 30,
			extraLarge: 40,
			padding: 10
		},
		separator: {
			lineThickness: 1,
			lineColor: "#EEEEEE"
		},
		supportsInteractivity: true,
		fontFamily: "Segoe UI, Helvetica Neue, Helvetica, sans-serif",
		fontSizes: {
			small: 12,
			default: 14,
			medium: 17,
			large: 21,
			extraLarge: 26
		},
		fontWeights: {
			lighter: 200,
			default: 400,
			bolder: 600
		},
		containerStyles: {
			default: {
				backgroundColor: "#00000000",
				foregroundColors: {
					default: {
						default: "#333333",
						subtle: "#EE333333"
					},
					accent: {
						default: "#2E89FC",
						subtle: "#882E89FC"
					},
					attention: {
						default: "#FF0000",
						subtle: "#DDFFD800"
					},
					good: {
						default: "#00FF00",
						subtle: "#DD00FF00"
					},
					warning: {
						default: "#FFD800",
						subtle: "#DDFF0000"
					}
				}
			},
			emphasis: {
				backgroundColor: "#08000000",
				foregroundColors: {
					default: {
						default: "#333333",
						subtle: "#EE333333"
					},
					accent: {
						default: "#2E89FC",
						subtle: "#882E89FC"
					},
					attention: {
						default: "#FF0000",
						subtle: "#DDFF0000"
					},
					good: {
						default: "#54a254",
						subtle: "#DD54a254"
					},
					warning: {
						default: "#c3ab23",
						subtle: "#DDc3ab23"
					}
				}
			}
		},
		imageSizes: {
			small: 40,
			medium: 80,
			large: 160
		},
		actions: {
			maxActions: 3,
			spacing: 2,
			buttonSpacing: 10,
			showCard: {
				actionMode: "inline",
				inlineTopMargin: 16
			},
			actionsOrientation: 0,
			actionAlignment: 0
		},
		adaptiveCard: {
			allowCustomStyle: false
		},
		image: {
			size: "medium",
		},
		imageSet: {
			imageSize: "medium",
			maxImageHeight: 100
		},
		factSet: {
			title: {
				color: "default",
				size: "default",
				isSubtle: false,
				weight: "bolder",
				wrap: true,
				maxWidth: 150
			},
			value: {
				color: "default",
				size: "default",
				isSubtle: false,
				weight: "default",
				wrap: true
			},
			spacing: 10
		},

	};


	$('.adaptivecard').each(function () {

		var cardUrl = $(this).attr("data-card-url");
		var el = $(this);
		if (cardUrl) {
			$.getJSON(cardUrl, function(json) { renderCard(el, JSON.parse(json)); });
		} else {
			renderCard($(this), JSON.parse(el.text()));
		}
	});

	function renderCard(el, json) {

		// TODO: clean this up to only provide custom host config options
		// it breaks on any rename as-is
		var adaptiveCard = new AdaptiveCards.AdaptiveCard();
		adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(hostConfig);
		adaptiveCard.parse(json);
		var renderedCard = adaptiveCard.render();

		el.text('').append(renderedCard).show();
	}

	$('.ac-properties table').addClass("w3-table w3-bordered w3-responsive");

	$(document).ready(function () {
		hljs.configure({
			tabReplace: '  '
		});
		$('pre code').each(function (i, block) {
			hljs.highlightBlock(block);
		});

		// weird bug the Visualizer editor isn't loading correctly
		// window.setTimeout(function() {
		//   window.dispatchEvent(new Event('resize'));
		// }, 200);

		$('#menu-nav').on('change', function () {
			window.location = this.value;
		});
	});

	if ($('#sidebar-todo').length) {
		new StickySidebar('#sidebar-todo', {
			topSpacing: 30,
			bottomSpacing: 20,
			containerSelector: '#content-wrapper',
			innerWrapperSelector: '.sidebar__inner'
		});
	}

});
