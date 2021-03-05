import * as Adaptive from "adaptivecards";
import { ActivityRequestError, ErrorResponse, SuccessResponse } from "adaptivecards";
import * as Shared from "./shared";

export class LocalChannelAdapter extends Adaptive.ChannelAdapter {
    async sendRequestAsync(request: Adaptive.IActivityRequest): Promise<Adaptive.ActivityResponse> {
        return new Promise<Adaptive.ActivityResponse>(
            (resolve, reject) => {
                switch (request.action.verb) {
                    case "succeedReturnCard":
                        window.setTimeout(
                            () => {
                                resolve(
                                    request.attemptNumber === 2 ?
                                        new SuccessResponse(request, JSON.stringify(Shared.sampleRefreshCard)) :
                                        new ErrorResponse(request, new ActivityRequestError(undefined, "It didn't work :("))
                                );
                            },
                            3000);
                        break;
                    case "succeedReturnString":
                        resolve(new SuccessResponse(request, "It worked!"));
                        break;
                    case "fail":
                        resolve(new ErrorResponse(request, new ActivityRequestError("error", "It failed miserably...")));
                        break;
                    case "exception":
                    default:
                        reject("It didn't work!");
                        break;
                }
            }
        );
    }
}
