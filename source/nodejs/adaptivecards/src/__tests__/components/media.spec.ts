import { AdaptiveCard } from "../../card-elements";
import { Media } from "../../card-elements";

declare function expect(thing: any): any;
declare namespace expect {
	function anything(): any;
};
declare function test(description: string, test: () => void);

const mp4_url = "https://github.com/mediaelement/mediaelement-files/blob/master/big_buck_bunny.mp4?raw=true";
const mp3_url = "https://github.com/mediaelement/mediaelement-files/blob/master/AirReview-Landmarks-02-ChasingCorporate.mp3?raw=true";
const pdf_url = "https://news.microsoft.com/uploads/2017/05/Build-2017-Harry-Shum-transcript.pdf";
const cat_url = "http://adaptivecards.io/content/cats/1.png";

const card_audio_video = {
	"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	"type": "AdaptiveCard",
	"version": "1.0",
	"body": [
		{
			"type": "Media",
			"poster": cat_url,
			"altText": "This is a video",
			"sources": [
				{
					"mimeType": "audio/mp3",
					"url": mp3_url
				},
				{
					"mimeType": "video/mp4",
					"url": mp4_url
				}
			]
		}
	]
};

const card_mp4_avi = {
	"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	"type": "AdaptiveCard",
	"version": "1.0",
	"body": [
		{
			"type": "Media",
			"poster": cat_url,
			"altText": "This is a video",
			"sources": [
				{
					"mimeType": "video/mp4",
					"url": "http://source1.mp4"
				},
				{
					"mimeType": "video/avi",
					"url": "http://source2.avi"
				}
			]
		}
	]
};

const card_video_audio = {
	"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	"type": "AdaptiveCard",
	"version": "1.0",
	"body": [
		{
			"type": "Media",
			"poster": cat_url,
			"altText": "This is a video",
			"sources": [
				{
					"mimeType": "video/mp4",
					"url": mp4_url
				},
				{
					"mimeType": "audio/mp3",
					"url": mp3_url
				}
			]
		}
	]
};

const card_pdf = {
	"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	"type": "AdaptiveCard",
	"version": "1.0",
	"body": [
		{
			"type": "Media",
			"poster": cat_url,
			"altText": "This is pdf",
			"sources": [
				{
					"mimeType": "application/pdf",
					"url": pdf_url
				}
			]
		}
	]
};

test('media element should be correctly parsed', () => {

    let ac = new AdaptiveCard();
    ac.parse(card_mp4_avi);
    expect(ac.getItemCount()).toBe(1);

    let element = ac.getItemAt(0);
    expect(element.getJsonTypeName()).toBe("Media");

    expect(element).toBeInstanceOf(Media);
    let media_element = <Media>element;

    expect(media_element.poster).toBe(cat_url);
    expect(media_element.altText).toBe("This is a video");

    var sources = media_element.sources;
    expect(sources.length).toBe(2);
    expect(sources[0].mimeType).toBe("video/mp4");
    expect(sources[0].url).toBe("http://source1.mp4");
    expect(sources[1].mimeType).toBe("video/avi");
    expect(sources[1].url).toBe("http://source2.avi");

})

test('media element should render video HTML element for video,audio', () => {
    let ac = new AdaptiveCard();
    ac.parse(card_video_audio);
    let element = ac.render();
    expect(element.innerHTML).toContain("<video");
    expect(element.innerHTML).not.toContain("<audio");
    let video_element = element.querySelector("video");
    expect(video_element).toBeInstanceOf(HTMLVideoElement);
    let sources = video_element.querySelectorAll("source");
    expect(sources.length).toBe(1);
	expect(sources[0].src).toBe(mp4_url);
})

test('media element should render audio HTML element for audio,video', () => {
    let ac = new AdaptiveCard();
    ac.parse(card_audio_video);
    let element = ac.render();
    expect(element.innerHTML).toContain("<audio");
    expect(element.innerHTML).not.toContain("<video");
    let audio_element = element.querySelector("audio");
    expect(audio_element).toBeInstanceOf(HTMLAudioElement);
    let sources = audio_element.querySelectorAll("source");
    expect(sources.length).toBe(1);
	expect(sources[0].src).toBe(mp3_url);
})

test('media should render with a visible play button', () => {
    let ac = new AdaptiveCard();
    ac.parse(card_audio_video);
    let element = ac.render();
	let button = <HTMLAnchorElement>element.querySelector("a.play");
	expect(button).toEqual(expect.anything());
	expect(button.style.display).toBe("");
})

test('media should render with an invisible pause button', () => {
    let ac = new AdaptiveCard();
    ac.parse(card_audio_video);
    let element = ac.render();
	let button = <HTMLAnchorElement>element.querySelector("a.pause");
	expect(button).toEqual(expect.anything());
	expect(button.style.display).toBe("none");
})

test('media should render with a reset button', () => {
    let ac = new AdaptiveCard();
    ac.parse(card_audio_video);
    let element = ac.render();
	let button = <HTMLAnchorElement>element.querySelector("a.reset");
	expect(button).toEqual(expect.anything());
})

test('media with invalid sources should render as a poster if poster indicated', () => {
    let ac = new AdaptiveCard();
    ac.parse(card_pdf);
    let element = ac.render();
	let found = false;
	let imgs: HTMLImageElement[] = [];
	element.querySelectorAll("img").forEach(img => {if (img.src === cat_url) imgs.push(img);});
	expect(imgs.length).toBe(1);
})