import React, { useEffect, useState } from "react";
import { HiPencil } from "react-icons/hi";

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
const AddMaterial: React.FC<MaterialProps> = ({
  id,
  name,
  img,
  properties,

  chooseMaterial,
  choosen,
}) => {
  const [style, setStyle] = useState("material");
  const [showButton, setShowButton] = useState(false);
  useEffect(() => {
    if (choosen === id) {
      setStyle("materialClicked");
    } else setStyle("material");
  }, [choosen]);

  const clickHandle = () => {
    setShowButton(true);
  };

  return (
    <div onClick={() => chooseMaterial(id)} className={style}>
      <img className="material__img" src={img}></img>
      <div className="material__info__name">
        <h3>{name}</h3>
      </div>
      <div className="material__details">
        <h4>Details:</h4>
        <p className="material__details properties">
          <span className="properties__item">
            <p>
              Heat transfer coefficient: {properties.heatTransferCoefficient}
              <HiPencil
                onClick={() => clickHandle()}
                className="properties__item__icon"
              />
            </p>
          </span>
          <span className="properties__item">
            <p>
              Specific heat: {properties.heatTransferCoefficient}
              <HiPencil className="properties__item__icon" />
            </p>
          </span>
          <span className="properties__item">
            <p>
              Density: {properties.density}
              <HiPencil className="properties__item__icon" />
            </p>
          </span>
          <span className="properties__item">
            <p>
              Thermal conductivity: {properties.thermalConductivity}
              <HiPencil className="properties__item__icon" />
            </p>
          </span>
        </p>
      </div>
      {showButton && <button className={`${style}__button`}>CONFIRM</button>}
    </div>
  );
};

export default AddMaterial;
