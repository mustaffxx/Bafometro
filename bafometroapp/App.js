import React from 'react';
import { Button, StyleSheet, Text, View, TextInput, SafeAreaView, FlatList, TouchableOpacity } from 'react-native';
import { createAppContainer } from 'react-navigation';
import { createBottomTabNavigator } from 'react-navigation-tabs'
import Icon from 'react-native-vector-icons/FontAwesome'
import { Dimensions } from 'react-native'
import RNSpeedometer from 'react-native-speedometer'

import {
  LineChart,
} from 'react-native-chart-kit'

class Home extends React.Component {

  state = {
    value: 0,
    status: 0,

  }

  onChange = (value) => this.setState({ value: parseFloat(value) })

  render() {
    const handlePress = () => false
    return (
      
      <View style = {styles.container}>
        <View style = {styles.header}>
          <Text style = {styles.textHeader}>BAFÔMETRO</Text>
        </View>
        <View style = {styles.body}>
          <View style = {styles.status}>
            <Text style = {
              this.state.value > 0.5 ? styles.textStatusBloq : styles.textStatusLib}>
                {this.state.value > 0.5 ? 'Bloqueado' : 'Liberado'}
              </Text>
          </View>
          <SafeAreaView style = {styles.container}>
            <TextInput placeholder="Speedometer Value" style={styles.textInput} onChangeText={this.onChange} />
            <RNSpeedometer value={this.state.value} size={300} 
              minValue = {0.0}
              maxValue = {10.0}
              allowedDecimals = {2}
              labels = {
                [
                  {
                    name: 'OK!',
                    labelColor: '#00ff6b',
                    activeBarColor: '#00ff6b',
                  },
                  {
                    name: 'Um copo!',
                    labelColor: '#14eb6e',
                    activeBarColor: '#14eb6e',
                  },
                  {
                    name: 'Dois copos!',
                    labelColor: '#f2cf1f',
                    activeBarColor: '#f2cf1f',
                  },
                  {
                    name: 'Bêbado!',
                    labelColor: '#f4ab44',
                    activeBarColor: '#f4ab44',
                  },
                  {
                    name: 'Chapado',
                    labelColor: '#ff5400',
                    activeBarColor: '#ff5400',
                  },
                  {
                    name: 'Dopado',
                    labelColor: '#ff2900',
                    activeBarColor: '#ff2900',
                  },
                ]
              }/>
          </SafeAreaView>
          {this.state.value > 0.5 ? 
            <Button title = 'Desbloquear' color = 'red' onPress = {handlePress} />
            :
            <Button title = 'Desbloquear' color = 'gray' disabled = {true} />
            }
        </View>
      </View>
    );
  }
}

class ListItem extends React.Component {

  render() {
      return (
              <View style = {styles.bodyList}>
                  <View style = {styles.subone}>
                      <Text style = {styles.textList}>
                          mg/L: {this.props.level}
                      </Text>
                      <Text style = {styles.textList}>
                          Situação: {this.props.situation}</Text>
                      <Text style = {styles.textList}>
                      Hora: {this.props.hora}
                      </Text>
                  </View>
              </View>
            )
          }
}

class History extends React.Component {

  render() {
    return (
      <View style = {styles.container}>
        <View style = {styles.header}>
          <Text style = {styles.textHeader}>BAFÔMETRO</Text>
        </View>
        <View style = {styles.body}>
          <LineChart
            data={{
              labels: ['0', '1', '2', '3', '4', '5'],
              datasets: [{
                data: [
                  0.1,
                  0.4,
                  0.2,
                  0.9,
                  0.4,
                  1.0
                ]
              }]
            }}
            width={Dimensions.get('window').width} // from react-native
            height={220}
            //yAxisLabel={'mg/L'}
            chartConfig={{
              //backgroundColor: '#e26a00',
              backgroundGradientFrom: 'white',
              backgroundGradientTo: 'white',
              decimalPlaces: 2, // optional, defaults to 2dp
              color: (opacity = 1) => `rgba(65, 90, 255, ${opacity})`,
              style: {
                borderRadius: 16
              }
            }}
            bezier
            style={{
              marginVertical: 8,
              borderRadius: 16,
              alignItems: 'center'
            }}
          />
          <FlatList   
            data={[
              {
                level: 0.1,
                situation: 'Liberado',
                hora: '01h01'
              },
              {
                level: 0.4,
                situation: 'Liberado',
                hora: '01h02'
              },
              {
                level: 0.2,
                situation: 'Liberado',
                hora: '01h03'
              },
              {
                level: 0.5,
                situation: 'Liberado',
                hora: '01h03'
              },
              {
                level: 0.1,
                situation: 'Bloqueado',
                hora: '01h03'
              },
              {
                level: 0.4,
                situation: 'Bloqueado',
                hora: '01h03'
              },
              {
                level: 0.2,
                situation: 'Bloqueado',
                hora: '01h03'
              },
              {
                level: 0.9,
                situation: 'Bloqueado',
                hora: '01h03'
              },
              {
                level: 0.4,
                situation: 'Bloqueado',
                hora: '01h03'
              },
              {
                level: 1.0,
                situation: 'Bloqueado',
                hora: '01h03'
              },
            ].reverse()}
            showsVerticalScrollIndicator={false}
            keyExtractor={(item, index) => index.toString()}
            renderItem={({item}) =>
            <TouchableOpacity onPress = {() => {}}>
              <ListItem level = {item.level} situation = {item.situation}
                        hora = {item.hora}/>
            </TouchableOpacity>
            }/>


        </View>
      </View>
    )
  }
}


export default createAppContainer(createBottomTabNavigator(
  {
    Home: { screen: Home,
    navigationOptions:{
      tabBarLabel: 'Home',
      tabBarIcon: ({tintColor}) => (
        <Icon name = "home" color = {tintColor} size = {24}/>
      )
    } },
    History: { screen: History,
      navigationOptions:{
        tabBarLabel: 'List',
        tabBarIcon: ({tintColor}) => (
          <Icon name = "line-chart" color = {tintColor} size = {24}/>
        )
      } },
  }, {
    tabBarOptions: {
      activeTintColor: 'white',
      inactiveTintColor: 'grey',
      style: {
        backgroundColor: '#415AFF',
        
      }
    }
  }
));

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: 'white',
  },
  header: {
    flex: 1,
    backgroundColor: '#415AFF',
    alignItems: 'center',
    justifyContent: 'center'
  },
  textHeader: {
    color: 'white',
    fontSize: 30,
  },
  body: {
    flex: 12,
  },
  textInput: {
    color: 'black',
    borderBottomWidth: 0.3,
    borderBottomColor: 'black',
    height: 25,
    fontSize: 16,
    marginVertical: 50,
    marginHorizontal: 20,
  },
  bodyList: {
    width: '98%',
    height: 30,
    borderBottomWidth: 1,
    borderBottomColor: '#415AFF',
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
  textList: {
      color: '#212121',
      fontSize: 15,
  },
  status: {
    width: '100%',
    height: 60,
    justifyContent: 'center',
    alignItems: 'center',
    },
    textStatusLib: {
      fontSize: 40,
      color: '#00ff6b'
    },
    textStatusBloq: {
      fontSize: 40,
      color: '#ff2900'
    }
})