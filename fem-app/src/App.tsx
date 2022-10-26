/* eslint-disable */
import React, { useEffect, useState } from "react";
import "./App.scss";
import Header from "./Components/Header";
import Layout from "./Components/Layout";
import Materials from "./Components/Materiels/Materials";
import Menu from "./Components/Menu";
import createModule from "./fem.js";

const App: React.FC = () => {
  // const [Module, setModule] = useState();
  const header = <Header />;
  const menu = <Menu />;
  useEffect(() => {
    console.log(createModule());
    // createModule().then((module: any) => {
    //   console.log(module._solve());
    // });
  }, []);

  return (
    <div className="App">
      <Layout header={header} menu={menu} />
    </div>
  );
};

export default App;
