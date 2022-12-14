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
      specificHeat: 600,
      density: 19.3,
      thermalConductivity: 314,
    },
  },
  {
    id: "glass",
    name: "GLASS",
    img: "./images/glass.png",
    // img: require("../../images/steel.png"),
    properties: {
      heatTransferCoefficient: 50,
      specificHeat: 543,
      density: 2500,
      thermalConductivity: 2.5,
    },
  },
  {
    id: "unknown",
    name: "Define material",
    img: "./images/unknown.png",
    // img: require("../../images/steel.png"),
    properties: {
      heatTransferCoefficient: 0,
      specificHeat: 0,
      density: 0,
      thermalConductivity: 0,
    },
  },
];

export default backendItems;

export const programParameters = {
  initialTemperature: 30,
  simulationTime: 500,
  simulationTimeStep: 50,
  timeStep: 1,
  ambientTemperature: 1200,
  size: {
    h: 0.1,
    b: 0.1,
  },
};
