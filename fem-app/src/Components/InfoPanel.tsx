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
        <div>
          <h3 className="infoPanel__details__heading">Program parameters</h3>
          <ul>
            <li>
              <span>Initial temperature: </span>
              <span>{parameters.initialTemperature}</span>
            </li>
            <li>
              <span>Simulation time: </span>
              <span>{parameters.simulationTime}</span>
            </li>
            <li>
              <span>Time step: </span>
              <span>{parameters.timeStep}</span>
            </li>
            <li>
              <span>Ambient temperature: </span>
              <span>{parameters.ambientTemperature}</span>
            </li>
            <li>
              <p>Size:</p>
              <span>H: </span>
              <span>{parameters.size.h} </span>
              <span>B: </span>
              <span>{parameters.size.b}</span>
            </li>
          </ul>
        </div>
      </div>
      <GiCancel onClick={() => closePanel()} className="infoPanel__close" />
    </div>
  );
};

export default InfoPanel;
