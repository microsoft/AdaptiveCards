import React from 'react';
import {
    TouchableOpacity,
    View,
    Text,
    Image,
    StyleSheet
} from 'react-native';

export class PayloadItem extends React.Component {

    render() {
        const { item, onItemSelection, index } = this.props;
        let icon = null;
        // icon
        if (item.icon) {
            icon = <Image source={item.icon} />
        }

        return (
            <TouchableOpacity
                style={[styles.item, this.getBackgroundColor(index)]}
                activeOpacity={0.5}
                onPress={onItemSelection}>
                {icon}
                <View style={styles.details}>
                    <Text style={styles.title}>{item.title.toUpperCase()}</Text>
                    {item.tags && item.tags.length > 0 ? (
                        <View style={styles.tags}>
                            {
                                item.tags.map((tag, index) => (
                                    <Text style={styles.tag} key={index}>{tag}</Text>
                                ))
                            }
                        </View>
                    ) : null}

                </View>
            </TouchableOpacity>
        )
    }

    getBackgroundColor = (index) => {
        const bgColor = backgroundColors[index % backgroundColors.length];
        return { backgroundColor: bgColor }
    }
}

// item bg colors
const backgroundColors = [
    "#53BA94",
    "#6E85CA",
    "#C78D4D",
    "#A566C4",
    "#BA5C96",
];

const styles = StyleSheet.create({
    item: {
        padding: 12,
        flexDirection: 'row',
        borderRadius: 5,
        marginBottom: 10,
        flex: 1
    },
    details: {
        marginLeft: 12,
        flex: 1,
    },
    title: {
        fontSize: 18,
        color: 'white',
    },
    tags: {
        flexDirection: 'row',
        flexWrap: 'wrap',
        marginLeft: -5,
        marginTop: 6
    },
    tag: {
        borderRadius: 10,
        borderWidth: 1,
        borderColor: 'white',
        paddingVertical: 2,
        paddingHorizontal: 6,
        overflow: 'hidden',
        margin: 5,
        fontSize: 13,
        color: 'white',
    }
});