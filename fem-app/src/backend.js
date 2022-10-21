//specificHeat - ciepło właściwe
//density - gestosc
//thermal conductivity - współczynnik przewodzenia ciepła

const backendItems = [
  {
    id: "steel",
    name: "STEEL",
    img: "./images/steel.png",
    // img: require("../../images/steel.png"),
    properties: {
      heatTransferCoefficient: 300,
      specificHeat: 700,
      density: 7800,
      thermalConductivity: 25,
    },
  },
  {
    id: "gold",
    name: "GOLD",
    img: "./images/gold.png",
    // img: require("../../images/steel.png"),
    properties: {
      heatTransferCoefficient: 233,
      specificHeat: 543,
      density: 11000,
      thermalConductivity: 20,
    },
  },
  {
    id: "glass",
    name: "GLASS",
    img: "./images/glass.png",
    // img: require("../../images/steel.png"),
    properties: {
      heatTransferCoefficient: 233,
      specificHeat: 543,
      density: 11000,
      thermalConductivity: 20,
    },
  },
  {
    id: "unkown",
    name: "Define material",
    img: "./images/unknown.png",
    // img: require("../../images/steel.png"),
    properties: {
      heatTransferCoefficient: 233,
      specificHeat: 543,
      density: 11000,
      thermalConductivity: 20,
    },
  },
];

export default backendItems;

export const programParameters = {
  initialTemperature: 30,
  simulationTime: 30,
  timeStep: 1,
  ambientTemperature: 1200,
  size: {
    h: 0.1,
    b: 0.1,
  },
};
