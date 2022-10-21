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
  chooseMaterial: (id: string) => void;
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
    <div onClick={() => chooseMaterial(id)} className={style}>
      <img className="material__img" src={img}></img>
      <div className="material__info__name">
        <h3>{name}</h3>
      </div>
      <div className="material__details">
        <h4>Details:</h4>
        <p className="material__details__properties">
          Heat transfer coefficient: {properties.heatTransferCoefficient} <br />
          Specific heat: {properties.heatTransferCoefficient} <br />
          Density: {properties.density} <br />
          Thermal conductivity: {properties.thermalConductivity} <br />
        </p>
      </div>
    </div>
  );
};

export default Material;
