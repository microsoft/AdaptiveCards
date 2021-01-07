// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
if (typeof hljs !== 'undefined') {
	hljs.configure({
		tabReplace: '  '
	});

	hljs.initHighlightingOnLoad();
}

$(function () {
	if(localStorage.getItem("enable-templating") === null) {
		localStorage.setItem("enable-templating", true);
	}

	$("#enableTemplating").prop("checked", localStorage.getItem("enable-templating") === "true");

	if (typeof AdaptiveCards !== 'undefined') {
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
	}


	var hostConfig = {
		"spacing": {
			"small": 3,
			"default": 8,
			"medium": 20,
			"large": 30,
			"extraLarge": 40,
			"padding": 10
		},
		"separator": {
			"lineThickness": 1,
			"lineColor": "#EEEEEE"
		},
		"supportsInteractivity": true,
		"fontTypes": {
			"default": {
				"fontFamily": "Segoe UI, Helvetica Neue, Helvetica, sans-serif",
				"fontSizes": {
					"small": 12,
					"default": 14,
					"medium": 17,
					"large": 21,
					"extraLarge": 26
				},
				"fontWeights": {
					"lighter": 200,
					"default": 400,
					"bolder": 600
				}
			},
			"monospace": {
				"fontFamily": "'Courier New', Courier, monospace",
				"fontSizes": {
					"small": 12,
					"default": 14,
					"medium": 17,
					"large": 21,
					"extraLarge": 26
				},
				"fontWeights": {
					"lighter": 200,
					"default": 400,
					"bolder": 600
				}
			}
		},
		"containerStyles": {
			"default": {
				"backgroundColor": "#FFFFFF",
				"foregroundColors": {
					"default": {
						"default": "#000000",
						"subtle": "#6f6f6f"
					},
					"accent": {
						"default": "#0063B1",
						"subtle": "#0063B1"
					},
					"attention": {
						"default": "#EC130E",
						"subtle": "#DDEC130E"
					},
					"good": {
						"default": "#028A02",
						"subtle": "#DD028A02"
					},
					"light": {
						"default": "#646464",
						"subtle": "#767676"
					},
					"warning": {
						"default": "#B75C00",
						"subtle": "#DDB75C00"
					}
				}
			},
			"emphasis": {
				"backgroundColor": "#F9F9F9",
				"foregroundColors": {
					"default": {
						"default": "#000000",
						"subtle": "#6f6f6f"
					},
					"accent": {
						"default": "#1F6BF1",
						"subtle": "#881F6BF1"
					},
					"attention": {
						"default": "#E31B13",
						"subtle": "#DDE31B13"
					},
					"good": {
						"default": "#0D860A",
						"subtle": "#DD0D860A"
					},
					"warning": {
						"default": "#BD5400",
						"subtle": "#DDBD5400"
					},
					"light": {
						"default": "#737373",
						"subtle": "#DD737373"
					}
				}
			},
			"accent": {
				"backgroundColor": "#D7E7FA",
				"foregroundColors": {
					"default": {
						"default": "#333333",
						"subtle": "#EE333333"
					},
					"dark": {
						"default": "#000000",
						"subtle": "#66000000"
					},
					"light": {
						"default": "#646464",
						"subtle": "#33646464"
					},
					"accent": {
						"default": "#145FDD",
						"subtle": "#88145FDD"
					},
					"attention": {
						"default": "#C42C07",
						"subtle": "#DDC42C07"
					},
					"good": {
						"default": "#0B7814",
						"subtle": "#DD0B7814"
					},
					"warning": {
						"default": "#935A10",
						"subtle": "#DD935A10"
					}
				}
			},
			"good": {
				"backgroundColor": "#CCFFCC",
				"foregroundColors": {
					"default": {
						"default": "#333333",
						"subtle": "#EE333333"
					},
					"dark": {
						"default": "#000000",
						"subtle": "#66000000"
					},
					"light": {
						"default": "#6E6E6E",
						"subtle": "#336E6E6E"
					},
					"accent": {
						"default": "#2168E4",
						"subtle": "#882168E4"
					},
					"attention": {
						"default": "#CC3300",
						"subtle": "#DDCC3300"
					},
					"good": {
						"default": "#0F8109",
						"subtle": "#DD0F8109"
					},
					"warning": {
						"default": "#9A630D",
						"subtle": "#DD9A630D"
					}
				}
			},
			"attention": {
				"backgroundColor": "#FFC5B2",
				"foregroundColors": {
					"default": {
						"default": "#333333",
						"subtle": "#EE333333"
					},
					"dark": {
						"default": "#000000",
						"subtle": "#66000000"
					},
					"light": {
						"default": "#5A5A5A",
						"subtle": "#335A5A5A"
					},
					"accent": {
						"default": "#0854C5",
						"subtle": "#880854C5"
					},
					"attention": {
						"default": "#A92E0E",
						"subtle": "#DDA92E0E"
					},
					"good": {
						"default": "#256824",
						"subtle": "#DD256824"
					},
					"warning": {
						"default": "#775502",
						"subtle": "#DD775502"
					}
				}
			},
			"warning": {
				"backgroundColor": "#FFE2B2",
				"foregroundColors": {
					"default": {
						"default": "#333333",
						"subtle": "#EE333333"
					},
					"dark": {
						"default": "#000000",
						"subtle": "#66000000"
					},
					"light": {
						"default": "#646464",
						"subtle": "#33646464"
					},
					"accent": {
						"default": "#0F60DC",
						"subtle": "#880F60DC"
					},
					"attention": {
						"default": "#BF3505",
						"subtle": "#DDBF3505"
					},
					"good": {
						"default": "#207725",
						"subtle": "#DD207725"
					},
					"warning": {
						"default": "#866107",
						"subtle": "#DD866107"
					}
				}
			}
		},
		"imageSizes": {
			"small": 40,
			"medium": 80,
			"large": 160
		},
		"actions": {
			"maxActions": 100,
			"spacing": "default",
			"buttonSpacing": 8,
			"showCard": {
				"actionMode": "inline",
				"inlineTopMargin": 8
			},
			"actionsOrientation": "horizontal",
			"actionAlignment": "left"
		},
		"adaptiveCard": {
			"allowCustomStyle": false
		},
		"imageSet": {
			"imageSize": "medium",
			"maxImageHeight": 100
		},
		"factSet": {
			"title": {
				"color": "default",
				"size": "default",
				"isSubtle": false,
				"weight": "bolder",
				"wrap": true,
				"maxWidth": 150
			},
			"value": {
				"color": "default",
				"size": "default",
				"isSubtle": false,
				"weight": "default",
				"wrap": true
			},
			"spacing": 8
		}
	}

	$("#closeVideo").click(function () {
		$("#overviewVideo")[0].pause();
		$('#videoModal').css("display", "none");
	});

	$("#watchVideo").click(function () {
		$("#overviewVideo")[0].play();
		$('#videoModal').css("display", "block");

	});

	$(document).keyup(function (e) {
		if (e.keyCode === 27) $('#closeVideo').click();
	});

	// Loop videos
	$("video").each(function () {
		var $video = $(this);
		var loopDelay = $video.attr("data-loop-delay");
		if (loopDelay) {
			$video.on("ended", function () {
				setTimeout(function () {
					$video[0].play();
				}, loopDelay);
			});
		}
	});


	$('.ac-properties table').addClass("w3-table w3-bordered");


	// From https://github.com/30-seconds/30-seconds-of-code/blob/20e7d899f31ac3d8fb2b30b2e311acf9a1964fe8/snippets/copyToClipboard.md
	function copyToClipboard(str) {
		const el = document.createElement('textarea');
		el.value = str;
		el.setAttribute('readonly', '');
		el.style.position = 'absolute';
		el.style.left = '-9999px';
		document.body.appendChild(el);
		const selected =
			document.getSelection().rangeCount > 0 ? document.getSelection().getRangeAt(0) : false;
		el.select();
		document.execCommand('copy');
		document.body.removeChild(el);
		if (selected) {
			document.getSelection().removeAllRanges();
			document.getSelection().addRange(selected);
		}
	}


	function renderAllCards() {
		var enableTemplating = localStorage.getItem("enable-templating") === "true";

		$(".show-with-templating").css("display", "none");
		$(".hide-with-templating").css("display", "");

		$(".adaptivecard").each(function () {

			var cardUrl = $(this).attr("data-card-url");
			var templateUrl = $(this).attr("data-template-url");
			var dataUrl = $(this).attr("data-data-url");
			var el = $(this);

			if (templateUrl && enableTemplating) {

				$(".show-with-templating").css("display", "");
				$(".hide-with-templating").css("display", "none");

				$.getJSON(templateUrl, function (templateJson) {
					$.getJSON(dataUrl, function (dataJson) {
						renderCard(el, templateJson, dataJson);
					});
				});
			}
			else if (cardUrl) {
				$.getJSON(cardUrl, function (json) { renderCard(el, json); });
			} else {
				renderCard($(this), el.text());
			}
		});
	}
	renderAllCards();

	function renderCard(el, json, dataJson) {
		if (typeof json === "string")
			json = JSON.parse(json);

		if (dataJson && typeof dataJson === "string")
			dataJson = JSON.parse(dataJson);

		// TODO: clean this up to only provide custom host config options
		// it breaks on any rename as-is
		AdaptiveCards.GlobalSettings.setTabIndexAtCardRoot = false;
		var adaptiveCard = new AdaptiveCards.AdaptiveCard();
		adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(hostConfig);
		var renderedCard;

		if (dataJson) {
			var template = new ACData.Template(json);
			adaptiveCard.parse(template.expand({
				$root: dataJson
			}));
			renderedCard = adaptiveCard.render();
		} else {
			adaptiveCard.parse(json);
			renderedCard = adaptiveCard.render();
		}

		el.text('').append(renderedCard).show();
	}

	$("#enableTemplating").change(function () {
		localStorage.setItem("enable-templating", this.checked);
		renderAllCards();

	});

	$("button.copy-code").click(function (e) {
		var content = $(this).parent().next("pre").text();
		copyToClipboard(content);
    	$("button.copy-code").focus();
	});

	function launchDesigner(designerUrl, cardUrl, dataUrl) {
		if(!designerUrl || !cardUrl) {
			alert("Whoops, something went wrong. Please click the Feedback button in the top right and let us know what happened.");
			return;
		}

		designerUrl += "?card=" + cardUrl;

		if(dataUrl) {
			designerUrl += "&data=" + dataUrl
		}

		window.open(designerUrl);
	}

	$("button.try-adaptivecard").click(function (e) {
		var enableTemplating = localStorage.getItem("enable-templating") === "true";
		var cardEl = $(this).parent().siblings("div.adaptivecard");
		var designerUrl = cardEl.attr("data-designer-url");
		var cardUrl = cardEl.attr("data-card-url");
		var dataUrl = cardEl.attr("data-data-url");
		var templateUrl = cardEl.attr("data-template-url");

		if (enableTemplating && dataUrl && templateUrl) {
			launchDesigner(designerUrl, templateUrl, dataUrl);
		} else {
			launchDesigner(designerUrl, cardUrl);
		}
	});

	function invokeFeedback(e) {
		e.preventDefault();
		window.open("https://github.com/Microsoft/AdaptiveCards/issues/new?title="
			+ encodeURIComponent("[Website] [Your feedback title here]")
			+ "&body=" + encodeURIComponent("\r\n\r\n[Your detailed feedback here]\r\n\r\n---\r\n* URL: "
			+ window.location.href));
	}

	$("#feedback-button").on({
	click: invokeFeedback,
	keydown: function (e) {
		if (e.key === "Enter") {
			invokeFeedback(e);
		}
	}});

	$('#menu-nav').on('change', function () {
		window.location = this.value;
	});

	function isInViewport(elem) {
		var bounding = elem.getBoundingClientRect();
		return (
			bounding.top >= 0 &&
			bounding.left >= 0 &&
			bounding.bottom <= (window.innerHeight || document.documentElement.clientHeight) &&
			bounding.right <= (window.innerWidth || document.documentElement.clientWidth)
		);
	};

	var videos = document.querySelectorAll('video[data-autoplay]');
	$(window).scroll(function (event) {
		videos.forEach(function (video) {
			if (isInViewport(video)) {
				video.play();
			} else {
				video.pause();
			}
		});
	});

	// Resize youtube videos
	// https://css-tricks.com/NetMag/FluidWidthVideo/Article-FluidWidthVideo.php
	var $allVideos = $("iframe");

	// Figure out and save aspect ratio for each video
	$allVideos.each(function () {
		$(this)
			.data('aspectRatio', this.height / this.width)
			.removeAttr('height')
			.removeAttr('width');
	});

	// When the window is resized
	$(window).resize(function () {

		// Resize all videos according to their own aspect ratio
		$allVideos.each(function () {
			var $el = $(this);
			var newWidth = $el.parent().innerWidth();
			$el.width(newWidth).height(newWidth * $el.data('aspectRatio'));
		});

		// Kick off one resize to fix all videos on page load
	}).resize();

	// Code for making sidebar sticky
	var headerHolder;
	var footerHolder;
	var sidebar = $(".sidebar");

	if (sidebar.length > 0) {
		headerHolder = $(".header-holder");
		footerHolder = $(".footer-holder");

		updateSidebarTopOffset();

		$(document).scroll(function () {
			updateSidebarTopOffset();
		});
		$(document).resize(function () {
			updateSidebarTopOffset();
		});
	}

	function updateSidebarTopOffset() {
		var headerHeight = headerHolder.height();
		var footerHeight = footerHolder.height();
		var scrollOffset = $(document).scrollTop();
		var windowHeight = $(window).height();
		var footerPosition = footerHolder.offset().top;
		var hiddenAfter = (footerPosition + footerHeight) - (scrollOffset + windowHeight);

		var topPadding = 24;

		var calculatedTop = Math.max(headerHeight - scrollOffset + topPadding, topPadding);
		var calculatedBottom = Math.max(footerHeight - hiddenAfter, 0);

		sidebar.css("top", calculatedTop).css("bottom", calculatedBottom);
	}
});
