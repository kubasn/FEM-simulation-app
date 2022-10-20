import React, { useEffect, useState } from "react";
import backendItems from "../../backend";
import Material from "./Material";

import { Swiper, SwiperSlide } from "swiper/react";
import { Navigation, Pagination } from "swiper";

import "../../slider.css";
import "swiper/css";
import "swiper/css/pagination";
import "swiper/css";

import {
  BsFillArrowLeftCircleFill,
  BsFillArrowRightCircleFill,
} from "react-icons/bs";

const Materials: React.FC = () => {
  // const [innerWidth, setInnerWidth] = useState(window.innerWidth);
  // const [slides, setSlides] = useState(3);
  // useEffect(() => {
  //   console.log(window.innerWidth);

  //   const listener = () => {
  //     if (window.innerWidth < 700) {
  //       setSlides(1);
  //     }

  //     if (window.innerWidth > 800) {
  //       setSlides(2);
  //     }
  //     if (window.innerWidth > 1000) {
  //       setSlides(3);
  //     }
  //   };

  //   window.addEventListener("resize", listener);
  // }, []);

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
