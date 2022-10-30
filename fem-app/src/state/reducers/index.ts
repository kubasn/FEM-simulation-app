import { combineReducers } from "redux";
import temperaturesReducer from "./temperaturesReducer";

const reducers = combineReducers({
  temperatures: temperaturesReducer,
});
