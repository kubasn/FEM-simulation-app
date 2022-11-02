import { ActionType } from "../actionType";
import { Dispatch } from "redux";
import { Action } from "../actions";
import createModule from "../../fem.mjs";

interface SetTemperaturesProps {
  id: string;
  name: string;
  img: string;
  properties: {
    heatTransferCoefficient: number;
    specificHeat: number;
    density: number;
    thermalConductivity: number;
  };
}

export const setTemperatures = (material: SetTemperaturesProps) => {
  return (dispatch: Dispatch<Action>) => {
    console.log(material);

    dispatch({ type: ActionType.SET_TEMPERATURES });
    try {
      createModule().then(async (module: any) => {
        // let alfa = 300;
        // let cp = 700;
        // let ro = 7800;
        // let cond = 25;

        let alfa = material.properties.heatTransferCoefficient;
        let cp = material.properties.specificHeat;
        let ro = material.properties.density;
        let cond = material.properties.thermalConductivity;

        // alfa - heat transfer coefficient // cp - specific heat // ro - density // cond - thermal conductivity
        const b = await module.solve(alfa, cp, ro, cond);
        console.log(alfa, cp, ro, cond);
        console.log(b.get(1));
        let tab: any[] = [];
        let newTab: number[] = [];
        let j = 0;
        for (let i = 0; i < b.size(); i++) {
          newTab.push(b.get(i));

          if ((i + 1) % 16 == 0) {
            tab.push(newTab);

            newTab = [];
            j++;
          }
        }
        dispatch({ type: ActionType.SET_TEMPERATURES_COMPLATE, payload: tab });
      });
    } catch (err) {
      if (err instanceof Error)
        dispatch({
          type: ActionType.SET_TEMPERATURES_ERROR,
          payload: err.message,
        });
    }
  };
};

export const getTemperatures = () => {};
