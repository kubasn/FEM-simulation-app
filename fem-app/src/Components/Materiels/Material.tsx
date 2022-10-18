import React from "react";

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
}

const Material: React.FC<MaterialProps> = ({ id, name, img, properties }) => {
  let image = img;
  console.log(name);

  return (
    <div className="material">
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
