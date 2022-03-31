const db = require('../database');

const tilitapahtumat = {
  getById: function(id, callback) {
    return db.query('select * from tilitapahtumat where id_tilinro=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tilitapahtumat', callback);
  },
  add: function(tilitapahtumat, callback) {
    return db.query(
      'insert into tilitapahtumat (kortinnumero,pvmjaklo,tapahtumat,summa) values(?,?,?,?)',
      [tilitapahtumat.kortinnumero, tilitapahtumat.pvmjaklo, tilitapahtumat.tapahtumat, tilitapahtumat.summa],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from tilitapahtumat where id_tilinro=?', [id], callback);
  },
  update: function(id, tilitapahtumat, callback) {
    return db.query(
      'update tilitapahtumat set kortinnumero=?,pvmjaklo=?, tapahtumat=?, summa=? where id_asiakas=?',
      [tilitapahtumat.kortinnumero, tilitapahtumat.pvmjaklo, tilitapahtumat.tapahtumat,tilitapahtumat.summa, id],
      callback
    );
  }
};
module.exports = tilitapahtumat;