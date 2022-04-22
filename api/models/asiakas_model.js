const db = require('../database');

const asiakas = {
  getById: function(id, callback) {
    return db.query('select * from asiakas where id_asiakas=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from asiakas', callback);
  },
  add: function(asiakas, callback) {
    return db.query(
      'insert into asiakas (nimi,osoite,puhelinnumero) values(?,?,?)',
      [asiakas.nimi, asiakas.osoite, asiakas.puhelinnumero],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from asiakas where id_asiakas=?', [id], callback);
  },
  update: function(id, asiakas, callback) {
    return db.query(
      'update asiakas set nimi=?,osoite=?, puhelinnumero=? where id_asiakas=?',
      [asiakas.nimi, asiakas.osoite, asiakas.puhelinnumero, id],
      callback
    );
  },
  getAccount:function(korttinumero, callback){
    return db.query('select nimi, saldo, kortti.id_kortti, kortti.id_tili from asiakas inner join asiakastili on asiakas.id_asiakas=asiakastili.id_asiakas inner join tili on tili.id_tili=asiakastili.id_tili  inner join kortti on asiakas.id_asiakas=kortti.id_asiakas where kortti.korttinumero=?',
    [korttinumero], callback);
  }
};
module.exports = asiakas;