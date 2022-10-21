import React, { useState } from "react";
import { AiOutlineInfoCircle } from "react-icons/ai";

import InfoPanel from "./InfoPanel";

const Header: React.FC = () => {
  const [showInfo, setShowInfo] = useState(false);

  const closePanel = () => {
    setShowInfo(false);
  };

  return (
    <div className="header">
      <div className="header__title">
        <h1>FEM Simulation Application</h1>
      </div>
      {!showInfo ? (
        <AiOutlineInfoCircle
          onClick={() => setShowInfo(true)}
          className="header__button"
        />
      ) : (
        <InfoPanel closePanel={closePanel} />
      )}
    </div>
  );
};

export default Header;
