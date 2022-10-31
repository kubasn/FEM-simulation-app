import { combineReducers } from "redux";
import temperaturesReducer from "./temperaturesReducer";

const reducer = combineReducers({
  temperatures: temperaturesReducer,
});

export default reducer;
export type RootState = ReturnType<typeof reducer>;
