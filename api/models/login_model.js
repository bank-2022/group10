const db = require('../database');

const login={
  checkPassword: function(korttinumero, callback) {
      return db.query('SELECT pin FROM kortti WHERE korttinumero = ?',[korttinumero], callback); 
    },

  checkLocked: function(korttinumero, callback) {
      return db.query('SELECT locked FROM kortti WHERE korttinumero = ?',[korttinumero], callback); 
    },
  lockCard: function(korttinumero, callback) {
      return db.query('UPDATE kortti SET locked = "TRUE" WHERE korttinumero = ?',[korttinumero], callback); 
    },
  checkTries: function(korttinumero, callback) {
      return db.query('SELECT login_tries FROM kortti WHERE korttinumero = ?',[korttinumero], callback); 
    },
  addTries: function(dbTries, korttinumero, callback) {
      return db.query('UPDATE kortti SET login_tries = ? WHERE korttinumero = ?',[dbTries, korttinumero], callback); 
    }
};
          
module.exports = login;