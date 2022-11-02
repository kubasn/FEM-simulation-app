import React, { useState, useEffect } from "react";
import backendItems from "../backend";
import { useActions } from "../hooks/use-actions";
import { useTypedSelector } from "../hooks/use-typed-selector";
import Materials from "./Materials/Materials";
import Results from "./Results";

const Menu: React.FC = () => {
  const [choosen, setChoosen] = useState<string>("");
  const [showResults, setShowResults] = useState(false);
  // const [results, setResults] = useState<number[][]>();
  // const { setTemperatures } = useActions();
  // const data = useTypedSelector(({ temperatures }) => temperatures);

  const clickHandle = (e: React.MouseEvent<HTMLButtonElement>) => {
    e.preventDefault();
    // console.log(choosen);
    // const item = backendItems.filter((item) => choosen === item.id)[0];
    // console.log(item);
    setShowResults(true);
    // try {
    //   ;
    //   setShowResults(true);
    // } catch (err) {
    //   console.log(err);
    // }
  };

  // useEffect(() => {
  //   console.log(data.loading);
  // }, [setTemperatures, data.loading]);

  return (
    <div>
      <div className="menu">
        <h2>Choose a material </h2>
        <Materials setChoosen={setChoosen} choosen={choosen} />
      </div>
      <button
        type="button"
        disabled={choosen ? false : true}
        onClick={clickHandle}
        className="menu__button"
      >
        START
      </button>
      {showResults && <Results choosen={choosen} />}
    </div>
  );
};

export default Menu;
