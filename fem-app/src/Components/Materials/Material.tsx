import React, { useEffect, useState } from "react";

interface MaterialProps {
  id: string;
  name: string;
  img: string;
  properties: {
    heatTransferCoefficient: number;
    specificHeat: number;
    density: number;
    thermalConductivity: number;
  };
  chooseMaterial: (
    id: string,
    properties: {
      heatTransferCoefficient: number;
      specificHeat: number;
      density: number;
      thermalConductivity: number;
    }
  ) => void;
  choosen: string;
}
// "#f29f05"
const Material: React.FC<MaterialProps> = ({
  id,
  name,
  img,
  properties,

  chooseMaterial,
  choosen,
}) => {
  const [style, setStyle] = useState("material");

  useEffect(() => {
    if (choosen === id) {
      setStyle("materialClicked");
    } else setStyle("material");
  }, [choosen]);

  return (
    <div onClick={() => chooseMaterial(id, properties)} className={style}>
      <img className="material__img" src={img}></img>
      <div className="material__info__name">
        <h3>{name}</h3>
      </div>
      <div className="material__details">
        <h4>Details:</h4>
        <p className="material__details properties">
          <span>
            <p>
              Heat transfer coefficient: {properties.heatTransferCoefficient}
            </p>
          </span>
          <span>
            <p>Specific heat: {properties.specificHeat}</p>
          </span>
          <span>
            <p>Density: {properties.density}</p>
          </span>
          <span>
            <p>Thermal conductivity: {properties.thermalConductivity}</p>
          </span>
        </p>
      </div>
    </div>
  );
};

export default Material;
