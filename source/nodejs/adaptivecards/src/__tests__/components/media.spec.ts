import { AdaptiveCard } from "../../card-elements";
import { Media } from "../../card-elements";
declare function expect(thing: any): any;
declare function test(description: string, test: () => void);

test('media element should be correctly parsed', () => {
    let card_with_media_element = {
        "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
        "type": "AdaptiveCard",
        "version": "1.0",
        "body": [
            {
                "type": "Media",
                "poster": "http://adaptivecards.io/content/cats/1.png",
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
    let ac = new AdaptiveCard();
    ac.parse(card_with_media_element);
    expect(ac.getItemCount()).toBe(1);

    let element = ac.getItemAt(0);
    expect(element.getJsonTypeName()).toBe("Media");

    expect(element).toBeInstanceOf(Media);
    let media_element = <Media>element;

    expect(media_element.poster).toBe("http://adaptivecards.io/content/cats/1.png");
    expect(media_element.altText).toBe("This is a video");

    var sources = media_element.sources;
    expect(sources.length).toBe(2);
    expect(sources[0].mimeType).toBe("video/mp4");
    expect(sources[0].url).toBe("http://source1.mp4");
    expect(sources[1].mimeType).toBe("video/avi");
    expect(sources[1].url).toBe("http://source2.avi");

})

test('media element should render expected HTML elements', () => {
    const mp4_url = "https://github.com/mediaelement/mediaelement-files/blob/master/big_buck_bunny.mp4?raw=true";
    const mp3_url = "https://github.com/mediaelement/mediaelement-files/blob/master/AirReview-Landmarks-02-ChasingCorporate.mp3?raw=true";
    const card_with_media_element = {
        "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
        "type": "AdaptiveCard",
        "version": "1.0",
        "body": [
            {
                "type": "Media",
                "poster": "http://adaptivecards.io/content/cats/1.png",
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

    let ac = new AdaptiveCard();
    ac.parse(card_with_media_element);
    let element = ac.render();
    expect(element.innerHTML).toContain("<video");
    let video_element = element.querySelector("video");
    expect(video_element).toBeInstanceOf(HTMLVideoElement);
    let sources = video_element.querySelectorAll("source");
    expect(sources.length).toBe(1);
})