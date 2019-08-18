import React from 'react';
import {
  StyleSheet,
  Dimensions,
  Text, View,
  FlatList,
  TouchableOpacity
      } from 'react-native';
import firebase from 'react-native-firebase';
import Registro from './src/components/registro'
import {fetchData} from './src/api/firebaseData'

export default class App extends React.Component {
  constructor() {
    super();
    this.state = {
      data: [],
      id: null,
      level: null,
      situation: null,
      estimateTime: null,
    }
  }

  async componentDidMount() {
    this.interval = setInterval(() => this.updateData(), 1000)
  }

  componentWillUnmount() {
    clearInterval(this.interval)
  }
  

  updateData = () => {
    firebase.app()

    let ref = firebase.database().ref('registry')
    ref.once('value').then(snapshot => {
    console.log(snapshot.val())

      let items = []
      snapshot.forEach((child) => {
        items.push({
          id: child.key,
          level: child.val().level,
          situation: child.val().situation,
          estimateTime: child.val().estimateTime,

        })
      })
    this.setState({
      data: items
    })
    })
  }

  attMain = (e) => {
    this.setState({
      id: e.id,
      level: e.level,
      situation: e.situation,
      estimateTime: e.estimateTime  
    })
  }

  render() {

    const data = this.state.data.reverse()
    //console.log(users)

    return (
      <View style = {styles.container}>
        <View style = {styles.title}>
          <Text style = {styles.titleText}>Bafômetro</Text>
        </View>
        <View style = {styles.top}>
          <Text style = {styles.text}>Id:
            {this.state.id}</Text>
          <Text style = {styles.text}>Nível de Álcool:
            {this.state.level}</Text>
          <Text style = {styles.text}>Situação: 
            {this.state.situation}</Text>
          <Text style = {styles.text}>
            Tempo estimado: {this.state.estimateTime}
          </Text>
        </View>
        <View style = {styles.body}>
          <FlatList   
            data={data}
            showsVerticalScrollIndicator={false}
            keyExtractor={(item, index) => item.id}
            renderItem={({item}) =>
            <TouchableOpacity onPress = {() => this.attMain(item)}>
              <Registro level = {item.level} situation = {item.situation}
                        time = {item.estimateTime} id = {item.id}/>
            </TouchableOpacity>
            }/>
          
        </View>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#455a64',
    alignItems: 'center',
  },
  title: {
    width: '100%',
    height: 50,
    justifyContent: 'center',
    alignItems: 'center',
  },
  titleText: {
    fontSize: 35,
    color: 'white',
  },
  text: {
    color: '#212121',
    fontSize: 30,
    fontWeight: 'bold'
  },
  top: {
    flex: 2,
    backgroundColor: '#FFFFFF',
    borderRadius: 10,
    width: Dimensions.get("window").width - 30,    
    margin: 15,
    marginBottom: 15,
    paddingLeft: 5,
    paddingTop: 5,
    justifyContent: 'space-between'
  },
  body: {
    flex: 5,
    backgroundColor: '#FFFFFF',
    borderRadius: 10,
    width: Dimensions.get("window").width - 30,    
    margin: 15,
    marginTop: 0,
  },
});
