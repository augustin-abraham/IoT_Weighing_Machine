import React from "react";

function QrScanner({ setScannedData }) {

  const simulateScan = () => {

    const sampleProductId =
      "64b123456789abcd12345678";

    setScannedData(sampleProductId);
  };

  return (
    <div>

      <button onClick={simulateScan}>
        Scan Product
      </button>

    </div>
  );
}

export default QrScanner;