import React, { useState } from "react";
import { AiOutlineInfoCircle } from "react-icons/ai";
import { BsFillLightbulbFill } from "react-icons/bs";
import { GiCancel } from "react-icons/gi";
import { programParameters } from "../backend";

interface InfoPanelProps {
  closePanel: () => void;
}

const InfoPanel: React.FC<InfoPanelProps> = ({ closePanel }) => {
  const [parameters, setParameters] = useState(programParameters);
  return (
    <div className="infoPanel">
      <div className="infoPanel__details">
        <h2 className="infoPanel__details__title">
          <BsFillLightbulbFill className="infoPanel__details__icon" /> How
          program works?
        </h2>
        <div style={{ width: "100%" }}>
          <h3 className="infoPanel__details__heading">Program parameters</h3>
          <ul>
            <li>
              <span>Initial temperature: </span>
              <span>{parameters.initialTemperature} &#8451;</span>
            </li>
            <li>
              <span>Simulation time: </span>
              <span>{parameters.simulationTime} s</span>
            </li>
            <li>
              <span>Time step: </span>
              <span>{parameters.timeStep} s</span>
            </li>
            <li>
              <span>Ambient temperature: </span>
              <span>{parameters.ambientTemperature} &#8451;</span>
            </li>
            <li>
              <p>Size of 2D plate:</p>
              <span>H: </span>
              <span>{parameters.size.h} m </span>
              <span>B: </span>
              <span>{parameters.size.b} m</span>
            </li>
          </ul>
          <h3 className="infoPanel__details__heading">Description</h3>
          <p style={{ paddingLeft: "20px" }}>
            Program was created to solve Fourier equation - The equation
            describing heat transfer:
          </p>
          <img
            style={{ margin: " 20px auto", width: "50%", display: "block" }}
            src="./images/equation1.PNG"
          ></img>
        </div>
      </div>
      <GiCancel onClick={() => closePanel()} className="infoPanel__close" />
    </div>
  );
};

export default InfoPanel;
