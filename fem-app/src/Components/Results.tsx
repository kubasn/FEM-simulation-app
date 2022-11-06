import React, { useState, useEffect } from "react";
import { useActions } from "../hooks/use-actions";
import { useTypedSelector } from "../hooks/use-typed-selector";
import ResultsTable from "./ResultsTable";
import ResultVisualization from "./ResultVisualization";

interface ResultProps {
  choosen: string;
}

const Results: React.FC<ResultProps> = ({ choosen }) => {
  //   const [results, setResults] = useState<number[][]>([]);
  const data = useTypedSelector((state) => state.temperatures.data);
  const params = useTypedSelector((state) => state.params.data);

  const { setTemperatures } = useActions();
  useEffect(() => {
    console.log(params);
    setTemperatures(params);
  }, [choosen]);

  return (
    <div style={{ paddingBottom: "50px" }}>
      {data.length === 0 ? (
        "loading..."
      ) : (
        <>
          <ResultsTable data={data} />
          <ResultVisualization data={data} />
        </>
      )}
    </div>
  );
};

export default Results;
