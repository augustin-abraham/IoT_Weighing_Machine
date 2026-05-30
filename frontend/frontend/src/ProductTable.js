import React from "react";

function ProductTable({ products }) {

  const getTotal = () => {
    return products.reduce(
      (sum, item) =>
        sum + item.qty * item.productPrice,
      0
    );
  };

  return (
    <div>

      <table border="1">

        <thead>
          <tr>
            <th>Product</th>
            <th>Qty</th>
            <th>Price</th>
            <th>Total</th>
          </tr>
        </thead>

        <tbody>
          {products.map((item) => (

            <tr key={item._id}>
              <td>{item.productName}</td>
              <td>{item.qty}</td>
              <td>{item.productPrice}</td>
              <td>
                {(item.qty * item.productPrice).toFixed(2)}
              </td>
            </tr>

          ))}
        </tbody>

      </table>

      <h3>
        Grand Total : ₹{getTotal().toFixed(2)}
      </h3>

    </div>
  );
}

export default ProductTable;