
import { Breadcrumb, IBreadcrumbItem } from 'office-ui-fabric-react/lib/Breadcrumb';
import * as React from "react";

export const getBreadCrumbElement = (items: string, fontSize: string, fontWeight: string, color: string, customActionHandler: (item: IBreadcrumbItem) => void): JSX.Element => {
    const breadcrumbItems = JSON.parse(items) as IBreadcrumbItem[];
    const breadcrumbStyles = {
        root: {  selectors: { 'li > .ms-Breadcrumb-itemLink': { fontSize: fontSize + " !important", fontWeight: fontWeight + " !important", color: color + " !important"} } },
    };
    breadcrumbItems.forEach(item => {
        item.onClick = (ev?: React.MouseEvent<HTMLElement>, item?: IBreadcrumbItem) => {
            return customActionHandler(item)
        }
    })
    return (
        <Breadcrumb items={breadcrumbItems}
                    styles={breadcrumbStyles}/>
    );
}