import React, { useEffect, useState } from "react";
import backendItems from "../../backend";
import Material from "./Material";

import { Swiper, SwiperSlide } from "swiper/react";

import "../../slider.css";
import "swiper/css";
import "swiper/css/pagination";
import "swiper/css";

const Materials: React.FC = () => {
  const [choosen, setChoosen] = useState(false);
  return (
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
            <Material {...item} />
          </SwiperSlide>
        ))}
      </Swiper>
    </div>
  );
};

export default Materials;
