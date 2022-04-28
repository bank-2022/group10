const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const kortti = {
  getById: function(id, callback) {
    return db.query('select * from kortti where id_kortti=?', [id], callback);
  },
 
  getAll: function(callback) {
    return db.query('select * from kortti', callback);
  },
  add: function(kortti, callback) {
    bcrypt.hash(kortti.pin, saltRounds, function(err, hash) {
    return db.query('insert into kortti (korttinumero,pin,id_tili,id_asiakas) values(?,?,?,?)',
      [kortti.korttinumero, hash, kortti.id_tili, kortti.id_asiakas], callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from kortti where id_kortti=?', [id], callback);
  },
  update: function(id, kortti, callback) {
    bcrypt.hash(kortti.pin, saltRounds, function(err, hash) {
    return db.query('update kortti set korttinumero=?,pin=?, id_tili=?, id_asiakas=? where id_kortti=?',
      [kortti.korttinumero, hash, kortti.id_tili, kortti.id_asiakas, id], callback);
    });
  }
};
module.exports = kortti;