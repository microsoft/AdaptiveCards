hexo.extend.tag.register('adaptivecard', function (args) {
	var url = args[0];
	return `<div class="adaptivecard" data-card-url="${url}"></div>`;

});
