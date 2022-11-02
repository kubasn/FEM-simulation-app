import React from "react";
import backendItems from "../../backend";
import Material from "./Material";

import { Swiper, SwiperSlide } from "swiper/react";

import "../../slider.css";
import "swiper/css";
import "swiper/css/pagination";
import "swiper/css";
import AddMaterial from "./AddMaterial";
import { useActions } from "../../hooks/use-actions";

interface MaterialsProps {
  choosen: string;
  setChoosen: (id: string) => void;
}

const Materials: React.FC<MaterialsProps> = ({ setChoosen, choosen }) => {
  const { setParams } = useActions();
  const chooseMaterial = (
    id: string,
    properties: {
      heatTransferCoefficient: number;
      specificHeat: number;
      density: number;
      thermalConductivity: number;
    }
  ) => {
    let item: any;
    console.log(properties);
    // if (id !== "unknown") {
    //   item = backendItems.find((item) => item.id === id);
    //   setParams({ ...item!.properties });
    // } else {
    setParams({ ...properties });
    // }
    setChoosen(id);
  };

  return (
    <div>
      <div className="materials">
        <Swiper
          breakpoints={{
            320: {
              slidesPerView: 1,
              spaceBetween: 18,
            },
            768: {
              slidesPerView: 2,
              spaceBetween: 20,
            },
            1080: {
              slidesPerView: 3,
              spaceBetween: 20,
            },
          }}
        >
          {backendItems.map((item) => (
            <SwiperSlide key={item.id}>
              {item.id !== "unknown" ? (
                <Material
                  choosen={choosen}
                  chooseMaterial={chooseMaterial}
                  {...item}
                />
              ) : (
                <AddMaterial
                  choosen={choosen}
                  chooseMaterial={chooseMaterial}
                  {...item}
                />
              )}
            </SwiperSlide>
          ))}
        </Swiper>
      </div>
    </div>
  );
};

export default Materials;
