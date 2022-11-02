import React, { useState, useEffect } from "react";
import backendItems from "../backend";
import { useActions } from "../hooks/use-actions";
import { useTypedSelector } from "../hooks/use-typed-selector";
import Materials from "./Materials/Materials";
import Results from "./Results";

const Menu: React.FC = () => {
  const [choosen, setChoosen] = useState<string>("");
  const [showResults, setShowResults] = useState(false);

  const clickHandle = (e: React.MouseEvent<HTMLButtonElement>) => {
    e.preventDefault();
    console.log(choosen);
    setShowResults(true);
  };

  return (
    <div className="main">
      <div className="main__menu">
        <h2>Choose a material </h2>
        <Materials setChoosen={setChoosen} choosen={choosen} />
      </div>
      <button
        type="button"
        disabled={choosen ? false : true}
        onClick={clickHandle}
        className="main__button"
      >
        START
      </button>
      {showResults && <Results choosen={choosen} />}
    </div>
  );
};

export default Menu;
