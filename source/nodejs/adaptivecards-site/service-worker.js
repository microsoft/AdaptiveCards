// Used pwa-builder as reference: https://github.com/pwa-builder/pwabuilder-serviceworkers/blob/master/serviceWorker5/pwabuilder-sw.js
importScripts(
  'https://storage.googleapis.com/workbox-cdn/releases/6.4.1/workbox-sw.js'
);

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

// TODO: matching by regex might be a better way to register routes since there are a lot of destinations :)
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

workbox.routing.registerRoute(
  ({event}) => {
    return event.request.destination === 'script'},
  new workbox.strategies.StaleWhileRevalidate({
    cacheName: JS_CACHE,
    plugins: [
      new workbox.expiration.ExpirationPlugin({
        maxEntries: 15,
      })
    ]
  })
);

workbox.routing.registerRoute(
  ({event}) => {
    return event.request.destination === 'style'},
  new workbox.strategies.StaleWhileRevalidate({
    cacheName: STYLE_CACHE,
    plugins: [
      new workbox.expiration.ExpirationPlugin({
        maxEntries: 15,
      })
    ]
  })
);

workbox.routing.registerRoute(
  ({event}) => {
    return event.request.destination === 'image'},
  new workbox.strategies.StaleWhileRevalidate({
    cacheName: IMAGE_CACHE,
    plugins: [
      new workbox.expiration.ExpirationPlugin({
        maxEntries: 15,
      })
    ]
  })
);

workbox.routing.registerRoute(
  ({event}) => {
    return event.request.destination === 'font'},
  new workbox.strategies.StaleWhileRevalidate({
    cacheName: FONT_CACHE,
    plugins: [
      new workbox.expiration.ExpirationPlugin({
        maxEntries: 15,
      })
    ]
  })
);

// This route mostly caches payloads
workbox.routing.registerRoute(
  ({event}) => {
    return event.request.destination === ''},
  new workbox.strategies.StaleWhileRevalidate({
    cacheName: DEFAULT_CACHE,
    plugins: [
      new workbox.expiration.ExpirationPlugin({
        maxEntries: 50,
      })
    ]
  })
);
