const db = require('../database');

const login={
  checkPassword: function(korttinumero, callback) {
      return db.query('SELECT pin FROM kortti WHERE korttinumero = ?',[korttinumero], callback); 
    },

  checkLocked: function(korttinumero, callback) {
      return db.query('SELECT locked FROM kortti WHERE korttinumero = ?',[korttinumero], callback); 
    }
};
          
module.exports = login;