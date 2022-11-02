import { combineReducers } from "redux";
import temperaturesReducer from "./temperaturesReducer";
import paramsReducer from "./paramsReducer";

const reducer = combineReducers({
  params: paramsReducer,
  temperatures: temperaturesReducer,
});

export default reducer;
export type RootState = ReturnType<typeof reducer>;
