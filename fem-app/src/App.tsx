/* eslint-disable */
import React, { useEffect } from "react";
import "./App.scss";
import Header from "./Components/Header";
import Layout from "./Components/Layout";
import Menu from "./Components/Menu";

// @ts-ignore

const App: React.FC = () => {
  const header = <Header />;
  const menu = <Menu />;

  return (
    <div className="App">
      <Layout header={header} menu={menu} />
    </div>
  );
};

export default App;
