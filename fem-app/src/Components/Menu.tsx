import React from "react";
import Materials from "./Materiels/Materials";

const Menu: React.FC = () => {
  return (
    <div className="menu">
      <h2>Choose a material </h2>
      <Materials />
      <button className="menu__button">START</button>
    </div>
  );
};

export default Menu;
