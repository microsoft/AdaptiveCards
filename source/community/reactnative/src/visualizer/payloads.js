
import AdaptiveCardPayloads from './payloads/payloads';
import OtherCardPayloads from '../../experimental/adaptive-card-builder/payloads';
import DataBindingPayloads from './payloads/data-binding';

// sample scenarios
const calendarReminderPayload = require('./payloads/scenarios/calendar-reminder.json');
const flightUpdatePayload = require('./payloads/scenarios/flight-update.json');
const inputFormPayload = require('./payloads/scenarios/input-form.json');
const restaurantPayload = require('./payloads/scenarios/restaurant.json');
const containerPayload = require('./payloads/scenarios/container-item.json');
const weatherPayload = require('./payloads/scenarios/weather-large.json');
const activityUpdatePayload = require('./payloads/scenarios/activity-update.json');
const foodOrderPayload = require('./payloads/scenarios/food-order.json');
const imageGalleryPayload = require('./payloads/scenarios/image-gallery.json');
const sportingEventPayload = require('./payloads/scenarios/sporting-event.json');
const mediaPayload = require('./payloads/scenarios/media.json');
const markdownPayload = require('./payloads/scenarios/markdown.json');

/**
 * @description Return the unique element types present in the given payload json
 * @param {object} json - payload json
 * @return {Array} - Array of element types
*/
const getTags = (json) => {
    let tags = new Set();
    // elements
    json.body.map(element => {
        tags.add(element.type);
    });
    // actions
    if (json.actions && json.actions.length > 0) {
        tags.add("Actions");
    }
    return Array.from(tags);
}

const AdaptiveCardScenarios = [{
    title: 'Calendar reminder',
    json: calendarReminderPayload,
    tags: getTags(calendarReminderPayload),
    icon: require('./assets/calendar.png')
}, {
    title: 'Flight update',
    json: flightUpdatePayload,
    tags: getTags(flightUpdatePayload),
    icon: require('./assets/flight.png')
}, {
    title: 'Weather Large',
    json: weatherPayload,
    tags: getTags(weatherPayload),
    icon: require('./assets/cloud.png')
}, {
    title: 'Activity Update',
    json: activityUpdatePayload,
    tags: getTags(activityUpdatePayload),
    icon: require('./assets/done.png')
},
{
    title: 'Food order',
    json: foodOrderPayload,
    tags: getTags(foodOrderPayload),
    icon: require('./assets/fastfood.png')
},
{
    title: 'Image gallery',
    json: imageGalleryPayload,
    tags: getTags(imageGalleryPayload),
    icon: require('./assets/photo_library.png')
},
{
    title: 'Sporting event',
    json: sportingEventPayload,
    tags: getTags(sportingEventPayload),
    icon: require('./assets/run.png')
}, {
    title: 'Restaurant',
    json: restaurantPayload,
    tags: getTags(restaurantPayload),
    icon: require('./assets/restaurant.png')
},
{
    title: 'Input form',
    json: inputFormPayload,
    tags: getTags(inputFormPayload),
    icon: require('./assets/form.png')
},
{
    title: 'Media',
    json: mediaPayload,
    tags: getTags(mediaPayload),
    icon: require('./assets/video_library.png')
},
{
    title: 'Stock Update',
    json: containerPayload,
    tags: getTags(containerPayload),
    icon: require('./assets/square.png')
},
{
    title: 'Markdown',
    json: markdownPayload,
    tags: getTags(markdownPayload),
    icon: require('./assets/code.png')
}];


export { AdaptiveCardPayloads, AdaptiveCardScenarios, OtherCardPayloads, DataBindingPayloads };




