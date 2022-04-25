const db = require('../database');

const tilitapahtumat = {
  getById: function(id, callback) {
    return db.query('select date_format (paivays,"%d-%m-%Y %h:%i:%s") as "paivays", tapahtuma, summa from tilitapahtumat where id_tili=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tilitapahtumat', callback);
  },
  get: function(id, ttSivu, rivit, callback) {
    ttSivu = (ttSivu - 1) * 10;
    rivit = parseInt(rivit);
    return db.query('select date_format (paivays,"%d-%m-%Y %h:%i:%s") as "paivays", tapahtuma, summa from tilitapahtumat where id_tili=? order by id_tilitapahtumat desc LIMIT ?, ?'
    ,[id, ttSivu, rivit], callback);
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
