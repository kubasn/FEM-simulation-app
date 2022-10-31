import { ActionType } from "../actionType";
import { Dispatch } from "redux";
import { Action } from "../actions";
import createModule from "../../fem.mjs";

export const setTemperatures = () => {
  return (dispatch: Dispatch<Action>) => {
    try {
      createModule().then((module: any) => {
        let alfa = 300;
        let cp = 700;
        let ro = 7800;
        let cond = 25;
        // alfa - heat transfer coefficient // cp - specific heat // ro - density // cond - thermal conductivity
        const b = module.solve(alfa, cp, ro, cond);

        let tab: any[] = [];
        let newTab: number[] = [];
        let j = 0;
        for (let i = 0; i < b.size(); i++) {
          console.log(b.get(i));
          newTab.push(b.get(i));

          if ((i + 1) % 16 == 0) {
            tab.push(newTab);

            newTab = [];
            j++;
          }
        }
        console.log(tab);
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
