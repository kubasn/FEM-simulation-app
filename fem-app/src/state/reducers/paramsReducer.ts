import { Action } from "../actions";
import { ActionType } from "../actionType";
import produce from "immer";

interface paramsState {
  data: {
    heatTransferCoefficient: number;
    density: number;
    specificHeat: number;
    thermalConductivity: number;
  };
}

const initialState: paramsState = {
  data: {
    heatTransferCoefficient: 0,
    density: 0,
    specificHeat: 0,
    thermalConductivity: 0,
  },
};

const reducer = produce((state: paramsState = initialState, action: Action) => {
  switch (action.type) {
    //ok
    case ActionType.SET_PARAMS:
      state.data = action.payload;
      return state;
    default:
      return state;
  }
}, initialState);

export default reducer;
