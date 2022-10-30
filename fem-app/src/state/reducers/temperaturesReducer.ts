import { Action } from "../actions";
import { ActionType } from "../actionType";

interface temperaturesState {
  loading: boolean;
  error: string | null;
  data: {
    [iterationId: number]: number[];
  };
}

const initialState: temperaturesState = {
  loading: false,
  error: null,
  data: {},
};

const reducer = (state: temperaturesState = initialState, action: Action) => {
  switch (action.type) {
    case ActionType.GET_TEMPERATURES:
      state.error = null;
      return state;

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
};

export default reducer;
