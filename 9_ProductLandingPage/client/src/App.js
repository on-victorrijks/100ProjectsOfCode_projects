import './App.css';
import React, { Component } from "react";
import Slide from './components/slide';

class App extends Component {

  constructor(props) {
    super(props);
    this.ref_intro = React.createRef();
    this.state = { 
      productInit: '',
    };
  }

  callAPI() {
      fetch("http://localhost:9000/api/product/init")
          .then(res => res.text())
          .then(res => this.setState({ productInit: JSON.parse(res) }));
  }

  componentWillMount() {
      this.callAPI();
  }

  intro = () => {
    window.scrollTo(0, window.innerHeight);
  }

  render() {
    return (
      <div className="App">
        <div className="initContainer">
          {this.state.productInit["name"] !== undefined &&
            <div className="init">
              <h1 className="init-title">{this.state.productInit["name"]}</h1>
              <h3 className="init-description">{this.state.productInit["description"]}</h3>
              <h3 className="init-price">Starting from <b>{this.state.productInit["currency"]+this.state.productInit["price"]}</b></h3>
              <h4 className="init-date">Available on the {this.state.productInit["availableData"][0]+'/'+this.state.productInit["availableData"][1]+'/'+this.state.productInit["availableData"][2]}</h4>
              <button onClick={() => this.intro()}>See more</button>
            </div>
          }
        </div>
        <Slide className="Slide" custom_dataName="introduction"/>
        <Slide  className="Slide" custom_dataName="M1"/>
        <Slide  className="Slide" custom_dataName="M1_Speed"/>
        <Slide  className="Slide" custom_dataName="QuickCards"/>
        <Slide  className="Slide" custom_dataName="Prices"/>
      </div>
    )
  };
  
}

export default App;
