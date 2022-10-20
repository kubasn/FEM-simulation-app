import React from "react";

interface LayoutProps {
  header: React.ReactNode;
  menu: React.ReactNode;
}

const Layout: React.FC<LayoutProps> = ({ header, menu }) => {
  return (
    <div>
      {header}
      {menu}
    </div>
  );
};

export default Layout;
