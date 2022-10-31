import { ActionType } from "../actionType";

export interface GetTemperaturesAction {
  type: ActionType.GET_TEMPERATURES;
}

export interface SetTemperaturesAction {
  type: ActionType.SET_TEMPERATURES;
}

export interface SetTemperaturesComplateAction {
  type: ActionType.SET_TEMPERATURES_COMPLATE;
  // payload: {
  //   [iterationId: number]: number[];
  // };
  payload: number[][];
}

export interface SetTemperaturesErrorAction {
  type: ActionType.SET_TEMPERATURES_ERROR;
  payload: string;
}

export type Action =
  | GetTemperaturesAction
  | SetTemperaturesAction
  | SetTemperaturesComplateAction
  | SetTemperaturesErrorAction;
