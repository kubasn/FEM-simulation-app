import React, { useRef, useEffect, useState } from "react";
import { tempToColor } from "temp-color";
import { minMaxGlobal } from "../helpers/minMax";
import ResultsLegend from "./ResultsLegend";

interface ResultVisualization {
  data: number[][];
}

const ResultVisualization: React.FC<ResultVisualization> = ({ data }) => {
  const canvasRef: any = useRef();
  const [timeStep, setTimeStep] = useState<number>(0);
  const { min, max } = minMaxGlobal(data);

  useEffect(() => {
    if (canvasRef.current) {
      console.log(data[timeStep]);
      const ctx = canvasRef.current.getContext("2d");

      for (let i = 1; i <= 4; i++) {
        for (let j = 1; j <= 4; j++) {
          //console.log(data[timeStep][i * j - 1]);
          const { r, g, b } = tempToColor(
            data[timeStep][i * j - 1],
            min,
            max,
            "half"
          );
          ctx.fillStyle = `rgb(${r}, ${g}, 0)`;
          ctx.fillRect(j * 50, i * 25, 50, 25);
        }
      }
      console.log(ctx);
    }
  }, [timeStep]);

  const handleChange = (e: React.ChangeEvent<HTMLSelectElement>) => {
    setTimeStep(parseInt(e.target.value));
  };

  return (
    <div
      style={{
        display: "flex",
        alignItems: "center",
        justifyContent: "center",
        gap: "50px",
      }}
      className="resultVisualization"
    >
      <div style={{ display: "flex", gap: "30px", alignItems: "center" }}>
        <canvas style={{ width: "100px", height: "200px" }} ref={canvasRef} />
        <ResultsLegend min={min} max={max} data={data[timeStep]} />
      </div>
      <div style={{ display: "flex", alignItems: "center", gap: "30px" }}>
        <div style={{ margin: "auto" }}>
          <h3 style={{ marginTop: 0, marginBottom: "5px" }}>Choose time:</h3>
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
        </div>
      </div>
    </div>
  );
};

export default ResultVisualization;
