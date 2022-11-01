import React, { useEffect, useState } from "react";
import backendItems from "../../backend";
import Material from "./Material";

import { Swiper, SwiperSlide } from "swiper/react";

import "../../slider.css";
import "swiper/css";
import "swiper/css/pagination";
import "swiper/css";
import AddMaterial from "./AddMaterial";

import { useActions } from "../../hooks/use-actions";

const Materials: React.FC = () => {
  const [choosen, setChoosen] = useState<string>("");
  const { setTemperatures } = useActions();

  const chooseMaterial = (id: string) => {
    console.log(id);
    setChoosen(id);
  };

  const clickHandle = (e: React.MouseEvent<HTMLButtonElement>) => {
    e.preventDefault();
    console.log("ello");
    const item = backendItems.filter((item) => choosen === item.id)[0];
    //console.log(item);
    setTemperatures(item);
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
      <button onClick={clickHandle} className="menu__button">
        START
      </button>
    </div>
  );
};

export default Materials;
