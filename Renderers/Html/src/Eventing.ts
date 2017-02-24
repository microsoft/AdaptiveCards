/*
Strongly typed events from https://keestalkstech.com/2016/03/strongly-typed-event-handlers-in-typescript-part-1/
*/
export interface IEvent<TSender> {
    subscribe(fn: (sender: TSender, args: any) => void): void;
    unsubscribe(fn: (sender: TSender, args: any) => void): void;
}

export class EventDispatcher<TSender> implements IEvent<TSender> {
    private _subscriptions: Array<(sender: TSender, args: any) => void> = new Array<(sender: TSender, args: any) => void>();

    subscribe(fn: (sender: TSender, args: any) => void): void {
        if (fn) {
            this._subscriptions.push(fn);
        }
    }

    unsubscribe(fn: (sender: TSender, args: any) => void): void {
        let i = this._subscriptions.indexOf(fn);
        if (i > -1) {
            this._subscriptions.splice(i, 1);
        }
    }

    dispatch(sender: TSender, args: any): void {
        for (let handler of this._subscriptions) {
            handler(sender, args);
        }
    }
}