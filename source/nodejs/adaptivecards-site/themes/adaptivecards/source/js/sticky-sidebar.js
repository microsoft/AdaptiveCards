// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// Code for making our sidebar sticky

var $sidebar;
var $headerHolder;

$(function() {

	$(document).ready(function () {

		$sidebar = $(".sidebar");
		if ($sidebar.length > 0) {
			$headerHolder = $(".header-holder");

			updateSidebarTopOffset();

			$(document).scroll(function() {
				updateSidebarTopOffset();
			});
		}

	});

});

function updateSidebarTopOffset() {
	var headerHeight = $headerHolder.height();
	var scrollOffset = $(document).scrollTop();
	var topPadding = 24;

	var calculatedTop = headerHeight - scrollOffset + topPadding;
	if (calculatedTop < topPadding) {
		calculatedTop = topPadding;
	}

	$sidebar.css("top", calculatedTop);
}