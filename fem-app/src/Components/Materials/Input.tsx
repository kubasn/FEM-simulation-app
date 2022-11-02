import React, { useState } from "react";
import { HiPencil } from "react-icons/hi";

interface InputProps {
  // clickHandle: () => void;
  changeHandler: (id: string, value: number) => void;
  property: number;
  label: String;
  id: string;
}

const Input: React.FC<InputProps> = ({
  changeHandler,
  property,
  label,
  id,
}) => {
  const [showInput, setShowInput] = useState(false);
  const [value, setValue] = useState(property);
  const onClickHandle = () => {
    setShowInput(!showInput);
    // clickHandle();
  };
  const onChange = (e: string) => {
    const val = parseFloat(e);
    if (!isNaN(val)) setValue(val);
    changeHandler(id, val);
  };

  return (
    <div className="input">
      {label}
      <HiPencil
        onClick={() => onClickHandle()}
        className="input__icon active"
      />

      {showInput ? (
        <input
          onChange={(e) => onChange(e.target.value)}
          className="input__element"
        ></input>
      ) : (
        `${value}`
      )}
    </div>
  );
};

export default Input;
