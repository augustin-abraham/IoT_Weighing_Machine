const mongoose = require("mongoose");

const productSchema = new mongoose.Schema({

  productName: {
    type: String,
    required: true
  },

  productPrice: {
    type: Number,
    required: true
  },

  stockAvailable: {
    type: Number,
    required: true
  },

  shouldWeigh: {
    type: Boolean,
    default: false
  }

});

module.exports = mongoose.model(
  "Product",
  productSchema
);