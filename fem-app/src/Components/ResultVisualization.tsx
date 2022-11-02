import React, { useRef, useEffect, useState } from "react";
import { tempToColor } from "temp-color";

interface ResultVisualization {
  data: number[][];
}

const ResultVisualization: React.FC<ResultVisualization> = ({ data }) => {
  const canvasRef: any = useRef();
  const [timeStep, setTimeStep] = useState<number>(0);

  useEffect(() => {
    if (canvasRef.current) {
      console.log(data[timeStep]);
      const ctx = canvasRef.current.getContext("2d");

      for (let i = 1; i <= 4; i++) {
        for (let j = 1; j <= 4; j++) {
          //console.log(data[timeStep][i * j - 1]);
          const { r, g, b } = tempToColor(
            data[timeStep][i * j - 1],
            100,
            1000,
            "half"
          );
          ctx.fillStyle = `rgb(${r}, ${g}, 0)`;
          ctx.fillRect(j * 25, i * 25, 25, 25);
        }
      }
      console.log(ctx);
    }
  }, [timeStep]);

  const handleChange = (e: React.ChangeEvent<HTMLSelectElement>) => {
    // console.log(e.target.value);
    setTimeStep(parseInt(e.target.value));
  };

  return (
    <div
      style={{
        display: "flex",
        flex: 1,
        flexDirection: "column",
        alignItems: "center",
        justifyContent: "center",
      }}
    >
      <h3>Choose time:</h3>
      <select name="0" id="cars" onChange={handleChange}>
        <option value="0">50</option>
        <option value="1">100</option>
        <option value="2">150</option>
        <option value="3">200</option>
        <option value="4">250</option>
        <option value="5">300</option>
        <option value="6">350</option>
        <option value="7">400</option>
        <option value="8">450</option>
        <option value="9">500</option>
      </select>
      <canvas style={{ margin: "auto" }} ref={canvasRef} />
    </div>
  );
};

export default ResultVisualization;
