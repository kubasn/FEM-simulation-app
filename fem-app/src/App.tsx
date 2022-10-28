/* eslint-disable */
import React, { useEffect, useState } from "react";
import "./App.scss";
import Header from "./Components/Header";
import Layout from "./Components/Layout";
import Materials from "./Components/Materiels/Materials";
import Menu from "./Components/Menu";
import createModule from "./fem.mjs";
// @ts-ignore

const App: React.FC = () => {
  // const [Module, setModule] = useState();
  const header = <Header />;
  const menu = <Menu />;
  useEffect(() => {
    createModule().then((module: any) => {
      const b = module.solve();

      let tab: any[] = [];
      let newTab: number[] = [];
      let j = 0;
      for (let i = 0; i < b.size(); i++) {
        newTab.push(b.get(i));

        if ((i + 1) % 16 == 0) {
          tab.push(newTab);

          newTab = [];
          j++;
        }
      }
      console.log(tab);
    });
  }, []);

  return (
    <div className="App">
      <Layout header={header} menu={menu} />
    </div>
  );
};

export default App;
