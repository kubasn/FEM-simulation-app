import React, { useState, useEffect } from "react";
import backendItems from "../backend";
import { useActions } from "../hooks/use-actions";
import { useTypedSelector } from "../hooks/use-typed-selector";
import ResultsTable from "./ResultsTable";

interface ResultProps {
  choosen: string;
}

const Results: React.FC<ResultProps> = ({ choosen }) => {
  //   const [results, setResults] = useState<number[][]>([]);
  const data = useTypedSelector((state) => state.temperatures.data);

  const { setTemperatures } = useActions();
  useEffect(() => {
    const item = backendItems.filter((item) => choosen === item.id)[0];
    console.log(item);
    setTemperatures(item);
  }, [choosen]);

  return (
    <div>
      {data.length === 0 ? (
        "loading..."
      ) : (
        <>
          <ResultsTable data={data} />
        </>
      )}
    </div>
  );
};

export default Results;
