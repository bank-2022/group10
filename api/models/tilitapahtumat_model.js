const db = require('../database');

const tilitapahtumat = {
  getById: function(id, callback) {
    return db.query('select * from tilitapahtumat where id_tilitapahtumat=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tilitapahtumat', callback);
  },
  add: function(tilitapahtumat, callback) {
    return db.query(
      'insert into tilitapahtumat (paivays,tapahtuma,summa,id_kortti,id_tili,) values(?,?,?,?,?)',
      [tilitapahtumat.paivays, tilitapahtumat.tapahtuma, tilitapahtumat.summa,tilitapahtumat.id_kortti,tilitapahtumat.id_tili],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from tilitapahtumat where id_tilitapahtumat=?', [id], callback);
  },
  update: function(id, tilitapahtumat, callback) {
    return db.query(
      'update tilitapahtumat set payvays=?, tapahtuma=?, summa=?,id_kortti=?,id_tili where id_asiakas=?',
      [tilitapahtumat.paivays, tilitapahtumat.tapahtuma,tilitapahtumat.summa,id_kortti,id_tili],
      callback
    );
  }
};
module.exports = tilitapahtumat;