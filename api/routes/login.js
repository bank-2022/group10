const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');
const kortti = require('../models/kortti_model');
const cardLocked = "cardLocked";

let tries = 0;

router.get('/logintries/:korttinumero',
function(request, response) {
  if (request.params.korttinumero) {
    login.getLoginTries(request.params.korttinumero, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult[0].login_tries);
      }
    });
  }
}
);

router.post('/', 

  function(request, response) {
    if(request.body.korttinumero && request.body.pin){
      const korttinumero = request.body.korttinumero;
      const pin = request.body.pin;

      login.checkLocked(korttinumero,function(dbError, dbResult){
        if(dbError){
          response.json(dbError);
        }
        else if (dbResult.length > 0) {                                           // tsekataan onko kortti olemassa 1
          
        let locked = dbResult[0].locked;
        console.log("1");
        //console.log(locked);
            if (dbResult[0].locked == "FALSE"){
            console.log("TÄÄLLÄ: kortti ei ole lukossa");
            

            login.checkPassword(korttinumero, function(dbError, dbResult) {
              if(dbError){
                response.json(dbError);
              }
              else{
                if (dbResult.length > 0) {                                            // tsekataan onko kortti olemassa 2
                  bcrypt.compare(pin,dbResult[0].pin, function(err,compareResult) {
                    if(compareResult) {                         
                      console.log("succes");
                      let dbTries = 0;
                      login.addTries(dbTries, korttinumero, function(dbResult){});
                      const token = generateAccessToken({ korttinumero: korttinumero });
                      response.send(token);
                    }
                    else {
                        console.log("wrong pin");
                        login.checkTries(korttinumero, function(dbError, triesFromDB){
                          if(dbError){
                            response.json(dbError);
                          }else{
                          let dbTries = triesFromDB[0].login_tries;
                          dbTries=dbTries+1;
                          if (dbTries < 3){
                          console.log("yrityksiä käytetty ", dbTries);
                          login.addTries(dbTries, korttinumero, function(dbResult){});
                          }else if(dbTries == 3){
                            login.lockCard(korttinumero, function(dbError, dbResult){});
                          console.log("card locked");
                          }
                        }
                        });
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
              console.log("card is locked");
              response.send(cardLocked);
            }
        }else{
          console.log("card does not exists");
          response.send(false);
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