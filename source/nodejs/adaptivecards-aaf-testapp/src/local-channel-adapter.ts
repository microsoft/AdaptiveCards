import * as Adaptive from "adaptivecards";
import * as Shared from "./shared";

export class LocalChannelAdapter extends Adaptive.ChannelAdapter {
    async sendRequestAsync(request: Adaptive.ActivityRequest): Promise<Adaptive.ActivityResponse> {
        return new Promise<Adaptive.ActivityResponse>(
            (resolve, reject) => {
                switch (request.activity.value.action.verb) {
                    case "succeedReturnCard":
                        window.setTimeout(
                            () => {
                                resolve(
                                    {
                                        request: request,
                                        status: request.attemptNumber == 2 ? Adaptive.ActivityStatus.Success : Adaptive.ActivityStatus.Failure,
                                        content: request.attemptNumber == 2 ? JSON.stringify(Shared.sampleRefreshCard) : undefined
                                    });
                            },
                            3000);
                        break;
                    case "succeedReturnString":
                        resolve(
                            {
                                request: request,
                                status: Adaptive.ActivityStatus.Success,
                                content: "It worked!"
                            });
                        break;
                    case "fail":
                        resolve(
                            {
                                request: request,
                                status: Adaptive.ActivityStatus.Failure,
                                content: "It failed miserably..."
                            });
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
