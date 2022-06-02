// Used pwa-builder as reference: https://github.com/pwa-builder/pwabuilder-serviceworkers/blob/master/serviceWorker5/pwabuilder-sw.js
importScripts('/workbox/workbox-v6.5.3/workbox-sw.js');

workbox.setConfig({
  modulePathPrefix: '/workbox/workbox-v6.5.3/',
});;

// Precache all files from workbox-config
workbox.precaching.precacheAndRoute(self.__WB_MANIFEST);

const HTML_CACHE = "html";
const JS_CACHE = "javascript";
const STYLE_CACHE = "stylesheets";
const IMAGE_CACHE = "images";
const FONT_CACHE = "fonts";
const DEFAULT_CACHE = "default";

// Need separeate caching for our cross origin styling references
workbox.routing.registerRoute(
  ({url}) => {
    return (url.href === 'https://www.microsoft.com/onerfstatics/marketingsites-wcus-prod/west-european/shell/_scrf/css/themes=default.device=uplevel_web_pc/59-469920/ad-9005a4/bd-292223/26-13ca9e/b7-1464e7/8e-a868c0/58-faa810/34-4fda9f?ver=2.0') 
      || (url.href == 'https://statics-marketingsites-wcus-ms-com.akamaized.net/statics/override.css?c=7');
  }, new workbox.strategies.CacheFirst({
    plugins: [
      new workbox.cacheableResponse.CacheableResponsePlugin({
        statuses: [0, 200]
      })
    ]
  })
);

// TODO: could register routes with regex if we want to be more precise with caching
workbox.routing.registerRoute(
  ({event}) => {
    return event.request.destination === 'document'},
  new workbox.strategies.NetworkFirst({
    cacheName: HTML_CACHE,
    plugins: [
      new workbox.expiration.ExpirationPlugin({
        maxEntries: 10,
      })
    ]
  })
);

function registerStaleWhileRevalidate(destinationType, cache, entries) {
  workbox.routing.registerRoute(
    ({event}) => {
      return event.request.destination === destinationType},
    new workbox.strategies.StaleWhileRevalidate({
      cacheName: cache,
      plugins: [
        new workbox.expiration.ExpirationPlugin({
          maxEntries: entries,
        })
      ]
    })
  );
}

registerStaleWhileRevalidate('script', JS_CACHE, 15);
registerStaleWhileRevalidate('style', STYLE_CACHE, 15);
registerStaleWhileRevalidate('image', IMAGE_CACHE, 15);
registerStaleWhileRevalidate('font', FONT_CACHE, 15);

// This route mostly caches payloads
// We allow for a high cache so the sample cards and data are stored
registerStaleWhileRevalidate('', DEFAULT_CACHE, 100);
