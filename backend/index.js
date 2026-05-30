const express = require("express");
const mongoose = require("mongoose");
const cors = require("cors");

const Product = require("./productModel");

const app = express();

app.use(express.json());
app.use(cors());

mongoose.connect(
  "YOUR_MONGODB_CONNECTION_STRING",
  {
    useNewUrlParser: true,
    useUnifiedTopology: true
  }
)
.then(() => {
  console.log("MongoDB Connected");
})
.catch((err) => {
  console.log(err);
});

// Get product details by QR code/product ID
app.get("/product/:id", async (req, res) => {
  try {
    const { id } = req.params;

    const product = await Product.findById(id);

    if (product) {
      res.status(200).json(product);
    } else {
      res.status(404).json({
        message: "Product not found"
      });
    }
  } catch (err) {
    res.status(500).json({
      message: err.message
    });
  }
});

// Add product
app.post("/product", async (req, res) => {
  try {
    const {
      productName,
      productPrice,
      stockAvailable,
      shouldWeigh
    } = req.body;

    const product = await Product.create({
      productName,
      productPrice,
      stockAvailable,
      shouldWeigh
    });

    res.status(201).json(product);

  } catch (err) {
    res.status(500).json({
      message: err.message
    });
  }
});

// Update product
app.put("/product/:id", async (req, res) => {
  try {

    const { id } = req.params;

    const {
      productName,
      productPrice,
      stockAvailable,
      shouldWeigh
    } = req.body;

    const product = await Product.findByIdAndUpdate(
      id,
      {
        productName,
        productPrice,
        stockAvailable,
        shouldWeigh
      },
      {
        new: true
      }
    );

    if (product) {
      res.status(200).json({
        message: "Product updated successfully",
        product
      });
    } else {
      res.status(404).json({
        message: "Product not found"
      });
    }

  } catch (err) {
    res.status(500).json({
      message: err.message
    });
  }
});

// Delete product
app.delete("/product/:id", async (req, res) => {

  try {

    const { id } = req.params;

    const product = await Product.findByIdAndDelete(id);

    if (product) {
      res.status(200).json({
        message: "Product deleted successfully"
      });
    } else {
      res.status(404).json({
        message: "Product not found"
      });
    }

  } catch (err) {
    res.status(500).json({
      message: err.message
    });
  }
});

// ESP32 Weight Endpoint
app.get("/get-weight", async (req, res) => {

  // In actual project this endpoint
  // fetches weight from ESP32

  res.json({
    MSG: "SUCCESSFUL",
    Weight: "0.21"
  });

});

app.listen(5000, () => {
  console.log("Server is running on port 5000");
});