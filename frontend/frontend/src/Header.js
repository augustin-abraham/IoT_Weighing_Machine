import React from "react";
import { NavLink } from "react-router-dom";

function Header() {
  return (
    <header>
      <h1>Weigh2GO</h1>

      <nav>
        <NavLink to="/">
          Add Products
        </NavLink>

        {" | "}

        <NavLink to="/billing">
          Billing
        </NavLink>
      </nav>
    </header>
  );
}

export default Header;