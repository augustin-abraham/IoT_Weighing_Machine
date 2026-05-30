import React, {
  useState,
  useEffect
} from "react";

import ProductTable from "./ProductTable";
import QrScanner from "./QrScanner";

function Billing() {

  const [scannedData,
          setScannedData] = useState("");

  const [productArray,
          setProductArray] = useState([]);

  useEffect(() => {

    if (scannedData === "")
      return;

    fetch(
      "http://localhost:5000/product/" +
      scannedData
    )
      .then((response) =>
        response.json()
      )
      .then((product) => {

        product.qty = 1;

        if (product.shouldWeigh) {

          fetch(
            "http://localhost:5000/get-weight"
          )
            .then((response) =>
              response.json()
            )
            .then((data) => {

              product.qty =
                parseFloat(data.Weight);

              setProductArray(
                (prev) => [...prev, product]
              );
            });

        } else {

          setProductArray(
            (prev) => [...prev, product]
          );

        }

      });

  }, [scannedData]);

  const printBill = () => {

    let total = 0;

    productArray.forEach((item) => {

      total +=
        item.qty *
        item.productPrice;

    });

    alert(
      "Total Amount : ₹" +
      total.toFixed(2)
    );
  };

  return (
    <div>

      <h2>Billing</h2>

      <QrScanner
        setScannedData={
          setScannedData
        }
      />

      {productArray.length > 0 && (
        <ProductTable
          products={productArray}
        />
      )}

      <button onClick={printBill}>
        Print Bill
      </button>

    </div>
  );
}

export default Billing;