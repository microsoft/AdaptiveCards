import React from 'react';
import {
    View,
    Text,
    StyleSheet,
    TouchableOpacity
} from 'react-native';

export default class SegmentedControl extends React.Component {

    constructor(props) {
        super(props);
        this.state = {
            activeIndex: props.activeIndex || 0
        }
    }

    render() {

        const { items } = this.props;

        return (
            <View style={styles.container}>
                {items.map((item, index) => {

                    const computedControlStyles = [styles.control];
                    const computedTitleStyles = [styles.title];

                    // is active ?
                    if (index === this.state.activeIndex) {
                        computedControlStyles.push(styles.activeControl);
                        computedTitleStyles.push(styles.activeTitle);
                    }

                    // first item
                    if (index === 0) {
                        computedControlStyles.push(styles.firstControl);
                    }
                    // last item
                    if (index === items.length - 1) {
                        computedControlStyles.push(styles.lastControl);
                    }

                    return (
                        <TouchableOpacity activeOpacity={0.4} style={computedControlStyles} onPress={() => this.onStatusDidChange(index)} key={`CONTROL-${index}`}>
                            <Text style={computedTitleStyles}>{item.title}</Text>
                        </TouchableOpacity>)
                })}
            </View>
        )
    }

    onStatusDidChange = (index) => {
        this.setState({
            activeIndex: index
        });
        this.props.onStatusChange(index);
    }
}

const styles = StyleSheet.create({
    container: {
        flexDirection: 'row',
        backgroundColor: '#f9f9f9',
        marginVertical: 10
    },
    control: {
        height: 34,
        backgroundColor: 'white',
        flexGrow: 1,
        justifyContent: 'center',
        alignItems: 'center',
        borderWidth: 1,
        borderRightWidth: 0,
        borderColor: '#0078D7'
    },
    firstControl: {
        borderTopLeftRadius: 5,
        borderBottomLeftRadius: 5
    },
    lastControl: {
        borderTopRightRadius: 5,
        borderBottomRightRadius: 5,
        borderRightWidth: 1
    },
    activeControl: {
        backgroundColor: '#0078D7',
    },
    title: {
        fontSize: 16,
        color: 'black'
    },
    activeTitle: {
        color: 'white'
    }
});
