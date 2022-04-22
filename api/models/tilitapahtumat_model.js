const db = require('../database');

const tilitapahtumat = {
  getById: function(id, callback) {
    return db.query('select * from tilitapahtumat where id_tili=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tilitapahtumat', callback);
  },
  get10: function(ttSivu, callback) {
    ttSivu = (ttSivu - 1) * 10;
    return db.query('select * from tilitapahtumat LIMIT ?, 10',[ttSivu], callback);
  },
  add: function(tilitapahtumat, callback) {
    return db.query(
      'insert into tilitapahtumat (paivays,tapahtuma,summa,id_kortti,id_tili) values(?,?,?,?,?)',
      [tilitapahtumat.paivays, tilitapahtumat.tapahtuma, tilitapahtumat.summa, tilitapahtumat.id_kortti, tilitapahtumat.id_tili],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from tilitapahtumat where id_tilitapahtumat=?', [id], callback);
  },
  update: function(id, tilitapahtumat, callback) {
    return db.query(
      'update tilitapahtumat set paivays=?, tapahtuma=?, summa=?,id_kortti=?,id_tili=? where id_tilitapahtumat=?',
      [tilitapahtumat.paivays, tilitapahtumat.tapahtuma, tilitapahtumat.summa, tilitapahtumat.id_kortti, tilitapahtumat.id_tili,id],
      callback
    );
  },
  debit: function(data, callback) {
    return db.query('call debit_transfer(?,?,?)',[data.id_kortti, data.id_tili, data.summa], callback);

  }
};
module.exports = tilitapahtumat;
