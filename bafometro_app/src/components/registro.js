import React, {Component} from 'react'
import {View, Text, StyleSheet, TouchableOpacity} from 'react-native'

export default class Registro extends Component {


    render() {
        return (
            
                <View style = {styles.body}>
                    <View style = {styles.subone}>
                        <Text style = {styles.textId}>
                            id: {this.props.id}
                        </Text>
                        <Text style = {styles.text}>
                            Nível de Álcool: {this.props.level}</Text>
                        <Text style = {styles.text}>
                            Situação: {this.props.situation}
                        </Text>
                    </View>
                    <View style = {styles.subtwo}>
                        <Text style = {styles.text}>
                            Tempo estimado: {this.props.time}
                        </Text>
                        
                    </View>
                </View>
            
        )
    }
}

const styles = StyleSheet.create({
    body: {
        width: '98%',
        height: 70,
        borderBottomWidth: 1,
        borderBottomColor: 'black',
        justifyContent: 'center',
        marginLeft: 5,
        marginRight: 5,
    },
    subone: {
        flex: 1,
        flexDirection: 'row',
        justifyContent: 'space-between'
    },
    subtwo: {
        flex: 1,
        alignItems: 'center',
    },
    text: {
        color: '#757575',
        fontSize: 20,
    },
    textId: {
        color: '#757575',
        fontSize: 10,
    }
})