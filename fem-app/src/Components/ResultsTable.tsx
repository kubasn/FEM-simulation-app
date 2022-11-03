import React from "react";
import { programParameters } from "../backend";
import minMax from "../helpers/minMax";
interface ResultsTable {
  data: number[][];
}

const ResultsTable: React.FC<ResultsTable> = ({ data }) => {
  const result = minMax(data);
  let time = 0;
  return (
    <div className="resultTable">
      <h2>Results of simulation</h2>
      <h3>Min/Max material temperature after time [s] </h3>
      <table className="table">
        <tr>
          <th>After [s]</th>
          <th>Min [&#8451;]</th>
          <th>Max [&#8451;]</th>
        </tr>
        {result.minTab.map((item, key) => {
          time += programParameters.simulationTimeStep;
          return (
            <tr key={key}>
              <td>{time}</td>
              <td>{result.minTab[key]}</td>
              <td>{result.maxTab[key]}</td>
            </tr>
          );
        })}
      </table>
    </div>
  );
};

export default ResultsTable;
