import React, { useState, useEffect } from "react";
import backendItems from "../backend";
import { useActions } from "../hooks/use-actions";
import { useTypedSelector } from "../hooks/use-typed-selector";

interface ResultProps {
  choosen: string;
}

const Results: React.FC<ResultProps> = ({ choosen }) => {
  //   const [results, setResults] = useState<number[][]>([]);
  const data = useTypedSelector((state) => state.temperatures);

  const { setTemperatures } = useActions();
  useEffect(() => {
    const item = backendItems.filter((item) => choosen === item.id)[0];
    console.log(item);
    setTemperatures(item);
  }, []);

  useEffect(() => {
    console.log(data);
  }, [data.loading]);

  return (
    <div>
      {data.data.length === 0 ? "true" : "false"}
      {/* <p>{data && data}</p> dawd */}
      awd
    </div>
  );
};

export default Results;
