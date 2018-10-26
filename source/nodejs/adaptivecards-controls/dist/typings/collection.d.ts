export declare class Collection<TItem> {
    private _items;
    onItemAdded: (item: TItem) => void;
    onItemRemoved: (item: TItem) => void;
    get(index: number): TItem;
    add(item: TItem): void;
    remove(item: TItem): void;
    indexOf(item: TItem): number;
    readonly length: number;
}
