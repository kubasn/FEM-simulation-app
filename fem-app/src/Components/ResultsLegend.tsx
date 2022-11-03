import React from "react";
import legend from "../helpers/legend";

interface ResultsLegendProps {
  data: number[];
  min: number;
  max: number;
}

const ResultsLegend: React.FC<ResultsLegendProps> = ({ data, min, max }) => {
  const result = legend(data, min, max);
  return (
    <div>
      <p>Legend</p>

      {result.map((item, key) => {
        return (
          <div style={{ display: "flex", alignItems: "center" }}>
            <div
              style={{
                width: "10px",
                height: "10px",
                backgroundColor: `rgb(${item.r}, ${item.g}, ${item.b})`,
                marginRight: "5px",
              }}
            ></div>
            <span>{item.val} &#8451;</span>
          </div>
        );
      })}
    </div>
  );
};

export default ResultsLegend;
