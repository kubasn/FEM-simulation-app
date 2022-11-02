import React from "react";
import backendItems from "../../backend";
import Material from "./Material";

import { Swiper, SwiperSlide } from "swiper/react";

import "../../slider.css";
import "swiper/css";
import "swiper/css/pagination";
import "swiper/css";
import AddMaterial from "./AddMaterial";

interface MaterialsProps {
  choosen: string;
  setChoosen: (id: string) => void;
}

const Materials: React.FC<MaterialsProps> = ({ setChoosen, choosen }) => {
  const chooseMaterial = (id: string) => {
    console.log(id);
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
              {item.id !== "unkown" ? (
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
