/* eslint-disable */
import React, { useEffect, useState } from "react";
import { useDispatch } from "react-redux";
import "./App.scss";
import Header from "./Components/Header";
import Layout from "./Components/Layout";
import Menu from "./Components/Menu";
import { useActions } from "./hooks/use-actions";
import { actionCreators } from "./state";

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
