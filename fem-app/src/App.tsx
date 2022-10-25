/* eslint-disable */
import React, { useEffect, useState } from "react";
import "./App.scss";
import Header from "./Components/Header";
import Layout from "./Components/Layout";
import Materials from "./Components/Materiels/Materials";
import Menu from "./Components/Menu";
import createModule from "./fem.mjs";

const App: React.FC = () => {
  const [Module, setModule] = useState(false);
  const header = <Header />;
  const menu = <Menu />;
  const materials = <Materials />;
  useEffect(() => {
    createModule().then((Module: any) => {
      setModule(Module);

      console.log(Module);
      // console.log(Module);
    });
  }, []);

  return (
    <div className="App">
      <Layout header={header} menu={menu} />
    </div>
  );
};

export default App;
