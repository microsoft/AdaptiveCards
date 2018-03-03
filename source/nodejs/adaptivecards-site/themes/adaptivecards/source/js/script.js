(function ($) {
  // Adaptive Cards
  AdaptiveCards.AdaptiveCard.onExecuteAction = function (action) {
    var message = "Action executed\n";
    message += "    Title: " + action.title + "\n";

    if (action instanceof AdaptiveCards.OpenUrlAction) {
      message += "    Type: Action.OpenUrl\n";
      message += "    Url: " + action.url + "\n";
    }
    else if (action instanceof AdaptiveCards.SubmitAction) {
      message += "    Type: Action.Submit";
      message += "    Data: " + JSON.stringify(action.data);
    }
    else {
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


  $('.adaptivecard').each(function (item) {

    // TODO: clean this up to only provide custom host config options
    // it breaks on any rename as-is
    var adaptiveCard = new AdaptiveCards.AdaptiveCard();

    adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(hostConfig);
    var json = JSON.parse($(this).text());
    adaptiveCard.parse(json);
    var renderedCard = adaptiveCard.render();

    $(this).text('').append(renderedCard).show();

  });

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


  var sidebar = new StickySidebar('#sidebar-todo', {
    topSpacing: 30,
    bottomSpacing: 20,
    containerSelector: '#content-wrapper',
    innerWrapperSelector: '.sidebar__inner'
  });

  // Search
  var $searchWrap = $('#search-form-wrap'),
    isSearchAnim = false,
    searchAnimDuration = 200;

  var startSearchAnim = function () {
    isSearchAnim = true;
  };

  var stopSearchAnim = function (callback) {
    setTimeout(function () {
      isSearchAnim = false;
      callback && callback();
    }, searchAnimDuration);
  };

  $('#nav-search-btn').on('click', function () {
    if (isSearchAnim) return;

    startSearchAnim();
    $searchWrap.addClass('on');
    stopSearchAnim(function () {
      $('.search-form-input').focus();
    });
  });

  $('.search-form-input').on('blur', function () {
    startSearchAnim();
    $searchWrap.removeClass('on');
    stopSearchAnim();
  });

  // Share
  $('body').on('click', function () {
    $('.article-share-box.on').removeClass('on');
  }).on('click', '.article-share-link', function (e) {
    e.stopPropagation();

    var $this = $(this),
      url = $this.attr('data-url'),
      encodedUrl = encodeURIComponent(url),
      id = 'article-share-box-' + $this.attr('data-id'),
      offset = $this.offset();

    if ($('#' + id).length) {
      var box = $('#' + id);

      if (box.hasClass('on')) {
        box.removeClass('on');
        return;
      }
    } else {
      var html = [
        '<div id="' + id + '" class="article-share-box">',
        '<input class="article-share-input" value="' + url + '">',
        '<div class="article-share-links">',
        '<a href="https://twitter.com/intent/tweet?url=' + encodedUrl + '" class="article-share-twitter" target="_blank" title="Twitter"></a>',
        '<a href="https://www.facebook.com/sharer.php?u=' + encodedUrl + '" class="article-share-facebook" target="_blank" title="Facebook"></a>',
        '<a href="http://pinterest.com/pin/create/button/?url=' + encodedUrl + '" class="article-share-pinterest" target="_blank" title="Pinterest"></a>',
        '<a href="https://plus.google.com/share?url=' + encodedUrl + '" class="article-share-google" target="_blank" title="Google+"></a>',
        '</div>',
        '</div>'
      ].join('');

      var box = $(html);

      $('body').append(box);
    }

    $('.article-share-box.on').hide();

    box.css({
      top: offset.top + 25,
      left: offset.left
    }).addClass('on');
  }).on('click', '.article-share-box', function (e) {
    e.stopPropagation();
  }).on('click', '.article-share-box-input', function () {
    $(this).select();
  }).on('click', '.article-share-box-link', function (e) {
    e.preventDefault();
    e.stopPropagation();

    window.open(this.href, 'article-share-box-window-' + Date.now(), 'width=500,height=450');
  });

  // Caption
  $('.article-entry').each(function (i) {
    $(this).find('img').each(function () {
      if ($(this).parent().hasClass('fancybox')) return;

      var alt = this.alt;

      if (alt) $(this).after('<span class="caption">' + alt + '</span>');

      $(this).wrap('<a href="' + this.src + '" title="' + alt + '" class="fancybox"></a>');
    });

    $(this).find('.fancybox').each(function () {
      $(this).attr('rel', 'article' + i);
    });
  });

  if ($.fancybox) {
    $('.fancybox').fancybox();
  }

})(jQuery);