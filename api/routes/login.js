const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.korttinumero && request.body.pin){
      const korttinumero = request.body.korttinumero;
      const pin = request.body.pin;
        login.checkPassword(korttinumero, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pin,dbResult[0].pin, function(err,compareResult) {
                if(compareResult) {
                  console.log("succes");
                  const token = generateAccessToken({ korttinumero: korttinumero });
                  response.send(token);
                }
                else {
                    console.log("wrong pin");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("card does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("rfid or pin missing");
      response.send(false);
    }
  }
);

function generateAccessToken(korttinumero) {
    dotenv.config();
    return jwt.sign(korttinumero, process.env.MY_TOKEN, { expiresIn: '1800s' });
  }

module.exports=router;