'use strict';

const hljs = require('highlight.js/lib/highlight');
const Entities = require('html-entities').XmlEntities;
const entities = new Entities();
const alias = require('../highlight_alias.json');

function highlightUtil(str, options = {}) {
  if (typeof str !== 'string') throw new TypeError('str must be a string!');

  const useHljs = options.hasOwnProperty('hljs') ? options.hljs : false;
  const {
    gutter = true,
    firstLine = 1,
    caption,
    mark = [],
    tab
  } = options;
  let { wrap = true } = options;

  hljs.configure({ classPrefix: useHljs ? 'hljs-' : ''});

  const data = highlight(str, options);

  if (useHljs && !gutter) wrap = false;

  const before = useHljs ? `<pre><code class="hljs ${options.lang}">` : '<pre>';
  const after = useHljs ? '</code></pre>' : '</pre>';

  if (!wrap) return useHljs ? before + data.value + after : data.value;

  const lines = data.value.split('\n');
  let numbers = '';
  let content = '';

  for (let i = 0, len = lines.length; i < len; i++) {
    let line = lines[i];
    if (tab) line = replaceTabs(line, tab);
    numbers += `<span class="line">${firstLine + i}</span><br>`;
    content += formatLine(line, firstLine + i, mark, options);
  }

  let result = `<figure class="highlight${data.language ? ` ${data.language}` : ''}">`;

  if (caption) {
    result += `<figcaption>${caption}</figcaption>`;
  }

  result += '<table><tr>';

  if (gutter) {
    result += `<td class="gutter"><pre>${numbers}</pre></td>`;
  }

  result += `<td class="code">${before}${content}${after}</td>`;
  result += '</tr></table></figure>';

  return result;
}

function formatLine(line, lineno, marked, options) {
  const useHljs = options.hljs || false;
  let res = useHljs ? '' : '<span class="line';
  if (marked.includes(lineno)) {
    // Handle marked lines.
    res += useHljs ? `<mark>${line}</mark>` : ` marked">${line}</span>`;
  } else {
    res += useHljs ? line : `">${line}</span>`;
  }

  res += '<br>';
  return res;
}

function encodePlainString(str) {
  return entities.encode(str);
}

function replaceTabs(str, tab) {
  return str.replace(/^\t+/, match => {
    let result = '';

    for (let i = 0, len = match.length; i < len; i++) {
      result += tab;
    }

    return result;
  });
}

function loadLanguage(lang) {
  hljs.registerLanguage(lang, require(`highlight.js/lib/languages/${lang}`));
}

function tryLanguage(lang) {
  if (hljs.getLanguage(lang)) return true;
  if (!alias.aliases[lang]) return false;

  loadLanguage(alias.aliases[lang]);
  return true;
}

function loadAllLanguages() {
  alias.languages.filter(lang => !hljs.getLanguage(lang)).forEach(loadLanguage);
}

function highlight(str, options) {
  let { lang } = options;
  const { autoDetect = false } = options;

  if (!lang && autoDetect) {
    loadAllLanguages();
    const result = hljs.highlightAuto(str);
    if (result.relevance > 0 && result.language) lang = result.language;

  }

  if (!lang) {
    lang = 'plain';
  }

  const result = {
    value: encodePlainString(str),
    language: lang.toLowerCase()
  };

  if (result.language === 'plain') {
    return result;
  }

  if (!tryLanguage(result.language)) {
    result.language = 'plain';
    return result;
  }

  if (options.hljs) return hljs.highlight(lang, str);

  return tryHighlight(str, result.language) || result;
}

function tryHighlight(str, lang) {
  try {
    const matching = str.match(/(\r?\n)/);
    const separator = matching ? matching[1] : '';
    const lines = matching ? str.split(separator) : [str];
    let result = hljs.highlight(lang, lines.shift());
    let html = result.value;
    while (lines.length > 0) {
      result = hljs.highlight(lang, lines.shift(), false, result.top);
      html += separator + result.value;
    }

    result.value = html;
    return result;
  } catch (err) {

  }
}

module.exports = highlightUtil;