import React, { useEffect, useState } from "react";
import { useActions } from "../../hooks/use-actions";
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
  const { setParams } = useActions();

  useEffect(() => {
    if (choosen === id) {
      setStyle("materialClicked");
    } else setStyle("material");
  }, [choosen]);

  const changeHandler = (id: string, value: number) => {
    setMaterialProperties({ ...materialProperties, [id]: value });
    //
  };

  const clickHandle = () => {
    setParams(materialProperties);
  };

  return (
    <div
      onClick={() => chooseMaterial("unknown", materialProperties)}
      className={style}
    >
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
                changeHandler={changeHandler}
                label=" Heat transfer coefficient: "
                id="heatTransferCoefficient"
                property={materialProperties.heatTransferCoefficient}
              />
            </p>
          </span>
          <span className="properties__item">
            <p>
              <Input
                changeHandler={changeHandler}
                label="Specific heat: "
                id="specificHeat"
                property={materialProperties.specificHeat}
              />
            </p>
          </span>
          <span className="properties__item">
            <p>
              <Input
                changeHandler={changeHandler}
                label="Density: "
                id="density"
                property={materialProperties.density}
              />
            </p>
          </span>
          <span className="properties__item">
            <p>
              <Input
                changeHandler={changeHandler}
                id="thermalConductivity"
                label="Thermal conductivity: "
                property={materialProperties.thermalConductivity}
              />
            </p>
          </span>
        </p>
        <button className="material__button" onClick={clickHandle}>
          SAVE
        </button>
      </div>
    </div>
  );
};

export default AddMaterial;
