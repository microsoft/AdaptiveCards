import * as AAF from "adaptivecards-aaf";
import * as Shared from "./shared";

export class LocalChannelAdapter extends AAF.ChannelAdapter {
    async sendRequestAsync(request: AAF.ActivityRequest): Promise<AAF.ActivityResponse> {
        return new Promise<AAF.ActivityResponse>(
            (resolve, reject) => {
                switch (request.activity.value.action.verb) {
                    case "succeedReturnCard":
                        window.setTimeout(
                            () => {
                                resolve(
                                    {
                                        request: request,
                                        status: request.attemptNumber == 2 ? AAF.ActivityStatus.Success : AAF.ActivityStatus.Failure,
                                        content: request.attemptNumber == 2 ? JSON.stringify(Shared.sampleRefreshCard) : undefined
                                    });
                            },
                            3000);
                        break;
                    case "succeedReturnString":
                        resolve(
                            {
                                request: request,
                                status: AAF.ActivityStatus.Success,
                                content: "It worked!"
                            });
                        break;
                    case "fail":
                        resolve(
                            {
                                request: request,
                                status: AAF.ActivityStatus.Failure,
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
