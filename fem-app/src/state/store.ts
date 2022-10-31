import { applyMiddleware, configureStore } from "@reduxjs/toolkit";
import reducer from "./reducers";
import thunk from "redux-thunk";

export const store = configureStore({
  reducer,
});
