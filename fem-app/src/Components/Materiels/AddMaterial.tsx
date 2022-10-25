import React, { useEffect, useState } from "react";
import { HiPencil } from "react-icons/hi";
import Input from "./Input";

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
  const [materialProperties, setMaterialProperties] = useState(properties);
  useEffect(() => {
    if (choosen === id) {
      setStyle("materialClicked");
    } else setStyle("material");
  }, [choosen]);

  const clickHandle = () => {};

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
              <Input
                clickHandle={clickHandle}
                label=" Heat transfer coefficient: "
                property={materialProperties.heatTransferCoefficient}
              />
            </p>
          </span>
          <span className="properties__item">
            <p>
              <Input
                clickHandle={clickHandle}
                label="Specific heat: "
                property={materialProperties.specificHeat}
              />
            </p>
          </span>
          <span className="properties__item">
            <p>
              <Input
                clickHandle={clickHandle}
                label="Density: "
                property={materialProperties.density}
              />
            </p>
          </span>
          <span className="properties__item">
            <p>
              <Input
                clickHandle={clickHandle}
                label="Thermal conductivity: "
                property={materialProperties.thermalConductivity}
              />
            </p>
          </span>
        </p>
      </div>
    </div>
  );
};

export default AddMaterial;
