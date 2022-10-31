/* eslint-disable */
import React, { useEffect, useState } from "react";
import { useDispatch } from "react-redux";
import "./App.scss";
import Header from "./Components/Header";
import Layout from "./Components/Layout";
import Menu from "./Components/Menu";
import { setTemperatures } from "./state/actions";
// @ts-ignore

const App: React.FC = () => {
  // const [Module, setModule] = useState();
  const header = <Header />;
  const menu = <Menu />;
  useEffect(() => {
    const dispatch = useDispatch();
    dispatch(setTemperatures);
  }, []);

  return (
    <div className="App">
      <Layout header={header} menu={menu} />
    </div>
  );
};

export default App;
