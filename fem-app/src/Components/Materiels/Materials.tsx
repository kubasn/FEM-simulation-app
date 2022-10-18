import React from "react";
import backendItems from "../../backend";
import Material from "./Material";
import {
  BsFillArrowLeftCircleFill,
  BsFillArrowRightCircleFill,
} from "react-icons/bs";

const Materials: React.FC = () => {
  return (
    <div className="materials">
      <BsFillArrowLeftCircleFill className="materials__icons" />

      {backendItems.map((item) => (
        <Material {...item} />
      ))}
      <BsFillArrowRightCircleFill className="materials__icons" />
    </div>
  );
};

export default Materials;
