import { tempToColor } from "temp-color";

const legend = (data: number[], min: number, max: number) => {
  let newArray: { val: number; r: number; g: number; b: number }[] = [];

  //deduplicate values
  let uniqueArray = data.filter((element, index) => {
    return data.indexOf(element) === index;
  });

  uniqueArray.map((val) => {
    const { r, g, b } = tempToColor(val, min, max, "half");

    newArray.push({
      val,
      r,
      g,
      b,
    });
  });

  return newArray;
};

export default legend;
