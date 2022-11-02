import { ActionType } from "../actionType";

export interface SetParamsAction {
  type: ActionType.SET_PARAMS;
  payload: {
    heatTransferCoefficient: number;
    specificHeat: number;
    density: number;
    thermalConductivity: number;
  };
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
  | SetParamsAction
  | SetTemperaturesAction
  | SetTemperaturesComplateAction
  | SetTemperaturesErrorAction;
