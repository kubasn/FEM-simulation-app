import React, { useState } from "react";
import { HiPencil } from "react-icons/hi";

interface InputProps {
  clickHandle: () => void;
  property: Number;
  label: String;
}

const Input: React.FC<InputProps> = ({ clickHandle, property, label }) => {
  const [showInput, setShowInput] = useState(false);
  const [value, setValue] = useState(property);
  const onClickHandle = () => {
    setShowInput(!showInput);
    clickHandle();
  };
  const onChange = (e: string) => {
    const val = parseFloat(e);
    if (!isNaN(val)) setValue(val);
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
