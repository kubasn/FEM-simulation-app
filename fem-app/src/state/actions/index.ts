import { ActionType } from "../actionType";

export interface GetTemperatures {}

export interface SetTemperaturesAction {
  type: ActionType.SET_TEMPERATURES;
}

export interface SetTemperaturesComplate {
  type: ActionType.SET_TEMPERATURES_COMPLATE;
  payload: Cell[];
}

export interface SetTemperaturesErrorAction {
  type: ActionType.SET_TEMPERATURES_ERROR;
  payload: string;
}
