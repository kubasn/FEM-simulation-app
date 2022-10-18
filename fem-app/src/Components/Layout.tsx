import React from "react";

interface LayoutProps {
  header: React.ReactNode;
  menu: React.ReactNode;
  materials: React.ReactNode;
}

const Layout: React.FC<LayoutProps> = ({ header, menu, materials }) => {
  return (
    <div>
      {header}
      {menu}
      {materials}
    </div>
  );
};

export default Layout;
