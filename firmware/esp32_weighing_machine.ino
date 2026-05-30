 #include <WiFi.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

IPAddress staticIP(192,168,204,164); // Set the desired static IP address
IPAddress gateway(192,168,204,206);    // Set the gateway address
IPAddress subnet(255,255,255,0);

#define mySerial_txd 17
#define mySerial_rxd 16
#define Buf_size 1024
#define BUZZER_PIN 12
#define BUTTON_PIN 4 

WiFiServer server(80);

HardwareSerial mySerial(2);
// Define the pins for the HX711 module
const int DOUT_PIN =26 ;  // Replace with the correct ESP32 pin
const int CLK_PIN = 27;  // Replace with the correct ESP32 pin

// Define the calibration factor for the load cell
const float CALIBRATION_FACTOR = 115.61;

// Define the LCD parameters
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
const int LCD_ADDRESS = 0x3F;

// Initialize the LCD object
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

// Initialize the HX711 object
HX711 scale;

#define DEBUG

static void get_weight(char *buffer)
{
    // Read the weight from the load cell
    float weight = scale.get_units() / 1000.0; 
    lcd.setCursor(0, 0);
    lcd.print("Weight: ");
    lcd.print(weight, 1);
    lcd.print(" kg");
    delay(1000);

    // Beep the buzzer for 2 seconds
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    

    // convert weight to string
    char weight_str[10];
    dtostrf(weight, 4, 2, weight_str);

    // prepare json
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["MSG"] = "SUCCESSFUL";
    jsonDoc["Weight"] = weight_str;

    char json_string[200];
    serializeJson(jsonDoc, json_string);
#ifdef DEBUG
    Serial.print("JSON string: ");
    Serial.println(json_string);
#endif /* DEBUG */
    strcpy(buffer, json_string);
}


void display_weight_on_lcd()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Weight: ");

    // Read the weight from the load cell
    float weight = scale.get_units() / 1000.0; // Convert to kilograms

    // convert weight to string
    char weight_str[10];
    dtostrf(weight, 4, 2, weight_str);

    lcd.setCursor(8, 0);
    lcd.print(weight_str);
    lcd.print(" kg");
}

void setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(115200);
    mySerial.begin(115200, SERIAL_8N1, mySerial_txd, mySerial_rxd);

    WiFi.begin("AUGU", "333444666");
     WiFi.mode(WIFI_STA);
    WiFi.config(staticIP, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    server.begin();

    lcd.begin();
    lcd.backlight();

    // Set the pins for the HX711 module
    scale.begin(DOUT_PIN, CLK_PIN);

    // Set the calibration factor for the load cell
    scale.set_scale(CALIBRATION_FACTOR);

    // tare the scale to zero
    scale.tare();

    Serial.println("Server started");
}

void loop()
{  
  
 
  // Read the weight from the load cell
  float weight = scale.get_units() / 1000.0; // Convert to kilograms

  // Convert to integer and decimal parts
  int kg = int(weight);
  int grams = int((weight - kg) * 1000);

  // Display the weight on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Weight: ");
  lcd.print(kg);
  lcd.print(".");
  if (grams < 10) {
    lcd.print("00");
  } else if (grams < 100) {
    lcd.print("0");
  }
  lcd.print(grams);
  lcd.print(" kg");

  delay(1000);

  static bool buttonState = false;
  static bool lastButtonState = false;

  // Read the state of the push button
  buttonState = digitalRead(BUTTON_PIN);
   Serial.println(buttonState);
  delay(100);

  // If the button state has changed
  if (buttonState != lastButtonState)
 {
    // If the button is pressed down
    if (buttonState == LOW) {
      // Send the weight to the client
      
      if (client)
      {
        Serial.println("New client");
        while (client.connected())
        {
          if (client.available())
          {
            String request = client.readStringUntil('\r');
            Serial.println(request);

            if (request.indexOf("/get-weight") != -1)
            {
              char data[1000];
              memset(data, 0, sizeof(data));
              get_weight(data);

              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: application/json");
              client.println("Connection: close");
              client.println();

              client.println(data);
            }
            else if (request.indexOf("/print-banner") != -1)
            {
              while (client.available())
              {
                String line = client.readStringUntil('\r');
                mySerial.println(line);
                lcd.begin(16,2);
                lcd.clear();
                lcd.setCursor(0, 2);
                lcd.print("Weight: ");
                lcd.print("line");

                
              }

              client.println("HTTP/1.1 204 NO CONTENT");
              client.println("Connection: close");
              client.println();
            }
            else  
            {
              client.println("HTTP/1.1 404 NOT FOUND");
              client.println("Connection: close");
              client.println();
            }
            break;
          }
        }

        client.stop();
        Serial.println("Client disconnected");
      }
 
  
  .catch((err)=>{
    console.log("HERE")
    console.log(err)
  })

//   const url = 'https://jsonplaceholder.typicode.com/todos/1';

// fetch(url)
//   .then(response => response.json())
//   .then(jsonData => console.log(jsonData))
  // res.json({
  
  //     "MSG": "SUCCESSFUL",
  //     "Weight": "0.21"
    
  // })
})
app.put("/product/:id", async (req, res) => {
  const { id } = req.params;
  const { productName, productPrice, stockAvailable, shouldWeigh } = req.body;

  //code to update the product using product id
  const product = await Product.findByIdAndUpdate(id, {
    
    stockAvailable,
    shouldWeigh,
  });
  if (product) {
    res.status(200).json({
      message: "Product updated successfully",
      product: {
        productName,
        productPrice,
        stockAvailable,
        shouldWeigh,
      },
    });
  } else {
    res.status(404).json({ message: "Product not found" });
  }
});
app.listen(5000, () => {
  console.log("Server is running on port 5000");
});
{
  "name": "smart-backend",
  "version": "1.0.0",
  "description": "",
  "main": "index.js",
  "scripts": {
    "dev": "nodemon index.js",
    "test": "echo \"Error: no test specified\" && exit 1",
    "server": "node index.js"
  },
  
  
  "dependencies": {
    "body-parser": "^1.20.2",
    "cors": "^2.8.5",
    "expess": "^0.0.1-security",
    "express": "^4.18.2",
    "mongoose": "^7.0.2",
  }
}

import React, { useEffect, useState } from 'react'
import ProductTable from './ProductTable'
import QrScanner from './QrScanner'

import './QrScanner.css';

const Billing = () => {
    const [scannedData, setScannedData] = useState('')
    const [productArray, setProductArray] = useState([])

    useEffect(() => {
        if (scannedData !== "") {
            fetch('http://localhost:5000/product/' + scannedData)
                .then(response => response.json())
                .then(product => {

                    product.qty = 1
                    if (product.shouldWeigh === true) {
                        console.log(product, "product")

                        fetch('http://localhost:5000/get-weight', {
                            method: 'GET',
                            headers: {
                                'Content-Type': 'application/json'
                            }
                        })
                            .then(response => response.json())
                            .then(data => {
                                console.log(data, "res")
                                let res = data
                                console.log(res.Weight, "res")
                                product.qty = parseFloat(res.Weight)
                                console.log(product.qty, "product qty")
                                if (productArray.length === 0) {
                                    setProductArray([product])
                                else {
                                    productArray.forEach((item, index) => {
                                        console.log(item._id, "item._id")
                                        console.log(product._id, "product._id")

                                        if (item._id === product._id && product.shouldWeigh === true) {
                                            console.log(productArray[index].qty, "productArray[index].qty")
                                            product.qty = parseFloat(productArray[index].qty) + 
                                        
                                    })
                                    let newArray = [...productArray]
                                    newArray.push(product)
                                    setProductArray(newArray)
                                }
                            })
                            .catch(error => console.error(error));

                        // fetch("http://localhost:5000/get-weight").then(resp=>{
                        //     return resp.json()
                        // }).then((res)=>console.log(res)).catch((err)=>{
                        //     console.log(err)
                        // })
                        // xhttp.timeout =10000;

                        // xhttp.onreadystatechange = async function () {
                        //     if (this.readyState == 4 && this.status == 200) {
                        //         console.log("hello")
                        //         console.log(xhttp.responseText, "res")
                        //         let res = await JSON.parse(xhttp.responseText)
                        //         console.log(parseFloat(res.Weight), "res")
                        //         product.qty = parseFloat(res.Weight)
                        //         console.log(product.qty, "product qty")

                        //         if (productArray.length === 0) {
                        //             setProductArray([product])
                        //         }
                        //         else {
                        //             productArray.forEach((item, index) => {
                        
                        //                 console.log(product._id, "product._id")
                        //                 if (item._id === product._id && product.shouldWeigh === true) {
                        //                     console.log(productArray[index].qty, "productArray[index].qty")

                        //                     product.qty = parseFloat(productArray[index].qty) + parseFloat(product.qty)
                        //                     productArray.splice(index, 1)
                        //                 }
                        //             })
                        //             let newArray = [...productArray]
                        //             newArray.push(product)
                        //             setProductArray(newArray)
                        //         }
                        //     }
                        // };
                        // xhttp.open("GET", "http://192.168.137.179/get-weight");
                        // xhttp.send();
                    }
                    else {
                        if (productArray.length === 0) {
                            setProductArray([product])
                        


                                if (item._id === product._id && product.shouldWeigh === false) {
                                    product.qty = productArray[index].qty + 1
                                    productArray.splice(index, 1)
                                }
                            })
                            let newArray = [...productArray]
                            newArray.push(product)
                            setProductArray(newArray)
                        }
                    }
                    // let newArray = [...productArray]
                    // console.log(product)
                    // newArray.push(product)
                    // setProductArray(newArray)
                })
                .catch(error => {
                    
                });

       
    }, [scannedData])

    useEffect(() => {
        if (productArray.length !== 0) {
            console.log(productArray)
        }
    }, [productArray])

    const removeQtyByOne = (id) => {
        productArray.forEach((item, index) => {
            if (item._id === id) {
                if (item.qty > 1) {
                    item.qty = item.qty - 1
                } else {
                    productArray.splice(index, 1)
                }
            }
        })
        setProductArray([...productArray])
    }

const handleClickPrint = ()=>{
    let amt=0;
    productArray.map((item)=>{
        console.log(item.qty)
        const price = item.qty * item.productPrice
        amt+=price
        console.log(amt)
    })
    alert(`The total amout is : ${amt}`)
}
    return (
            
            {productArray.length !== 0 && <ProductTable products={productArray} removeQtyByOne={removeQtyByOne} />}

            <button onClick={handleClickPrint}>
            
        </div>
    )
}

export default Billing
import React from "react";
import { NavLink } from "react-router-dom";
import "./Header.css";
function Header() {
  return (
    <header className="header">
      <h1 className="header__title">Weigh2GO</h1>
      <nav className="header__nav">
        <ul className="header__list">
          <li className="header__item">
            <NavLink className="header__link" to="/">
              Add Products
            </NavLink>

          
          <li className="header__item">
            <NavLink className="header__link" to="/billing">
              Billing
            </NavLink>
          </li>
        </ul>
      </nav>
    </header>
  );
}

export default Header;

  "name": "smart-shopping",
  "version": "0.1.0",
  "private": true,
  "dependencies": {
    "@testing-library/jest-dom": "^5.16.5",
    
    "@testing-library/user-event": "^13.5.0",
    
    "jsqr": "^1.4.0",
    "react": "^18.2.0",
    "react-dom": "^18.2.0",
    "react-icons": "^4.8. 
    ]
  }
}
























  this is the code