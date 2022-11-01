import React from "react";
import Materials from "./Materiels/Materials";

const Menu: React.FC = () => {
  return (
    <div className="menu">
      <h2>Choose a material </h2>
      <Materials />
    </div>
  );
};

export default Menu;
