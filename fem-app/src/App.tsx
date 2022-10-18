import React from "react";
import "./App.scss";
import Header from "./Components/Header";
import Layout from "./Components/Layout";
import Materials from "./Components/Materiels/Materials";
import Menu from "./Components/Menu";

const App: React.FC = () => {
  const header = <Header />;
  const menu = <Menu />;
  const materials = <Materials />;

  return (
    <div className="App">
      <Layout header={header} menu={menu} materials={materials} />
    </div>
  );
};

export default App;
