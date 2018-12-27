const DATE_REGEX = /\{{2}DATE\((\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:Z|(?:(?:-|\+)\d{2}:\d{2})))(?:, ?(COMPACT|LONG|SHORT))?\)\}{2}/g;
const TIME_REGEX = /\{{2}TIME\((\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:Z|(?:(?:-|\+)\d{2}:\d{2})))\)\}{2}/g;

/**
 * This function is used to format the DATE.
 * @example "Scheduled at {{DATE(2017-02-14T06:08:39Z,LONG)}}" formatted as "Tuesday, February 14, 2017"
 * 
 * @param {string} lang 
 * @param {string} input 
 * @return {string} Text with `DATE` part formatted
 */
function formatDate(lang, input) {

	var result = input;
	var matches;
	var localeDateString;

	while ((matches = DATE_REGEX.exec(input)) != null) {

		var date = new Date(Date.parse(matches[1]));
		var format = matches[2] != undefined ? matches[2].toLowerCase() : "compact";

		if (format != "compact") {
			localeDateString = date.toLocaleDateString(lang,
				{
					day: "numeric",
					weekday: format,
					month: format,
					year: "numeric"
				});
		}
		else {
			localeDateString = date.toLocaleDateString();
		}
		result = result.replace(matches[0], localeDateString);
	};
	return result;

}

/**
 * This function is used to format the TIME.
 * @example "Scheduled at {{TIME(2017-02-14T06:08:39Z)}}" formatted as "Scheduled at 11:38 AM"
 * 
 * @param {string} lang 
 * @param {string} input 
 * @return {string} Text with `TIME` part formatted
 */
function formatTime(lang, input) {
	var result = input;
	var matches;
	var localeTimeString;

	while ((matches = TIME_REGEX.exec(input)) != null) {

		var date = new Date(Date.parse(matches[1]));
		localeTimeString = date.toLocaleTimeString(lang,
			{
				hour: 'numeric',
				minute: '2-digit'
			});

		result = result.replace(matches[0], localeTimeString);
	};
	return result;
}

/**
 * This formats the DATE and TIME that present in the given text
 * @param {string} lang 
 * @param {string} text - Text that contains DATE & TIME for formatting.
 * @return {string} Text where `DATE` & `TIME` are formatted
 */
export const TextFormatter = (lang, text) => {
	if (!text) return undefined;

	let dateFormattedText = formatDate(lang, text);
	let formattedText = formatTime(lang, dateFormattedText);

	return formattedText;
}