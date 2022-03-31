const db = require('../database');

const tili = {
  getById: function(id, callback) {
    return db.query('select * from tili where id_tili=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tili', callback);
  },
  add: function(tili, callback) {
    return db.query(
      'insert into tili (id_tili,tilinumero,saldo) values(?,?,?)',
      [tili.id_tili, tili.tilinumero, tili.saldo],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from tili where id_tili=?', [id], callback);
  },
  update: function(id, tili, callback) {
    return db.query(
      'update tili set id_tili=?,tilinumero=?, saldo=? where id_tili=?',
      [tili.id_tili, tili.tilinumero, tili.saldo, tili.id_tili, id],
      callback
    );
  }
};
module.exports = tili;