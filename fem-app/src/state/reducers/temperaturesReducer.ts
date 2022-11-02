import { Action } from "../actions";
import { ActionType } from "../actionType";
import produce from "immer";
interface temperaturesState {
  loading: boolean;
  error: string | null;
  data: number[][];
}

const initialState: temperaturesState = {
  loading: false,
  error: null,
  data: [],
};

const reducer = produce(
  (state: temperaturesState = initialState, action: Action) => {
    switch (action.type) {
      //ok
      case ActionType.SET_TEMPERATURES:
        state.loading = true;
        state.error = null;
        return state;

      case ActionType.SET_TEMPERATURES_COMPLATE:
        state.loading = false;
        state.error = null;
        state.data = action.payload;
        return state;
      case ActionType.SET_TEMPERATURES_ERROR:
        state.loading = false;
        state.error = action.payload;
        return state;
      default:
        return state;
    }
  },
  initialState
);

export default reducer;
