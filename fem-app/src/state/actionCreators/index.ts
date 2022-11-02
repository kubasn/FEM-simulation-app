import { ActionType } from "../actionType";
import { Dispatch } from "redux";
import { Action } from "../actions";
import createModule from "../../fem.mjs";

interface SetTemperaturesProps {
  heatTransferCoefficient: number;
  specificHeat: number;
  density: number;
  thermalConductivity: number;
}

interface SetParamsProps {
  heatTransferCoefficient: number;
  specificHeat: number;
  density: number;
  thermalConductivity: number;
}

export const setTemperatures = (material: SetTemperaturesProps) => {
  return (dispatch: Dispatch<Action>) => {
    dispatch({ type: ActionType.SET_TEMPERATURES });
    try {
      createModule().then(async (module: any) => {
        // let alfa = 300;
        // let cp = 700;
        // let ro = 7800;
        // let cond = 25;

        let alfa = material.heatTransferCoefficient;
        let cp = material.specificHeat;
        let ro = material.density;
        let cond = material.thermalConductivity;

        // alfa - heat transfer coefficient // cp - specific heat // ro - density // cond - thermal conductivity
        const b = await module.solve(alfa, cp, ro, cond);

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

export const setParams = (params: SetParamsProps) => {
  return {
    type: ActionType.SET_PARAMS,
    payload: {
      ...params,
    },
  };
};
